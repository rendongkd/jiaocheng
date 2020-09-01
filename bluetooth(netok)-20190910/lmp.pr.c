/* Process model C form file: lmp.pr.c */
/* Portions of this file copyright 1986-2008 by OPNET Technologies, Inc. */



/* This variable carries the header into the object file */
const char lmp_pr_c [] = "MIL_3_Tfile_Hdr_ 145A 30A modeler 7 5D727BF9 5D727BF9 1 USER-20151017SA Administrator 0 0 none none 0 0 none 0 0 0 0 0 0 0 0 1bcc 1                                                                                                                                                                                                                                                                                                                                                                                            ";
#include <string.h>



/* OPNET system definitions */
#include <opnet.h>



/* Header Block */

/*define symbolic constant*/
#define  instrm_from_low 		0
#define  instrm_from_up 		1
#define  instrm_to_low 			0
#define  instrm_to_up 			1
#define	 Time					100

#define	 back_off				0
#define	 send_frame				1000


#define	 FS						1//frame space
#define	 FS_TIMES				0.00006//frame space times 60 microsecond
#define	 RX_INSTAT 			    0
#define  DATA_RATE				1000000     //bps

/*define macros*/
#define LOW_ARVL 			(op_intrpt_type() == OPC_INTRPT_STRM && op_intrpt_code() == instrm_from_low)
#define UP_ARVL 			(op_intrpt_type() == OPC_INTRPT_STRM && op_intrpt_code() == instrm_from_up)

#define SEND_FRAME 			(op_intrpt_type() == OPC_INTRPT_SELF && op_intrpt_code() == send_frame)
#define TIME_BUFF 			(op_intrpt_type() == OPC_INTRPT_SELF && op_intrpt_code() == Time)

#define	RX_BUSY				((op_intrpt_type()== OPC_INTRPT_STAT) && (op_intrpt_stat () == RX_INSTAT ) && op_stat_local_read (RX_INSTAT) == 1.0)
#define	RX_IDLE				((op_intrpt_type()== OPC_INTRPT_STAT) && (op_intrpt_stat () == RX_INSTAT ) && op_stat_local_read (RX_INSTAT) == 0.0)

/* End of Header Block */

#if !defined (VOSD_NO_FIN)
#undef	BIN
#undef	BOUT
#define	BIN		FIN_LOCAL_FIELD(_op_last_line_passed) = __LINE__ - _op_block_origin;
#define	BOUT	BIN
#define	BINIT	FIN_LOCAL_FIELD(_op_last_line_passed) = 0; _op_block_origin = __LINE__;
#else
#define	BINIT
#endif /* #if !defined (VOSD_NO_FIN) */



/* State variable definitions */
typedef struct
	{
	/* Internal state tracking for FSM */
	FSM_SYS_STATE
	/* State Variables */
	Objid	                  		node_id                                         ;
	int	                    		listen_times                                    ;
	int	                    		channel_busy                                    ;
	List*	                  		time_buffer                                     ;
	double	                 		channel_status_value                            ;
	} lmp_state;

#define node_id                 		op_sv_ptr->node_id
#define listen_times            		op_sv_ptr->listen_times
#define channel_busy            		op_sv_ptr->channel_busy
#define time_buffer             		op_sv_ptr->time_buffer
#define channel_status_value    		op_sv_ptr->channel_status_value

/* These macro definitions will define a local variable called	*/
/* "op_sv_ptr" in each function containing a FIN statement.	*/
/* This variable points to the state variable data structure,	*/
/* and can be used from a C debugger to display their values.	*/
#undef FIN_PREAMBLE_DEC
#undef FIN_PREAMBLE_CODE
#define FIN_PREAMBLE_DEC	lmp_state *op_sv_ptr;
#define FIN_PREAMBLE_CODE	\
		op_sv_ptr = ((lmp_state *)(OP_SIM_CONTEXT_PTR->_op_mod_state_ptr));


/* Function Block */

#if !defined (VOSD_NO_FIN)
enum { _op_block_origin = __LINE__ + 2};
#endif

