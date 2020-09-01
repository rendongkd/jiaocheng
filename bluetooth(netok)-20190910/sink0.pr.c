/* Process model C form file: sink0.pr.c */
/* Portions of this file copyright 1986-2008 by OPNET Technologies, Inc. */



/* This variable carries the header into the object file */
const char sink0_pr_c [] = "MIL_3_Tfile_Hdr_ 145A 30A op_runsim 7 5D771CBC 5D771CBC 1 7FPCYKRFROZNOYF Zhi@Ren 0 0 none none 0 0 none 0 0 0 0 0 0 0 0 1d79 5                                                                                                                                                                                                                                                                                                                                                                                                ";
#include <string.h>



/* OPNET system definitions */
#include <opnet.h>



/* Header Block */

int	rcvd_pk_nb = 0;
extern int sent_pk_nb;
double	start_send_pk_time = 0.0;
double	total_rcvd_bit = 0.0;

Stathandle rcvd_pk_nb_gshandle;
Stathandle ete_delay_gshandle;
Stathandle success_rate_gshandle;
Stathandle throughput_gshandle;

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
	Stathandle	             		bits_rcvd_stathandle                            ;
	Stathandle	             		bitssec_rcvd_stathandle                         ;
	Stathandle	             		pkts_rcvd_stathandle                            ;
	Stathandle	             		pktssec_rcvd_stathandle                         ;
	Stathandle	             		ete_delay_stathandle                            ;
	Stathandle	             		bits_rcvd_gstathandle                           ;
	Stathandle	             		bitssec_rcvd_gstathandle                        ;
	Stathandle	             		pkts_rcvd_gstathandle                           ;
	Stathandle	             		pktssec_rcvd_gstathandle                        ;
	Stathandle	             		ete_delay_gstathandle                           ;
	int	                    		node_addr                                       ;
	} sink0_state;

#define bits_rcvd_stathandle    		op_sv_ptr->bits_rcvd_stathandle
#define bitssec_rcvd_stathandle 		op_sv_ptr->bitssec_rcvd_stathandle
#define pkts_rcvd_stathandle    		op_sv_ptr->pkts_rcvd_stathandle
#define pktssec_rcvd_stathandle 		op_sv_ptr->pktssec_rcvd_stathandle
#define ete_delay_stathandle    		op_sv_ptr->ete_delay_stathandle
#define bits_rcvd_gstathandle   		op_sv_ptr->bits_rcvd_gstathandle
#define bitssec_rcvd_gstathandle		op_sv_ptr->bitssec_rcvd_gstathandle
#define pkts_rcvd_gstathandle   		op_sv_ptr->pkts_rcvd_gstathandle
#define pktssec_rcvd_gstathandle		op_sv_ptr->pktssec_rcvd_gstathandle
#define ete_delay_gstathandle   		op_sv_ptr->ete_delay_gstathandle
#define node_addr               		op_sv_ptr->node_addr

/* These macro definitions will define a local variable called	*/
/* "op_sv_ptr" in each function containing a FIN statement.	*/
/* This variable points to the state variable data structure,	*/
/* and can be used from a C debugger to display their values.	*/
#undef FIN_PREAMBLE_DEC
#undef FIN_PREAMBLE_CODE
#define FIN_PREAMBLE_DEC	sink0_state *op_sv_ptr;
#define FIN_PREAMBLE_CODE	\
		op_sv_ptr = ((sink0_state *)(OP_SIM_CONTEXT_PTR->_op_mod_state_ptr));


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
	void sink0 (OP_SIM_CONTEXT_ARG_OPT);
	VosT_Obtype _op_sink0_init (int * init_block_ptr);
	void _op_sink0_diag (OP_SIM_CONTEXT_ARG_OPT);
	void _op_sink0_terminate (OP_SIM_CONTEXT_ARG_OPT);
	VosT_Address _op_sink0_alloc (VosT_Obtype, int);
	void _op_sink0_svar (void *, const char *, void **);


#if defined (__cplusplus)
} /* end of 'extern "C"' */
#endif




/* Process model interrupt handling procedure */


