MIL_3_Tfile_Hdr_ 145A 140A modeler 9 5D6C7452 5D771638 E8 7FPCYKRFROZNOYF Zhi@Ren 0 0 none none 0 0 none A68B9C31 34E7 0 0 0 0 0 0 1d79 5                                                                                                                                                                                                                                                                                                                                                                                       ��g�      @   D   H      �  .�  .�  .�  .�  .�  2�  2�  �           	   begsim intrpt         
   ����   
   doc file            	nd_module      endsim intrpt         
   ����   
   failure intrpts            disabled      intrpt interval         ԲI�%��}����      priority              ����      recovery intrpts            disabled      subqueue         
            count    ���   
   ����   
      list   	���   
          
   
   super priority             ����          .   Objid	\node_id;       int	\listen_times;       double	\channel_status_value;       double	\cycle_time;       int	\dest_addr;       int	\node_address;       int	\n;       List*	\record_slave_list;       int	\beacon_num;       
int	\flag;       int	\i;       List*	\data_packet;       List*	\record_node;       List*	\slot_table;       int	\node_number;       int	\slot_number;       int	\channel;       int	\setout;       List*	\record_node_list;       int	\channel_busy;       int	\slot_time;       int	\time_index;       Stathandle	\join_net;          /*declare variables*/   Packet*	pkptr;       int 	dest,source;   Packet*	pk;   Packet* bt;   	int type;   	double t;               !   /*define symbolic constant*/   #include <iostream.h>    #define  instrm_from_low		0   #define  instrm_from_up 		1   #define  instrm_to_low		    0   #define  instrm_to_up 			1   #define	 RX_INSTAT 			    0    &#define   group                   1500   "#define   tdma                1400   "#define   CSMA_d              1300       	//cmh add   #define	 beacon_code					500   +#define  request_slot_resource_code     300   +#define  csma_code                      800       f#define  SEND_BEACON		        (op_intrpt_type() == OPC_INTRPT_SELF && op_intrpt_code() == beacon_code)   b#define  SEND_CSMA		        (op_intrpt_type() == OPC_INTRPT_SELF && op_intrpt_code() == csma_code)   "#define  acl_code              700   7#define FREE (op_stat_local_read (CH_BUSY_STAT) == 0.0)   4#define PKTS_QUEUED (!op_strm_empty (instrm_to_low))   �#define	RX_BUSY				((op_intrpt_type()== OPC_INTRPT_STAT) && (op_intrpt_stat () == RX_INSTAT ) && op_stat_local_read (RX_INSTAT) == 1.0)   �#define	RX_IDLE				((op_intrpt_type()== OPC_INTRPT_STAT) && (op_intrpt_stat () == RX_INSTAT ) && op_stat_local_read (RX_INSTAT) == 0.0)   /*define macros*/   c#define LOW_ARVL 			(op_intrpt_type() == OPC_INTRPT_STRM &&(op_intrpt_strm() == instrm_from_low  ))   ^#define UP_ARVL 			(op_intrpt_type() == OPC_INTRPT_STRM && op_intrpt_strm() == instrm_from_up)   ^#define	SEND_DATA			((op_intrpt_type()== OPC_INTRPT_SELF) && (op_intrpt_code () == acl_code) )   U#define	TDMA			((op_intrpt_type()== OPC_INTRPT_SELF) && (op_intrpt_code () == tdma) )   a#define CSMA                ( op_intrpt_type() == OPC_INTRPT_SELF) &&(op_intrpt_code() == CSMA_d)       _#define GROUP              ( op_intrpt_type() == OPC_INTRPT_SELF) &&(op_intrpt_code() == group)       #Stathandle		join_net_time_gshandle;      0void op_pk_send2(Packet* pktptr, int stream_num)   	{   	int 		dest,source;   	Packet* 	pk;   	   '	FIN(op_pk_send2(pktptr1, stream_num));   	   (	node_id = op_topo_parent(op_id_self());   	   V	op_ima_obj_attr_get(node_id,"Destination Address",&dest);//get dest frome attributes;   5	op_ima_obj_attr_get(node_id,"node_address",&source);       	//create and set MAC packet   !	pk=op_pk_create_fmt("spma_mac");   	   	op_pk_nfd_set(pk,"DEST",dest);    	op_pk_nfd_set(pk,"SRC",source);   /	op_pk_nfd_set(pk, "DATA", pktptr);  //may fail   <	op_pk_nfd_set(pk,"FCS",1);//for the time being meaningless;   	   	op_pk_send(pk, stream_num);   	   //	listen_times = 0;   6//	op_intrpt_schedule_self(op_sim_time()+FS_TIMES,FS);       	FOUT;   	}                                           �            
   init   
       J      'node_id = op_topo_parent(op_id_self());       Zop_ima_obj_attr_get(node_id,"destination_address",&dest_addr);//get dest frome attributes;   :op_ima_obj_attr_get(node_id,"node_address",&node_address);       +//record_slave_list = op_prg_list_create();   slot_time=10E-3;   time_index=0;   'cycle_time = 1;  //1s, broadcast beacon   flag=0;       if(node_address!=0)     {       (//record_node_list=op_prg_list_create();   "//slot_table=op_prg_list_create();   Kop_intrpt_schedule_self(op_sim_time() + op_dist_uniform(2.0), beacon_code);       };       \join_net_time_gshandle = op_stat_reg("Join Net Time", OPC_STAT_INDEX_NONE, OPC_STAT_GLOBAL);   J                     
   ����   
          pr_state        J            
   idle   
       
       
                         ����             pr_state        J   Z          
   
