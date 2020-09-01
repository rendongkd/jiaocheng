/* Process model C form file: test.pr.c */
/* Portions of this file copyright 1986-2008 by OPNET Technologies, Inc. */



/* This variable carries the header into the object file */
const char test_pr_c [] = "MIL_3_Tfile_Hdr_ 145A 30A modeler 7 5D67D67A 5D67D67A 1 USER-20151017SA Administrator 0 0 none none 0 0 none 0 0 0 0 0 0 0 0 1bcc 1                                                                                                                                                                                                                                                                                                                                                                                            ";
#include <string.h>



/* OPNET system definitions */
#include <opnet.h>



/* Header Block */

#define	 beacon_code			250
#define LOW_ARVL 			(op_intrpt_type() == OPC_INTRPT_STRM && (op_intrpt_strm() == instrm_from_low())
#define UP_ARVL 			(op_intrpt_type() == OPC_INTRPT_STRM && op_intrpt_strm() == instrm_from_up)#define  instrm_from_low 		0
#define  instrm_from_up 		1
#define  instrm_to_up 			1
#define  instrm_to_low 		    0
#include <stdio.h>
#include <stdlib.h>

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
	int	                    		node_id                                         ;
	int	                    		dest_addr                                       ;
	int	                    		node_address                                    ;
	double	                 		cycle_time                                      ;
	} test_state;

#define node_id                 		op_sv_ptr->node_id
#define dest_addr               		op_sv_ptr->dest_addr
#define node_address            		op_sv_ptr->node_address
#define cycle_time              		op_sv_ptr->cycle_time

/* These macro definitions will define a local variable called	*/
/* "op_sv_ptr" in each function containing a FIN statement.	*/
/* This variable points to the state variable data structure,	*/
/* and can be used from a C debugger to display their values.	*/
#undef FIN_PREAMBLE_DEC
#undef FIN_PREAMBLE_CODE
#define FIN_PREAMBLE_DEC	test_state *op_sv_ptr;
#define FIN_PREAMBLE_CODE	\
		op_sv_ptr = ((test_state *)(OP_SIM_CONTEXT_PTR->_op_mod_state_ptr));


/* No Function Block */

#if !defined (VOSD_NO_FIN)
enum { _op_block_origin = __LINE__ };
#endif

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
	void test (OP_SIM_CONTEXT_ARG_OPT);
	VosT_Obtype _op_test_init (int * init_block_ptr);
	void _op_test_diag (OP_SIM_CONTEXT_ARG_OPT);
	void _op_test_terminate (OP_SIM_CONTEXT_ARG_OPT);
	VosT_Address _op_test_alloc (VosT_Obtype, int);
	void _op_test_svar (void *, const char *, void **);


#if defined (__cplusplus)
} /* end of 'extern "C"' */
#endif




/* Process model interrupt handling procedure */


