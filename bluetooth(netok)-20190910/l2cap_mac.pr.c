/* Process model C form file: l2cap_mac.pr.c */
/* Portions of this file copyright 1986-2008 by OPNET Technologies, Inc. */



/* This variable carries the header into the object file */
const char l2cap_mac_pr_c [] = "MIL_3_Tfile_Hdr_ 145A 30A modeler 7 5D750FE5 5D750FE5 1 USER-20151017SA Administrator 0 0 none none 0 0 none 0 0 0 0 0 0 0 0 1bcc 1                                                                                                                                                                                                                                                                                                                                                                                            ";
#include <string.h>



/* OPNET system definitions */
#include <opnet.h>



/* Header Block */

/*define symbolic constant*/
#define  instrm_from_low0 		0
#define  instrm_from_up 		1
#define  instrm_to_low0 		0
#define  instrm_to_up 			1
#define	 Time					100

#define	 back_off				0
#define	 send_frame				1000


#define	 FS						1//frame space
#define	 FS_TIMES				0.00006//frame space times 60 microsecond
#define	 RX_INSTAT 			    0
//#define  DATA_RATE				1000000     //bps


//cmh add
#define	 Beacon_code					500
#define  request_slot_resource_code     300
#define  SEND_BEACON		        (op_intrpt_type() == OPC_INTRPT_SELF && op_intrpt_code() == Beacon_code)
#define  REQUEST_SLOT_RESOURCE		(op_intrpt_type() == OPC_INTRPT_SELF && op_intrpt_code() == request_slot_resource_code)
#define  instrm_from_low2 		2
#define  instrm_to_low2 		2
#define  instrm_from_low3 		3
#define  instrm_to_low3 		3
#define  instrm_from_low4 		4
#define  instrm_to_low4 		4



#define  tdma_code              600
#define  slot_time              10E-3  //10ms
#define  csma_code              700
#define  send_code              800
/*define macros*/
#define LOW_ARVL 			(op_intrpt_type() == OPC_INTRPT_STRM && (op_intrpt_strm() == instrm_from_low0 || op_intrpt_strm() == instrm_from_low2 || op_intrpt_strm() == instrm_from_low3 || op_intrpt_strm() == instrm_from_low4 ))
#define UP_ARVL 			(op_intrpt_type() == OPC_INTRPT_STRM && op_intrpt_strm() == instrm_from_up)
#define SEND_TDMA 			(op_intrpt_type() == OPC_INTRPT_SELF && op_intrpt_code() == tdma_code)
#define SEND_CSMA 			(op_intrpt_type() == OPC_INTRPT_SELF && op_intrpt_code() == csma_code)
#define send			    (op_intrpt_type() == OPC_INTRPT_SELF && op_intrpt_code() == send_code)


#define TIME_BUFF 			(op_intrpt_type() == OPC_INTRPT_SELF && op_intrpt_code() == Time)

#define	RX_BUSY				((op_intrpt_type()== OPC_INTRPT_STAT) && (op_intrpt_stat () == RX_INSTAT ) && op_stat_local_read (RX_INSTAT) == 1.0)
#define	RX_IDLE				((op_intrpt_type()== OPC_INTRPT_STAT) && (op_intrpt_stat () == RX_INSTAT ) && op_stat_local_read (RX_INSTAT) == 0.0)


double	src_lat, src_long, src_alt, dest_lat, dest_long, dest_alt, x, y, z;

//cmh add
void op_pk_send2(Packet* pktptr, int stream_num);
typedef struct record_value
	{
	int UE_value;
	}record_value;

typedef struct slot_element
	{
	int node_num;
	int slot_num;
	int subcarrier_num;
	}slot_element;

record_value * str_lookup(int address); 
record_value* create_new_insert();

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
	double	                 		cycle_time                                      ;
	int	                    		dest_addr                                       ;
	int	                    		node_address                                    ;
	int	                    		n                                               ;
	List*	                  		record_UE_list                                  ;
	List*	                  		slot_table                                      ;
	int	                    		slot_index                                      ;
	int	                    		beacon_num                                      ;
	int	                    		flag                                            ;
	int	                    		slot_number                                     ;
	int	                    		slot_assignment                                 ;
	int	                    		sub_carrier_number                              ;
	} l2cap_mac_state;

