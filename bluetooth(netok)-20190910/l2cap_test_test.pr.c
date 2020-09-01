/* Process model C form file: l2cap_test_test.pr.c */
/* Portions of this file copyright 1986-2008 by OPNET Technologies, Inc. */



/* This variable carries the header into the object file */
const char l2cap_test_test_pr_c [] = "MIL_3_Tfile_Hdr_ 145A 30A modeler 7 5D71B965 5D71B965 1 USER-20151017SA Administrator 0 0 none none 0 0 none 0 0 0 0 0 0 0 0 1bcc 1                                                                                                                                                                                                                                                                                                                                                                                            ";
#include <string.h>



/* OPNET system definitions */
#include <opnet.h>



/* Header Block */

/*define symbolic constant*/
#define  instrm_from_low		0
#define  instrm_from_up 		1
#define  instrm_to_low		    0
#define  instrm_to_up 			1

//cmh add
#define	 beacon_code					500
#define  request_slot_resource_code     300
#define  csma_code                      800
#define  SEND_BEACON		        (op_intrpt_type() == OPC_INTRPT_SELF && op_intrpt_code() == beacon_code)
#define  SEND_CSMA		        (op_intrpt_type() == OPC_INTRPT_SELF && op_intrpt_code() == csma_code)
#define  acl_code              700

/*define macros*/
#define LOW_ARVL 			(op_intrpt_type() == OPC_INTRPT_STRM &&(op_intrpt_strm() == instrm_from_low  ))
#define UP_ARVL 			(op_intrpt_type() == OPC_INTRPT_STRM && op_intrpt_strm() == instrm_from_up)
#define	SEND_DATA			((op_intrpt_type()== OPC_INTRPT_SELF) && (op_intrpt_code () == acl_code) )




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
	double	                 		channel_status_value                            ;
	double	                 		cycle_time                                      ;
	int	                    		dest_addr                                       ;
	int	                    		node_address                                    ;
	int	                    		n                                               ;
	List*	                  		record_slave_list                               ;
	int	                    		beacon_num                                      ;
	int	                    		flag                                            ;
	int	                    		i                                               ;
	List*	                  		data_packet                                     ;
	List*	                  		record_node                                     ;
	List*	                  		slot_table                                      ;
	int	                    		node_number                                     ;
	int	                    		slot_number                                     ;
	int	                    		channel                                         ;
	int	                    		setout                                          ;
	List*	                  		record_node_list                                ;
	double	                 		MAC_address                                     ;
	} l2cap_test_test_state;

#define node_id                 		op_sv_ptr->node_id
#define listen_times            		op_sv_ptr->listen_times
#define channel_status_value    		op_sv_ptr->channel_status_value
#define cycle_time              		op_sv_ptr->cycle_time
#define dest_addr               		op_sv_ptr->dest_addr
#define node_address            		op_sv_ptr->node_address
#define n                       		op_sv_ptr->n
#define record_slave_list       		op_sv_ptr->record_slave_list
#define beacon_num              		op_sv_ptr->beacon_num
#define flag                    		op_sv_ptr->flag
#define i                       		op_sv_ptr->i
#define data_packet             		op_sv_ptr->data_packet
#define record_node             		op_sv_ptr->record_node
#define slot_table              		op_sv_ptr->slot_table
#define node_number             		op_sv_ptr->node_number
#define slot_number             		op_sv_ptr->slot_number
#define channel                 		op_sv_ptr->channel
#define setout                  		op_sv_ptr->setout
#define record_node_list        		op_sv_ptr->record_node_list
#define MAC_address             		op_sv_ptr->MAC_address

/* These macro definitions will define a local variable called	*/
/* "op_sv_ptr" in each function containing a FIN statement.	*/
/* This variable points to the state variable data structure,	*/
/* and can be used from a C debugger to display their values.	*/
#undef FIN_PREAMBLE_DEC
#undef FIN_PREAMBLE_CODE
#define FIN_PREAMBLE_DEC	l2cap_test_test_state *op_sv_ptr;
#define FIN_PREAMBLE_CODE	\
		op_sv_ptr = ((l2cap_test_test_state *)(OP_SIM_CONTEXT_PTR->_op_mod_state_ptr));


