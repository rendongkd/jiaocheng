MIL_3_Tfile_Hdr_ 145A 140A modeler 9 5D6882AB 5D727C9C 3 USER-20151017SA Administrator 0 0 none none 0 0 none 3B1D0723 4C6C 0 0 0 0 0 0 1bcc 1                                                                                                                                                                                                                                                                                                                                                                                  ��g�      @   D   H      
�  FJ  FN  FR  FV  Fp  Jd  Jh  
�           	   begsim intrpt             ����      doc file            	nd_module      endsim intrpt             ����      failure intrpts            disabled      intrpt interval         ԲI�%��}����      priority              ����      recovery intrpts            disabled      subqueue         
            count    ���   
   ����   
      list   	���   
          
   
   super priority             ����          
   Objid	\node_id;       int	\listen_times;       int	\channel_busy;       List*	\time_buffer;       double	\channel_status_value;          /*declare variables*/   Packet*	pkptr;   Packet*	pktptr;       int 	dest,source,num=0;   double	cur_time;   double	*saved_time_ptr;      /*define symbolic constant*/   #define  instrm_from_low 		0   #define  instrm_from_up 		1   #define  instrm_to_low 			0   #define  instrm_to_up 			1   #define	 Time					100       #define	 back_off				0   #define	 send_frame				1000           #define	 FS						1//frame space   >#define	 FS_TIMES				0.00006//frame space times 60 microsecond   #define	 RX_INSTAT 			    0   '#define  DATA_RATE				1000000     //bps       /*define macros*/   `#define LOW_ARVL 			(op_intrpt_type() == OPC_INTRPT_STRM && op_intrpt_code() == instrm_from_low)   ^#define UP_ARVL 			(op_intrpt_type() == OPC_INTRPT_STRM && op_intrpt_code() == instrm_from_up)       ]#define SEND_FRAME 			(op_intrpt_type() == OPC_INTRPT_SELF && op_intrpt_code() == send_frame)   V#define TIME_BUFF 			(op_intrpt_type() == OPC_INTRPT_SELF && op_intrpt_code() == Time)       �#define	RX_BUSY				((op_intrpt_type()== OPC_INTRPT_STAT) && (op_intrpt_stat () == RX_INSTAT ) && op_stat_local_read (RX_INSTAT) == 1.0)   �#define	RX_IDLE				((op_intrpt_type()== OPC_INTRPT_STAT) && (op_intrpt_stat () == RX_INSTAT ) && op_stat_local_read (RX_INSTAT) == 0.0)      0void op_pk_send2(Packet* pktptr, int stream_num)   	{   	int 		dest,source;   	Packet* 	pk;   	   '	FIN(op_pk_send2(pktptr1, stream_num));   	   (	node_id = op_topo_parent(op_id_self());   	   V	op_ima_obj_attr_get(node_id,"Destination Address",&dest);//get dest frome attributes;   5	op_ima_obj_attr_get(node_id,"node_address",&source);       	//create and set MAC packet   !	pk=op_pk_create_fmt("spma_mac");   	   	op_pk_nfd_set(pk,"DEST",dest);    	op_pk_nfd_set(pk,"SRC",source);   /	op_pk_nfd_set(pk, "DATA", pktptr);  //may fail   <	op_pk_nfd_set(pk,"FCS",1);//for the time being meaningless;   	   	op_pk_send(pk, stream_num);   	   //	listen_times = 0;   6//	op_intrpt_schedule_self(op_sim_time()+FS_TIMES,FS);       	FOUT;   	}                                 
      Z            
   init   
       
   
   'node_id = op_topo_parent(op_id_self());       Uop_ima_obj_attr_get(node_id,"Destination Address",&dest);//get dest frome attributes;   4op_ima_obj_attr_get(node_id,"node_address",&source);       #time_buffer = op_prg_list_create();       channel_status_value = 1.0;   	   Fop_intrpt_schedule_self(op_sim_time(), Time); //collect channel status   
                     
   ����   
          pr_state        J            
   idle   
       
       
                         ����             pr_state        J             
   