void op_pk_send2(Packet* pktptr, int stream_num)
	{
	int 		dest,source;
	Packet* 	pk;
	
	FIN(op_pk_send2(pktptr1, stream_num));
	
	node_id = op_topo_parent(op_id_self());
	
	op_ima_obj_attr_get(node_id,"Destination Address",&dest);//get dest frome attributes;
	op_ima_obj_attr_get(node_id,"node_address",&source);

	//create and set MAC packet
	pk=op_pk_create_fmt("spma_mac");
	
	op_pk_nfd_set(pk,"DEST",dest);
	op_pk_nfd_set(pk,"SRC",source);
	op_pk_nfd_set(pk, "DATA", pktptr);  //may fail
	op_pk_nfd_set(pk,"FCS",1);//for the time being meaningless;
	
	op_pk_send(pk, stream_num);
	
//	listen_times = 0;
//	op_intrpt_schedule_self(op_sim_time()+FS_TIMES,FS);

	FOUT;
	}

/* End of Function Block */

/* Undefine optional tracing in FIN/FOUT/FRET */
/* The FSM has its own tracing code and the other */
/* functions should not have any tracing.		  */
#undef FIN_TRACING
#define FIN_TRACING

#undef FOUTRET_TRACING
#define FOUTRET_TRACING

#if defined (__cplusplus)
extern "C" {
#endif
	void lmp (OP_SIM_CONTEXT_ARG_OPT);
	VosT_Obtype _op_lmp_init (int * init_block_ptr);
	void _op_lmp_diag (OP_SIM_CONTEXT_ARG_OPT);
	void _op_lmp_terminate (OP_SIM_CONTEXT_ARG_OPT);
	VosT_Address _op_lmp_alloc (VosT_Obtype, int);
	void _op_lmp_svar (void *, const char *, void **);


#if defined (__cplusplus)
} /* end of 'extern "C"' */
#endif




/* Process model interrupt handling procedure */