/* Function Block */

#if !defined (VOSD_NO_FIN)
enum { _op_block_origin = __LINE__ + 2};
#endif



/*record_value * str_lookup(int address)  
{  
    int st_size, i;  
    record_value * st_str;  
    FIN(str_lookup(address));  
	
    st_size = op_prg_list_size(record_slave_list);  
    for(i=0; i<st_size; i++)  
	{  
        st_str = op_prg_list_access(record_slave_list, i);  
        if(st_str->SLAVE_value == address)    
            FRET(st_str);  
	}  
    FRET(OPC_NIL);  
}


record_value* create_new_insert()
{
	record_value* st_str;
	/*create a new connect table entry*/
	//st_str = (record_value *)op_prg_mem_alloc(sizeof(record_value)); 
	/*initializing variables*/
	//st_str->SLAVE_value = -1; 
	
	
	//return st_str;
//}

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
	void l2cap_test_test (OP_SIM_CONTEXT_ARG_OPT);
	VosT_Obtype _op_l2cap_test_test_init (int * init_block_ptr);
	void _op_l2cap_test_test_diag (OP_SIM_CONTEXT_ARG_OPT);
	void _op_l2cap_test_test_terminate (OP_SIM_CONTEXT_ARG_OPT);
	VosT_Address _op_l2cap_test_test_alloc (VosT_Obtype, int);
	void _op_l2cap_test_test_svar (void *, const char *, void **);


#if defined (__cplusplus)
} /* end of 'extern "C"' */
#endif




/* Process model interrupt handling procedure */


