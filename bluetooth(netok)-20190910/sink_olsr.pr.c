/* Process model C form file: sink_olsr.pr.c */
/* Portions of this file copyright 1986-2008 by OPNET Technologies, Inc. */



/* This variable carries the header into the object file */
const char sink_olsr_pr_c [] = "MIL_3_Tfile_Hdr_ 145A 30A op_runsim 7 5DBA4311 5DBA4311 1 7FPCYKRFROZNOYF Zhi@Ren 0 0 none none 0 0 none 0 0 0 0 0 0 0 0 1d79 5                                                                                                                                                                                                                                                                                                                                                                                                ";
#include <string.h>



/* OPNET system definitions */
#include <opnet.h>



/* Header Block */

Stathandle throughput_gstathandle;

double	total_pk_size = 0.0;
extern double	start_time1;

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
	Stathandle	             		priority0_ete_delay_gstathandle                 ;
	Stathandle	             		priority1_ete_delay_gstathandle                 ;
	Stathandle	             		priority2_ete_delay_gstathandle                 ;
	Stathandle	             		priority3_ete_delay_gstathandle                 ;
	Stathandle	             		priority4_ete_delay_gstathandle                 ;
	Stathandle	             		priority5_ete_delay_gstathandle                 ;
	Stathandle	             		priority6_ete_delay_gstathandle                 ;
	Stathandle	             		priority7_ete_delay_gstathandle                 ;
	} sink_olsr_state;

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
#define priority0_ete_delay_gstathandle		op_sv_ptr->priority0_ete_delay_gstathandle
#define priority1_ete_delay_gstathandle		op_sv_ptr->priority1_ete_delay_gstathandle
#define priority2_ete_delay_gstathandle		op_sv_ptr->priority2_ete_delay_gstathandle
#define priority3_ete_delay_gstathandle		op_sv_ptr->priority3_ete_delay_gstathandle
#define priority4_ete_delay_gstathandle		op_sv_ptr->priority4_ete_delay_gstathandle
#define priority5_ete_delay_gstathandle		op_sv_ptr->priority5_ete_delay_gstathandle
#define priority6_ete_delay_gstathandle		op_sv_ptr->priority6_ete_delay_gstathandle
#define priority7_ete_delay_gstathandle		op_sv_ptr->priority7_ete_delay_gstathandle

/* These macro definitions will define a local variable called	*/
/* "op_sv_ptr" in each function containing a FIN statement.	*/
/* This variable points to the state variable data structure,	*/
/* and can be used from a C debugger to display their values.	*/
#undef FIN_PREAMBLE_DEC
#undef FIN_PREAMBLE_CODE
#define FIN_PREAMBLE_DEC	sink_olsr_state *op_sv_ptr;
#define FIN_PREAMBLE_CODE	\
		op_sv_ptr = ((sink_olsr_state *)(OP_SIM_CONTEXT_PTR->_op_mod_state_ptr));


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
	void sink_olsr (OP_SIM_CONTEXT_ARG_OPT);
	VosT_Obtype _op_sink_olsr_init (int * init_block_ptr);
	void _op_sink_olsr_diag (OP_SIM_CONTEXT_ARG_OPT);
	void _op_sink_olsr_terminate (OP_SIM_CONTEXT_ARG_OPT);
	VosT_Address _op_sink_olsr_alloc (VosT_Obtype, int);
	void _op_sink_olsr_svar (void *, const char *, void **);


#if defined (__cplusplus)
} /* end of 'extern "C"' */
#endif




/* Process model interrupt handling procedure */


