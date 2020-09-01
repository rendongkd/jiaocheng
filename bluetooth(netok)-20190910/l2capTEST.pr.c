/* Process model C form file: l2capTEST.pr.c */
/* Portions of this file copyright 1986-2008 by OPNET Technologies, Inc. */



/* This variable carries the header into the object file */
const char l2capTEST_pr_c [] = "MIL_3_Tfile_Hdr_ 145A 30A modeler 7 5D6B671B 5D6B671B 1 USER-20151017SA Administrator 0 0 none none 0 0 none 0 0 0 0 0 0 0 0 1bcc 1                                                                                                                                                                                                                                                                                                                                                                                            ";
#include <string.h>



/* OPNET system definitions */
#include <opnet.h>

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
	int	                    		cycle_time                                      ;
	int	                    		dest_addr                                       ;
	int	                    		node_address                                    ;
	int	                    		ack_count                                       ;
	List*	                  		slaves_list                                     ;
	int	                    		beacon_count                                    ;
	int	                    		new_variable                                    ;
	} l2capTEST_state;

#define node_id                 		op_sv_ptr->node_id
#define cycle_time              		op_sv_ptr->cycle_time
#define dest_addr               		op_sv_ptr->dest_addr
#define node_address            		op_sv_ptr->node_address
#define ack_count               		op_sv_ptr->ack_count
#define slaves_list             		op_sv_ptr->slaves_list
#define beacon_count            		op_sv_ptr->beacon_count
#define new_variable            		op_sv_ptr->new_variable

/* These macro definitions will define a local variable called	*/
/* "op_sv_ptr" in each function containing a FIN statement.	*/
/* This variable points to the state variable data structure,	*/
/* and can be used from a C debugger to display their values.	*/
#undef FIN_PREAMBLE_DEC
#undef FIN_PREAMBLE_CODE
#define FIN_PREAMBLE_DEC	l2capTEST_state *op_sv_ptr;
#define FIN_PREAMBLE_CODE	\
		op_sv_ptr = ((l2capTEST_state *)(OP_SIM_CONTEXT_PTR->_op_mod_state_ptr));


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
	void l2capTEST (OP_SIM_CONTEXT_ARG_OPT);
	VosT_Obtype _op_l2capTEST_init (int * init_block_ptr);
	void _op_l2capTEST_diag (OP_SIM_CONTEXT_ARG_OPT);
	void _op_l2capTEST_terminate (OP_SIM_CONTEXT_ARG_OPT);
	VosT_Address _op_l2capTEST_alloc (VosT_Obtype, int);
	void _op_l2capTEST_svar (void *, const char *, void **);


#if defined (__cplusplus)
} /* end of 'extern "C"' */
#endif




/* Process model interrupt handling procedure */


