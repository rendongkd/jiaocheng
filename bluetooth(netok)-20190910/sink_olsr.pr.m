MIL_3_Tfile_Hdr_ 145A 140A modeler 9 5DB2650A 5DBA4307 7 7FPCYKRFROZNOYF Zhi@Ren 0 0 none none 0 0 none E8F0B99E 27F0 0 0 0 0 0 0 1d79 5                                                                                                                                                                                                                                                                                                                                                                                        ��g�      @   D   H    �  �  �  �  O  $  $  %�  %�  �           	   begsim intrpt         
   ����   
   doc file            	nd_module      endsim intrpt             ����      failure intrpts            disabled      intrpt interval         ԲI�%��}����      priority              ����      recovery intrpts            disabled      subqueue         
            count    ���   
   ����   
      list   	���   
          
   
   super priority             ����            begsim intrpt      begsim intrpt����   ����           ����          ����          ����                     $   !Stathandle	\bits_rcvd_stathandle;       $Stathandle	\bitssec_rcvd_stathandle;       !Stathandle	\pkts_rcvd_stathandle;       $Stathandle	\pktssec_rcvd_stathandle;       !Stathandle	\ete_delay_stathandle;       "Stathandle	\bits_rcvd_gstathandle;       %Stathandle	\bitssec_rcvd_gstathandle;       "Stathandle	\pkts_rcvd_gstathandle;       %Stathandle	\pktssec_rcvd_gstathandle;       "Stathandle	\ete_delay_gstathandle;       ,Stathandle	\priority0_ete_delay_gstathandle;       ,Stathandle	\priority1_ete_delay_gstathandle;       ,Stathandle	\priority2_ete_delay_gstathandle;       ,Stathandle	\priority3_ete_delay_gstathandle;       ,Stathandle	\priority4_ete_delay_gstathandle;       ,Stathandle	\priority5_ete_delay_gstathandle;       ,Stathandle	\priority6_ete_delay_gstathandle;       ,Stathandle	\priority7_ete_delay_gstathandle;          Packet*		pkptr;   double		pk_size;   double		ete_delay;   int priority1=0;      "Stathandle throughput_gstathandle;       double	total_pk_size = 0.0;   extern double	start_time1;                                       	   �   Z          
   DISCARD   
                     J   C   !/* Obtain the incoming packet.	*/   &pkptr = op_pk_get (op_intrpt_strm ());   .op_pk_nfd_access(pkptr,"priority",&priority1);   '/* Caclulate metrics to be updated.		*/   0pk_size = (double) op_pk_total_size_get (pkptr);       total_pk_size += pk_size;       //output throughput   7if(start_time1 > 0 && start_time1 < (op_sim_time() -1))   V	op_stat_write(throughput_gstathandle, total_pk_size / (op_sim_time() - start_time1));   	   else;	       =ete_delay = op_sim_time () - op_pk_creation_time_get (pkptr);       switch(priority1)   	{   	case 0:   :	op_stat_write(priority0_ete_delay_gstathandle,ete_delay);   	break;   	case 1:   :	op_stat_write(priority1_ete_delay_gstathandle,ete_delay);   	break;   	case 2:   :	op_stat_write(priority2_ete_delay_gstathandle,ete_delay);   	break;	   	case 3:   :	op_stat_write(priority3_ete_delay_gstathandle,ete_delay);   	break;	   	case 4:   :	op_stat_write(priority4_ete_delay_gstathandle,ete_delay);   	break;	   	case 5:   :	op_stat_write(priority5_ete_delay_gstathandle,ete_delay);   	break;	   	case 6:   :	op_stat_write(priority6_ete_delay_gstathandle,ete_delay);   	break;   	case 7:   :	op_stat_write(priority7_ete_delay_gstathandle,ete_delay);   	break;   
	default:;   	}       !/* Update local statistics.				*/   0op_stat_write (bits_rcvd_stathandle, 		pk_size);   ,op_stat_write (pkts_rcvd_stathandle, 		1.0);   2op_stat_write (ete_delay_stathandle, 		ete_delay);       2op_stat_write (bitssec_rcvd_stathandle, 	pk_size);   .op_stat_write (bitssec_rcvd_stathandle, 	0.0);   .op_stat_write (pktssec_rcvd_stathandle, 	1.0);   .op_stat_write (pktssec_rcvd_stathandle, 	0.0);       /* Update global statistics.	*/   1op_stat_write (bits_rcvd_gstathandle, 		pk_size);   -op_stat_write (pkts_rcvd_gstathandle, 		1.0);   3op_stat_write (ete_delay_gstathandle, 		ete_delay);       3op_stat_write (bitssec_rcvd_gstathandle, 	pk_size);   /op_stat_write (bitssec_rcvd_gstathandle, 	0.0);   /op_stat_write (pktssec_rcvd_gstathandle, 	1.0);   /op_stat_write (pktssec_rcvd_gstathandle, 	0.0);       "/* Destroy the received packet.	*/   op_pk_destroy (pkptr);   J           ����             pr_state         Z   Z          
   INIT   
       
      ./* Initilaize the statistic handles to keep	*/   ./* track of traffic sinked by this process.	*/   ubits_rcvd_stathandle 		= op_stat_reg ("Traffic Sink.Traffic Received (bits)",			OPC_STAT_INDEX_NONE, OPC_STAT_LOCAL);   zbitssec_rcvd_stathandle 	= op_stat_reg ("Traffic Sink.Traffic Received (bits/sec)",		OPC_STAT_INDEX_NONE, OPC_STAT_LOCAL);   wpkts_rcvd_stathandle 		= op_stat_reg ("Traffic Sink.Traffic Received (packets)",		OPC_STAT_INDEX_NONE, OPC_STAT_LOCAL);   |pktssec_rcvd_stathandle 	= op_stat_reg ("Traffic Sink.Traffic Received (packets/sec)",	OPC_STAT_INDEX_NONE, OPC_STAT_LOCAL);   vete_delay_stathandle		= op_stat_reg ("Traffic Sink.End-to-End Delay (seconds)",		OPC_STAT_INDEX_NONE, OPC_STAT_LOCAL);       wbits_rcvd_gstathandle 		= op_stat_reg ("Traffic Sink.Traffic Received (bits)",			OPC_STAT_INDEX_NONE, OPC_STAT_GLOBAL);   |bitssec_rcvd_gstathandle 	= op_stat_reg ("Traffic Sink.Traffic Received (bits/sec)",		OPC_STAT_INDEX_NONE, OPC_STAT_GLOBAL);   ypkts_rcvd_gstathandle 		= op_stat_reg ("Traffic Sink.Traffic Received (packets)",		OPC_STAT_INDEX_NONE, OPC_STAT_GLOBAL);   ~pktssec_rcvd_gstathandle 	= op_stat_reg ("Traffic Sink.Traffic Received (packets/sec)",	OPC_STAT_INDEX_NONE, OPC_STAT_GLOBAL);   xete_delay_gstathandle		= op_stat_reg ("Traffic Sink.End-to-End Delay (seconds)",		OPC_STAT_INDEX_NONE, OPC_STAT_GLOBAL);       npriority0_ete_delay_gstathandle		= op_stat_reg ("priority0 ete delay",		OPC_STAT_INDEX_NONE, OPC_STAT_GLOBAL);   npriority1_ete_delay_gstathandle		= op_stat_reg ("priority1 ete delay",		OPC_STAT_INDEX_NONE, OPC_STAT_GLOBAL);   npriority2_ete_delay_gstathandle		= op_stat_reg ("priority2 ete delay",		OPC_STAT_INDEX_NONE, OPC_STAT_GLOBAL);   npriority3_ete_delay_gstathandle		= op_stat_reg ("priority3 ete delay",		OPC_STAT_INDEX_NONE, OPC_STAT_GLOBAL);   npriority4_ete_delay_gstathandle		= op_stat_reg ("priority4 ete delay",		OPC_STAT_INDEX_NONE, OPC_STAT_GLOBAL);   npriority5_ete_delay_gstathandle		= op_stat_reg ("priority5 ete delay",		OPC_STAT_INDEX_NONE, OPC_STAT_GLOBAL);   npriority6_ete_delay_gstathandle		= op_stat_reg ("priority6 ete delay",		OPC_STAT_INDEX_NONE, OPC_STAT_GLOBAL);   npriority7_ete_delay_gstathandle		= op_stat_reg ("priority7 ete delay",		OPC_STAT_INDEX_NONE, OPC_STAT_GLOBAL);       fthroughput_gstathandle	= op_stat_reg ("Throughput (bits/sec)",		OPC_STAT_INDEX_NONE, OPC_STAT_GLOBAL);   
                     
   ����   
          pr_state                	   	   �   �      �   u   �   �   �   m          
       
       ����          ����              ����             ����                       pr_transition            	   �   Y      s   Y   �   Y          
   tr_12   
       ����          ����          