upper_arvl   
       
   P   //get pk from upper stream   "pkptr = op_pk_get(instrm_from_up);       num=(int)op_dist_uniform(4);       switch(num)   	{   	case 0:   A		if (op_subq_pk_insert (0, pkptr, OPC_QPOS_TAIL) != OPC_QINS_OK)   			{   4			/* if the insertion failed, discard the packet */   			op_pk_destroy (pkptr);   			}   		else;   	break;   			   	case 1:   A		if (op_subq_pk_insert (1, pkptr, OPC_QPOS_TAIL) != OPC_QINS_OK)   			{   4			/* if the insertion failed, discard the packet */   			op_pk_destroy (pkptr);   			}   		else;   	break;   			   	case 2:   A		if (op_subq_pk_insert (2, pkptr, OPC_QPOS_TAIL) != OPC_QINS_OK)   			{   4			/* if the insertion failed, discard the packet */   			op_pk_destroy (pkptr);   			}   		else;   	break;   			   	case 3:   A		if (op_subq_pk_insert (3, pkptr, OPC_QPOS_TAIL) != OPC_QINS_OK)   			{   4			/* if the insertion failed, discard the packet */   			op_pk_destroy (pkptr);   			}   		else;   	break;       		default:   	break;   	}       Mop_intrpt_schedule_self(op_sim_time(), send_frame);//self intrupt to send FSM           "//put the data pk into a mac frame   /*   &pkptr  = op_pk_create_fmt("spma_mac");   %op_pk_nfd_set(pkptr, "DATA", pktptr);   */   //send pk to lower layer   #//op_pk_send(pkptr, instrm_to_low);           /*   //allocate a list    5list_ptr = (List *) op_prg_mem_alloc (sizeof (List));       //initialize a list    op_prg_list_init (list_ptr);       1//move the contents of subqueue #0 into the list        2//determine the number of packets in the subqueue    /subq_size = op_subq_stat (0, OPC_QSTAT_PKSIZE);       for (i = 0; i < subq_size; i++)   	{   .	//take a single packet from the subqueue head   .	pkptr = op_subq_pk_remove (0, OPC_QPOS_HEAD);       (	//insert the packet onto the list tail    8	op_prg_list_insert (list_ptr, pkptr, OPC_LISTPOS_TAIL);   	}    */   
                     
   ����   
          pr_state        J  �          
   