void
lmp (OP_SIM_CONTEXT_ARG_OPT)
	{
#if !defined (VOSD_NO_FIN)
	int _op_block_origin = 0;
#endif
	FIN_MT (lmp ());

		{
		/* Temporary Variables */
		/*declare variables*/
		Packet*	pkptr;
		Packet*	pktptr;
		
		int 	dest,source,num=0;
		double	cur_time;
		double	*saved_time_ptr;
		/* End of Temporary Variables */


		FSM_ENTER ("lmp")

		FSM_BLOCK_SWITCH
			{
			/*---------------------------------------------------------*/
			/** state (init) enter executives **/
			FSM_STATE_ENTER_FORCED_NOLABEL (0, "init", "lmp [init enter execs]")
				FSM_PROFILE_SECTION_IN ("lmp [init enter execs]", state0_enter_exec)
				{
				node_id = op_topo_parent(op_id_self());
				
				op_ima_obj_attr_get(node_id,"Destination Address",&dest);//get dest frome attributes;
				op_ima_obj_attr_get(node_id,"node_address",&source);
				
				time_buffer = op_prg_list_create();
				
				channel_status_value = 1.0;
					
				op_intrpt_schedule_self(op_sim_time(), Time); //collect channel status
				}
				FSM_PROFILE_SECTION_OUT (state0_enter_exec)

			/** state (init) exit executives **/
			FSM_STATE_EXIT_FORCED (0, "init", "lmp [init exit execs]")


			/** state (init) transition processing **/
			FSM_TRANSIT_FORCE (1, state1_enter_exec, ;, "default", "", "init", "idle", "tr_0", "lmp [init -> idle : default / ]")
				/*---------------------------------------------------------*/



			/** state (idle) enter executives **/
			FSM_STATE_ENTER_UNFORCED (1, "idle", state1_enter_exec, "lmp [idle enter execs]")

			/** blocking after enter executives of unforced state. **/
			FSM_EXIT (3,"lmp")


			/** state (idle) exit executives **/
			FSM_STATE_EXIT_UNFORCED (1, "idle", "lmp [idle exit execs]")


			/** state (idle) transition processing **/
			FSM_PROFILE_SECTION_IN ("lmp [idle trans conditions]", state1_trans_conds)
			FSM_INIT_COND (UP_ARVL)
			FSM_TEST_COND (LOW_ARVL)
			FSM_TEST_COND (RX_IDLE)
			FSM_TEST_COND (SEND_FRAME)
			FSM_TEST_COND (RX_BUSY)
			FSM_TEST_COND (TIME_BUFF)
			FSM_TEST_COND (SEND_BEACON)
			FSM_TEST_COND (LOW_ARVL)
			FSM_DFLT_COND
			FSM_TEST_LOGIC ("idle")
			FSM_PROFILE_SECTION_OUT (state1_trans_conds)

			FSM_TRANSIT_SWITCH
				{
				FSM_CASE_TRANSIT (0, 2, state2_enter_exec, ;, "UP_ARVL", "", "idle", "upper_arvl", "tr_1", "lmp [idle -> upper_arvl : UP_ARVL / ]")
				FSM_CASE_TRANSIT (1, 3, state3_enter_exec, ;, "LOW_ARVL", "", "idle", "lower_arvl", "tr_10", "lmp [idle -> lower_arvl : LOW_ARVL / ]")
				FSM_CASE_TRANSIT (2, 5, state5_enter_exec, ;, "RX_IDLE", "", "idle", "channel_idle", "tr_19", "lmp [idle -> channel_idle : RX_IDLE / ]")
				FSM_CASE_TRANSIT (3, 4, state4_enter_exec, ;, "SEND_FRAME", "", "idle", "send", "tr_21", "lmp [idle -> send : SEND_FRAME / ]")
				FSM_CASE_TRANSIT (4, 6, state6_enter_exec, ;, "RX_BUSY", "", "idle", "channle_busy", "tr_23", "lmp [idle -> channle_busy : RX_BUSY / ]")
				FSM_CASE_TRANSIT (5, 7, state7_enter_exec, ;, "TIME_BUFF", "", "idle", "statistic", "tr_25", "lmp [idle -> statistic : TIME_BUFF / ]")
				FSM_CASE_TRANSIT (6, 8, state8_enter_exec, ;, "SEND_BEACON", "", "idle", "send_beacon", "tr_18", "lmp [idle -> send_beacon : SEND_BEACON / ]")
				FSM_CASE_TRANSIT (7, 9, state9_enter_exec, ;, "LOW_ARVL", "", "idle", "lower_arvl_0", "tr_12", "lmp [idle -> lower_arvl_0 : LOW_ARVL / ]")
				FSM_CASE_TRANSIT (8, 1, state1_enter_exec, ;, "default", "", "idle", "idle", "tr_14", "lmp [idle -> idle : default / ]")
				}
				/*---------------------------------------------------------*/



			/** state (upper_arvl) enter executives **/
			FSM_STATE_ENTER_FORCED (2, "upper_arvl", state2_enter_exec, "lmp [upper_arvl enter execs]")
				FSM_PROFILE_SECTION_IN ("lmp [upper_arvl enter execs]", state2_enter_exec)
				{
				//get pk from upper stream
				pkptr = op_pk_get(instrm_from_up);
				
				num=(int)op_dist_uniform(4);
				
				switch(num)
					{
					case 0:
						if (op_subq_pk_insert (0, pkptr, OPC_QPOS_TAIL) != OPC_QINS_OK)
							{
							/* if the insertion failed, discard the packet */
							op_pk_destroy (pkptr);
							}
						else;
					break;
							
					case 1:
						if (op_subq_pk_insert (1, pkptr, OPC_QPOS_TAIL) != OPC_QINS_OK)
							{
							/* if the insertion failed, discard the packet */
							op_pk_destroy (pkptr);
							}
						else;
					break;
							
					case 2:
						if (op_subq_pk_insert (2, pkptr, OPC_QPOS_TAIL) != OPC_QINS_OK)
							{
							/* if the insertion failed, discard the packet */
							op_pk_destroy (pkptr);
							}
						else;
					break;
							
					case 3:
						if (op_subq_pk_insert (3, pkptr, OPC_QPOS_TAIL) != OPC_QINS_OK)
							{
							/* if the insertion failed, discard the packet */
							op_pk_destroy (pkptr);
							}
						else;
					break;
				
					default:
					break;
					}
				
				op_intrpt_schedule_self(op_sim_time(), send_frame);//self intrupt to send FSM
				
				
				//put the data pk into a mac frame
				/*
				pkptr  = op_pk_create_fmt("spma_mac");
				op_pk_nfd_set(pkptr, "DATA", pktptr);
				*/
				//send pk to lower layer
				//op_pk_send(pkptr, instrm_to_low);
				
				
				/*
				//allocate a list 
				list_ptr = (List *) op_prg_mem_alloc (sizeof (List));
				
				//initialize a list 
				op_prg_list_init (list_ptr);
				
				//move the contents of subqueue #0 into the list 
				
				//determine the number of packets in the subqueue 
				subq_size = op_subq_stat (0, OPC_QSTAT_PKSIZE);
				
				for (i = 0; i < subq_size; i++)
					{
					//take a single packet from the subqueue head
					pkptr = op_subq_pk_remove (0, OPC_QPOS_HEAD);
				
					//insert the packet onto the list tail 
					op_prg_list_insert (list_ptr, pkptr, OPC_LISTPOS_TAIL);
					} 
				*/
				}
				FSM_PROFILE_SECTION_OUT (state2_enter_exec)

			/** state (upper_arvl) exit executives **/
			FSM_STATE_EXIT_FORCED (2, "upper_arvl", "lmp [upper_arvl exit execs]")


			/** state (upper_arvl) transition processing **/
			FSM_TRANSIT_FORCE (1, state1_enter_exec, ;, "default", "", "upper_arvl", "idle", "tr_2", "lmp [upper_arvl -> idle : default / ]")
				/*---------------------------------------------------------*/



			/** state (lower_arvl) enter executives **/
			FSM_STATE_ENTER_FORCED (3, "lower_arvl", state3_enter_exec, "lmp [lower_arvl enter execs]")
				FSM_PROFILE_SECTION_IN ("lmp [lower_arvl enter execs]", state3_enter_exec)
				{
				//get pk from lower stream
				pkptr = op_pk_get(instrm_from_low);
				
				op_pk_nfd_access(pkptr,"DEST",&dest);
				
				node_id = op_topo_parent(op_id_self());
				
				op_ima_obj_attr_get(node_id,"node_address",&source);
				
				if(source == dest)
					op_pk_send(pkptr,instrm_to_up);//send pk to upper layer
				else
					op_pk_destroy(pkptr);
				
				//op_pk_send(pkptr, instrm_to_up);
				}
				FSM_PROFILE_SECTION_OUT (state3_enter_exec)

			/** state (lower_arvl) exit executives **/
			FSM_STATE_EXIT_FORCED (3, "lower_arvl", "lmp [lower_arvl exit execs]")


			/** state (lower_arvl) transition processing **/
			FSM_TRANSIT_FORCE (1, state1_enter_exec, ;, "default", "", "lower_arvl", "idle", "tr_11", "lmp [lower_arvl -> idle : default / ]")
				/*---------------------------------------------------------*/



			/** state (send) enter executives **/
			FSM_STATE_ENTER_FORCED (4, "send", state4_enter_exec, "lmp [send enter execs]")
				FSM_PROFILE_SECTION_IN ("lmp [send enter execs]", state4_enter_exec)
				{
				if(channel_busy == 0)  //if channel is idle, send frame
					{
						if(!op_subq_empty (0))
							{
								pktptr = op_subq_pk_remove (0, OPC_QPOS_HEAD);
								op_pk_send2(pktptr,instrm_to_low);//send to stream 0 to low layer;
							}
						else if(!op_subq_empty (1))
							{
								pktptr = op_subq_pk_remove (1, OPC_QPOS_HEAD);
								op_pk_send2(pktptr,instrm_to_low);
							}
						else if(!op_subq_empty (2))
							{
								pktptr = op_subq_pk_remove (2, OPC_QPOS_HEAD);
								op_pk_send2(pktptr,instrm_to_low);
							}
						else if(!op_subq_empty (3))
							{
								pktptr = op_subq_pk_remove (3, OPC_QPOS_HEAD);
								op_pk_send2(pktptr,instrm_to_low);
							}
					}
				/*
				else     //channel is busy, judge channel status value, spma
					{
					if(channel_status_value <= 0.75 && channel_status_value > 0.5) //send frame with priority 0
						{
						if(!op_subq_empty (0))
							{
								pktptr = op_subq_pk_remove (0, OPC_QPOS_HEAD);
								op_pk_send2(pktptr,instrm_to_low);//send to stream 0 to low layer;
							}
						}
				
					else if(channel_status_value <= 0.5 && channel_status_value > 0.25) //send frame with priority 0 and 1
						{
						if(!op_subq_empty (0))
							{
								pktptr = op_subq_pk_remove (0, OPC_QPOS_HEAD);
								op_pk_send2(pktptr,instrm_to_low);//send to stream 0 to low layer;
							}
						else if(!op_subq_empty (1))
							{
								pktptr = op_subq_pk_remove (1, OPC_QPOS_HEAD);
								op_pk_send2(pktptr,instrm_to_low);
							}
						else;
						}
					
					else if(channel_status_value <= 0.25 && channel_status_value > 0) //send frame with priority 0, 1, and 2
						{
						if(!op_subq_empty (0))
							{
								pktptr = op_subq_pk_remove (0, OPC_QPOS_HEAD);
								op_pk_send2(pktptr,instrm_to_low);//send to stream 0 to low layer;
							}
						else if(!op_subq_empty (1))
							{
								pktptr = op_subq_pk_remove (1, OPC_QPOS_HEAD);
								op_pk_send2(pktptr,instrm_to_low);
							}
						else if(!op_subq_empty (2))
							{
								pktptr = op_subq_pk_remove (2, OPC_QPOS_HEAD);
								op_pk_send2(pktptr,instrm_to_low);
							}
						else;
						}
					
					else if(channel_status_value <= 0) //send frame with priority 0, 1, and 2
						{
						if(!op_subq_empty (0))
							{
								pktptr = op_subq_pk_remove (0, OPC_QPOS_HEAD);
								op_pk_send2(pktptr,instrm_to_low);//send to stream 0 to low layer;
							}
						else if(!op_subq_empty (1))
							{
								pktptr = op_subq_pk_remove (1, OPC_QPOS_HEAD);
								op_pk_send2(pktptr,instrm_to_low);
							}
						else if(!op_subq_empty (2))
							{
								pktptr = op_subq_pk_remove (2, OPC_QPOS_HEAD);
								op_pk_send2(pktptr,instrm_to_low);
							}
						else if(!op_subq_empty (3))
							{
								pktptr = op_subq_pk_remove (3, OPC_QPOS_HEAD);
								op_pk_send2(pktptr,instrm_to_low);
							}
						else;
						}
					else;
					}
				*/	
				//	listen_times = 0;
				
				//if a frame waits to be sent, re-enter send status
				if(!op_subq_empty (0) || !op_subq_empty (1) || !op_subq_empty (2) ||!op_subq_empty (3))
					op_intrpt_schedule_self(op_sim_time() + 0.001 + FS_TIMES,FS); //?
					
					
					
					
				/*			if(listen_times == 10)
								{
									if(op_prg_list_size(pk_buffer[0]))
										{
										pktptr = op_prg_list_remove(pk_buffer[0],0);
										op_pk_destroy(pktptr);
										}
									else if(op_prg_list_size(pk_buffer[1]))
										{
										pktptr = op_prg_list_remove(pk_buffer[1],0);
										op_pk_destroy(pktptr);
										}
									else if(op_prg_list_size(pk_buffer[2]))
										{
										pktptr = op_prg_list_remove(pk_buffer[2],0);
										op_pk_destroy(pktptr);
										}
									else if(op_prg_list_size(pk_buffer[3]))
										{
										pktptr = op_prg_list_remove(pk_buffer[3],0);
										op_pk_destroy(pktptr);
										}
								}
						
						else
								{
								back_off_time = op_dist_uniform(1.0);
								op_intrpt_schedule_self(op_sim_time() + back_off_time,back_off);
								listen_times++;
								op_intrpt_schedule_self(op_sim_time(),instrm_from_up);//self intrupt back send FSM
								}
				*/
				}
				FSM_PROFILE_SECTION_OUT (state4_enter_exec)

			/** state (send) exit executives **/
			FSM_STATE_EXIT_FORCED (4, "send", "lmp [send exit execs]")


			/** state (send) transition processing **/
			FSM_TRANSIT_FORCE (1, state1_enter_exec, ;, "default", "", "send", "idle", "tr_22", "lmp [send -> idle : default / ]")
				/*---------------------------------------------------------*/



			/** state (channel_idle) enter executives **/
			FSM_STATE_ENTER_FORCED (5, "channel_idle", state5_enter_exec, "lmp [channel_idle enter execs]")
				FSM_PROFILE_SECTION_IN ("lmp [channel_idle enter execs]", state5_enter_exec)
				{
				channel_busy = 0;//channle idle
				}
				FSM_PROFILE_SECTION_OUT (state5_enter_exec)

			/** state (channel_idle) exit executives **/
			FSM_STATE_EXIT_FORCED (5, "channel_idle", "lmp [channel_idle exit execs]")


			/** state (channel_idle) transition processing **/
			FSM_TRANSIT_FORCE (1, state1_enter_exec, ;, "default", "", "channel_idle", "idle", "tr_20", "lmp [channel_idle -> idle : default / ]")
				/*---------------------------------------------------------*/



			/** state (channle_busy) enter executives **/
			FSM_STATE_ENTER_FORCED (6, "channle_busy", state6_enter_exec, "lmp [channle_busy enter execs]")
				FSM_PROFILE_SECTION_IN ("lmp [channle_busy enter execs]", state6_enter_exec)
				{
				channel_busy = 1;//channel busy
				}
				FSM_PROFILE_SECTION_OUT (state6_enter_exec)

			/** state (channle_busy) exit executives **/
			FSM_STATE_EXIT_FORCED (6, "channle_busy", "lmp [channle_busy exit execs]")


			/** state (channle_busy) transition processing **/
			FSM_TRANSIT_FORCE (1, state1_enter_exec, ;, "default", "", "channle_busy", "idle", "tr_24", "lmp [channle_busy -> idle : default / ]")
				/*---------------------------------------------------------*/



			/** state (statistic) enter executives **/
			FSM_STATE_ENTER_FORCED (7, "statistic", state7_enter_exec, "lmp [statistic enter execs]")
				FSM_PROFILE_SECTION_IN ("lmp [statistic enter execs]", state7_enter_exec)
				{
				//statistic channel busy level
				if(channel_busy == 1)
					{
					cur_time = op_sim_time();
					
					if((op_prg_list_size(time_buffer)) <= 100)  //put current time into list
						{
				//		saved_time_ptr = op_prg_mem_alloc (sizeof (double));
				//		*saved_time_ptr = cur_time;
						op_prg_list_insert(time_buffer, &cur_time, OPC_LISTPOS_TAIL);	
						}
					else
						{
						op_prg_list_remove(time_buffer, 0); //remove the first element
						op_prg_list_insert(time_buffer, &cur_time, OPC_LISTPOS_TAIL);	
						}
					
					//check if element expire
					if(op_prg_list_size(time_buffer) > 0)
						{
						saved_time_ptr = (double*)op_prg_list_access(time_buffer, OPC_LISTPOS_HEAD);
					
						while(cur_time - *saved_time_ptr >= 1.0)
							{
							op_prg_list_remove(time_buffer, 0); //remove the expired element
							if(op_prg_list_size(time_buffer) > 0)
								saved_time_ptr = (double*)op_prg_list_access(time_buffer, OPC_LISTPOS_HEAD);
							else
								break;
							}
						}
						
					channel_status_value = (op_prg_list_size(time_buffer)) / 100;
						
					}
				
				op_intrpt_schedule_self(op_sim_time()+0.001, Time); //to FSM statistic every 0.01s
				
				}
				FSM_PROFILE_SECTION_OUT (state7_enter_exec)

			/** state (statistic) exit executives **/
			FSM_STATE_EXIT_FORCED (7, "statistic", "lmp [statistic exit execs]")


			/** state (statistic) transition processing **/
			FSM_TRANSIT_FORCE (1, state1_enter_exec, ;, "default", "", "statistic", "idle", "tr_26", "lmp [statistic -> idle : default / ]")
				/*---------------------------------------------------------*/



			/** state (send_beacon) enter executives **/
			FSM_STATE_ENTER_FORCED (8, "send_beacon", state8_enter_exec, "lmp [send_beacon enter execs]")
				FSM_PROFILE_SECTION_IN ("lmp [send_beacon enter execs]", state8_enter_exec)
				{
				//create MASTER hello packet
				//if(flag==0)
				pk=op_pk_create_fmt("MS_beacon");	
				op_pk_nfd_set(pk,"DEST",0);
				op_pk_nfd_set(pk,"SRC",node_address);
				op_pk_nfd_set(pk, "Type", 10); 
				op_pk_send(pk,instrm_to_low);
				//t=op_dist_uniform(10)*slot_time;
				
				
				
				
				
				}
				FSM_PROFILE_SECTION_OUT (state8_enter_exec)

			/** state (send_beacon) exit executives **/
			FSM_STATE_EXIT_FORCED (8, "send_beacon", "lmp [send_beacon exit execs]")


			/** state (send_beacon) transition processing **/
			FSM_TRANSIT_FORCE (1, state1_enter_exec, ;, "default", "", "send_beacon", "idle", "tr_27", "lmp [send_beacon -> idle : default / ]")
				/*---------------------------------------------------------*/



			/** state (lower_arvl_0) enter executives **/
			FSM_STATE_ENTER_FORCED (9, "lower_arvl_0", state9_enter_exec, "lmp [lower_arvl_0 enter execs]")
				FSM_PROFILE_SECTION_IN ("lmp [lower_arvl_0 enter execs]", state9_enter_exec)
				{
				//get pk from lower stream
				
					t=op_dist_uniform(100)*1E-3;
				pkptr = op_pk_get(instrm_from_low);
				op_pk_nfd_access(pkptr,"SRC",&source);
				op_pk_nfd_access(pkptr,"DEST",&dest);
				op_pk_nfd_access(pkptr,"Type",&type);
				switch(type)
					{
					case 10 :{
					if(node_address==0)
					{
					pk=op_pk_create_fmt("rest");	
					op_pk_nfd_set(pk,"DEST",source);
					op_pk_nfd_set(pk,"SRC",node_address);
					op_pk_nfd_set(pk, "Type", 15);
					num=op_dist_uniform(3);
					if (op_subq_pk_insert (num, pk, OPC_QPOS_TAIL) != OPC_QINS_OK)
					{
					op_pk_destroy(pk);
					op_intrpt_schedule_self(op_sim_time()+t,CSMA);};
					}
					else 
						op_pk_destroy(pkptr);
					break;};
					case 15 :
					{
					if(node_address==dest&&node_address!=0)
					{
					flag=1;
					pk=op_pk_create_fmt("re_ack");	//in order to request access node0
					op_pk_nfd_set(pk,"DEST",source);
					op_pk_nfd_set(pk,"SRC",node_address);
					op_pk_nfd_set(pk, "Type", 20);
					num=op_dist_uniform(3);
					if (op_subq_pk_insert (num, pk, OPC_QPOS_TAIL) != OPC_QINS_OK)
						{op_pk_destroy(pk);
					op_intrpt_schedule_self(op_sim_time()+t,CSMA);};}
					else 
					op_pk_destroy(pkptr);
					break;};
					case 20 :
					{
					if(node_address==0)
					{		
					pk=op_pk_create_fmt("rv_ack");	//in order to request access node0
					op_pk_nfd_set(pk,"DEST",source);
					op_pk_nfd_set(pk,"SRC",node_address);
					op_pk_nfd_set(pk, "Type", 25);
					num=op_dist_uniform(3);
					if (op_subq_pk_insert (num, pk, OPC_QPOS_TAIL) != OPC_QINS_OK)
						{op_pk_destroy(pk);
					op_intrpt_schedule_self(op_sim_time()+t,CSMA);
					};
					}
					else 
					op_pk_destroy(pkptr);
					break;};
				    case 25 :
					{
					if(node_address==dest&&node_address!=0)
					{
				
				    printf("matched sucess");
					printf("flag=%d",flag);
					//t=op_dist_uniform(300E-3);
					op_intrpt_schedule_self(op_sim_time()+t,acl_code);
					}
					else
					op_pk_destroy(pkptr);
				    break;};
					case 100 :
					{
					if(node_address==0)
						{
					n=op_prg_list_size(record_node_list);
					op_pk_send(pkptr,instrm_to_up);
					pk=op_pk_create_fmt("data");	
					op_pk_nfd_set(pk,"DEST",source);
					op_pk_nfd_set(pk,"SRC",0);
					op_pk_nfd_set(pk, "Type", 150);
					num=op_dist_uniform(3);
					if (op_subq_pk_insert (num, pk, OPC_QPOS_TAIL) != OPC_QINS_OK)
						{
						op_pk_destroy(pk);
					op_intrpt_schedule_self(op_sim_time()+t,CSMA);};
					
						}
					else 
						op_pk_destroy(pkptr);break;};
					case 150 :
					{
						if(node_address==dest&&node_address!=0)
							{
							op_pk_destroy(pkptr);
							op_intrpt_schedule_self(op_sim_time()+t,acl_code);
							};
						break;
						};
					}
					
				
				
				}
				FSM_PROFILE_SECTION_OUT (state9_enter_exec)

			/** state (lower_arvl_0) exit executives **/
			FSM_STATE_EXIT_FORCED (9, "lower_arvl_0", "lmp [lower_arvl_0 exit execs]")


			/** state (lower_arvl_0) transition processing **/
			FSM_TRANSIT_FORCE (1, state1_enter_exec, ;, "default", "", "lower_arvl_0", "idle", "tr_13", "lmp [lower_arvl_0 -> idle : default / ]")
				/*---------------------------------------------------------*/



			}


		FSM_EXIT (0,"lmp")
		}
	}