void
l2capTEST (OP_SIM_CONTEXT_ARG_OPT)
	{
#if !defined (VOSD_NO_FIN)
	int _op_block_origin = 0;
#endif
	FIN_MT (l2capTEST ());

		{
		/* Temporary Variables */
		
		/* End of Temporary Variables */


		FSM_ENTER ("l2capTEST")

		FSM_BLOCK_SWITCH
			{
			/*---------------------------------------------------------*/
			/** state (init) enter executives **/
			FSM_STATE_ENTER_FORCED_NOLABEL (0, "init", "l2capTEST [init enter execs]")
				FSM_PROFILE_SECTION_IN ("l2capTEST [init enter execs]", state0_enter_exec)
				{
				
				
				
				
				}
				FSM_PROFILE_SECTION_OUT (state0_enter_exec)

			/** state (init) exit executives **/
			FSM_STATE_EXIT_FORCED (0, "init", "l2capTEST [init exit execs]")


			/** state (init) transition processing **/
			FSM_TRANSIT_FORCE (1, state1_enter_exec, ;, "default", "", "init", "idle", "tr_0", "l2capTEST [init -> idle : default / ]")
				/*---------------------------------------------------------*/



			/** state (idle) enter executives **/
			FSM_STATE_ENTER_UNFORCED (1, "idle", state1_enter_exec, "l2capTEST [idle enter execs]")

			/** blocking after enter executives of unforced state. **/
			FSM_EXIT (3,"l2capTEST")


			/** state (idle) exit executives **/
			FSM_STATE_EXIT_UNFORCED (1, "idle", "l2capTEST [idle exit execs]")


			/** state (idle) transition processing **/
			FSM_PROFILE_SECTION_IN ("l2capTEST [idle trans conditions]", state1_trans_conds)
			FSM_INIT_COND ((1))
			FSM_TEST_COND ((1))
			FSM_TEST_COND ((1))
			FSM_TEST_COND ((1))
			FSM_TEST_COND ((1))
			FSM_TEST_COND ((1))
			FSM_DFLT_COND
			FSM_TEST_LOGIC ("idle")
			FSM_PROFILE_SECTION_OUT (state1_trans_conds)

			FSM_TRANSIT_SWITCH
				{
				FSM_CASE_TRANSIT (0, 2, state2_enter_exec, ;, "", "", "idle", "up_arvl", "tr_1", "l2capTEST [idle -> up_arvl :  / ]")
				FSM_CASE_TRANSIT (1, 3, state3_enter_exec, ;, "", "", "idle", "low_arvl", "tr_10", "l2capTEST [idle -> low_arvl :  / ]")
				FSM_CASE_TRANSIT (2, 4, state4_enter_exec, ;, "", "", "idle", "send_beacon", "tr_43", "l2capTEST [idle -> send_beacon :  / ]")
				FSM_CASE_TRANSIT (3, 5, state5_enter_exec, ;, "", "", "idle", "tx", "tr_45", "l2capTEST [idle -> tx :  / ]")
				FSM_CASE_TRANSIT (4, 6, state6_enter_exec, ;, "", "", "idle", "ACL_data", "SEND_DATA", "l2capTEST [idle -> ACL_data :  / ]")
				FSM_CASE_TRANSIT (5, 5, state5_enter_exec, ;, "", "", "idle", "tx", "tr_50", "l2capTEST [idle -> tx :  / ]")
				FSM_CASE_TRANSIT (6, 1, state1_enter_exec, ;, "default", "", "idle", "idle", "tr_44", "l2capTEST [idle -> idle : default / ]")
				}
				/*---------------------------------------------------------*/



			/** state (up_arvl) enter executives **/
			FSM_STATE_ENTER_FORCED (2, "up_arvl", state2_enter_exec, "l2capTEST [up_arvl enter execs]")
				FSM_PROFILE_SECTION_IN ("l2capTEST [up_arvl enter execs]", state2_enter_exec)
				{
				
				}
				FSM_PROFILE_SECTION_OUT (state2_enter_exec)

			/** state (up_arvl) exit executives **/
			FSM_STATE_EXIT_FORCED (2, "up_arvl", "l2capTEST [up_arvl exit execs]")


			/** state (up_arvl) transition processing **/
			FSM_TRANSIT_FORCE (1, state1_enter_exec, ;, "default", "", "up_arvl", "idle", "tr_2", "l2capTEST [up_arvl -> idle : default / ]")
				/*---------------------------------------------------------*/



			/** state (low_arvl) enter executives **/
			FSM_STATE_ENTER_FORCED (3, "low_arvl", state3_enter_exec, "l2capTEST [low_arvl enter execs]")
				FSM_PROFILE_SECTION_IN ("l2capTEST [low_arvl enter execs]", state3_enter_exec)
				{
				
				}
				FSM_PROFILE_SECTION_OUT (state3_enter_exec)

			/** state (low_arvl) exit executives **/
			FSM_STATE_EXIT_FORCED (3, "low_arvl", "l2capTEST [low_arvl exit execs]")


			/** state (low_arvl) transition processing **/
			FSM_TRANSIT_FORCE (1, state1_enter_exec, ;, "default", "", "low_arvl", "idle", "tr_11", "l2capTEST [low_arvl -> idle : default / ]")
				/*---------------------------------------------------------*/



			/** state (send_beacon) enter executives **/
			FSM_STATE_ENTER_FORCED (4, "send_beacon", state4_enter_exec, "l2capTEST [send_beacon enter execs]")

			/** state (send_beacon) exit executives **/
			FSM_STATE_EXIT_FORCED (4, "send_beacon", "l2capTEST [send_beacon exit execs]")


			/** state (send_beacon) transition processing **/
			FSM_TRANSIT_FORCE (1, state1_enter_exec, ;, "default", "", "send_beacon", "idle", "tr_42", "l2capTEST [send_beacon -> idle : default / ]")
				/*---------------------------------------------------------*/



			/** state (tx) enter executives **/
			FSM_STATE_ENTER_FORCED (5, "tx", state5_enter_exec, "l2capTEST [tx enter execs]")

			/** state (tx) exit executives **/
			FSM_STATE_EXIT_FORCED (5, "tx", "l2capTEST [tx exit execs]")


			/** state (tx) transition processing **/
			FSM_TRANSIT_FORCE (1, state1_enter_exec, ;, "default", "", "tx", "idle", "tr_46", "l2capTEST [tx -> idle : default / ]")
				/*---------------------------------------------------------*/



			/** state (ACL_data) enter executives **/
			FSM_STATE_ENTER_FORCED (6, "ACL_data", state6_enter_exec, "l2capTEST [ACL_data enter execs]")

			/** state (ACL_data) exit executives **/
			FSM_STATE_EXIT_FORCED (6, "ACL_data", "l2capTEST [ACL_data exit execs]")


			/** state (ACL_data) transition processing **/
			FSM_TRANSIT_FORCE (1, state1_enter_exec, ;, "default", "", "ACL_data", "idle", "tr_49", "l2capTEST [ACL_data -> idle : default / ]")
				/*---------------------------------------------------------*/



			}


		FSM_EXIT (0,"l2capTEST")
		}
	}