#define node_id                 		op_sv_ptr->node_id
#define listen_times            		op_sv_ptr->listen_times
#define channel_busy            		op_sv_ptr->channel_busy
#define time_buffer             		op_sv_ptr->time_buffer
#define channel_status_value    		op_sv_ptr->channel_status_value
#define cycle_time              		op_sv_ptr->cycle_time
#define dest_addr               		op_sv_ptr->dest_addr
#define node_address            		op_sv_ptr->node_address
#define n                       		op_sv_ptr->n
#define record_UE_list          		op_sv_ptr->record_UE_list
#define slot_table              		op_sv_ptr->slot_table
#define slot_index              		op_sv_ptr->slot_index
#define beacon_num              		op_sv_ptr->beacon_num
#define flag                    		op_sv_ptr->flag
#define slot_number             		op_sv_ptr->slot_number
#define slot_assignment         		op_sv_ptr->slot_assignment
#define sub_carrier_number      		op_sv_ptr->sub_carrier_number

/* These macro definitions will define a local variable called	*/
/* "op_sv_ptr" in each function containing a FIN statement.	*/
/* This variable points to the state variable data structure,	*/
/* and can be used from a C debugger to display their values.	*/
#undef FIN_PREAMBLE_DEC
#undef FIN_PREAMBLE_CODE
#define FIN_PREAMBLE_DEC	l2cap_mac_state *op_sv_ptr;
#define FIN_PREAMBLE_CODE	\
		op_sv_ptr = ((l2cap_mac_state *)(OP_SIM_CONTEXT_PTR->_op_mod_state_ptr));


/* Function Block */

#if !defined (VOSD_NO_FIN)
enum { _op_block_origin = __LINE__ + 2};
#endif

/*void op_pk_send2(Packet* pktptr, int stream_num)
	{
	
	Packet* 	pk;
	
	FIN(op_pk_send2(pktptr, stream_num));

	//create and set MAC packet
	pk=op_pk_create_fmt("nbiot_mac");
	
	op_pk_nfd_set(pk,"DEST",dest_addr);
	op_pk_nfd_set(pk,"SRC",node_address);
	op_pk_nfd_set_pkt(pk, "DATA", pktptr);  //may fail
	op_pk_nfd_set(pk,"Message ID",5);
	op_pk_send(pk, stream_num);
	
//	listen_times = 0;
//	op_intrpt_schedule_self(op_sim_time()+FS_TIMES,FS);

	FOUT;
	}
*/

record_value * str_lookup(int address)  
{  
    int st_size, i;  
    record_value * st_str;  
    FIN(str_lookup(address));  
	
    st_size = op_prg_list_size(record_UE_list);  
    for(i=0; i<st_size; i++)  
	{  
        st_str = op_prg_list_access(record_UE_list, i);  
        if(st_str->UE_value == address)    
            FRET(st_str);  
	}  
    FRET(OPC_NIL);  
}


record_value* create_new_insert()
{
	record_value* st_str;
	/*create a new connect table entry*/
	st_str = (record_value *)op_prg_mem_alloc(sizeof(record_value)); 
	/*initializing variables*/
	st_str->UE_value = -1; 
	
	
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
	void l2cap_mac (OP_SIM_CONTEXT_ARG_OPT);
	VosT_Obtype _op_l2cap_mac_init (int * init_block_ptr);
	void _op_l2cap_mac_diag (OP_SIM_CONTEXT_ARG_OPT);
	void _op_l2cap_mac_terminate (OP_SIM_CONTEXT_ARG_OPT);
	VosT_Address _op_l2cap_mac_alloc (VosT_Obtype, int);
	void _op_l2cap_mac_svar (void *, const char *, void **);


#if defined (__cplusplus)
} /* end of 'extern "C"' */
#endif




/* Process model interrupt handling procedure */