void
_op_lmp_diag (OP_SIM_CONTEXT_ARG_OPT)
	{
	/* No Diagnostic Block */
	}




void
_op_lmp_terminate (OP_SIM_CONTEXT_ARG_OPT)
	{

	FIN_MT (_op_lmp_terminate ())


	/* No Termination Block */

	Vos_Poolmem_Dealloc (op_sv_ptr);

	FOUT
	}


/* Undefine shortcuts to state variables to avoid */
/* syntax error in direct access to fields of */
/* local variable prs_ptr in _op_lmp_svar function. */
#undef node_id
#undef listen_times
#undef channel_busy
#undef time_buffer
#undef channel_status_value

#undef FIN_PREAMBLE_DEC
#undef FIN_PREAMBLE_CODE

#define FIN_PREAMBLE_DEC
#define FIN_PREAMBLE_CODE

VosT_Obtype
_op_lmp_init (int * init_block_ptr)
	{
	VosT_Obtype obtype = OPC_NIL;
	FIN_MT (_op_lmp_init (init_block_ptr))

	obtype = Vos_Define_Object_Prstate ("proc state vars (lmp)",
		sizeof (lmp_state));
	*init_block_ptr = 0;

	FRET (obtype)
	}

VosT_Address
_op_lmp_alloc (VosT_Obtype obtype, int init_block)
	{
#if !defined (VOSD_NO_FIN)
	int _op_block_origin = 0;
#endif
	lmp_state * ptr;
	FIN_MT (_op_lmp_alloc (obtype))

	ptr = (lmp_state *)Vos_Alloc_Object (obtype);
	if (ptr != OPC_NIL)
		{
		ptr->_op_current_block = init_block;
#if defined (OPD_ALLOW_ODB)
		ptr->_op_current_state = "lmp [init enter execs]";
#endif
		}
	FRET ((VosT_Address)ptr)
	}