@����   
          ����                       pr_transition                   End-to-End Delay (seconds)          FEnd-to-end delay of packets received by the traffic sink in this node.   Traffic Sink    bucket/default total/sample mean   linear        ԲI�%��}   Traffic Received (bits)          <Traffic received (in bits) by the traffic sink in this node.   Traffic Sink   bucket/default total/sum   linear        ԲI�%��}   Traffic Received (bits/sec)          @Traffic received (in bits/sec) by the traffic sink in this node.   Traffic Sink   bucket/default total/sum_time   linear        ԲI�%��}   Traffic Received (packets)          ?Traffic received (in packets) by the traffic sink in this node.   Traffic Sink   bucket/default total/sum   linear        ԲI�%��}   Traffic Received (packets/sec)          CTraffic received (in packets/sec) by the traffic sink in this node.   Traffic Sink   bucket/default total/sum_time   linear        ԲI�%��}      End-to-End Delay (seconds)          GEnd-to-end delay of packets received by traffic sinks across all nodes.   Traffic Sink    bucket/default total/sample mean   linear        ԲI�%��}   Traffic Received (bits)          ATraffic received (in bits) by the traffic sinks across all nodes.   Traffic Sink   bucket/default total/sum   linear        ԲI�%��}   Traffic Received (bits/sec)          ETraffic received (in bits/sec) by the traffic sinks across all nodes.   Traffic Sink   bucket/default total/sum_time   linear        ԲI�%��}   Traffic Received (packets)          DTraffic received (in packets) by the traffic sinks across all nodes.   Traffic Sink   bucket/default total/sum   linear        ԲI�%��}   Traffic Received (packets/sec)          HTraffic received (in packets/sec) by the traffic sinks across all nodes.   Traffic Sink   bucket/default total/sum_time   linear        ԲI�%��}   priority0 ete delay        ������������        ԲI�%��}   priority1 ete delay        ������������        ԲI�%��}   priority2 ete delay        ������������        ԲI�%��}   priority3 ete delay        ������������        ԲI�%��}   priority4 ete delay        ������������        ԲI�%��}   priority5 ete delay        ������������        ԲI�%��}   priority6 ete delay        ������������        ԲI�%��}   priority7 ete delay        ������������        ԲI�%��}   Throughput (bits/sec)        ������������        ԲI�%��}                  General Process Description:    ----------------------------    zThe sink process model accepts packets from any number of sources and discards them regardless of their content or format.       ICI Interfaces:    --------------    None        Packet Formats:    ---------------    None        Statistic Wires:    ----------------    None        Process Registry:    -----------------    Not Applicable       Restrictions:    -------------    None        