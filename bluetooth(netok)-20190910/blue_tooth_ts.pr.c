/* Process model C form file: blue_tooth_ts.pr.c */
/* Portions of this file copyright 1986-2008 by OPNET Technologies, Inc. */



/* This variable carries the header into the object file */
const char blue_tooth_ts_pr_c [] = "MIL_3_Tfile_Hdr_ 145A 30A op_runsim 7 5D771C74 5D771C74 1 7FPCYKRFROZNOYF Zhi@Ren 0 0 none none 0 0 none 0 0 0 0 0 0 0 0 1d79 5                                                                                                                                                                                                                                                                                                                                                                                                ";
#include <string.h>



/* OPNET system definitions */
#include <opnet.h>



/* Header Block */

#define	instrm_from_routing	0
#define	instrm_from_mac		1
#define	instrm_to_routing	0
#define	instrm_to_mac		1

#define UP_ARVL 			(op_intrpt_type() == OPC_INTRPT_STRM && op_intrpt_strm() == instrm_from_routing)
#define LOW_ARVL 			(op_intrpt_type() == OPC_INTRPT_STRM && op_intrpt_strm() == instrm_from_mac)

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
	List*	                  		record_src_list                                 ;
	int	                    		i                                               ;
	int	                    		new_variable                                    ;
	} blue_tooth_ts_state;

#define node_id                 		op_sv_ptr->node_id
#define dest_addr               		op_sv_ptr->dest_addr
#define node_address            		op_sv_ptr->node_address
#define record_src_list         		op_sv_ptr->record_src_list
#define i                       		op_sv_ptr->i
#define new_variable            		op_sv_ptr->new_variable

/* These macro definitions will define a local variable called	*/
/* "op_sv_ptr" in each function containing a FIN statement.	*/
/* This variable points to the state variable data structure,	*/
/* and can be used from a C debugger to display their values.	*/
#undef FIN_PREAMBLE_DEC
#undef FIN_PREAMBLE_CODE
#define FIN_PREAMBLE_DEC	blue_tooth_ts_state *op_sv_ptr;
#define FIN_PREAMBLE_CODE	\
		op_sv_ptr = ((blue_tooth_ts_state *)(OP_SIM_CONTEXT_PTR->_op_mod_state_ptr));


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
	void blue_tooth_ts (OP_SIM_CONTEXT_ARG_OPT);
	VosT_Obtype _op_blue_tooth_ts_init (int * init_block_ptr);
	void _op_blue_tooth_ts_diag (OP_SIM_CONTEXT_ARG_OPT);
	void _op_blue_tooth_ts_terminate (OP_SIM_CONTEXT_ARG_OPT);
	VosT_Address _op_blue_tooth_ts_alloc (VosT_Obtype, int);
	void _op_blue_tooth_ts_svar (void *, const char *, void **);


#if defined (__cplusplus)
} /* end of 'extern "C"' */
#endif




/* Process model interrupt handling procedure */