void
_op_lmp_svar (void * gen_ptr, const char * var_name, void ** var_p_ptr)
	{
	lmp_state		*prs_ptr;

	FIN_MT (_op_lmp_svar (gen_ptr, var_name, var_p_ptr))

	if (var_name == OPC_NIL)
		{
		*var_p_ptr = (void *)OPC_NIL;
		FOUT
		}
	prs_ptr = (lmp_state *)gen_ptr;

	if (strcmp ("node_id" , var_name) == 0)
		{
		*var_p_ptr = (void *) (&prs_ptr->node_id);
		FOUT
		}
	if (strcmp ("listen_times" , var_name) == 0)
		{
		*var_p_ptr = (void *) (&prs_ptr->listen_times);
		FOUT
		}
	if (strcmp ("channel_busy" , var_name) == 0)
		{
		*var_p_ptr = (void *) (&prs_ptr->channel_busy);
		FOUT
		}
	if (strcmp ("time_buffer" , var_name) == 0)
		{
		*var_p_ptr = (void *) (&prs_ptr->time_buffer);
		FOUT
		}
	if (strcmp ("channel_status_value" , var_name) == 0)
		{
		*var_p_ptr = (void *) (&prs_ptr->channel_status_value);
		FOUT
		}
	*var_p_ptr = (void *)OPC_NIL;

	FOUT
	}