void
test (OP_SIM_CONTEXT_ARG_OPT)
	{
#if !defined (VOSD_NO_FIN)
	int _op_block_origin = 0;
#endif
	FIN_MT (test ());

		{
		/* Temporary Variables */
		Packet*	pkptr;
		
		Packet* pk;
		
		int 	dest,source,type,num=0;
		/* End of Temporary Variables */


		FSM_ENTER ("test")

		FSM_BLOCK_SWITCH
			{
			/*---------------------------------------------------------*/
			/** state (init) enter executives **/
			FSM_STATE_ENTER_FORCED_NOLABEL (0, "init", "test [init enter execs]")
				FSM_PROFILE_SECTION_IN ("test [init enter execs]", state0_enter_exec)
				{
				node_id = op_topo_parent(op_id_self());
				op_ima_obj_attr_get(node_id,"destination_address",&dest_addr);
				op_ima_obj_attr_get(node_id,"node_address",&node_address);
				//record_slaves_list = op_prg_list_create();
				cycle_time = 50E-3;//50ms
				
				op_intrpt_schedule_self(op_sim_time()+cycle_time,beacon_code);  
				
				
				
				
				
				
				}
				FSM_PROFILE_SECTION_OUT (state0_enter_exec)

			/** state (init) exit executives **/
			FSM_STATE_EXIT_FORCED (0, "init", "test [init exit execs]")


			/** state (init) transition processing **/
			FSM_TRANSIT_FORCE (3, state3_enter_exec, ;, "default", "", "init", "wait", "tr_0", "test [init -> wait : default / ]")
				/*---------------------------------------------------------*/



			/** state (send_beacon) enter executives **/
			FSM_STATE_ENTER_FORCED (1, "send_beacon", state1_enter_exec, "test [send_beacon enter execs]")
				FSM_PROFILE_SECTION_IN ("test [send_beacon enter execs]", state1_enter_exec)
				{
				//create radio hello
				pk=op_pk_create_fmt("hello");	
				op_pk_nfd_set(hello,"DEST",-1);
				op_pk_nfd_set(hello,"SRC",node_address);
				op_pk_nfd_set(hello, "Type", 10);  
				op_pk_send(hello, instrm_to_low);
				
				beacon_count++;
				op_intrpt_schedule_self(op_sim_time()+cycle_time,hello_code);  
				}
				FSM_PROFILE_SECTION_OUT (state1_enter_exec)

			/** state (send_beacon) exit executives **/
			FSM_STATE_EXIT_FORCED (1, "send_beacon", "test [send_beacon exit execs]")


			/** state (send_beacon) transition processing **/
			FSM_TRANSIT_FORCE (3, state3_enter_exec, ;, "default", "", "send_beacon", "wait", "tr_4", "test [send_beacon -> wait : default / ]")
				/*---------------------------------------------------------*/



			/** state (low_arvl) enter executives **/
			FSM_STATE_ENTER_FORCED (2, "low_arvl", state2_enter_exec, "test [low_arvl enter execs]")
				FSM_PROFILE_SECTION_IN ("test [low_arvl enter execs]", state2_enter_exec)
				{
				//get  packet from lower stream
				pkptr = op_pk_get(instrm_from_low);
				
				op_pk_nfd_access(pkptr,"SRC",&source);
				op_pk_nfd_access(pkptr,"DEST",&dest);
				op_pk_nfd_access(pkptr,"Type",&type);
				
				if(type==10)
					{
					  //receive master hello packet
				pk=op_pk_create_fmt("hello");	
				op_pk_nfd_set(rst,"DEST",source);
				op_pk_nfd_set(rst,"SRC",node_address);
				op_pk_nfd_set(rst, "Type", 10);
				op_pk_send(pkptr,instrm_to_low);
				
						else;
						op_pk_destroy(pkptr);
						
				}
				FSM_PROFILE_SECTION_OUT (state2_enter_exec)

			/** state (low_arvl) exit executives **/
			FSM_STATE_EXIT_FORCED (2, "low_arvl", "test [low_arvl exit execs]")


			/** state (low_arvl) transition processing **/
			FSM_TRANSIT_FORCE (3, state3_enter_exec, ;, "default", "", "low_arvl", "wait", "tr_2", "test [low_arvl -> wait : default / ]")
				/*---------------------------------------------------------*/



			/** state (wait) enter executives **/
			FSM_STATE_ENTER_UNFORCED (3, "wait", state3_enter_exec, "test [wait enter execs]")

			/** blocking after enter executives of unforced state. **/
			FSM_EXIT (7,"test")


			/** state (wait) exit executives **/
			FSM_STATE_EXIT_UNFORCED (3, "wait", "test [wait exit execs]")


			/** state (wait) transition processing **/
			FSM_PROFILE_SECTION_IN ("test [wait trans conditions]", state3_trans_conds)
			FSM_INIT_COND ((1))
			FSM_TEST_COND ((1))
			FSM_TEST_LOGIC ("wait")
			FSM_PROFILE_SECTION_OUT (state3_trans_conds)

			FSM_TRANSIT_SWITCH
				{
				FSM_CASE_TRANSIT (0, 2, state2_enter_exec, ;, "", "", "wait", "low_arvl", "tr_1", "test [wait -> low_arvl :  / ]")
				FSM_CASE_TRANSIT (1, 1, state1_enter_exec, ;, "", "", "wait", "send_beacon", "tr_3", "test [wait -> send_beacon :  / ]")
				}
				/*---------------------------------------------------------*/



			}


		FSM_EXIT (0,"test")
		}
	}




void
_op_test_diag (OP_SIM_CONTEXT_ARG_OPT)
	{
	/* No Diagnostic Block */
	}




void
_op_test_terminate (OP_SIM_CONTEXT_ARG_OPT)
	{

	FIN_MT (_op_test_terminate ())


	/* No Termination Block */

	Vos_Poolmem_Dealloc (op_sv_ptr);

	FOUT
	}


/* Undefine shortcuts to state variables to avoid */
/* syntax error in direct access to fields of */
/* local variable prs_ptr in _op_test_svar function. */
#undef node_id
#undef dest_addr
#undef node_address
#undef cycle_time

#undef FIN_PREAMBLE_DEC
#undef FIN_PREAMBLE_CODE

#define FIN_PREAMBLE_DEC
#define FIN_PREAMBLE_CODE

VosT_Obtype
_op_test_init (int * init_block_ptr)
	{
	VosT_Obtype obtype = OPC_NIL;
	FIN_MT (_op_test_init (init_block_ptr))

	obtype = Vos_Define_Object_Prstate ("proc state vars (test)",
		sizeof (test_state));
	*init_block_ptr = 0;

	FRET (obtype)
	}

VosT_Address
_op_test_alloc (VosT_Obtype obtype, int init_block)
	{
#if !defined (VOSD_NO_FIN)
	int _op_block_origin = 0;
#endif
	test_state * ptr;
	FIN_MT (_op_test_alloc (obtype))

	ptr = (test_state *)Vos_Alloc_Object (obtype);
	if (ptr != OPC_NIL)
		{
		ptr->_op_current_block = init_block;
#if defined (OPD_ALLOW_ODB)
		ptr->_op_current_state = "test [init enter execs]";
#endif
		}
	FRET ((VosT_Address)ptr)
	}



void
_op_test_svar (void * gen_ptr, const char * var_name, void ** var_p_ptr)
	{
	test_state		*prs_ptr;

	FIN_MT (_op_test_svar (gen_ptr, var_name, var_p_ptr))

	if (var_name == OPC_NIL)
		{
		*var_p_ptr = (void *)OPC_NIL;
		FOUT
		}
	prs_ptr = (test_state *)gen_ptr;

	if (strcmp ("node_id" , var_name) == 0)
		{
		*var_p_ptr = (void *) (&prs_ptr->node_id);
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
	if (strcmp ("cycle_time" , var_name) == 0)
		{
		*var_p_ptr = (void *) (&prs_ptr->cycle_time);
		FOUT
		}
	*var_p_ptr = (void *)OPC_NIL;

	FOUT
	}