void
sink0 (OP_SIM_CONTEXT_ARG_OPT)
	{
#if !defined (VOSD_NO_FIN)
	int _op_block_origin = 0;
#endif
	FIN_MT (sink0 ());

		{
		/* Temporary Variables */
		Packet*		pkptr;
		double		pk_size;
		double		ete_delay;
		/* End of Temporary Variables */


		FSM_ENTER_NO_VARS ("sink0")

		FSM_BLOCK_SWITCH
			{
			/*---------------------------------------------------------*/
			/** state (DISCARD) enter executives **/
			FSM_STATE_ENTER_UNFORCED (0, "DISCARD", state0_enter_exec, "sink0 [DISCARD enter execs]")

			/** blocking after enter executives of unforced state. **/
			FSM_EXIT (1,"sink0")


			/** state (DISCARD) exit executives **/
			FSM_STATE_EXIT_UNFORCED (0, "DISCARD", "sink0 [DISCARD exit execs]")
				FSM_PROFILE_SECTION_IN ("sink0 [DISCARD exit execs]", state0_exit_exec)
				{
				/* Obtain the incoming packet.	*/
				pkptr = op_pk_get (op_intrpt_strm ());
				
				/* Caclulate metrics to be updated.		*/
				pk_size = (double) op_pk_total_size_get (pkptr);
				total_rcvd_bit += pk_size;
				
				ete_delay = op_sim_time () - op_pk_creation_time_get (pkptr);  
				
				if(ete_delay > 0.0)
					op_stat_write (ete_delay_gshandle, ete_delay);
				else;
				
				rcvd_pk_nb++;
				op_stat_write (rcvd_pk_nb_gshandle, rcvd_pk_nb);
				
				
				if(sent_pk_nb > 0)
					op_stat_write (success_rate_gshandle, (double)rcvd_pk_nb / (double)sent_pk_nb);
				else;
				
				if(op_sim_time() - start_send_pk_time > 0)
					{
					if(op_sim_time() - start_send_pk_time < 1)
						op_stat_write (throughput_gshandle, total_rcvd_bit / 1.0);
					else
						op_stat_write (throughput_gshandle, total_rcvd_bit / (op_sim_time() - start_send_pk_time));
					}
				else;
				
				
				/* Update local statistics.	*/			
				op_stat_write (bits_rcvd_stathandle, 		pk_size);
				op_stat_write (pkts_rcvd_stathandle, 		1.0);
				op_stat_write (ete_delay_stathandle, 		ete_delay);
				
				op_stat_write (bitssec_rcvd_stathandle, 	pk_size);
				op_stat_write (bitssec_rcvd_stathandle, 	0.0);
				op_stat_write (pktssec_rcvd_stathandle, 	1.0);
				op_stat_write (pktssec_rcvd_stathandle, 	0.0);
				
				/* Update global statistics. */	
				op_stat_write (bits_rcvd_gstathandle, 		pk_size);
				op_stat_write (pkts_rcvd_gstathandle, 		1.0);
				op_stat_write (ete_delay_gstathandle, 		ete_delay);
				
				op_stat_write (bitssec_rcvd_gstathandle, 	pk_size);
				op_stat_write (bitssec_rcvd_gstathandle, 	0.0);
				op_stat_write (pktssec_rcvd_gstathandle, 	1.0);
				op_stat_write (pktssec_rcvd_gstathandle, 	0.0);
				
				/* Destroy the received packet.	*/
				op_pk_destroy (pkptr);
				}
				FSM_PROFILE_SECTION_OUT (state0_exit_exec)


			/** state (DISCARD) transition processing **/
			FSM_TRANSIT_FORCE (0, state0_enter_exec, ;, "default", "", "DISCARD", "DISCARD", " ", "sink0 [DISCARD -> DISCARD : default / ]")
				/*---------------------------------------------------------*/



			/** state (INIT) enter executives **/
			FSM_STATE_ENTER_FORCED_NOLABEL (1, "INIT", "sink0 [INIT enter execs]")
				FSM_PROFILE_SECTION_IN ("sink0 [INIT enter execs]", state1_enter_exec)
				{
				/* Initilaize the statistic handles to keep	*/
				/* track of traffic sinked by this process.	*/
				bits_rcvd_stathandle 		= op_stat_reg ("Traffic Sink.Traffic Received (bits)",			OPC_STAT_INDEX_NONE, OPC_STAT_LOCAL);
				bitssec_rcvd_stathandle 	= op_stat_reg ("Traffic Sink.Traffic Received (bits/sec)",		OPC_STAT_INDEX_NONE, OPC_STAT_LOCAL);
				pkts_rcvd_stathandle 		= op_stat_reg ("Traffic Sink.Traffic Received (packets)",		OPC_STAT_INDEX_NONE, OPC_STAT_LOCAL);
				pktssec_rcvd_stathandle 	= op_stat_reg ("Traffic Sink.Traffic Received (packets/sec)",	OPC_STAT_INDEX_NONE, OPC_STAT_LOCAL);
				ete_delay_stathandle		= op_stat_reg ("Traffic Sink.End-to-End Delay (seconds)",		OPC_STAT_INDEX_NONE, OPC_STAT_LOCAL);
				
				bits_rcvd_gstathandle 		= op_stat_reg ("Traffic Sink.Traffic Received (bits)",			OPC_STAT_INDEX_NONE, OPC_STAT_GLOBAL);
				bitssec_rcvd_gstathandle 	= op_stat_reg ("Traffic Sink.Traffic Received (bits/sec)",		OPC_STAT_INDEX_NONE, OPC_STAT_GLOBAL);
				pkts_rcvd_gstathandle 		= op_stat_reg ("Traffic Sink.Traffic Received (packets)",		OPC_STAT_INDEX_NONE, OPC_STAT_GLOBAL);
				pktssec_rcvd_gstathandle 	= op_stat_reg ("Traffic Sink.Traffic Received (packets/sec)",	OPC_STAT_INDEX_NONE, OPC_STAT_GLOBAL);
				ete_delay_gstathandle		= op_stat_reg ("Traffic Sink.End-to-End Delay (seconds)",		OPC_STAT_INDEX_NONE, OPC_STAT_GLOBAL);
				
				
				//abz
				rcvd_pk_nb = 0;
				total_rcvd_bit = 0.0;
				start_send_pk_time = 5.0;  //send pks from 5s
				
				rcvd_pk_nb_gshandle 		= op_stat_reg ("Number of Rcvd Pks", OPC_STAT_INDEX_NONE, OPC_STAT_GLOBAL);
				ete_delay_gshandle 			= op_stat_reg ("ETE Delay (s)", OPC_STAT_INDEX_NONE, OPC_STAT_GLOBAL);
				success_rate_gshandle 		= op_stat_reg ("Success Rate", OPC_STAT_INDEX_NONE, OPC_STAT_GLOBAL);
				throughput_gshandle 		= op_stat_reg ("Throughput (bps)", OPC_STAT_INDEX_NONE, OPC_STAT_GLOBAL);
				
				op_ima_obj_attr_get (op_topo_parent(op_id_self()), "node_address", &node_addr);
				}
				FSM_PROFILE_SECTION_OUT (state1_enter_exec)

			/** state (INIT) exit executives **/
			FSM_STATE_EXIT_FORCED (1, "INIT", "sink0 [INIT exit execs]")


			/** state (INIT) transition processing **/
			FSM_TRANSIT_FORCE (0, state0_enter_exec, ;, "default", "", "INIT", "DISCARD", "tr_12", "sink0 [INIT -> DISCARD : default / ]")
				/*---------------------------------------------------------*/



			}


		FSM_EXIT (1,"sink0")
		}
	}