void
blue_tooth_ts (OP_SIM_CONTEXT_ARG_OPT)
	{
#if !defined (VOSD_NO_FIN)
	int _op_block_origin = 0;
#endif
	FIN_MT (blue_tooth_ts ());

		{
		/* Temporary Variables */
		//Packet*		pktptr;
		
		Packet*	pkptr;
		
		//int 	dest,source;
		//Packet*	pk;
		//int type;
		//int k,m;
		/* End of Temporary Variables */


		FSM_ENTER ("blue_tooth_ts")

		FSM_BLOCK_SWITCH
			{
			/*---------------------------------------------------------*/
			/** state (init) enter executives **/
			FSM_STATE_ENTER_FORCED_NOLABEL (0, "init", "blue_tooth_ts [init enter execs]")
				FSM_PROFILE_SECTION_IN ("blue_tooth_ts [init enter execs]", state0_enter_exec)
				{
				node_id = op_topo_parent(op_id_self());
				
				op_ima_obj_attr_get(node_id,"destination_address",&dest_addr);//get dest frome attributes;
				//op_ima_obj_attr_get(node_id,"MAC_address",&MAC_address);
				op_ima_obj_attr_get(node_id,"node_address",&node_address);
				record_src_list=op_prg_list_create();
				}
				FSM_PROFILE_SECTION_OUT (state0_enter_exec)

			/** state (init) exit executives **/
			FSM_STATE_EXIT_FORCED (0, "init", "blue_tooth_ts [init exit execs]")


			/** state (init) transition processing **/
			FSM_TRANSIT_FORCE (1, state1_enter_exec, ;, "default", "", "init", "idle", "tr_7", "blue_tooth_ts [init -> idle : default / ]")
				/*---------------------------------------------------------*/



			/** state (idle) enter executives **/
			FSM_STATE_ENTER_UNFORCED (1, "idle", state1_enter_exec, "blue_tooth_ts [idle enter execs]")

			/** blocking after enter executives of unforced state. **/
			FSM_EXIT (3,"blue_tooth_ts")


			/** state (idle) exit executives **/
			FSM_STATE_EXIT_UNFORCED (1, "idle", "blue_tooth_ts [idle exit execs]")


			/** state (idle) transition processing **/
			FSM_PROFILE_SECTION_IN ("blue_tooth_ts [idle trans conditions]", state1_trans_conds)
			FSM_INIT_COND (UP_ARVL)
			FSM_TEST_COND (LOW_ARVL)
			FSM_DFLT_COND
			FSM_TEST_LOGIC ("idle")
			FSM_PROFILE_SECTION_OUT (state1_trans_conds)

			FSM_TRANSIT_SWITCH
				{
				FSM_CASE_TRANSIT (0, 2, state2_enter_exec, ;, "UP_ARVL", "", "idle", "up_arvl", "tr_9", "blue_tooth_ts [idle -> up_arvl : UP_ARVL / ]")
				FSM_CASE_TRANSIT (1, 3, state3_enter_exec, ;, "LOW_ARVL", "", "idle", "low_arvl", "tr_10", "blue_tooth_ts [idle -> low_arvl : LOW_ARVL / ]")
				FSM_CASE_TRANSIT (2, 1, state1_enter_exec, ;, "default", "", "idle", "idle", "tr_12", "blue_tooth_ts [idle -> idle : default / ]")
				}
				/*---------------------------------------------------------*/



			/** state (up_arvl) enter executives **/
			FSM_STATE_ENTER_FORCED (2, "up_arvl", state2_enter_exec, "blue_tooth_ts [up_arvl enter execs]")
				FSM_PROFILE_SECTION_IN ("blue_tooth_ts [up_arvl enter execs]", state2_enter_exec)
				{
				pkptr=op_pk_get(instrm_from_routing);
				
				op_pk_send(pkptr,instrm_to_mac);
				
				/*
				op_prg_list_init(record_src_list);
				op_prg_list_size(record_src_list);
				m=op_prg_list_size(record_src_list);
				for(k=0;k<m;k++)
				{
				pk=op_prg_list_remove(record_src_list,k);
				op_pk_nfd_access(pk,"SRC",&source);
				op_pk_nfd_access(pk,"DEST",&dest);
				op_pk_nfd_access(pk,"Type",&type);
				if(type==25)
					{
					pk=op_pk_create_fmt("data");	
					op_pk_nfd_set(pk,"DEST",0);
					op_pk_nfd_set(pk,"SRC",dest);
					op_pk_nfd_set(pk, "Type", 150);
					break;};
				if(type==100)
					{
				pk=op_pk_create_fmt("data");	
					op_pk_nfd_set(pk,"DEST",0);
					op_pk_nfd_set(pk,"SRC",dest);
					op_pk_nfd_set(pk, "Type", 150);
					break;}
				else
					if(type==150)
					{
					pk=op_pk_create_fmt("data_slave");	
					op_pk_nfd_set(pk,"DEST",source);
					op_pk_nfd_set(pk,"SRC",0);
					op_pk_nfd_set(pk, "Type", 100);
					break;};
				};
				*/	
				
				}
				FSM_PROFILE_SECTION_OUT (state2_enter_exec)

			/** state (up_arvl) exit executives **/
			FSM_STATE_EXIT_FORCED (2, "up_arvl", "blue_tooth_ts [up_arvl exit execs]")


			/** state (up_arvl) transition processing **/
			FSM_TRANSIT_FORCE (1, state1_enter_exec, ;, "default", "", "up_arvl", "idle", "tr_8", "blue_tooth_ts [up_arvl -> idle : default / ]")
				/*---------------------------------------------------------*/



			/** state (low_arvl) enter executives **/
			FSM_STATE_ENTER_FORCED (3, "low_arvl", state3_enter_exec, "blue_tooth_ts [low_arvl enter execs]")
				FSM_PROFILE_SECTION_IN ("blue_tooth_ts [low_arvl enter execs]", state3_enter_exec)
				{
				pkptr=op_pk_get(instrm_from_mac);
				
				/*
				for(i=0;i<7;i++)
				{
				op_pk_nfd_access(pkptr,"SRC",&source);
				op_pk_nfd_access(pkptr,"DEST",&dest);
				op_pk_nfd_access(pkptr,"Type",&type);
				op_prg_list_insert(record_src_list,pkptr,i);
				op_pk_destroy(pkptr);};
				*/
					
				op_pk_send(pkptr,instrm_to_routing);
				}
				FSM_PROFILE_SECTION_OUT (state3_enter_exec)

			/** state (low_arvl) exit executives **/
			FSM_STATE_EXIT_FORCED (3, "low_arvl", "blue_tooth_ts [low_arvl exit execs]")


			/** state (low_arvl) transition processing **/
			FSM_TRANSIT_FORCE (1, state1_enter_exec, ;, "default", "", "low_arvl", "idle", "tr_11", "blue_tooth_ts [low_arvl -> idle : default / ]")
				/*---------------------------------------------------------*/



			}


		FSM_EXIT (0,"blue_tooth_ts")
		}
	}