lower_arvl   
       
      //get pk from lower stream   #pkptr = op_pk_get(instrm_from_low);       %op_pk_nfd_access(pkptr,"DEST",&dest);       'node_id = op_topo_parent(op_id_self());       4op_ima_obj_attr_get(node_id,"node_address",&source);       if(source == dest)   8	op_pk_send(pkptr,instrm_to_up);//send pk to upper layer   else   	op_pk_destroy(pkptr);       "//op_pk_send(pkptr, instrm_to_up);   
                     
   ����   
          pr_state        v            
   send   
       
   �   7if(channel_busy == 0)  //if channel is idle, send frame   	{   		if(!op_subq_empty (0))   			{   2				pktptr = op_subq_pk_remove (0, OPC_QPOS_HEAD);   F				op_pk_send2(pktptr,instrm_to_low);//send to stream 0 to low layer;   			}   		else if(!op_subq_empty (1))   			{   2				pktptr = op_subq_pk_remove (1, OPC_QPOS_HEAD);   &				op_pk_send2(pktptr,instrm_to_low);   			}   		else if(!op_subq_empty (2))   			{   2				pktptr = op_subq_pk_remove (2, OPC_QPOS_HEAD);   &				op_pk_send2(pktptr,instrm_to_low);   			}   		else if(!op_subq_empty (3))   			{   2				pktptr = op_subq_pk_remove (3, OPC_QPOS_HEAD);   &				op_pk_send2(pktptr,instrm_to_low);   			}   	}   /*   <else     //channel is busy, judge channel status value, spma   	{   \	if(channel_status_value <= 0.75 && channel_status_value > 0.5) //send frame with priority 0   		{   		if(!op_subq_empty (0))   			{   2				pktptr = op_subq_pk_remove (0, OPC_QPOS_HEAD);   F				op_pk_send2(pktptr,instrm_to_low);//send to stream 0 to low layer;   			}   		}       g	else if(channel_status_value <= 0.5 && channel_status_value > 0.25) //send frame with priority 0 and 1   		{   		if(!op_subq_empty (0))   			{   2				pktptr = op_subq_pk_remove (0, OPC_QPOS_HEAD);   F				op_pk_send2(pktptr,instrm_to_low);//send to stream 0 to low layer;   			}   		else if(!op_subq_empty (1))   			{   2				pktptr = op_subq_pk_remove (1, OPC_QPOS_HEAD);   &				op_pk_send2(pktptr,instrm_to_low);   			}   		else;   		}   	   i	else if(channel_status_value <= 0.25 && channel_status_value > 0) //send frame with priority 0, 1, and 2   		{   		if(!op_subq_empty (0))   			{   2				pktptr = op_subq_pk_remove (0, OPC_QPOS_HEAD);   F				op_pk_send2(pktptr,instrm_to_low);//send to stream 0 to low layer;   			}   		else if(!op_subq_empty (1))   			{   2				pktptr = op_subq_pk_remove (1, OPC_QPOS_HEAD);   &				op_pk_send2(pktptr,instrm_to_low);   			}   		else if(!op_subq_empty (2))   			{   2				pktptr = op_subq_pk_remove (2, OPC_QPOS_HEAD);   &				op_pk_send2(pktptr,instrm_to_low);   			}   		else;   		}   	   J	else if(channel_status_value <= 0) //send frame with priority 0, 1, and 2   		{   		if(!op_subq_empty (0))   			{   2				pktptr = op_subq_pk_remove (0, OPC_QPOS_HEAD);   F				op_pk_send2(pktptr,instrm_to_low);//send to stream 0 to low layer;   			}   		else if(!op_subq_empty (1))   			{   2				pktptr = op_subq_pk_remove (1, OPC_QPOS_HEAD);   &				op_pk_send2(pktptr,instrm_to_low);   			}   		else if(!op_subq_empty (2))   			{   2				pktptr = op_subq_pk_remove (2, OPC_QPOS_HEAD);   &				op_pk_send2(pktptr,instrm_to_low);   			}   		else if(!op_subq_empty (3))   			{   2				pktptr = op_subq_pk_remove (3, OPC_QPOS_HEAD);   &				op_pk_send2(pktptr,instrm_to_low);   			}   		else;   		}   	else;   	}   */	   //	listen_times = 0;       3//if a frame waits to be sent, re-enter send status   Wif(!op_subq_empty (0) || !op_subq_empty (1) || !op_subq_empty (2) ||!op_subq_empty (3))   B	op_intrpt_schedule_self(op_sim_time() + 0.001 + FS_TIMES,FS); //?   	   	   	   	   /*			if(listen_times == 10)   				{   '					if(op_prg_list_size(pk_buffer[0]))   						{   2						pktptr = op_prg_list_remove(pk_buffer[0],0);   						op_pk_destroy(pktptr);   						}   ,					else if(op_prg_list_size(pk_buffer[1]))   						{   2						pktptr = op_prg_list_remove(pk_buffer[1],0);   						op_pk_destroy(pktptr);   						}   ,					else if(op_prg_list_size(pk_buffer[2]))   						{   2						pktptr = op_prg_list_remove(pk_buffer[2],0);   						op_pk_destroy(pktptr);   						}   ,					else if(op_prg_list_size(pk_buffer[3]))   						{   2						pktptr = op_prg_list_remove(pk_buffer[3],0);   						op_pk_destroy(pktptr);   						}   				}   		   		else   				{   )				back_off_time = op_dist_uniform(1.0);   D				op_intrpt_schedule_self(op_sim_time() + back_off_time,back_off);   				listen_times++;   V				op_intrpt_schedule_self(op_sim_time(),instrm_from_up);//self intrupt back send FSM   				}   */   
                     
   ����   
          pr_state        :   Z          
   channel_idle   
       
      channel_busy = 0;//channle idle   
                     
   ����   
          pr_state        �  �          
   channle_busy   
       
      channel_busy = 1;//channel busy   
                     
   ����   
          pr_state         �   Z          
   	statistic   
       
   &   //statistic channel busy level   if(channel_busy == 1)   	{   	cur_time = op_sim_time();   	   I	if((op_prg_list_size(time_buffer)) <= 100)  //put current time into list   		{   8//		saved_time_ptr = op_prg_mem_alloc (sizeof (double));   //		*saved_time_ptr = cur_time;   @		op_prg_list_insert(time_buffer, &cur_time, OPC_LISTPOS_TAIL);	   		}   	else   		{   @		op_prg_list_remove(time_buffer, 0); //remove the first element   @		op_prg_list_insert(time_buffer, &cur_time, OPC_LISTPOS_TAIL);	   		}   	   	//check if element expire   &	if(op_prg_list_size(time_buffer) > 0)   		{   N		saved_time_ptr = (double*)op_prg_list_access(time_buffer, OPC_LISTPOS_HEAD);   	   *		while(cur_time - *saved_time_ptr >= 1.0)   			{   C			op_prg_list_remove(time_buffer, 0); //remove the expired element   (			if(op_prg_list_size(time_buffer) > 0)   P				saved_time_ptr = (double*)op_prg_list_access(time_buffer, OPC_LISTPOS_HEAD);   			else   
				break;   			}   		}   		   >	channel_status_value = (op_prg_list_size(time_buffer)) / 100;   		   	}       Rop_intrpt_schedule_self(op_sim_time()+0.001, Time); //to FSM statistic every 0.01s       
                     
   ����   
          pr_state      	   �  �          J   send_beacon   J       
      //create MASTER hello packet   //if(flag==0)   "pk=op_pk_create_fmt("MS_beacon");	   op_pk_nfd_set(pk,"DEST",0);   %op_pk_nfd_set(pk,"SRC",node_address);   op_pk_nfd_set(pk, "Type", 10);    op_pk_send(pk,instrm_to_low);   "//t=op_dist_uniform(10)*slot_time;                       
                     
   ����   
          pr_state      
  �  �          J   lower_arvl_0   J       
   g   //get pk from lower stream       	t=op_dist_uniform(100)*1E-3;   #pkptr = op_pk_get(instrm_from_low);   &op_pk_nfd_access(pkptr,"SRC",&source);   %op_pk_nfd_access(pkptr,"DEST",&dest);   %op_pk_nfd_access(pkptr,"Type",&type);   switch(type)   	{   	case 10 :{   	if(node_address==0)   	{   	pk=op_pk_create_fmt("rest");	   !	op_pk_nfd_set(pk,"DEST",source);   &	op_pk_nfd_set(pk,"SRC",node_address);   	op_pk_nfd_set(pk, "Type", 15);   	num=op_dist_uniform(3);   ?	if (op_subq_pk_insert (num, pk, OPC_QPOS_TAIL) != OPC_QINS_OK)   	{   	op_pk_destroy(pk);   1	op_intrpt_schedule_self(op_sim_time()+t,CSMA);};   	}   	else    		op_pk_destroy(pkptr);   		break;};   
	case 15 :   	{   (	if(node_address==dest&&node_address!=0)   	{   	flag=1;   B	pk=op_pk_create_fmt("re_ack");	//in order to request access node0   !	op_pk_nfd_set(pk,"DEST",source);   &	op_pk_nfd_set(pk,"SRC",node_address);   	op_pk_nfd_set(pk, "Type", 20);   	num=op_dist_uniform(3);   ?	if (op_subq_pk_insert (num, pk, OPC_QPOS_TAIL) != OPC_QINS_OK)   		{op_pk_destroy(pk);   2	op_intrpt_schedule_self(op_sim_time()+t,CSMA);};}   	else    	op_pk_destroy(pkptr);   		break;};   
	case 20 :   	{   	if(node_address==0)   	{		   B	pk=op_pk_create_fmt("rv_ack");	//in order to request access node0   !	op_pk_nfd_set(pk,"DEST",source);   &	op_pk_nfd_set(pk,"SRC",node_address);   	op_pk_nfd_set(pk, "Type", 25);   	num=op_dist_uniform(3);   ?	if (op_subq_pk_insert (num, pk, OPC_QPOS_TAIL) != OPC_QINS_OK)   		{op_pk_destroy(pk);   /	op_intrpt_schedule_self(op_sim_time()+t,CSMA);   	};   	}   	else    	op_pk_destroy(pkptr);   		break;};       case 25 :   	{   (	if(node_address==dest&&node_address!=0)   	{           printf("matched sucess");   	printf("flag=%d",flag);   	//t=op_dist_uniform(300E-3);   3	op_intrpt_schedule_self(op_sim_time()+t,acl_code);   	}   	else   	op_pk_destroy(pkptr);       break;};   	case 100 :   	{   	if(node_address==0)   		{   &	n=op_prg_list_size(record_node_list);    	op_pk_send(pkptr,instrm_to_up);   	pk=op_pk_create_fmt("data");	   !	op_pk_nfd_set(pk,"DEST",source);   	op_pk_nfd_set(pk,"SRC",0);    	op_pk_nfd_set(pk, "Type", 150);   	num=op_dist_uniform(3);   ?	if (op_subq_pk_insert (num, pk, OPC_QPOS_TAIL) != OPC_QINS_OK)   		{   		op_pk_destroy(pk);   1	op_intrpt_schedule_self(op_sim_time()+t,CSMA);};   	   		}   	else    		op_pk_destroy(pkptr);break;};   	case 150 :   	{   )		if(node_address==dest&&node_address!=0)   			{   			op_pk_destroy(pkptr);   5			op_intrpt_schedule_self(op_sim_time()+t,acl_code);   			};   		break;   		};   	}   	           
                     
   ����   
          pr_state                     �        W    K            
   tr_0   
       ����          ����          
    ����   
          ����                       pr_transition              &   �     E    E             
   tr_1   
       
   UP_ARVL   
       ����          
    ����   
          ����                       pr_transition              M   �     M     M            
   tr_2   
       ����          ����          
    ����   
          ����                       pr_transition                o     E    E  �          
   tr_10   
       
   LOW_ARVL   
       ����          
    ����   
          ����                       pr_transition              O  e     O  �  O  
          
   tr_11   
       ����          ����          
    ����   
          ����                       pr_transition      	        �   �     >    �   �  l   �  8            
   tr_14   
       
   default   
       ����          
    ����   
          ����                       pr_transition      
        �   �     S     5   N          
   tr_19   
       
   RX_IDLE   
       ����          
    ����   
          ����                       pr_transition              �   �     >   j  ]  
          
   tr_20   
       ����          ����          
    ����   
          ����                       pr_transition              �   �     Y    u            
   tr_21   
       
   
SEND_FRAME   
       ����          
    ����   
          ����                       pr_transition              �       m    Z            
   tr_22   
       ����          ����          
    ����   
          ����                       pr_transition              �  G     Y    �  ~          
   tr_23   
       
   RX_BUSY   
       ����          
    ����   
          ����                       pr_transition              �  Q     �  �  K            
   tr_24   
       ����          ����          
    ����   
          ����                       pr_transition               �   �     E     �   Y          
   tr_25   
       
   	TIME_BUFF   
       ����          
    ����   
          ����                       pr_transition               �   �      �   U  T  	          
   tr_26   
       ����          ����          
    ����   
          ����                       pr_transition            	   �  [     :     �  v          J   tr_18   J       
   SEND_BEACON   
       ����          
    ����   
          ����                       pr_transition         	       \      �  �  =             J   tr_27   J       ����          ����          
    ����   
          ����                       pr_transition            
  �  q     S  #  �  �          J   tr_12   J       
   LOW_ARVL   
       ����          
    ����   
          ����                       pr_transition         
     �  p     �  �  Y  !          J   tr_13   J       ����          ����          
    ����   
          ����                       pr_transition                           
link_delay           +   General Process Description:   ----------------------------        �The pc_fifo queueing process model accepts packets from any number of sources and holds them until it receives a request from another module to forward the next packet in the queue. The packets are forwarded in a first-in-first-out (FIFO) manner.        �Note that the request to forward the packets should come in the form of an "access interrupt" delivered by the module which is the destination module for the concerned packets.               ICI Interfaces:   ---------------        None                Packet Formats:   ---------------        None                Statistic Wires:   ----------------        None                Process Registry:   -----------------        Not Applicable               Restrictions:   -------------        F1. The pc_fifo process model must be contained within a queue module.        c2. The source stream index of the output packet stream of the surrounding queue module should be 0.        