void
sink_olsr (OP_SIM_CONTEXT_ARG_OPT)
	{
#if !defined (VOSD_NO_FIN)
	int _op_block_origin = 0;
#endif
	FIN_MT (sink_olsr ());

		{
		/* Temporary Variables */
		Packet*		pkptr;
		double		pk_size;
		double		ete_delay;
		int priority1=0;
		/* End of Temporary Variables */


		FSM_ENTER_NO_VARS ("sink_olsr")

		FSM_BLOCK_SWITCH
			{
			/*---------------------------------------------------------*/
			/** state (DISCARD) enter executives **/
			FSM_STATE_ENTER_UNFORCED (0, "DISCARD", state0_enter_exec, "sink_olsr [DISCARD enter execs]")

			/** blocking after enter executives of unforced state. **/
			FSM_EXIT (1,"sink_olsr")


			/** state (DISCARD) exit executives **/
			FSM_STATE_EXIT_UNFORCED (0, "DISCARD", "sink_olsr [DISCARD exit execs]")
				FSM_PROFILE_SECTION_IN ("sink_olsr [DISCARD exit execs]", state0_exit_exec)
				{
				/* Obtain the incoming packet.	*/
				pkptr = op_pk_get (op_intrpt_strm ());
				op_pk_nfd_access(pkptr,"priority",&priority1);
				/* Caclulate metrics to be updated.		*/
				pk_size = (double) op_pk_total_size_get (pkptr);
				
				total_pk_size += pk_size;
				
				//output throughput
				if(start_time1 > 0 && start_time1 < (op_sim_time() -1))
					op_stat_write(throughput_gstathandle, total_pk_size / (op_sim_time() - start_time1));
					
				else;	
				
				ete_delay = op_sim_time () - op_pk_creation_time_get (pkptr);
				
				switch(priority1)
					{
					case 0:
					op_stat_write(priority0_ete_delay_gstathandle,ete_delay);
					break;
					case 1:
					op_stat_write(priority1_ete_delay_gstathandle,ete_delay);
					break;
					case 2:
					op_stat_write(priority2_ete_delay_gstathandle,ete_delay);
					break;	
					case 3:
					op_stat_write(priority3_ete_delay_gstathandle,ete_delay);
					break;	
					case 4:
					op_stat_write(priority4_ete_delay_gstathandle,ete_delay);
					break;	
					case 5:
					op_stat_write(priority5_ete_delay_gstathandle,ete_delay);
					break;	
					case 6:
					op_stat_write(priority6_ete_delay_gstathandle,ete_delay);
					break;
					case 7:
					op_stat_write(priority7_ete_delay_gstathandle,ete_delay);
					break;
					default:;
					}
				
				/* Update local statistics.				*/
				op_stat_write (bits_rcvd_stathandle, 		pk_size);
				op_stat_write (pkts_rcvd_stathandle, 		1.0);
				op_stat_write (ete_delay_stathandle, 		ete_delay);
				
				op_stat_write (bitssec_rcvd_stathandle, 	pk_size);
				op_stat_write (bitssec_rcvd_stathandle, 	0.0);
				op_stat_write (pktssec_rcvd_stathandle, 	1.0);
				op_stat_write (pktssec_rcvd_stathandle, 	0.0);
				
				/* Update global statistics.	*/
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
			FSM_TRANSIT_FORCE (0, state0_enter_exec, ;, "default", "", "DISCARD", "DISCARD", " ", "sink_olsr [DISCARD -> DISCARD : default / ]")
				/*---------------------------------------------------------*/



			/** state (INIT) enter executives **/
			FSM_STATE_ENTER_FORCED_NOLABEL (1, "INIT", "sink_olsr [INIT enter execs]")
				FSM_PROFILE_SECTION_IN ("sink_olsr [INIT enter execs]", state1_enter_exec)
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
				
				priority0_ete_delay_gstathandle		= op_stat_reg ("priority0 ete delay",		OPC_STAT_INDEX_NONE, OPC_STAT_GLOBAL);
				priority1_ete_delay_gstathandle		= op_stat_reg ("priority1 ete delay",		OPC_STAT_INDEX_NONE, OPC_STAT_GLOBAL);
				priority2_ete_delay_gstathandle		= op_stat_reg ("priority2 ete delay",		OPC_STAT_INDEX_NONE, OPC_STAT_GLOBAL);
				priority3_ete_delay_gstathandle		= op_stat_reg ("priority3 ete delay",		OPC_STAT_INDEX_NONE, OPC_STAT_GLOBAL);
				priority4_ete_delay_gstathandle		= op_stat_reg ("priority4 ete delay",		OPC_STAT_INDEX_NONE, OPC_STAT_GLOBAL);
				priority5_ete_delay_gstathandle		= op_stat_reg ("priority5 ete delay",		OPC_STAT_INDEX_NONE, OPC_STAT_GLOBAL);
				priority6_ete_delay_gstathandle		= op_stat_reg ("priority6 ete delay",		OPC_STAT_INDEX_NONE, OPC_STAT_GLOBAL);
				priority7_ete_delay_gstathandle		= op_stat_reg ("priority7 ete delay",		OPC_STAT_INDEX_NONE, OPC_STAT_GLOBAL);
				
				throughput_gstathandle	= op_stat_reg ("Throughput (bits/sec)",		OPC_STAT_INDEX_NONE, OPC_STAT_GLOBAL);
				}
				FSM_PROFILE_SECTION_OUT (state1_enter_exec)

			/** state (INIT) exit executives **/
			FSM_STATE_EXIT_FORCED (1, "INIT", "sink_olsr [INIT exit execs]")


			/** state (INIT) transition processing **/
			FSM_TRANSIT_FORCE (0, state0_enter_exec, ;, "default", "", "INIT", "DISCARD", "tr_12", "sink_olsr [INIT -> DISCARD : default / ]")
				/*---------------------------------------------------------*/



			}


		FSM_EXIT (1,"sink_olsr")
		}
	}