void
_op_blue_tooth_ts_diag (OP_SIM_CONTEXT_ARG_OPT)
	{
	/* No Diagnostic Block */
	}




void
_op_blue_tooth_ts_terminate (OP_SIM_CONTEXT_ARG_OPT)
	{

	FIN_MT (_op_blue_tooth_ts_terminate ())


	/* No Termination Block */

	Vos_Poolmem_Dealloc (op_sv_ptr);

	FOUT
	}


/* Undefine shortcuts to state variables to avoid */
/* syntax error in direct access to fields of */
/* local variable prs_ptr in _op_blue_tooth_ts_svar function. */
#undef node_id
#undef dest_addr
#undef node_address
#undef record_src_list
#undef i
#undef new_variable

#undef FIN_PREAMBLE_DEC
#undef FIN_PREAMBLE_CODE

#define FIN_PREAMBLE_DEC
#define FIN_PREAMBLE_CODE

VosT_Obtype
_op_blue_tooth_ts_init (int * init_block_ptr)
	{
	VosT_Obtype obtype = OPC_NIL;
	FIN_MT (_op_blue_tooth_ts_init (init_block_ptr))

	obtype = Vos_Define_Object_Prstate ("proc state vars (blue_tooth_ts)",
		sizeof (blue_tooth_ts_state));
	*init_block_ptr = 0;

	FRET (obtype)
	}

VosT_Address
_op_blue_tooth_ts_alloc (VosT_Obtype obtype, int init_block)
	{
#if !defined (VOSD_NO_FIN)
	int _op_block_origin = 0;
#endif
	blue_tooth_ts_state * ptr;
	FIN_MT (_op_blue_tooth_ts_alloc (obtype))

	ptr = (blue_tooth_ts_state *)Vos_Alloc_Object (obtype);
	if (ptr != OPC_NIL)
		{
		ptr->_op_current_block = init_block;
#if defined (OPD_ALLOW_ODB)
		ptr->_op_current_state = "blue_tooth_ts [init enter execs]";
#endif
		}
	FRET ((VosT_Address)ptr)
	}



void
_op_blue_tooth_ts_svar (void * gen_ptr, const char * var_name, void ** var_p_ptr)
	{
	blue_tooth_ts_state		*prs_ptr;

	FIN_MT (_op_blue_tooth_ts_svar (gen_ptr, var_name, var_p_ptr))

	if (var_name == OPC_NIL)
		{
		*var_p_ptr = (void *)OPC_NIL;
		FOUT
		}
	prs_ptr = (blue_tooth_ts_state *)gen_ptr;

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
	if (strcmp ("record_src_list" , var_name) == 0)
		{
		*var_p_ptr = (void *) (&prs_ptr->record_src_list);
		FOUT
		}
	if (strcmp ("i" , var_name) == 0)
		{
		*var_p_ptr = (void *) (&prs_ptr->i);
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