upper_arvl   
       
   
       t=op_dist_uniform(10)*(2E-3);   "pkptr = op_pk_get(instrm_from_up);   '//op_pk_nfd_access(pkptr,"Type",&type);   )op_subq_pk_insert(3,pkptr,OPC_QPOS_TAIL);   ,op_intrpt_schedule_self(op_sim_time(),CSMA);   "//op_pk_send(pkptr,instrm_to_low);               
                     
   ����   
          pr_state        J  �          
   
lower_arvl   
       J   p       $	pkptr = op_pk_get(instrm_from_low);   '	op_pk_nfd_access(pkptr,"SRC",&source);   &	op_pk_nfd_access(pkptr,"DEST",&dest);   &	op_pk_nfd_access(pkptr,"Type",&type);   	   	switch(type)   		{   		case 10 :  //receive beacon       		if(node_address==0&&flag==0)   			   				{     $					pk = op_pk_create_fmt("rest");	   %					op_pk_nfd_set(pk,"DEST",source);   *					op_pk_nfd_set(pk,"SRC",node_address);   <					op_pk_nfd_set(pk, "Type", 15);   //1st message to slave   					   C					op_pk_send_delayed (pk, instrm_to_low, op_dist_uniform(0.1));    					   					   /*					   >					if(op_subq_pk_insert (0, pk, OPC_QPOS_TAIL)!=OPC_QINS_OK)   						{   						op_pk_destroy(pk);   2						op_intrpt_schedule_self(op_sim_time(),CSMA);   						break;   						}   						else   1					op_intrpt_schedule_self(op_sim_time(),CSMA);   */				       		}   		   			break;;   		   (		case 15 :  //1st ACK from primary node   			{   			   		if(node_address==dest)   				{   					flag=1;   //join net   $					pk=op_pk_create_fmt("re_ack");	    					op_pk_nfd_set(pk,"DEST",0);   *					op_pk_nfd_set(pk,"SRC",node_address);   #					op_pk_nfd_set(pk, "Type", 20);   "					op_pk_send(pk,instrm_to_low);       9					op_stat_write(join_net_time_gshandle, node_address);   					}   		else    			op_pk_destroy(pkptr);   
		break;};   		   		case 20 :   		{   		if(node_address==0)   			{	   #				pk=op_pk_create_fmt("rv_ack");	   $				op_pk_nfd_set(pk,"DEST",source);   )				op_pk_nfd_set(pk,"SRC",node_address);   "				op_pk_nfd_set(pk, "Type", 25);   		   <			if(op_subq_pk_insert (1, pk, OPC_QPOS_TAIL)==OPC_QINS_OK)   			   /			op_intrpt_schedule_self(op_sim_time(),CSMA);   			else   				op_pk_destroy(pk);   				}   		   			   	   		else    		op_pk_destroy(pkptr);   
		break;};   		case 25 :   		{   		if(node_address==dest)   			{   )            op_stat_write(join_net,flag);   			printf("matched sucess");   			printf("flag=%d",flag);   			   #			op_pk_send(pkptr,instrm_to_low);   		}   		else   		op_pk_destroy(pkptr);   
		break;};   		case 100 :   			{   		if(node_address==0)   				{   				   		   !		op_pk_send(pkptr,instrm_to_up);       		   			}   		else     			op_pk_destroy(pkptr);break;};   		case 150 :   		{   			if(node_address==dest)   				{   #				op_pk_send(pkptr,instrm_to_up);   				};   				break;   			};   		}   		           J                     
   ����   
          pr_state         �   �          
   send_beacon   
       J      //create MASTER hello packet   if(flag==0)   	{   "//t=op_dist_uniform(10)*slot_time;   "pk=op_pk_create_fmt("MS_beacon");	   op_pk_nfd_set(pk,"DEST",-1);   %op_pk_nfd_set(pk,"SRC",node_address);   op_pk_nfd_set(pk, "Type", 10);   +//op_subq_pk_insert (0, pk, OPC_QPOS_TAIL);   op_pk_send(pk,instrm_to_low);       Aop_intrpt_schedule_self(op_sim_time() + cycle_time ,beacon_code);   };                       J                     
   ����   
          pr_state        �  �          
   channle_busy   
       
      channel_busy = 1;//channel busy   
                     
   ����   
          pr_state        �   �          
   channel_free   
       
      channel_busy=0;   
                     
   ����   
          pr_state        �            
   csma   
       
      t=op_dist_uniform(100);   7if(channel_busy == 0)  //if channel is idle, send frame   	{   		if(!op_subq_empty (0))   			{   .				bt = op_subq_pk_remove (0, OPC_QPOS_HEAD);   !				op_pk_send(bt,instrm_to_low);   			}   		else if(!op_subq_empty (1))   			{   .				bt = op_subq_pk_remove (1, OPC_QPOS_HEAD);   !				op_pk_send(bt,instrm_to_low);   			}   		else if(!op_subq_empty (2))   			{   .				bt = op_subq_pk_remove (2, OPC_QPOS_HEAD);   !				op_pk_send(bt,instrm_to_low);   			}   		else if(!op_subq_empty (3))   			{   .				bt = op_subq_pk_remove (3, OPC_QPOS_HEAD);   !				op_pk_send(bt,instrm_to_low);   			}   	};           Wif(!op_subq_empty (0) || !op_subq_empty (1) || !op_subq_empty (2) ||!op_subq_empty (3))   :	op_intrpt_schedule_self(op_sim_time() + slot_time,CSMA);    	   
                     
   ����   
          pr_state                     �        �    K            
   tr_0   
       ����          ����          
    ����   
          ����                       pr_transition              C   �     E    E   Y          
   tr_1   
       
   UP_ARVL   
       ����          
    ����   
          ����                       pr_transition              N   �     M   Z  M            
   tr_2   
       ����          ����          
    ����   
          ����                       pr_transition              C  u     E    E  �          
   tr_10   
       
   LOW_ARVL   
       ����          
    ����   
          ����                       pr_transition              S  j     O  �  O  
          
   tr_11   
       ����          ����          
    ����   
          ����                       pr_transition      	         �  S     >     �  W   �  3  8            
   tr_14   
       
   default   
       ����          
    ����   
          ����                       pr_transition               �   �     7     �   �          
   tr_18   
       
   SEND_BEACON   
       ����          
    ����   
          ����                       pr_transition                 �      �   �  D   �          
   tr_19   
       ����          ����          
    ����   
          ����                       pr_transition      /        �  O     L     �  ~          
   tr_24   
       
   RX_BUSY   
       ����          
    ����   
          ����                       pr_transition      0        �  ]     �  �  N  &          
   tr_27   
       ����          ����          
    ����   
          ����                       pr_transition      1        �   �     X   �  �   �          
   tr_49   
       
   RX_IDLE   
       ����          
    ����   
          ����                       pr_transition      2        �   �     �   �  ]   �          
   tr_50   
       ����          ����          
    ����   
          ����                       pr_transition      5        �           9            
   tr_53   
       ����          ����          
    ����   
          ����                       pr_transition      6        �       9                 
   tr_54   
       
   CSMA   
       ����          
    ����   
          ����                       pr_transition         =              Join Net Time        ������������        ԲI�%��}      
link_delay           +   General Process Description:   ----------------------------        �The pc_fifo queueing process model accepts packets from any number of sources and holds them until it receives a request from another module to forward the next packet in the queue. The packets are forwarded in a first-in-first-out (FIFO) manner.        �Note that the request to forward the packets should come in the form of an "access interrupt" delivered by the module which is the destination module for the concerned packets.               ICI Interfaces:   ---------------        None                Packet Formats:   ---------------        None                Statistic Wires:   ----------------        None                Process Registry:   -----------------        Not Applicable               Restrictions:   -------------        F1. The pc_fifo process model must be contained within a queue module.        c2. The source stream index of the output packet stream of the surrounding queue module should be 0.        