void
_op_sink_olsr_diag (OP_SIM_CONTEXT_ARG_OPT)
	{
	/* No Diagnostic Block */
	}




void
_op_sink_olsr_terminate (OP_SIM_CONTEXT_ARG_OPT)
	{

	FIN_MT (_op_sink_olsr_terminate ())


	/* No Termination Block */

	Vos_Poolmem_Dealloc (op_sv_ptr);

	FOUT
	}


/* Undefine shortcuts to state variables to avoid */
/* syntax error in direct access to fields of */
/* local variable prs_ptr in _op_sink_olsr_svar function. */
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
#undef priority0_ete_delay_gstathandle
#undef priority1_ete_delay_gstathandle
#undef priority2_ete_delay_gstathandle
#undef priority3_ete_delay_gstathandle
#undef priority4_ete_delay_gstathandle
#undef priority5_ete_delay_gstathandle
#undef priority6_ete_delay_gstathandle
#undef priority7_ete_delay_gstathandle

#undef FIN_PREAMBLE_DEC
#undef FIN_PREAMBLE_CODE

#define FIN_PREAMBLE_DEC
#define FIN_PREAMBLE_CODE

VosT_Obtype
_op_sink_olsr_init (int * init_block_ptr)
	{
	VosT_Obtype obtype = OPC_NIL;
	FIN_MT (_op_sink_olsr_init (init_block_ptr))

	obtype = Vos_Define_Object_Prstate ("proc state vars (sink_olsr)",
		sizeof (sink_olsr_state));
	*init_block_ptr = 2;

	FRET (obtype)
	}

VosT_Address
_op_sink_olsr_alloc (VosT_Obtype obtype, int init_block)
	{
#if !defined (VOSD_NO_FIN)
	int _op_block_origin = 0;
#endif
	sink_olsr_state * ptr;
	FIN_MT (_op_sink_olsr_alloc (obtype))

	ptr = (sink_olsr_state *)Vos_Alloc_Object (obtype);
	if (ptr != OPC_NIL)
		{
		ptr->_op_current_block = init_block;
#if defined (OPD_ALLOW_ODB)
		ptr->_op_current_state = "sink_olsr [INIT enter execs]";
#endif
		}
	FRET ((VosT_Address)ptr)
	}



void
_op_sink_olsr_svar (void * gen_ptr, const char * var_name, void ** var_p_ptr)
	{
	sink_olsr_state		*prs_ptr;

	FIN_MT (_op_sink_olsr_svar (gen_ptr, var_name, var_p_ptr))

	if (var_name == OPC_NIL)
		{
		*var_p_ptr = (void *)OPC_NIL;
		FOUT
		}
	prs_ptr = (sink_olsr_state *)gen_ptr;

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
	if (strcmp ("priority0_ete_delay_gstathandle" , var_name) == 0)
		{
		*var_p_ptr = (void *) (&prs_ptr->priority0_ete_delay_gstathandle);
		FOUT
		}
	if (strcmp ("priority1_ete_delay_gstathandle" , var_name) == 0)
		{
		*var_p_ptr = (void *) (&prs_ptr->priority1_ete_delay_gstathandle);
		FOUT
		}
	if (strcmp ("priority2_ete_delay_gstathandle" , var_name) == 0)
		{
		*var_p_ptr = (void *) (&prs_ptr->priority2_ete_delay_gstathandle);
		FOUT
		}
	if (strcmp ("priority3_ete_delay_gstathandle" , var_name) == 0)
		{
		*var_p_ptr = (void *) (&prs_ptr->priority3_ete_delay_gstathandle);
		FOUT
		}
	if (strcmp ("priority4_ete_delay_gstathandle" , var_name) == 0)
		{
		*var_p_ptr = (void *) (&prs_ptr->priority4_ete_delay_gstathandle);
		FOUT
		}
	if (strcmp ("priority5_ete_delay_gstathandle" , var_name) == 0)
		{
		*var_p_ptr = (void *) (&prs_ptr->priority5_ete_delay_gstathandle);
		FOUT
		}
	if (strcmp ("priority6_ete_delay_gstathandle" , var_name) == 0)
		{
		*var_p_ptr = (void *) (&prs_ptr->priority6_ete_delay_gstathandle);
		FOUT
		}
	if (strcmp ("priority7_ete_delay_gstathandle" , var_name) == 0)
		{
		*var_p_ptr = (void *) (&prs_ptr->priority7_ete_delay_gstathandle);
		FOUT
		}
	*var_p_ptr = (void *)OPC_NIL;

	FOUT
	}