void
_op_l2capTEST_diag (OP_SIM_CONTEXT_ARG_OPT)
	{
	/* No Diagnostic Block */
	}




void
_op_l2capTEST_terminate (OP_SIM_CONTEXT_ARG_OPT)
	{

	FIN_MT (_op_l2capTEST_terminate ())


	/* No Termination Block */

	Vos_Poolmem_Dealloc (op_sv_ptr);

	FOUT
	}


/* Undefine shortcuts to state variables to avoid */
/* syntax error in direct access to fields of */
/* local variable prs_ptr in _op_l2capTEST_svar function. */
#undef node_id
#undef cycle_time
#undef dest_addr
#undef node_address
#undef ack_count
#undef slaves_list
#undef beacon_count
#undef new_variable

#undef FIN_PREAMBLE_DEC
#undef FIN_PREAMBLE_CODE

#define FIN_PREAMBLE_DEC
#define FIN_PREAMBLE_CODE

VosT_Obtype
_op_l2capTEST_init (int * init_block_ptr)
	{
	VosT_Obtype obtype = OPC_NIL;
	FIN_MT (_op_l2capTEST_init (init_block_ptr))

	obtype = Vos_Define_Object_Prstate ("proc state vars (l2capTEST)",
		sizeof (l2capTEST_state));
	*init_block_ptr = 0;

	FRET (obtype)
	}

VosT_Address
_op_l2capTEST_alloc (VosT_Obtype obtype, int init_block)
	{
#if !defined (VOSD_NO_FIN)
	int _op_block_origin = 0;
#endif
	l2capTEST_state * ptr;
	FIN_MT (_op_l2capTEST_alloc (obtype))

	ptr = (l2capTEST_state *)Vos_Alloc_Object (obtype);
	if (ptr != OPC_NIL)
		{
		ptr->_op_current_block = init_block;
#if defined (OPD_ALLOW_ODB)
		ptr->_op_current_state = "l2capTEST [init enter execs]";
#endif
		}
	FRET ((VosT_Address)ptr)
	}



void
_op_l2capTEST_svar (void * gen_ptr, const char * var_name, void ** var_p_ptr)
	{
	l2capTEST_state		*prs_ptr;

	FIN_MT (_op_l2capTEST_svar (gen_ptr, var_name, var_p_ptr))

	if (var_name == OPC_NIL)
		{
		*var_p_ptr = (void *)OPC_NIL;
		FOUT
		}
	prs_ptr = (l2capTEST_state *)gen_ptr;

	if (strcmp ("node_id" , var_name) == 0)
		{
		*var_p_ptr = (void *) (&prs_ptr->node_id);
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
	if (strcmp ("ack_count" , var_name) == 0)
		{
		*var_p_ptr = (void *) (&prs_ptr->ack_count);
		FOUT
		}
	if (strcmp ("slaves_list" , var_name) == 0)
		{
		*var_p_ptr = (void *) (&prs_ptr->slaves_list);
		FOUT
		}
	if (strcmp ("beacon_count" , var_name) == 0)
		{
		*var_p_ptr = (void *) (&prs_ptr->beacon_count);
		FOUT
		}
	if (strcmp ("new_variable" , var_name) == 0)
		{
		*var_p_ptr = (void *) (&prs_ptr->new_variable);
		FOUT
		}
	*var_p_ptr = (void *)OPC_NIL;

	FOUT
	}