void
l2cap_test_test (OP_SIM_CONTEXT_ARG_OPT)
	{
#if !defined (VOSD_NO_FIN)
	int _op_block_origin = 0;
#endif
	FIN_MT (l2cap_test_test ());

		{
		/* Temporary Variables */
		/*declare variables*/
		Packet*	pkptr;
		
		int 	dest,source;
		Packet*	pk;
		Packet* bt;
		int type;
		//double t;
		
		
		/* End of Temporary Variables */


		FSM_ENTER ("l2cap_test_test")

		FSM_BLOCK_SWITCH
			{
			/*---------------------------------------------------------*/
			/** state (init) enter executives **/
			FSM_STATE_ENTER_FORCED_NOLABEL (0, "init", "l2cap_test_test [init enter execs]")
				FSM_PROFILE_SECTION_IN ("l2cap_test_test [init enter execs]", state0_enter_exec)
				{
				node_id = op_topo_parent(op_id_self());
				
				op_ima_obj_attr_get(node_id,"destination_address",&dest_addr);//get dest frome attributes;
				op_ima_obj_attr_get(node_id,"MAC_address",&MAC_address);
				op_ima_obj_attr_get(node_id,"node_address",&node_address);
				
				//record_slave_list = op_prg_list_create();
				cycle_time = 500E-3;//50ms
				flag=0;
				if(node_address!=0)
				  {
				beacon_num=0;
				setout=1;
				channel=0;
				record_node_list=op_prg_list_create();
				slot_table=op_prg_list_create();
				node_number=1;
				op_intrpt_schedule_self(op_sim_time(),csma_code);
				
				};
				
				}
				FSM_PROFILE_SECTION_OUT (state0_enter_exec)

			/** state (init) exit executives **/
			FSM_STATE_EXIT_FORCED (0, "init", "l2cap_test_test [init exit execs]")


			/** state (init) transition processing **/
			FSM_TRANSIT_FORCE (1, state1_enter_exec, ;, "default", "", "init", "idle", "tr_0", "l2cap_test_test [init -> idle : default / ]")
				/*---------------------------------------------------------*/



			/** state (idle) enter executives **/
			FSM_STATE_ENTER_UNFORCED (1, "idle", state1_enter_exec, "l2cap_test_test [idle enter execs]")

			/** blocking after enter executives of unforced state. **/
			FSM_EXIT (3,"l2cap_test_test")


			/** state (idle) exit executives **/
			FSM_STATE_EXIT_UNFORCED (1, "idle", "l2cap_test_test [idle exit execs]")


			/** state (idle) transition processing **/
			FSM_PROFILE_SECTION_IN ("l2cap_test_test [idle trans conditions]", state1_trans_conds)
			FSM_INIT_COND (UP_ARVL)
			FSM_TEST_COND (LOW_ARVL)
			FSM_TEST_COND (SEND_BEACON)
			FSM_TEST_COND (SEND_DATA)
			FSM_TEST_COND (SEND_CSMA)
			FSM_DFLT_COND
			FSM_TEST_LOGIC ("idle")
			FSM_PROFILE_SECTION_OUT (state1_trans_conds)

			FSM_TRANSIT_SWITCH
				{
				FSM_CASE_TRANSIT (0, 2, state2_enter_exec, ;, "UP_ARVL", "", "idle", "upper_arvl", "tr_1", "l2cap_test_test [idle -> upper_arvl : UP_ARVL / ]")
				FSM_CASE_TRANSIT (1, 3, state3_enter_exec, ;, "LOW_ARVL", "", "idle", "lower_arvl", "tr_10", "l2cap_test_test [idle -> lower_arvl : LOW_ARVL / ]")
				FSM_CASE_TRANSIT (2, 4, state4_enter_exec, ;, "SEND_BEACON", "", "idle", "send_beacon", "tr_18", "l2cap_test_test [idle -> send_beacon : SEND_BEACON / ]")
				FSM_CASE_TRANSIT (3, 5, state5_enter_exec, ;, "SEND_DATA", "", "idle", "DATA_SEND", "tr_20", "l2cap_test_test [idle -> DATA_SEND : SEND_DATA / ]")
				FSM_CASE_TRANSIT (4, 6, state6_enter_exec, ;, "SEND_CSMA", "", "idle", "bind_csma", "tr_25", "l2cap_test_test [idle -> bind_csma : SEND_CSMA / ]")
				FSM_CASE_TRANSIT (5, 1, state1_enter_exec, ;, "default", "", "idle", "idle", "tr_14", "l2cap_test_test [idle -> idle : default / ]")
				}
				/*---------------------------------------------------------*/



			/** state (upper_arvl) enter executives **/
			FSM_STATE_ENTER_FORCED (2, "upper_arvl", state2_enter_exec, "l2cap_test_test [upper_arvl enter execs]")
				FSM_PROFILE_SECTION_IN ("l2cap_test_test [upper_arvl enter execs]", state2_enter_exec)
				{
				//get pk from upper stream
				pkptr = op_pk_get(instrm_from_up);
				op_pk_send(pkptr,instrm_to_low);
				
				
				
				}
				FSM_PROFILE_SECTION_OUT (state2_enter_exec)

			/** state (upper_arvl) exit executives **/
			FSM_STATE_EXIT_FORCED (2, "upper_arvl", "l2cap_test_test [upper_arvl exit execs]")


			/** state (upper_arvl) transition processing **/
			FSM_TRANSIT_FORCE (1, state1_enter_exec, ;, "default", "", "upper_arvl", "idle", "tr_2", "l2cap_test_test [upper_arvl -> idle : default / ]")
				/*---------------------------------------------------------*/



			/** state (lower_arvl) enter executives **/
			FSM_STATE_ENTER_FORCED (3, "lower_arvl", state3_enter_exec, "l2cap_test_test [lower_arvl enter execs]")
				FSM_PROFILE_SECTION_IN ("l2cap_test_test [lower_arvl enter execs]", state3_enter_exec)
				{
				//get pk from lower stream
				//if((op_q_empty (0) == OPC_FALSE))
					//{
				if(op_stat_local_read(CH_BUSY_STAT)==0))
					{
				pkptr = op_pk_get(instrm_from_low);
				op_pk_nfd_access(pkptr,"SRC",&source);
				op_pk_nfd_access(pkptr,"DEST",&dest);
				op_pk_nfd_access(pkptr,"Type",&type);}
				//op_subq_pk_insert (0, pkptr, OPC_QPOS_HEAD);
				//};
				switch(type)
					{
					case 10 :{
					if(node_address==0)
					{
					//op_subq_pk_access (0, OPC_QPOS_HEAD);
					pk=op_pk_create_fmt("rest");	
					op_pk_nfd_set(pk,"DEST",source);
					op_pk_nfd_set(pk,"SRC",node_address);
					op_pk_nfd_set(pk, "Type", 15);
					if(op_stat_local_read(CH_BUSY_STAT)==0))
					{
					op_pk_send(pk,instrm_to_low);
					}
					//op_subq_pk_insert(0,pk,OPC_QPOS_HEAD);
					//_pk_send(pk,instrm_to_low);}
					else op_pk_destroy(pkptr);
					break;};
					case 15 :
					{//op_subq_pk_remove(0,OPC_QPOS_HEAD);
					if(node_address==dest&&node_address!=0)
					{ //if(op_stat_local_read(CH_BUSY_STAT)==0))
					flag=1;
					//if(!op_strm_empty (0);
						//op_subq_pk_remove(0,,OPC_QPOS_HEAD)
					pk=op_pk_create_fmt("re_ack");	//in order to request access node0
					op_pk_nfd_set(pk,"DEST",source);
					op_pk_nfd_set(pk,"SRC",node_address);
					op_pk_nfd_set(pk, "Type", 20);
					if(op_stat_local_read(CH_BUSY_STAT)==0))
					{
					op_pk_send(pk,instrm_to_low);}
				else 
					op_subq_pk_insert(0,pk,OPC_QPOS_HEAD);
				}
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
					if(op_stat_local_read(CH_BUSY_STAT)==0))
					op_pk_send(pk,instrm_to_low);}
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
					op_intrpt_schedule_self(op_sim_time(),acl_code);
					}
					else
					op_pk_destroy(pkptr);
				    break;};
					case 100 :
					{
					if(node_address==0)
						{
				//	n=op_prg_list_size(record_node_list);
					op_pk_send(pkptr,instrm_to_up);
					bt=op_pk_create_fmt("data");	
					op_pk_nfd_set(bt,"DEST",source);
					op_pk_nfd_set(bt,"SRC",0);
					op_pk_nfd_set(bt, "Type", 150);	
					if(op_stat_local_read(CH_BUSY_STAT)==0))
					{
					op_pk_send(pk,instrm_to_low);}
				else 
					op_subq_pk_insert(0,pk,OPC_QPOS_HEAD);
					
						}
					else 
						op_pk_destroy(pkptr);break;};
					case 150 :
					{
						if(node_address==dest&&node_address!=0)
							{
							op_intrpt_schedule_self(op_sim_time(),acl_code);
							op_pk_destroy(pkptr);
							//op_intrpt_schedule_self(op_sim_time(),acl_code);
							};break;};
					}
				
				
				
				}
				FSM_PROFILE_SECTION_OUT (state3_enter_exec)

			/** state (lower_arvl) exit executives **/
			FSM_STATE_EXIT_FORCED (3, "lower_arvl", "l2cap_test_test [lower_arvl exit execs]")


			/** state (lower_arvl) transition processing **/
			FSM_TRANSIT_FORCE (1, state1_enter_exec, ;, "default", "", "lower_arvl", "idle", "tr_11", "l2cap_test_test [lower_arvl -> idle : default / ]")
				/*---------------------------------------------------------*/



			/** state (send_beacon) enter executives **/
			FSM_STATE_ENTER_FORCED (4, "send_beacon", state4_enter_exec, "l2cap_test_test [send_beacon enter execs]")
				FSM_PROFILE_SECTION_IN ("l2cap_test_test [send_beacon enter execs]", state4_enter_exec)
				{
				//create MASTER hello packet
				//if(flag==0)
				//if(op_stat_local_read(CH_BUSY_STAT)==0))
				pk=op_pk_create_fmt("MS_beacon");	
				op_pk_nfd_set(pk,"DEST",0);
				op_pk_nfd_set(pk,"SRC",node_address);
				op_pk_nfd_set(pk, "Type", 10);  
				op_pk_send(pk, instrm_to_low);
				
				
				}
				FSM_PROFILE_SECTION_OUT (state4_enter_exec)

			/** state (send_beacon) exit executives **/
			FSM_STATE_EXIT_FORCED (4, "send_beacon", "l2cap_test_test [send_beacon exit execs]")


			/** state (send_beacon) transition processing **/
			FSM_TRANSIT_FORCE (1, state1_enter_exec, ;, "default", "", "send_beacon", "idle", "tr_19", "l2cap_test_test [send_beacon -> idle : default / ]")
				/*---------------------------------------------------------*/



			/** state (DATA_SEND) enter executives **/
			FSM_STATE_ENTER_FORCED (5, "DATA_SEND", state5_enter_exec, "l2cap_test_test [DATA_SEND enter execs]")
				FSM_PROFILE_SECTION_IN ("l2cap_test_test [DATA_SEND enter execs]", state5_enter_exec)
				{
				
					op_prg_list_init(record_node_list);
					//pf=fopen("node_address.txt","a+");
					//&source=op_prg_list_access(record_node_list,OPC_LISTPOS_TAIL);
					bt=op_pk_create_fmt("data_slave");	
					op_pk_nfd_set(bt,"DEST",0);
					op_pk_nfd_set(bt,"SRC",node_address);
					op_pk_nfd_set(bt, "Type", 100);
				    op_pk_send(bt,instrm_to_low);
					op_prg_list_size(record_node_list);
				
				}
				FSM_PROFILE_SECTION_OUT (state5_enter_exec)

			/** state (DATA_SEND) exit executives **/
			FSM_STATE_EXIT_FORCED (5, "DATA_SEND", "l2cap_test_test [DATA_SEND exit execs]")


			/** state (DATA_SEND) transition processing **/
			FSM_TRANSIT_FORCE (1, state1_enter_exec, ;, "default", "", "DATA_SEND", "idle", "tr_23", "l2cap_test_test [DATA_SEND -> idle : default / ]")
				/*---------------------------------------------------------*/



			/** state (bind_csma) enter executives **/
			FSM_STATE_ENTER_FORCED (6, "bind_csma", state6_enter_exec, "l2cap_test_test [bind_csma enter execs]")
				FSM_PROFILE_SECTION_IN ("l2cap_test_test [bind_csma enter execs]", state6_enter_exec)
				{
				if(channel==0&&setout==1)
					{op_intrpt_schedule_self(op_sim_time()+cycle_time,beacon_code);}
				
				
				}
				FSM_PROFILE_SECTION_OUT (state6_enter_exec)

			/** state (bind_csma) exit executives **/
			FSM_STATE_EXIT_FORCED (6, "bind_csma", "l2cap_test_test [bind_csma exit execs]")


			/** state (bind_csma) transition processing **/
			FSM_TRANSIT_FORCE (1, state1_enter_exec, ;, "default", "", "bind_csma", "idle", "tr_26", "l2cap_test_test [bind_csma -> idle : default / ]")
				/*---------------------------------------------------------*/



			}


		FSM_EXIT (0,"l2cap_test_test")
		}
	}




