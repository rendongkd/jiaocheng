/* Process model C form file: test_mac5.pr.c */
/* Portions of this file copyright 1986-2008 by OPNET Technologies, Inc. */



/* This variable carries the header into the object file */
const char test_mac5_pr_c [] = "MIL_3_Tfile_Hdr_ 145A 30A modeler 7 5D7365A3 5D7365A3 1 USER-20151017SA Administrator 0 0 none none 0 0 none 0 0 0 0 0 0 0 0 1bcc 1                                                                                                                                                                                                                                                                                                                                                                                            ";
#include <string.h>



/* OPNET system definitions */
#include <opnet.h>



/* Header Block */

/*define symbolic constant*/
#define  instrm_from_low 		0
#define  instrm_from_up 		1
#define  instrm_to_low 			0
#define  instrm_to_up 			1
//#define	 Time					100

#define	 back_off				0
#define	 send_csma				1000
#define	 bind_csma			2000
#define	 slot_control			3000
#define	 send_tdma				4000

#define	 FS						1      //frame space
#define	 FS_TIMES				10   //frame space times 60 microsecond
#define slot_time				10E-3//10MS

#define	 RX_INSTAT 			    0
//#define	 TX_INSTAT 			    1

#define  DATA_RATE				1000000         //bps

/*define macros*/
#define LOW_ARVL 			(op_intrpt_type() == OPC_INTRPT_STRM && op_intrpt_code() == instrm_from_low)
#define UP_ARVL 			(op_intrpt_type() == OPC_INTRPT_STRM && op_intrpt_code() == instrm_from_up)

#define BIND_CSMA			(op_intrpt_type() == OPC_INTRPT_SELF && op_intrpt_code() == bind_csma)
#define  SEND_BEACON		(op_intrpt_type() == OPC_INTRPT_SELF && op_intrpt_code() == Beacon_code)
#define SEND_CSMA			(op_intrpt_type() == OPC_INTRPT_SELF && op_intrpt_code() == send_csma)
#define SLOT_CONTROL			(op_intrpt_type() == OPC_INTRPT_SELF && op_intrpt_code() == slot_control)
#define TIME_BUFF 			(op_intrpt_type() == OPC_INTRPT_SELF && op_intrpt_code() == Time)
#define SEND_TDMA 			(op_intrpt_type() == OPC_INTRPT_SELF && op_intrpt_code() == send_tdma)
#define	RX_BUSY				((op_intrpt_type()== OPC_INTRPT_STAT) && (op_intrpt_stat () == RX_INSTAT ) && op_stat_local_read (RX_INSTAT) == 1.0)
#define	RX_IDLE				((op_intrpt_type()== OPC_INTRPT_STAT) && (op_intrpt_stat () == RX_INSTAT ) && op_stat_local_read (RX_INSTAT) == 0.0)

//#define	TX_BUSY				((op_intrpt_type()== OPC_INTRPT_STAT) && (op_intrpt_stat () == TX_INSTAT ) && op_stat_local_read (TX_INSTAT) == 1.0)
//#define	TX_IDLE				((op_intrpt_type()== OPC_INTRPT_STAT) && (op_intrpt_stat () == TX_INSTAT ) && op_stat_local_read (TX_INSTAT) == 0.0)


//cmh add
#define Beacon_code			500
#define  tdma_code              600



//cmh add
void op_pk_send2(Packet* pktptr, int stream_num);
typedef struct record_value
	{
	int node_value;
	}record_value;

typedef struct slot_element
	{
	int node_num;
	int slot_num;
	int subcarrier_num;
	}slot_element;

record_value * str_lookup(int address); 
record_value* create_new_insert();
//int 	beacon_slot1, csma_slot1,tdma_slot1,bind_csma_slot1;

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
	int	                    		rx_busy                                         ;
	List*	                  		time_buffer                                     ;
	double	                 		channel_status_value                            ;
	int	                    		tx_busy                                         ;
	int	                    		node_address                                    ;
	double	                 		comm_dist                                       ;	/* communication range */
	int	                    		dest_addr                                       ;
	int	                    		cycle_time                                      ;
	int	                    		beacon_num                                      ;
	int	                    		flag                                            ;
	int	                    		node_number                                     ;
	List*	                  		record_node_list                                ;
	List*	                  		slot_table                                      ;
	int	                    		slot_index                                      ;
	int	                    		slot_number                                     ;
	int	                    		slot_assignment                                 ;
	} test_mac5_state;

#define node_id                 		op_sv_ptr->node_id
#define listen_times            		op_sv_ptr->listen_times
#define rx_busy                 		op_sv_ptr->rx_busy
#define time_buffer             		op_sv_ptr->time_buffer
#define channel_status_value    		op_sv_ptr->channel_status_value
#define tx_busy                 		op_sv_ptr->tx_busy
#define node_address            		op_sv_ptr->node_address
#define comm_dist               		op_sv_ptr->comm_dist
#define dest_addr               		op_sv_ptr->dest_addr
#define cycle_time              		op_sv_ptr->cycle_time
#define beacon_num              		op_sv_ptr->beacon_num
#define flag                    		op_sv_ptr->flag
#define node_number             		op_sv_ptr->node_number
#define record_node_list        		op_sv_ptr->record_node_list
#define slot_table              		op_sv_ptr->slot_table
#define slot_index              		op_sv_ptr->slot_index
#define slot_number             		op_sv_ptr->slot_number
#define slot_assignment         		op_sv_ptr->slot_assignment