void
_op_sink0_diag (OP_SIM_CONTEXT_ARG_OPT)
	{
	/* No Diagnostic Block */
	}




void
_op_sink0_terminate (OP_SIM_CONTEXT_ARG_OPT)
	{

	FIN_MT (_op_sink0_terminate ())


	/* No Termination Block */

	Vos_Poolmem_Dealloc (op_sv_ptr);

	FOUT
	}


/* Undefine shortcuts to state variables to avoid */
/* syntax error in direct access to fields of */
/* local variable prs_ptr in _op_sink0_svar function. */
#undef bits_rcvd_stathandle
#undef bitssec_rcvd_stathandle
#undef pkts_rcvd_stathandle
#undef pktssec_rcvd_stathandle
#undef ete_delay_stathandle
#undef bits_rcvd_gstathandle
#undef bitssec_rcvd_gstathandle
#undef pkts_rcvd_gstathandle
#undef pktssec_rcvd_gstathandle
#undef ete_delay_gstathandle
#undef node_addr

#undef FIN_PREAMBLE_DEC
#undef FIN_PREAMBLE_CODE

#define FIN_PREAMBLE_DEC
#define FIN_PREAMBLE_CODE

VosT_Obtype
_op_sink0_init (int * init_block_ptr)
	{
	VosT_Obtype obtype = OPC_NIL;
	FIN_MT (_op_sink0_init (init_block_ptr))

	obtype = Vos_Define_Object_Prstate ("proc state vars (sink0)",
		sizeof (sink0_state));
	*init_block_ptr = 2;

	FRET (obtype)
	}