void
_op_l2cap_test_test_diag (OP_SIM_CONTEXT_ARG_OPT)
	{
	/* No Diagnostic Block */
	}




void
_op_l2cap_test_test_terminate (OP_SIM_CONTEXT_ARG_OPT)
	{

	FIN_MT (_op_l2cap_test_test_terminate ())


	/* No Termination Block */

	Vos_Poolmem_Dealloc (op_sv_ptr);

	FOUT
	}


/* Undefine shortcuts to state variables to avoid */
/* syntax error in direct access to fields of */
/* local variable prs_ptr in _op_l2cap_test_test_svar function. */
#undef node_id
#undef listen_times
#undef channel_status_value
#undef cycle_time
#undef dest_addr
#undef node_address
#undef n
#undef record_slave_list
#undef beacon_num
#undef flag
#undef i
#undef data_packet
#undef record_node
#undef slot_table
#undef node_number
#undef slot_number
#undef channel
#undef setout
#undef record_node_list
#undef MAC_address

#undef FIN_PREAMBLE_DEC
#undef FIN_PREAMBLE_CODE

#define FIN_PREAMBLE_DEC
#define FIN_PREAMBLE_CODE

VosT_Obtype
_op_l2cap_test_test_init (int * init_block_ptr)
	{
	VosT_Obtype obtype = OPC_NIL;
	FIN_MT (_op_l2cap_test_test_init (init_block_ptr))

	obtype = Vos_Define_Object_Prstate ("proc state vars (l2cap_test_test)",
		sizeof (l2cap_test_test_state));
	*init_block_ptr = 0;

	FRET (obtype)
	}