void
l2cap_mac (OP_SIM_CONTEXT_ARG_OPT)
	{
#if !defined (VOSD_NO_FIN)
	int _op_block_origin = 0;
#endif
	FIN_MT (l2cap_mac ());

		{
		/* Temporary Variables */
		/*declare variables*/
		Packet*	pkptr;
		Packet*	pktptr;
		
		int 	dest,source,num=0;
		//double	cur_time;
		//double	*saved_time_ptr;
		
		//Objid	dest_id;
		//double	distance;
		
		Packet*	pk;
		int type;
		record_value* str;
		//int size;
		int i;
		//int a[5],b[5];
		
		slot_element* slot_str;
		double time;
		int t;
		int slot,sub_number;
		/* End of Temporary Variables */


		FSM_ENTER ("l2cap_mac")

		FSM_BLOCK_SWITCH
			{
			/*---------------------------------------------------------*/
			/** state (init) enter executives **/
			FSM_STATE_ENTER_FORCED_NOLABEL (0, "init", "l2cap_mac [init enter execs]")
				FSM_PROFILE_SECTION_IN ("l2cap_mac [init enter execs]", state0_enter_exec)
				{
				node_id = op_topo_parent(op_id_self());
				
				op_ima_obj_attr_get(node_id,"destination_address",&dest_addr);//get dest frome attributes;
				op_ima_obj_attr_get(node_id,"node_address",&node_address);
				record_UE_list = op_prg_list_create();//BS record the UE's address
				slot_table= op_prg_list_create();//create slot table
				
				n=0;
				cycle_time = 50E-3;//50ms
				if(node_address == 0)//BS
					op_intrpt_schedule_self(op_sim_time(),Beacon_code);
				else//UE
					op_intrpt_schedule_self(op_sim_time(),request_slot_resource_code);
				
				slot_index = 0;
				
				beacon_num =0;
				flag=0;//the lable to judge UE whether accrss BS or not
				slot_number=0;//time slot number
				
				slot_assignment=0;//the lable to judge UE whether get time slot
				
				sub_carrier_number=3;//subcarrier
				}
				FSM_PROFILE_SECTION_OUT (state0_enter_exec)

			/** state (init) exit executives **/
			FSM_STATE_EXIT_FORCED (0, "init", "l2cap_mac [init exit execs]")


			/** state (init) transition processing **/
			FSM_TRANSIT_FORCE (1, state1_enter_exec, ;, "default", "", "init", "idle", "tr_0", "l2cap_mac [init -> idle : default / ]")
				/*---------------------------------------------------------*/



			/** state (idle) enter executives **/
			FSM_STATE_ENTER_UNFORCED (1, "idle", state1_enter_exec, "l2cap_mac [idle enter execs]")

			/** blocking after enter executives of unforced state. **/
			FSM_EXIT (3,"l2cap_mac")


			/** state (idle) exit executives **/
			FSM_STATE_EXIT_UNFORCED (1, "idle", "l2cap_mac [idle exit execs]")


			/** state (idle) transition processing **/
			FSM_PROFILE_SECTION_IN ("l2cap_mac [idle trans conditions]", state1_trans_conds)
			FSM_INIT_COND (UP_ARVL)
			FSM_TEST_COND (LOW_ARVL)
			FSM_TEST_COND (SEND_BEACON)
			FSM_TEST_COND (RX_IDLE	)
			FSM_TEST_COND (RX_BUSY)
			FSM_TEST_COND (SEND_TDMA)
			FSM_TEST_COND (SEND_CSMA)
			FSM_TEST_COND (send)
			FSM_TEST_COND (REQUEST_SLOT_RESOURCE)
			FSM_DFLT_COND
			FSM_TEST_LOGIC ("idle")
			FSM_PROFILE_SECTION_OUT (state1_trans_conds)

			FSM_TRANSIT_SWITCH
				{
				FSM_CASE_TRANSIT (0, 2, state2_enter_exec, ;, "UP_ARVL", "", "idle", "upper_arvl", "tr_1", "l2cap_mac [idle -> upper_arvl : UP_ARVL / ]")
				FSM_CASE_TRANSIT (1, 3, state3_enter_exec, ;, "LOW_ARVL", "", "idle", "lower_arvl", "tr_10", "l2cap_mac [idle -> lower_arvl : LOW_ARVL / ]")
				FSM_CASE_TRANSIT (2, 4, state4_enter_exec, ;, "SEND_BEACON", "", "idle", "send_beacon", "tr_18", "l2cap_mac [idle -> send_beacon : SEND_BEACON / ]")
				FSM_CASE_TRANSIT (3, 5, state5_enter_exec, ;, "RX_IDLE	", "", "idle", "channel_idle", "tr_20", "l2cap_mac [idle -> channel_idle : RX_IDLE	 / ]")
				FSM_CASE_TRANSIT (4, 6, state6_enter_exec, ;, "RX_BUSY", "", "idle", "channel_busy", "tr_24", "l2cap_mac [idle -> channel_busy : RX_BUSY / ]")
				FSM_CASE_TRANSIT (5, 7, state7_enter_exec, ;, "SEND_TDMA", "", "idle", "tdma", "tr_25", "l2cap_mac [idle -> tdma : SEND_TDMA / ]")
				FSM_CASE_TRANSIT (6, 8, state8_enter_exec, ;, "SEND_CSMA", "", "idle", "csma", "tr_27", "l2cap_mac [idle -> csma : SEND_CSMA / ]")
				FSM_CASE_TRANSIT (7, 9, state9_enter_exec, ;, "send", "", "idle", "send_csma", "tr_30", "l2cap_mac [idle -> send_csma : send / ]")
				FSM_CASE_TRANSIT (8, 10, state10_enter_exec, ;, "REQUEST_SLOT_RESOURCE", "", "idle", "request_slot_resource", "tr_33", "l2cap_mac [idle -> request_slot_resource : REQUEST_SLOT_RESOURCE / ]")
				FSM_CASE_TRANSIT (9, 1, state1_enter_exec, ;, "default", "", "idle", "idle", "tr_14", "l2cap_mac [idle -> idle : default / ]")
				}
				/*---------------------------------------------------------*/



			/** state (upper_arvl) enter executives **/
			FSM_STATE_ENTER_FORCED (2, "upper_arvl", state2_enter_exec, "l2cap_mac [upper_arvl enter execs]")
				FSM_PROFILE_SECTION_IN ("l2cap_mac [upper_arvl enter execs]", state2_enter_exec)
				{
				//get pk from upper stream
				pkptr = op_pk_get(instrm_from_up);
				if(node_address != 0)
					{
					if (op_subq_pk_insert (1, pkptr, OPC_QPOS_TAIL) != OPC_QINS_OK)
						{
						//if the insertion failed, discard the packet 
						op_pk_destroy (pkptr);
						}  
					else;   
					}
				else
					op_pk_send(pkptr,instrm_to_low0);
				
				
				}
				FSM_PROFILE_SECTION_OUT (state2_enter_exec)

			/** state (upper_arvl) exit executives **/
			FSM_STATE_EXIT_FORCED (2, "upper_arvl", "l2cap_mac [upper_arvl exit execs]")


			/** state (upper_arvl) transition processing **/
			FSM_TRANSIT_FORCE (1, state1_enter_exec, ;, "default", "", "upper_arvl", "idle", "tr_2", "l2cap_mac [upper_arvl -> idle : default / ]")
				/*---------------------------------------------------------*/



			/** state (lower_arvl) enter executives **/
			FSM_STATE_ENTER_FORCED (3, "lower_arvl", state3_enter_exec, "l2cap_mac [lower_arvl enter execs]")
				FSM_PROFILE_SECTION_IN ("l2cap_mac [lower_arvl enter execs]", state3_enter_exec)
				{
				//get pk from lower stream
				pkptr = op_pk_get(op_intrpt_strm());
				
				op_pk_nfd_access(pkptr,"SRC",&source);
				op_pk_nfd_access(pkptr,"DEST",&dest);
				op_pk_nfd_access(pkptr,"Type",&type);
				
				switch(type)
					{
					case 10:  //receive BS beacon packet
						if(beacon_num == 0)
							{
							op_intrpt_schedule_self(op_sim_time()+slot_time,tdma_code);//when UE receives the beacon packet firstly,the slot_time starts.
							}
						else;
						beacon_num=1;
						if(flag == 0)
							{
							pk=op_pk_create_fmt("UE_request");	//in order to request access BS
							op_pk_nfd_set(pk,"DEST",source);
							op_pk_nfd_set(pk,"SRC",node_address);
							op_pk_nfd_set(pk, "Type", 15); 
							if (op_subq_pk_insert (0, pk, OPC_QPOS_TAIL) != OPC_QINS_OK)//put the packet into buffer0
								{
								//if the insertion failed, discard the packet 
								op_pk_destroy (pk);
								}  
							else; 
							op_intrpt_schedule_self(op_sim_time(),csma_code);
							}
						else//flag=1,UE has accessed BS
							op_pk_destroy (pkptr);		
					break;
					
					case 15://BS receive UE request packet
						if(node_address == dest)
						{
						str=str_lookup(source);	
						if(str == OPC_NIL)
							{
							str=create_new_insert();
							str->UE_value =source;
							op_prg_list_insert(record_UE_list,str,OPC_LISTPOS_TAIL);
							
							pk=op_pk_create_fmt("ack_information");//tell UE that it accessed BS successfully
							op_pk_nfd_set(pk,"DEST",source);
							op_pk_nfd_set(pk,"SRC",node_address);
							op_pk_nfd_set(pk,"Type",12);
							op_pk_send(pk, instrm_to_low0);
							}
						else;
						}
						else
							op_pk_destroy(pkptr);
					break;
								
					case 12://receive BS's ack information(UE has accessed BS)
						if(node_address == dest)
							{
							flag=1;
							op_subq_flush(0);//flush the queue 0
							}
						else
							op_pk_destroy(pkptr);
					break;
						
					case 11://BS receive request slot resource packet
						if(node_address == dest)
						{
						 pk=op_pk_create_fmt("uplink_assignment_message");
						 op_pk_nfd_set(pk,"DEST",source);
						 op_pk_nfd_set(pk,"SRC",node_address);
						 op_pk_nfd_set(pk,"Type",13);
						 op_pk_nfd_set(pk,"MS_access_identity",slot_number);
						 op_pk_nfd_set(pk,"PUSCH sub-carrier",sub_carrier_number);
						 op_pk_send(pk, instrm_to_low0);
						 slot_number++; 
						if(slot_number%4 == 0)
							{
							slot_number=0;
							sub_carrier_number++;
							}
						}
						else
							op_pk_destroy(pkptr);
					break;
					
					case 13://UE receive time_slot_assignment packet
						if(node_address == dest)
						{
						op_pk_nfd_get(pkptr,"MS_access_identity",&slot); 
						op_pk_nfd_get(pkptr,"PUSCH sub-carrier",&sub_number);
						slot_str = (slot_element*)op_prg_mem_alloc(sizeof(slot_element)); 
						slot_str->node_num = node_address;
						slot_str->slot_num = slot;
						slot_str->subcarrier_num = sub_number;
						op_prg_list_insert(slot_table,slot_str,OPC_LISTPOS_TAIL); 
						slot_assignment=1;
						op_subq_flush(0);//flush the queue 0
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
				FSM_PROFILE_SECTION_OUT (state3_enter_exec)

			/** state (lower_arvl) exit executives **/
			FSM_STATE_EXIT_FORCED (3, "lower_arvl", "l2cap_mac [lower_arvl exit execs]")


			/** state (lower_arvl) transition processing **/
			FSM_TRANSIT_FORCE (1, state1_enter_exec, ;, "default", "", "lower_arvl", "idle", "tr_11", "l2cap_mac [lower_arvl -> idle : default / ]")
				/*---------------------------------------------------------*/



			/** state (send_beacon) enter executives **/
			FSM_STATE_ENTER_FORCED (4, "send_beacon", state4_enter_exec, "l2cap_mac [send_beacon enter execs]")
				FSM_PROFILE_SECTION_IN ("l2cap_mac [send_beacon enter execs]", state4_enter_exec)
				{
				//create BS hello packet
				pk=op_pk_create_fmt("BS_beacon");	
				op_pk_nfd_set(pk,"DEST",-1);
				op_pk_nfd_set(pk,"SRC",node_address);
				op_pk_nfd_set(pk, "Type", 10);  
				op_pk_send(pk, instrm_to_low0);
				
				//sending is cycle(10ms)
				op_intrpt_schedule_self(op_sim_time()+cycle_time,Beacon_code);  
				}
				FSM_PROFILE_SECTION_OUT (state4_enter_exec)

			/** state (send_beacon) exit executives **/
			FSM_STATE_EXIT_FORCED (4, "send_beacon", "l2cap_mac [send_beacon exit execs]")


			/** state (send_beacon) transition processing **/
			FSM_TRANSIT_FORCE (1, state1_enter_exec, ;, "default", "", "send_beacon", "idle", "tr_19", "l2cap_mac [send_beacon -> idle : default / ]")
				/*---------------------------------------------------------*/



			/** state (channel_idle) enter executives **/
			FSM_STATE_ENTER_FORCED (5, "channel_idle", state5_enter_exec, "l2cap_mac [channel_idle enter execs]")
				FSM_PROFILE_SECTION_IN ("l2cap_mac [channel_idle enter execs]", state5_enter_exec)
				{
				channel_busy = 0;
				}
				FSM_PROFILE_SECTION_OUT (state5_enter_exec)

			/** state (channel_idle) exit executives **/
			FSM_STATE_EXIT_FORCED (5, "channel_idle", "l2cap_mac [channel_idle exit execs]")


			/** state (channel_idle) transition processing **/
			FSM_TRANSIT_FORCE (1, state1_enter_exec, ;, "default", "", "channel_idle", "idle", "tr_23", "l2cap_mac [channel_idle -> idle : default / ]")
				/*---------------------------------------------------------*/



			/** state (channel_busy) enter executives **/
			FSM_STATE_ENTER_FORCED (6, "channel_busy", state6_enter_exec, "l2cap_mac [channel_busy enter execs]")
				FSM_PROFILE_SECTION_IN ("l2cap_mac [channel_busy enter execs]", state6_enter_exec)
				{
				channel_busy = 1;
				}
				FSM_PROFILE_SECTION_OUT (state6_enter_exec)

			/** state (channel_busy) exit executives **/
			FSM_STATE_EXIT_FORCED (6, "channel_busy", "l2cap_mac [channel_busy exit execs]")


			/** state (channel_busy) transition processing **/
			FSM_TRANSIT_FORCE (1, state1_enter_exec, ;, "default", "", "channel_busy", "idle", "tr_22_1", "l2cap_mac [channel_busy -> idle : default / ]")
				/*---------------------------------------------------------*/



			/** state (tdma) enter executives **/
			FSM_STATE_ENTER_FORCED (7, "tdma", state7_enter_exec, "l2cap_mac [tdma enter execs]")
				FSM_PROFILE_SECTION_IN ("l2cap_mac [tdma enter execs]", state7_enter_exec)
				{
				if((slot_index>=0)&&(slot_index<=3))
					op_intrpt_schedule_self(op_sim_time()+slot_time,tdma_code);
				/*else if(slot_index == 3)
					{
					op_intrpt_schedule_self(op_sim_time()+slot_time,tdma_code);
					slot_index = -1;	
					}*/
				
				for(i=0;i<op_prg_list_size(slot_table);i++)
					{
					slot_str = op_prg_list_access(slot_table,i);
					if((slot_str->node_num == node_address) && (slot_str->slot_num == slot_index))
						{
						if(!op_subq_empty(1))
							{
							pkptr = op_subq_pk_remove(1,OPC_QPOS_HEAD);
							sub_number = slot_str->subcarrier_num;
							op_pk_send(pkptr,sub_number);
							}
						else;
						}
					else;
					
					}
				
				slot_index++;
				if(slot_index == 4)
					{
					slot_index=0;
					}
				else;
				}
				FSM_PROFILE_SECTION_OUT (state7_enter_exec)

			/** state (tdma) exit executives **/
			FSM_STATE_EXIT_FORCED (7, "tdma", "l2cap_mac [tdma exit execs]")


			/** state (tdma) transition processing **/
			FSM_TRANSIT_FORCE (1, state1_enter_exec, ;, "default", "", "tdma", "idle", "tr_26", "l2cap_mac [tdma -> idle : default / ]")
				/*---------------------------------------------------------*/



			/** state (csma) enter executives **/
			FSM_STATE_ENTER_FORCED (8, "csma", state8_enter_exec, "l2cap_mac [csma enter execs]")
				FSM_PROFILE_SECTION_IN ("l2cap_mac [csma enter execs]", state8_enter_exec)
				{
				if(channel_busy == 0)
					{
					if(!op_subq_empty (0))
						
						{
						t =(int)op_dist_uniform(4);
						time=t*slot_time;
						op_intrpt_schedule_self(op_sim_time()+time,send_code);
						//pktptr = op_subq_pk_remove (0, OPC_QPOS_HEAD);
					
						//op_pk_send(pktptr,instrm_to_low2);//send to stream 2 to low layer;
						}
					else;
					}
				else//channel_busy =1
					{
					if(!op_subq_empty (0))
						{
						op_intrpt_schedule_self(op_sim_time()+slot_time,csma_code);
						}
					}
				
				
				}
				FSM_PROFILE_SECTION_OUT (state8_enter_exec)

			/** state (csma) exit executives **/
			FSM_STATE_EXIT_FORCED (8, "csma", "l2cap_mac [csma exit execs]")


			/** state (csma) transition processing **/
			FSM_TRANSIT_FORCE (1, state1_enter_exec, ;, "default", "", "csma", "idle", "tr_29", "l2cap_mac [csma -> idle : default / ]")
				/*---------------------------------------------------------*/



			/** state (send_csma) enter executives **/
			FSM_STATE_ENTER_FORCED (9, "send_csma", state9_enter_exec, "l2cap_mac [send_csma enter execs]")
				FSM_PROFILE_SECTION_IN ("l2cap_mac [send_csma enter execs]", state9_enter_exec)
				{
				if(channel_busy == 0)
					{
					if(!op_subq_empty (0))
						{
						pktptr = op_subq_pk_remove (0, OPC_QPOS_HEAD);
						op_pk_send(pktptr,instrm_to_low2);
						}
					else;
					}
				else
					{
					if(!op_subq_empty (0))
						{
						op_intrpt_schedule_self(op_sim_time()+slot_time,csma_code);
						}
					}
				}
				FSM_PROFILE_SECTION_OUT (state9_enter_exec)

			/** state (send_csma) exit executives **/
			FSM_STATE_EXIT_FORCED (9, "send_csma", "l2cap_mac [send_csma exit execs]")


			/** state (send_csma) transition processing **/
			FSM_TRANSIT_FORCE (1, state1_enter_exec, ;, "default", "", "send_csma", "idle", "tr_31", "l2cap_mac [send_csma -> idle : default / ]")
				/*---------------------------------------------------------*/



			/** state (request_slot_resource) enter executives **/
			FSM_STATE_ENTER_FORCED (10, "request_slot_resource", state10_enter_exec, "l2cap_mac [request_slot_resource enter execs]")
				FSM_PROFILE_SECTION_IN ("l2cap_mac [request_slot_resource enter execs]", state10_enter_exec)
				{
				if((flag== 1) && (!op_subq_empty(1)))//request slot time
					{
					if(slot_assignment == 0)
						{	
						pk=op_pk_create_fmt("REQUEST_slot_resource");	
						op_pk_nfd_set(pk,"DEST",0);
						op_pk_nfd_set(pk,"SRC",node_address);
						op_pk_nfd_set(pk, "Type", 11);  
						if (op_subq_pk_insert (0, pk, OPC_QPOS_TAIL) != OPC_QINS_OK)//put the packet into buffer0
							{
							//if the insertion failed, discard the packet 
							op_pk_destroy (pk);
							}  
						else; 
						op_intrpt_schedule_self(op_sim_time(),csma_code);
						}
					else;//slot_assignment=1 this label UE has got time slot
				//		op_subq_flush(0);//flush the queue 0
					
					}
				else;
				op_intrpt_schedule_self(op_sim_time()+cycle_time,request_slot_resource_code);//cycle time=10ms  
				
					
					
					
					
				}
				FSM_PROFILE_SECTION_OUT (state10_enter_exec)

			/** state (request_slot_resource) exit executives **/
			FSM_STATE_EXIT_FORCED (10, "request_slot_resource", "l2cap_mac [request_slot_resource exit execs]")


			/** state (request_slot_resource) transition processing **/
			FSM_TRANSIT_FORCE (1, state1_enter_exec, ;, "default", "", "request_slot_resource", "idle", "tr_34", "l2cap_mac [request_slot_resource -> idle : default / ]")
				/*---------------------------------------------------------*/



			}


		FSM_EXIT (0,"l2cap_mac")
		}
	}




void
_op_l2cap_mac_diag (OP_SIM_CONTEXT_ARG_OPT)
	{
	/* No Diagnostic Block */
	}




void
_op_l2cap_mac_terminate (OP_SIM_CONTEXT_ARG_OPT)
	{

	FIN_MT (_op_l2cap_mac_terminate ())


	/* No Termination Block */

	Vos_Poolmem_Dealloc (op_sv_ptr);

	FOUT
	}


/* Undefine shortcuts to state variables to avoid */
/* syntax error in direct access to fields of */
/* local variable prs_ptr in _op_l2cap_mac_svar function. */
#undef node_id
#undef listen_times
#undef channel_busy
#undef time_buffer
#undef channel_status_value
#undef cycle_time
#undef dest_addr
#undef node_address
#undef n
#undef record_UE_list
#undef slot_table
#undef slot_index
#undef beacon_num
#undef flag
#undef slot_number
#undef slot_assignment
#undef sub_carrier_number

#undef FIN_PREAMBLE_DEC
#undef FIN_PREAMBLE_CODE

#define FIN_PREAMBLE_DEC
#define FIN_PREAMBLE_CODE

VosT_Obtype
_op_l2cap_mac_init (int * init_block_ptr)
	{
	VosT_Obtype obtype = OPC_NIL;
	FIN_MT (_op_l2cap_mac_init (init_block_ptr))

	obtype = Vos_Define_Object_Prstate ("proc state vars (l2cap_mac)",
		sizeof (l2cap_mac_state));
	*init_block_ptr = 0;

	FRET (obtype)
	}

VosT_Address
_op_l2cap_mac_alloc (VosT_Obtype obtype, int init_block)
	{
#if !defined (VOSD_NO_FIN)
	int _op_block_origin = 0;
#endif
	l2cap_mac_state * ptr;
	FIN_MT (_op_l2cap_mac_alloc (obtype))

	ptr = (l2cap_mac_state *)Vos_Alloc_Object (obtype);
	if (ptr != OPC_NIL)
		{
		ptr->_op_current_block = init_block;
#if defined (OPD_ALLOW_ODB)
		ptr->_op_current_state = "l2cap_mac [init enter execs]";
#endif
		}
	FRET ((VosT_Address)ptr)
	}



void
_op_l2cap_mac_svar (void * gen_ptr, const char * var_name, void ** var_p_ptr)
	{
	l2cap_mac_state		*prs_ptr;

	FIN_MT (_op_l2cap_mac_svar (gen_ptr, var_name, var_p_ptr))

	if (var_name == OPC_NIL)
		{
		*var_p_ptr = (void *)OPC_NIL;
		FOUT
		}
	prs_ptr = (l2cap_mac_state *)gen_ptr;

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
	if (strcmp ("cycle_time" , var_name) == 0)
		{
		*var_p_ptr = (void *) (&prs_ptr->cycle_time);
		FOUT
		}
	if (strcmp ("dest_addr" , var_name) == 0)
		{
		*var_p_ptr = (void *) (&prs_ptr->dest_addr);
		FOUT
		}
	if (strcmp ("node_address" , var_name) == 0)
		{
		*var_p_ptr = (void *) (&prs_ptr->node_address);
		FOUT
		}
	if (strcmp ("n" , var_name) == 0)
		{
		*var_p_ptr = (void *) (&prs_ptr->n);
		FOUT
		}
	if (strcmp ("record_UE_list" , var_name) == 0)
		{
		*var_p_ptr = (void *) (&prs_ptr->record_UE_list);
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
	if (strcmp ("sub_carrier_number" , var_name) == 0)
		{
		*var_p_ptr = (void *) (&prs_ptr->sub_carrier_number);
		FOUT
		}
	*var_p_ptr = (void *)OPC_NIL;

	FOUT
	}