VosT_Address
_op_sink0_alloc (VosT_Obtype obtype, int init_block)
	{
#if !defined (VOSD_NO_FIN)
	int _op_block_origin = 0;
#endif
	sink0_state * ptr;
	FIN_MT (_op_sink0_alloc (obtype))

	ptr = (sink0_state *)Vos_Alloc_Object (obtype);
	if (ptr != OPC_NIL)
		{
		ptr->_op_current_block = init_block;
#if defined (OPD_ALLOW_ODB)
		ptr->_op_current_state = "sink0 [INIT enter execs]";
#endif
		}
	FRET ((VosT_Address)ptr)
	}



void
_op_sink0_svar (void * gen_ptr, const char * var_name, void ** var_p_ptr)
	{
	sink0_state		*prs_ptr;

	FIN_MT (_op_sink0_svar (gen_ptr, var_name, var_p_ptr))

	if (var_name == OPC_NIL)
		{
		*var_p_ptr = (void *)OPC_NIL;
		FOUT
		}
	prs_ptr = (sink0_state *)gen_ptr;

	if (strcmp ("bits_rcvd_stathandle" , var_name) == 0)
		{
		*var_p_ptr = (void *) (&prs_ptr->bits_rcvd_stathandle);
		FOUT
		}
	if (strcmp ("bitssec_rcvd_stathandle" , var_name) == 0)
		{
		*var_p_ptr = (void *) (&prs_ptr->bitssec_rcvd_stathandle);
		FOUT
		}
	if (strcmp ("pkts_rcvd_stathandle" , var_name) == 0)
		{
		*var_p_ptr = (void *) (&prs_ptr->pkts_rcvd_stathandle);
		FOUT
		}
	if (strcmp ("pktssec_rcvd_stathandle" , var_name) == 0)
		{
		*var_p_ptr = (void *) (&prs_ptr->pktssec_rcvd_stathandle);
		FOUT
		}
	if (strcmp ("ete_delay_stathandle" , var_name) == 0)
		{
		*var_p_ptr = (void *) (&prs_ptr->ete_delay_stathandle);
		FOUT
		}
	if (strcmp ("bits_rcvd_gstathandle" , var_name) == 0)
		{
		*var_p_ptr = (void *) (&prs_ptr->bits_rcvd_gstathandle);
		FOUT
		}
	if (strcmp ("bitssec_rcvd_gstathandle" , var_name) == 0)
		{
		*var_p_ptr = (void *) (&prs_ptr->bitssec_rcvd_gstathandle);
		FOUT
		}
	if (strcmp ("pkts_rcvd_gstathandle" , var_name) == 0)
		{
		*var_p_ptr = (void *) (&prs_ptr->pkts_rcvd_gstathandle);
		FOUT
		}
	if (strcmp ("pktssec_rcvd_gstathandle" , var_name) == 0)
		{
		*var_p_ptr = (void *) (&prs_ptr->pktssec_rcvd_gstathandle);
		FOUT
		}
	if (strcmp ("ete_delay_gstathandle" , var_name) == 0)
		{
		*var_p_ptr = (void *) (&prs_ptr->ete_delay_gstathandle);
		FOUT
		}
	if (strcmp ("node_addr" , var_name) == 0)
		{
		*var_p_ptr = (void *) (&prs_ptr->node_addr);
		FOUT
		}
	*var_p_ptr = (void *)OPC_NIL;

	FOUT
	}