VosT_Address
_op_l2cap_test_test_alloc (VosT_Obtype obtype, int init_block)
	{
#if !defined (VOSD_NO_FIN)
	int _op_block_origin = 0;
#endif
	l2cap_test_test_state * ptr;
	FIN_MT (_op_l2cap_test_test_alloc (obtype))

	ptr = (l2cap_test_test_state *)Vos_Alloc_Object (obtype);
	if (ptr != OPC_NIL)
		{
		ptr->_op_current_block = init_block;
#if defined (OPD_ALLOW_ODB)
		ptr->_op_current_state = "l2cap_test_test [init enter execs]";
#endif
		}
	FRET ((VosT_Address)ptr)
	}



void
_op_l2cap_test_test_svar (void * gen_ptr, const char * var_name, void ** var_p_ptr)
	{
	l2cap_test_test_state		*prs_ptr;

	FIN_MT (_op_l2cap_test_test_svar (gen_ptr, var_name, var_p_ptr))

	if (var_name == OPC_NIL)
		{
		*var_p_ptr = (void *)OPC_NIL;
		FOUT
		}
	prs_ptr = (l2cap_test_test_state *)gen_ptr;

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
	if (strcmp ("record_slave_list" , var_name) == 0)
		{
		*var_p_ptr = (void *) (&prs_ptr->record_slave_list);
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
	if (strcmp ("i" , var_name) == 0)
		{
		*var_p_ptr = (void *) (&prs_ptr->i);
		FOUT
		}
	if (strcmp ("data_packet" , var_name) == 0)
		{
		*var_p_ptr = (void *) (&prs_ptr->data_packet);
		FOUT
		}
	if (strcmp ("record_node" , var_name) == 0)
		{
		*var_p_ptr = (void *) (&prs_ptr->record_node);
		FOUT
		}
	if (strcmp ("slot_table" , var_name) == 0)
		{
		*var_p_ptr = (void *) (&prs_ptr->slot_table);
		FOUT
		}
	if (strcmp ("node_number" , var_name) == 0)
		{
		*var_p_ptr = (void *) (&prs_ptr->node_number);
		FOUT
		}
	if (strcmp ("slot_number" , var_name) == 0)
		{
		*var_p_ptr = (void *) (&prs_ptr->slot_number);
		FOUT
		}
	if (strcmp ("channel" , var_name) == 0)
		{
		*var_p_ptr = (void *) (&prs_ptr->channel);
		FOUT
		}
	if (strcmp ("setout" , var_name) == 0)
		{
		*var_p_ptr = (void *) (&prs_ptr->setout);
		FOUT
		}
	if (strcmp ("record_node_list" , var_name) == 0)
		{
		*var_p_ptr = (void *) (&prs_ptr->record_node_list);
		FOUT
		}
	if (strcmp ("MAC_address" , var_name) == 0)
		{
		*var_p_ptr = (void *) (&prs_ptr->MAC_address);
		FOUT
		}
	*var_p_ptr = (void *)OPC_NIL;

	FOUT
	}