/* These macro definitions will define a local variable called	*/
/* "op_sv_ptr" in each function containing a FIN statement.	*/
/* This variable points to the state variable data structure,	*/
/* and can be used from a C debugger to display their values.	*/
#undef FIN_PREAMBLE_DEC
#undef FIN_PREAMBLE_CODE
#define FIN_PREAMBLE_DEC	test_mac5_state *op_sv_ptr;
#define FIN_PREAMBLE_CODE	\
		op_sv_ptr = ((test_mac5_state *)(OP_SIM_CONTEXT_PTR->_op_mod_state_ptr));


/* Function Block */

#if !defined (VOSD_NO_FIN)
enum { _op_block_origin = __LINE__ + 2};
#endif

void op_pk_send2(Packet* pktptr, int stream_num)
	{
//	int 		dest,source;
//	Packet* 	pk;
	FILE*		fp;
	
	FIN(op_pk_send2(pktptr, stream_num));
/*	
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
*/
	//op_pk_send_delayed(pktptr, stream_num,op_dist_uniform(FS_TIMES));
	op_pk_send(pktptr, stream_num);
	fp = fopen("c:\\send_time.txt", "a+");
	if(fp != NULL)
		{
		fprintf(fp, "\n%f", op_sim_time());
		fclose(fp);
		}
	else;
	
//	listen_times = 0;
//	op_intrpt_schedule_self(op_sim_time()+FS_TIMES,FS);

	FOUT;
	}

record_value * str_lookup(int address)  
{  
    int st_size, i;  
    record_value * st_str;  
    FIN(str_lookup(address));  
	
    st_size = op_prg_list_size(record_node_list);  
    for(i=0; i<st_size; i++)  
	{  
        st_str = op_prg_list_access(record_node_list, i);  
        if(st_str->node_value == address)    
            FRET(st_str) ;
	}  
    FRET(OPC_NIL);
}


record_value* create_new_insert()
{
	record_value* st_str;
	/*create a new connect table entry*/
	st_str = (record_value *)op_prg_mem_alloc(sizeof(record_value)); 
	/*initializing variables*/
	st_str->node_value = -1; 
	
	
	return st_str;
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
	void test_mac5 (OP_SIM_CONTEXT_ARG_OPT);
	VosT_Obtype _op_test_mac5_init (int * init_block_ptr);
	void _op_test_mac5_diag (OP_SIM_CONTEXT_ARG_OPT);
	void _op_test_mac5_terminate (OP_SIM_CONTEXT_ARG_OPT);
	VosT_Address _op_test_mac5_alloc (VosT_Obtype, int);
	void _op_test_mac5_svar (void *, const char *, void **);


#if defined (__cplusplus)
} /* end of 'extern "C"' */
#endif




/* Process model interrupt handling procedure */


void
test_mac5 (OP_SIM_CONTEXT_ARG_OPT)
	{
#if !defined (VOSD_NO_FIN)
	int _op_block_origin = 0;
#endif
	FIN_MT (test_mac5 ());

		{
		/* Temporary Variables */
		/*declare variables*/
		Packet*	pkptr;
		Packet*	pktptr;
		Packet*	pk;
		int 	dest, source,type;
		int 	beacon_slot1=1, csma_slot1=6,tdma_slot1=15,bind_csma_slot1=20;
		int i;
		int	num = 0;
		double accept = 0.0, distance = 0.0;
		slot_element* slot_str;
		//int sub_number;
		record_value* str;
		int slot;
		//int sub_number;
		int t;
		double time;
		/* End of Temporary Variables */


		FSM_ENTER ("test_mac5")

		FSM_BLOCK_SWITCH
			{
			/*---------------------------------------------------------*/
			/** state (init) enter executives **/
			FSM_STATE_ENTER_FORCED_NOLABEL (0, "init", "test_mac5 [init enter execs]")
				FSM_PROFILE_SECTION_IN ("test_mac5 [init enter execs]", state0_enter_exec)
				{
				node_id = op_topo_parent(op_id_self());
				
				//op_ima_obj_attr_get(node_id,"Destination Address",&dest);//get dest frome attributes;
				op_ima_obj_attr_get(node_id,"node address",&node_address);
				op_ima_obj_attr_get(node_id,"destination_address",&dest_addr);
				channel_status_value = 1.0;
				
				
				rx_busy = 1;
					
				//op_intrpt_schedule_self(op_sim_time(), Time); //collect channel status
				cycle_time=50E-3;//50ms
				if( node_address==0)
					op_intrpt_schedule_self(op_sim_time(),slot_control);
				//else;
				beacon_num=0;
				flag=0;
				slot_number=0;//time slot number
				record_node_list = op_prg_list_create();
				slot_table = op_prg_list_create();
				node_number=1;
				
				}
				FSM_PROFILE_SECTION_OUT (state0_enter_exec)

			/** state (init) exit executives **/
			FSM_STATE_EXIT_FORCED (0, "init", "test_mac5 [init exit execs]")


			/** state (init) transition processing **/
			FSM_TRANSIT_FORCE (1, state1_enter_exec, ;, "default", "", "init", "idle", "tr_0", "test_mac5 [init -> idle : default / ]")
				/*---------------------------------------------------------*/



			/** state (idle) enter executives **/
			FSM_STATE_ENTER_UNFORCED (1, "idle", state1_enter_exec, "test_mac5 [idle enter execs]")

			/** blocking after enter executives of unforced state. **/
			FSM_EXIT (3,"test_mac5")


			/** state (idle) exit executives **/
			FSM_STATE_EXIT_UNFORCED (1, "idle", "test_mac5 [idle exit execs]")


			/** state (idle) transition processing **/
			FSM_PROFILE_SECTION_IN ("test_mac5 [idle trans conditions]", state1_trans_conds)
			FSM_INIT_COND (UP_ARVL)
			FSM_TEST_COND (LOW_ARVL)
			FSM_TEST_COND (RX_IDLE)
			FSM_TEST_COND (SEND_CSMA)
			FSM_TEST_COND (RX_BUSY)
			FSM_TEST_COND (SEND_BEACON)
			FSM_TEST_COND (SLOT_CONTROL)
			FSM_TEST_COND (BIND_CSMA)
			FSM_TEST_COND (SEND_TDMA)
			FSM_DFLT_COND
			FSM_TEST_LOGIC ("idle")
			FSM_PROFILE_SECTION_OUT (state1_trans_conds)

			FSM_TRANSIT_SWITCH
				{
				FSM_CASE_TRANSIT (0, 2, state2_enter_exec, ;, "UP_ARVL", "", "idle", "upper_arvl", "tr_1", "test_mac5 [idle -> upper_arvl : UP_ARVL / ]")
				FSM_CASE_TRANSIT (1, 3, state3_enter_exec, ;, "LOW_ARVL", "", "idle", "lower_arvl", "tr_10", "test_mac5 [idle -> lower_arvl : LOW_ARVL / ]")
				FSM_CASE_TRANSIT (2, 5, state5_enter_exec, ;, "RX_IDLE", "", "idle", "rx_idle", "tr_19", "test_mac5 [idle -> rx_idle : RX_IDLE / ]")
				FSM_CASE_TRANSIT (3, 4, state4_enter_exec, ;, "SEND_CSMA", "", "idle", "send_csma", "tr_21", "test_mac5 [idle -> send_csma : SEND_CSMA / ]")
				FSM_CASE_TRANSIT (4, 6, state6_enter_exec, ;, "RX_BUSY", "", "idle", "rx_busy", "tr_23", "test_mac5 [idle -> rx_busy : RX_BUSY / ]")
				FSM_CASE_TRANSIT (5, 7, state7_enter_exec, ;, "SEND_BEACON", "", "idle", "send_beacon", "tr_22_0", "test_mac5 [idle -> send_beacon : SEND_BEACON / ]")
				FSM_CASE_TRANSIT (6, 8, state8_enter_exec, ;, "SLOT_CONTROL", "", "idle", "slot_control", "tr_24_0", "test_mac5 [idle -> slot_control : SLOT_CONTROL / ]")
				FSM_CASE_TRANSIT (7, 9, state9_enter_exec, ;, "BIND_CSMA", "", "idle", "bind_csma", "tr_25", "test_mac5 [idle -> bind_csma : BIND_CSMA / ]")
				FSM_CASE_TRANSIT (8, 10, state10_enter_exec, ;, "SEND_TDMA", "", "idle", "send_tdma", "tr_28", "test_mac5 [idle -> send_tdma : SEND_TDMA / ]")
				FSM_CASE_TRANSIT (9, 1, state1_enter_exec, ;, "default", "", "idle", "idle", "tr_14", "test_mac5 [idle -> idle : default / ]")
				}
				/*---------------------------------------------------------*/



			/** state (upper_arvl) enter executives **/
			FSM_STATE_ENTER_FORCED (2, "upper_arvl", state2_enter_exec, "test_mac5 [upper_arvl enter execs]")
				FSM_PROFILE_SECTION_IN ("test_mac5 [upper_arvl enter execs]", state2_enter_exec)
				{
				//get pk from upper stream
				pkptr = op_pk_get(instrm_from_up);
				
				//num=(int)op_dist_uniform(4);
				num = 0;
				
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
							// if the insertion failed, discard the packet 
							op_pk_destroy (pkptr);
							}
						else;
					break;
							
					case 2:
						if (op_subq_pk_insert (2, pkptr, OPC_QPOS_TAIL) != OPC_QINS_OK)
							{
							//if the insertion failed, discard the packet 
							op_pk_destroy (pkptr);
							}
						else;
					break;
							
					case 3:
						if (op_subq_pk_insert (3, pkptr, OPC_QPOS_TAIL) != OPC_QINS_OK)
							{
							// if the insertion failed, discard the packet //
							op_pk_destroy (pkptr);
							}
						else;
				
					break;
				
					default:
					break;
					}
				op_intrpt_schedule_self(op_sim_time() , slot_control); 
				//self intrupt to send pks, add a random period to avoid collision
				//op_intrpt_schedule_self(op_sim_time() + op_dist_uniform(FS_TIMES), send_frame); 
				
				//op_intrpt_schedule_self(op_sim_time() + 20, send_frame);
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
			FSM_STATE_EXIT_FORCED (2, "upper_arvl", "test_mac5 [upper_arvl exit execs]")


			/** state (upper_arvl) transition processing **/
			FSM_TRANSIT_FORCE (1, state1_enter_exec, ;, "default", "", "upper_arvl", "idle", "tr_2", "test_mac5 [upper_arvl -> idle : default / ]")
				/*---------------------------------------------------------*/



			/** state (lower_arvl) enter executives **/
			FSM_STATE_ENTER_FORCED (3, "lower_arvl", state3_enter_exec, "test_mac5 [lower_arvl enter execs]")
				FSM_PROFILE_SECTION_IN ("test_mac5 [lower_arvl enter execs]", state3_enter_exec)
				{
				//get pk from lower stream
				
				pkptr = op_pk_get(instrm_from_low);
				op_pk_nfd_access(pkptr,"SRC",&source);
				op_pk_nfd_access(pkptr,"DEST",&dest);
				op_pk_nfd_access(pkptr,"Type",&type);
				
				if(type==10)
					{
					op_pk_nfd_access(pkptr,"beacon_slot",&beacon_slot1);
					op_pk_nfd_access(pkptr,"csma_slot",&csma_slot1);
					op_pk_nfd_access(pkptr,"tdma_slot",&tdma_slot1);
					op_pk_nfd_access(pkptr,"bind_csma_slot",&bind_csma_slot1);
					}
				//////////////abz, consider distance
				distance = op_td_get_dbl (pkptr, OPC_TDA_BU_DISTANCE);  //get distance between tx and rx
				if(distance == 0.0) 
					op_pk_destroy (pkptr);  //if distance = 0, do not accept
				
				else
					
				{
				
				switch(type)
					{
					
					//receive node0 beacon packet
					case 10: 
				
						if(beacon_num == 0)
							{
							//beacon_num++;//to know how many becon packet has receive		
							beacon_num=1;
							op_intrpt_schedule_self(op_sim_time()+slot_time,slot_control);
							} 
						else//beacon_num==1
							{
							op_intrpt_schedule_self(op_sim_time()+slot_time,slot_control);
							}
						
					case 11:  // the second floor sta receive pco beacon packet
						
						if(flag == 0)
							{
							pk=op_pk_create_fmt("node_request");	//in order to request access node0
							op_pk_nfd_set(pk,"DEST",source);
							op_pk_nfd_set(pk,"SRC",node_address);
							op_pk_nfd_set(pk, "Type", 15); 
							//op_pk_send(pk, instrm_to_low);
							if (op_subq_pk_insert (2, pk, OPC_QPOS_TAIL) != OPC_QINS_OK)//put the packet into buffer0
								{
								//if the insertion failed, discard the packet 
								op_pk_destroy (pk);
								}  
							
							else; 
							
							op_intrpt_schedule_self(op_sim_time()+slot_time,send_csma);
							}
							
							
						else//flag=1,node has accessed BS
							{
							op_pk_destroy (pkptr);		
							}
						
						break;
				
						//cco receive other sta packet
						case 15:
						
						if(node_address == 0)//&&(source >= 0 && source <= 5))//write  list approve
						{
							if(source >= 1 && source <= 15)//write node list approve
									{
									str=str_lookup(source);
									if(str == OPC_NIL) 
										{
										str=create_new_insert();
										str->node_value =source;
										op_prg_list_insert(record_node_list,str,OPC_LISTPOS_TAIL);
							
										pk=op_pk_create_fmt("ack_information");//tell node that it accessed BS successfully
										op_pk_nfd_set(pk,"DEST",source);
										op_pk_nfd_set(pk,"SRC",node_address);
										op_pk_nfd_set(pk,"MS_access_identity",slot_number);
										op_pk_nfd_set(pk,"Type",16);
										op_pk_send(pk, instrm_to_low);
										slot_number++;
										}
									else;
									}
						//if the node is not belong to the write list ,it will not send req packet to network for 150 seconds
							else
								{
								pk=op_pk_create_fmt("node_request2");	//in order to request access node0
								op_pk_nfd_set(pk,"DEST",0);
								op_pk_nfd_set(pk,"SRC",node_address);
								op_pk_nfd_set(pk, "Type", 17); 
								op_pk_send_delayed(pk, instrm_to_low,1);//150s
								/*if (op_subq_pk_insert (1, pk, OPC_QPOS_TAIL) != OPC_QINS_OK)//put the packet into buffer0
								{
								//if the insertion failed, discard the packet 
								op_pk_destroy (pk);
								}  
								else; 
								slot_index=slot_index+5;
								op_intrpt_schedule_self(op_sim_time()+5*slot_time,send_csma);
								}
								*/	
								//else;
								}
						}
						else
							op_pk_destroy(pkptr);
						break;
						
						case 16://node receive time_slot_assignment packet
						if(node_address == dest)
						{
						op_pk_nfd_get(pkptr,"MS_access_identity",&slot); 
						//op_pk_nfd_get(pkptr,"PUSCH sub-carrier",&sub_number);
						slot_str = (slot_element*)op_prg_mem_alloc(sizeof(slot_element)); 
						slot_str->node_num = node_address;
						slot_str->slot_num = slot;
						//slot_str->subcarrier_num = sub_number;
						op_prg_list_insert(slot_table,slot_str,OPC_LISTPOS_TAIL); 
						slot_assignment=1;
						flag=1;//to show this node had input the network
						node_number++;//to show if the gorup network has finish
						op_subq_flush(0);//flush the queue 0
						}
						else
							op_pk_destroy(pkptr);
						
						break;
					
						case 17:
						
						if(node_address == 0)//&&(source >= 0 && source <= 5))//write node list approve
						{
							if(source >= 1 && source <= 15)//write node list approve
									{
									str=str_lookup(source);
									if(str == OPC_NIL) 
										{
										str=create_new_insert();
										str->node_value =source;
										op_prg_list_insert(record_node_list,str,OPC_LISTPOS_TAIL);
							
										pk=op_pk_create_fmt("ack_information");//tell node that it accessed BS successfully
										op_pk_nfd_set(pk,"DEST",source);
										op_pk_nfd_set(pk,"SRC",node_address);
										op_pk_nfd_set(pk,"MS_access_identity",slot_number);
										op_pk_nfd_set(pk,"Type",16);
										op_pk_send(pk, instrm_to_low);
										slot_number++;
										}
									else;
									}
						//if the node is not belong to the write list ,it will not send req packet to network for 150 seconds
							else
								{
								pk=op_pk_create_fmt("node_request3");	//in order to request access node0
								op_pk_nfd_set(pk,"DEST",0);
								op_pk_nfd_set(pk,"SRC",node_address);
								op_pk_nfd_set(pk, "Type", 18); 
								op_pk_send_delayed(pk, instrm_to_low,1);//150s
								/*if (op_subq_pk_insert (1, pk, OPC_QPOS_TAIL) != OPC_QINS_OK)//put the packet into buffer0
								{
								//if the insertion failed, discard the packet 
								op_pk_destroy (pk);
								}  
								else; 
								slot_index=slot_index+5;
								op_intrpt_schedule_self(op_sim_time()+5*slot_time,send_csma);
								}
								*/	
								//else;
						
								}
						}
						else
							op_pk_destroy(pkptr);
						break;
						case 100://receive data packet
						op_pk_send(pkptr,instrm_to_up);
					break;
						
					case 200:
						if(node_address == dest)
						{
							op_pk_send(pkptr,instrm_to_up);
						}
						else
							op_pk_destroy(pkptr);
						
					break;
						
					case 300:
						if(node_address == dest)
						{
							op_pk_send(pkptr,instrm_to_up);
						}
						else
							op_pk_destroy(pkptr);
						
					break;
						
					default:  ;
						}
				}
				}
				FSM_PROFILE_SECTION_OUT (state3_enter_exec)

			/** state (lower_arvl) exit executives **/
			FSM_STATE_EXIT_FORCED (3, "lower_arvl", "test_mac5 [lower_arvl exit execs]")


			/** state (lower_arvl) transition processing **/
			FSM_TRANSIT_FORCE (1, state1_enter_exec, ;, "default", "", "lower_arvl", "idle", "tr_11", "test_mac5 [lower_arvl -> idle : default / ]")
				/*---------------------------------------------------------*/



			/** state (send_csma) enter executives **/
			FSM_STATE_ENTER_FORCED (4, "send_csma", state4_enter_exec, "test_mac5 [send_csma enter execs]")
				FSM_PROFILE_SECTION_IN ("test_mac5 [send_csma enter execs]", state4_enter_exec)
				{
						if(flag == 0 )
							{
							
							pk=op_pk_create_fmt("node_request");	//in order to request access node0
							op_pk_nfd_set(pk,"DEST",0);
							op_pk_nfd_set(pk,"SRC",node_address);
							op_pk_nfd_set(pk, "Type", 15); 
							//op_pk_send(pk, instrm_to_low);
							if (op_subq_pk_insert (1, pk, OPC_QPOS_TAIL) != OPC_QINS_OK)//put the packet into buffer0
								{
								//if the insertion failed, discard the packet 
								op_pk_destroy (pk);
								}  
							else; 
							 //slot_index=slot_index+5;
							//op_intrpt_schedule_self(op_sim_time()+5*slot_time,send_csma);
							}
						/*	
							else;
						else//flag=1,node has accessed BS
							{
							op_pk_destroy (pkptr);		
							}
						*/
					if(rx_busy == 0 )  //if channel is idle, send frame
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
				else
				{
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
				if(!op_subq_empty (1) )//flag=1
				//	op_intrpt_schedule_self(op_sim_time() + 0.001 + FS_TIMES, FS); 
					op_intrpt_schedule_self(op_sim_time() + FS_TIMES + op_dist_uniform(FS_TIMES), send_csma); 
				else;
					
				}	
				slot_index=slot_index+4;	
				op_intrpt_schedule_self(op_sim_time()+slot_time,slot_control);	
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

			/** state (send_csma) exit executives **/
			FSM_STATE_EXIT_FORCED (4, "send_csma", "test_mac5 [send_csma exit execs]")


			/** state (send_csma) transition processing **/
			FSM_TRANSIT_FORCE (1, state1_enter_exec, ;, "default", "", "send_csma", "idle", "tr_22", "test_mac5 [send_csma -> idle : default / ]")
				/*---------------------------------------------------------*/



			/** state (rx_idle) enter executives **/
			FSM_STATE_ENTER_FORCED (5, "rx_idle", state5_enter_exec, "test_mac5 [rx_idle enter execs]")
				FSM_PROFILE_SECTION_IN ("test_mac5 [rx_idle enter execs]", state5_enter_exec)
				{
				rx_busy = 0;  //rx idle
				}
				FSM_PROFILE_SECTION_OUT (state5_enter_exec)

			/** state (rx_idle) exit executives **/
			FSM_STATE_EXIT_FORCED (5, "rx_idle", "test_mac5 [rx_idle exit execs]")


			/** state (rx_idle) transition processing **/
			FSM_TRANSIT_FORCE (1, state1_enter_exec, ;, "default", "", "rx_idle", "idle", "tr_20", "test_mac5 [rx_idle -> idle : default / ]")
				/*---------------------------------------------------------*/



			/** state (rx_busy) enter executives **/
			FSM_STATE_ENTER_FORCED (6, "rx_busy", state6_enter_exec, "test_mac5 [rx_busy enter execs]")
				FSM_PROFILE_SECTION_IN ("test_mac5 [rx_busy enter execs]", state6_enter_exec)
				{
				rx_busy = 1;  //rx busy
				}
				FSM_PROFILE_SECTION_OUT (state6_enter_exec)

			/** state (rx_busy) exit executives **/
			FSM_STATE_EXIT_FORCED (6, "rx_busy", "test_mac5 [rx_busy exit execs]")


			/** state (rx_busy) transition processing **/
			FSM_TRANSIT_FORCE (1, state1_enter_exec, ;, "default", "", "rx_busy", "idle", "tr_24", "test_mac5 [rx_busy -> idle : default / ]")
				/*---------------------------------------------------------*/



			/** state (send_beacon) enter executives **/
			FSM_STATE_ENTER_FORCED (7, "send_beacon", state7_enter_exec, "test_mac5 [send_beacon enter execs]")
				FSM_PROFILE_SECTION_IN ("test_mac5 [send_beacon enter execs]", state7_enter_exec)
				{
				//create BS hello packet
				switch(beacon_num)
					{
				case 0:
					{
					pk=op_pk_create_fmt("node0_beacon");	
					op_pk_nfd_set(pk,"DEST",-1);
					op_pk_nfd_set(pk,"SRC",node_address);
					op_pk_nfd_set(pk, "Type", 10);  
					op_pk_nfd_set(pk, "beacon_slot", 5);  
					op_pk_nfd_set(pk, "csma_slot", 10);  
					op_pk_nfd_set(pk, "tdma_slot", 15);  
					op_pk_nfd_set(pk, "bind_csma_slot", 20);  
					op_pk_send(pk, instrm_to_low);
				}
				break;
				//slot_index=slot_index+4;
				/*beacon_slot_number++;
				if(beacon_slot_number%5 == 0)
					{
					beacon_slot_number=0;
					}
				else
					op_pk_destroy(pk);
				*/
				//sending is cycle(50ms)
				//op_intrpt_schedule_self(op_sim_time()+5,Beacon_code);  
				case 1:
					{ 
					pk= op_pk_create_fmt ("pco_beacon");
					op_pk_nfd_set(pk,"SRC" ,node_address);
					op_pk_nfd_set(pk,"DEST" ,dest_addr);
					op_pk_nfd_set(pk,"Type", 11);
					op_pk_send(pk,instrm_to_low);
					}
					break;
				default: ;
				}
				}
				FSM_PROFILE_SECTION_OUT (state7_enter_exec)

			/** state (send_beacon) exit executives **/
			FSM_STATE_EXIT_FORCED (7, "send_beacon", "test_mac5 [send_beacon exit execs]")


			/** state (send_beacon) transition processing **/
			FSM_TRANSIT_FORCE (1, state1_enter_exec, ;, "default", "", "send_beacon", "idle", "tr_22_1", "test_mac5 [send_beacon -> idle : default / ]")
				/*---------------------------------------------------------*/



			/** state (slot_control) enter executives **/
			FSM_STATE_ENTER_FORCED (8, "slot_control", state8_enter_exec, "test_mac5 [slot_control enter execs]")
				FSM_PROFILE_SECTION_IN ("test_mac5 [slot_control enter execs]", state8_enter_exec)
				{
				/*if(!op_subq_empty(1))
					{
					pkptr=op_subq_pk_remove(1,OPC_QPOS_HEAD);
					op_pk_send(pkptr,instrm_to_low);
				
					}
				   else;
				*/
				t=op_dist_uniform(150E-3);//150ms
				time=t*slot_time;
				if(slot_index>=0&&slot_index<beacon_slot1)
					op_intrpt_schedule_self(op_sim_time(),Beacon_code);
				
				if(slot_index>=beacon_slot1&&slot_index<csma_slot1)
				op_intrpt_schedule_self(op_sim_time()+time,send_csma);	
				 
				if(slot_index>=csma_slot1&&slot_index<tdma_slot1)
				op_intrpt_schedule_self(op_sim_time(),send_tdma);
				
				if(slot_index>=tdma_slot1&&slot_index<bind_csma_slot1)
				op_intrpt_schedule_self(op_sim_time()+time,bind_csma);	
				/*else if(slot_index == 3)
					{
					op_intrpt_schedule_self(op_sim_time()+slot_time,tdma_code);
					slot_index = -1;	
					}*/
				//if(slot_index>0)
				/*for(i=0;i<op_prg_list_size(slot_table);i++)
					{
					slot_str = op_prg_list_access(slot_table,i);
					if((slot_str->node_num == node_address) && (slot_str->slot_num == slot_index))
						{
						if(!op_subq_empty(0))
							{
							pkptr = op_subq_pk_remove(0,OPC_QPOS_HEAD);
							op_pk_send(pkptr,instrm_to_low);
							}
						else;
						}
					else;
					
					}
				*/
				slot_index++;
				if(slot_index == 20)
					{
					slot_index=0;
					}
				else;
				}
				FSM_PROFILE_SECTION_OUT (state8_enter_exec)

			/** state (slot_control) exit executives **/
			FSM_STATE_EXIT_FORCED (8, "slot_control", "test_mac5 [slot_control exit execs]")


			/** state (slot_control) transition processing **/
			FSM_TRANSIT_FORCE (1, state1_enter_exec, ;, "default", "", "slot_control", "idle", "tr_24_1", "test_mac5 [slot_control -> idle : default / ]")
				/*---------------------------------------------------------*/



			/** state (bind_csma) enter executives **/
			FSM_STATE_ENTER_FORCED (9, "bind_csma", state9_enter_exec, "test_mac5 [bind_csma enter execs]")
				FSM_PROFILE_SECTION_IN ("test_mac5 [bind_csma enter execs]", state9_enter_exec)
				{
				if(rx_busy == 0 )  //if channel is idle, send frame
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
				else
				{
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
				if(!op_subq_empty (0) )
				//	op_intrpt_schedule_self(op_sim_time() + 0.001 + FS_TIMES, FS); 
					op_intrpt_schedule_self(op_sim_time() + op_dist_uniform(FS_TIMES), bind_csma); 
				else;
					
				}
				
				op_intrpt_schedule_self(op_sim_time()+slot_time,slot_control);		
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
				FSM_PROFILE_SECTION_OUT (state9_enter_exec)

			/** state (bind_csma) exit executives **/
			FSM_STATE_EXIT_FORCED (9, "bind_csma", "test_mac5 [bind_csma exit execs]")


			/** state (bind_csma) transition processing **/
			FSM_TRANSIT_FORCE (1, state1_enter_exec, ;, "default", "", "bind_csma", "idle", "tr_26", "test_mac5 [bind_csma -> idle : default / ]")
				/*---------------------------------------------------------*/



			/** state (send_tdma) enter executives **/
			FSM_STATE_ENTER_FORCED (10, "send_tdma", state10_enter_exec, "test_mac5 [send_tdma enter execs]")
				FSM_PROFILE_SECTION_IN ("test_mac5 [send_tdma enter execs]", state10_enter_exec)
				{
				//if(slot_index>0)
				for(i=0;i<op_prg_list_size(slot_table);i++)
					{
					slot_str = op_prg_list_access(slot_table,i);
					if((slot_str->node_num == node_address) && (slot_str->slot_num == slot_index))
						{
						if(!op_subq_empty(0))
							{
							pkptr = op_subq_pk_remove(0,OPC_QPOS_HEAD);
							op_pk_send(pkptr,instrm_to_low);
							}
						else;
						}
					else;
					
					}
				op_intrpt_schedule_self(op_sim_time()+slot_time,slot_control);	
				//slot_index++;
				}
				FSM_PROFILE_SECTION_OUT (state10_enter_exec)

			/** state (send_tdma) exit executives **/
			FSM_STATE_EXIT_FORCED (10, "send_tdma", "test_mac5 [send_tdma exit execs]")


			/** state (send_tdma) transition processing **/
			FSM_TRANSIT_FORCE (1, state1_enter_exec, ;, "default", "", "send_tdma", "idle", "tr_29", "test_mac5 [send_tdma -> idle : default / ]")
				/*---------------------------------------------------------*/



			}


		FSM_EXIT (0,"test_mac5")
		}
	}




void
_op_test_mac5_diag (OP_SIM_CONTEXT_ARG_OPT)
	{
	/* No Diagnostic Block */
	}




void
_op_test_mac5_terminate (OP_SIM_CONTEXT_ARG_OPT)
	{

	FIN_MT (_op_test_mac5_terminate ())


	/* No Termination Block */

	Vos_Poolmem_Dealloc (op_sv_ptr);

	FOUT
	}


/* Undefine shortcuts to state variables to avoid */
/* syntax error in direct access to fields of */
/* local variable prs_ptr in _op_test_mac5_svar function. */
#undef node_id
#undef listen_times
#undef rx_busy
#undef time_buffer
#undef channel_status_value
#undef tx_busy
#undef node_address
#undef comm_dist
#undef dest_addr
#undef cycle_time
#undef beacon_num
#undef flag
#undef node_number
#undef record_node_list
#undef slot_table
#undef slot_index
#undef slot_number
#undef slot_assignment

#undef FIN_PREAMBLE_DEC
#undef FIN_PREAMBLE_CODE

#define FIN_PREAMBLE_DEC
#define FIN_PREAMBLE_CODE

VosT_Obtype
_op_test_mac5_init (int * init_block_ptr)
	{
	VosT_Obtype obtype = OPC_NIL;
	FIN_MT (_op_test_mac5_init (init_block_ptr))

	obtype = Vos_Define_Object_Prstate ("proc state vars (test_mac5)",
		sizeof (test_mac5_state));
	*init_block_ptr = 0;

	FRET (obtype)
	}

VosT_Address
_op_test_mac5_alloc (VosT_Obtype obtype, int init_block)
	{
#if !defined (VOSD_NO_FIN)
	int _op_block_origin = 0;
#endif
	test_mac5_state * ptr;
	FIN_MT (_op_test_mac5_alloc (obtype))

	ptr = (test_mac5_state *)Vos_Alloc_Object (obtype);
	if (ptr != OPC_NIL)
		{
		ptr->_op_current_block = init_block;
#if defined (OPD_ALLOW_ODB)
		ptr->_op_current_state = "test_mac5 [init enter execs]";
#endif
		}
	FRET ((VosT_Address)ptr)
	}



void
_op_test_mac5_svar (void * gen_ptr, const char * var_name, void ** var_p_ptr)
	{
	test_mac5_state		*prs_ptr;

	FIN_MT (_op_test_mac5_svar (gen_ptr, var_name, var_p_ptr))

	if (var_name == OPC_NIL)
		{
		*var_p_ptr = (void *)OPC_NIL;
		FOUT
		}
	prs_ptr = (test_mac5_state *)gen_ptr;

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
	if (strcmp ("rx_busy" , var_name) == 0)
		{
		*var_p_ptr = (void *) (&prs_ptr->rx_busy);
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
	if (strcmp ("tx_busy" , var_name) == 0)
		{
		*var_p_ptr = (void *) (&prs_ptr->tx_busy);
		FOUT
		}
	if (strcmp ("node_address" , var_name) == 0)
		{
		*var_p_ptr = (void *) (&prs_ptr->node_address);
		FOUT
		}
	if (strcmp ("comm_dist" , var_name) == 0)
		{
		*var_p_ptr = (void *) (&prs_ptr->comm_dist);
		FOUT
		}
	if (strcmp ("dest_addr" , var_name) == 0)
		{
		*var_p_ptr = (void *) (&prs_ptr->dest_addr);
		FOUT
		}
	if (strcmp ("cycle_time" , var_name) == 0)
		{
		*var_p_ptr = (void *) (&prs_ptr->cycle_time);
		FOUT
		}
	if (strcmp ("beacon_num" , var_name) == 0)
		{
		*var_p_ptr = (void *) (&prs_ptr->beacon_num);
		FOUT
		}
	if (strcmp ("flag" , var_name) == 0)
		{
		*var_p_ptr = (void *) (&prs_ptr->flag);
		FOUT
		}
	if (strcmp ("node_number" , var_name) == 0)
		{
		*var_p_ptr = (void *) (&prs_ptr->node_number);
		FOUT
		}
	if (strcmp ("record_node_list" , var_name) == 0)
		{
		*var_p_ptr = (void *) (&prs_ptr->record_node_list);
		FOUT
		}
	if (strcmp ("slot_table" , var_name) == 0)
		{
		*var_p_ptr = (void *) (&prs_ptr->slot_table);
		FOUT
		}
	if (strcmp ("slot_index" , var_name) == 0)
		{
		*var_p_ptr = (void *) (&prs_ptr->slot_index);
		FOUT
		}
	if (strcmp ("slot_number" , var_name) == 0)
		{
		*var_p_ptr = (void *) (&prs_ptr->slot_number);
		FOUT
		}
	if (strcmp ("slot_assignment" , var_name) == 0)
		{
		*var_p_ptr = (void *) (&prs_ptr->slot_assignment);
		FOUT
		}
	*var_p_ptr = (void *)OPC_NIL;

	FOUT
	}

