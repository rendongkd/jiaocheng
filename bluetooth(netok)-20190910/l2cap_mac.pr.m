MIL_3_Tfile_Hdr_ 145A 140A modeler 9 5D70CF9F 5D737913 2 USER-20151017SA Administrator 0 0 none none 0 0 none 73E0C96F 4A49 0 0 0 0 0 0 1bcc 1                                                                                                                                                                                                                                                                                                                                                                                  ��g�      @   D   H      D  D'  D+  D/  D3  DM  HA  HE  8           	   begsim intrpt             ����      doc file            	nd_module      endsim intrpt             ����      failure intrpts            disabled      intrpt interval         ԲI�%��}����      priority              ����      recovery intrpts            disabled      subqueue         
            count    ���   
   ����   
      list   	���   
          
   
   super priority             ����          "   Objid	\node_id;       int	\listen_times;       int	\channel_busy;       List*	\time_buffer;       double	\channel_status_value;       double	\cycle_time;       int	\dest_addr;       int	\node_address;       int	\n;       List*	\record_UE_list;       List*	\slot_table;       int	\slot_index;       int	\beacon_num;       
int	\flag;       int	\slot_number;       int	\slot_assignment;       int	\sub_carrier_number;          /*declare variables*/   Packet*	pkptr;   Packet*	pktptr;       int 	dest,source,num=0;   //double	cur_time;   //double	*saved_time_ptr;       //Objid	dest_id;   //double	distance;       Packet*	pk;   	int type;   record_value* str;   //int size;   int i;   //int a[5],b[5];       slot_element* slot_str;   double time;   int t;   int slot,sub_number;   C   /*define symbolic constant*/   #define  instrm_from_low0 		0   #define  instrm_from_up 		1   #define  instrm_to_low0 		0   #define  instrm_to_up 			1   #define	 Time					100       #define	 back_off				0   #define	 send_frame				1000           #define	 FS						1//frame space   >#define	 FS_TIMES				0.00006//frame space times 60 microsecond   #define	 RX_INSTAT 			    0   )//#define  DATA_RATE				1000000     //bps           	//cmh add   #define	 Beacon_code					500   +#define  request_slot_resource_code     300   f#define  SEND_BEACON		        (op_intrpt_type() == OPC_INTRPT_SELF && op_intrpt_code() == Beacon_code)   w#define  REQUEST_SLOT_RESOURCE		(op_intrpt_type() == OPC_INTRPT_SELF && op_intrpt_code() == request_slot_resource_code)   #define  instrm_from_low2 		2   #define  instrm_to_low2 		2   #define  instrm_from_low3 		3   #define  instrm_to_low3 		3   #define  instrm_from_low4 		4   #define  instrm_to_low4 		4               ##define  tdma_code              600   -#define  slot_time              10E-3  //10ms   ##define  csma_code              700   ##define  send_code              800   /*define macros*/   �#define LOW_ARVL 			(op_intrpt_type() == OPC_INTRPT_STRM && (op_intrpt_strm() == instrm_from_low0 || op_intrpt_strm() == instrm_from_low2 || op_intrpt_strm() == instrm_from_low3 || op_intrpt_strm() == instrm_from_low4 ))   ^#define UP_ARVL 			(op_intrpt_type() == OPC_INTRPT_STRM && op_intrpt_strm() == instrm_from_up)   [#define SEND_TDMA 			(op_intrpt_type() == OPC_INTRPT_SELF && op_intrpt_code() == tdma_code)   [#define SEND_CSMA 			(op_intrpt_type() == OPC_INTRPT_SELF && op_intrpt_code() == csma_code)   Y#define send			    (op_intrpt_type() == OPC_INTRPT_SELF && op_intrpt_code() == send_code)           V#define TIME_BUFF 			(op_intrpt_type() == OPC_INTRPT_SELF && op_intrpt_code() == Time)       �#define	RX_BUSY				((op_intrpt_type()== OPC_INTRPT_STAT) && (op_intrpt_stat () == RX_INSTAT ) && op_stat_local_read (RX_INSTAT) == 1.0)   �#define	RX_IDLE				((op_intrpt_type()== OPC_INTRPT_STAT) && (op_intrpt_stat () == RX_INSTAT ) && op_stat_local_read (RX_INSTAT) == 0.0)           Jdouble	src_lat, src_long, src_alt, dest_lat, dest_long, dest_alt, x, y, z;       	//cmh add   1void op_pk_send2(Packet* pktptr, int stream_num);   typedef struct record_value   	{   	int UE_value;   	}record_value;       typedef struct slot_element   	{   	int node_num;   	int slot_num;   	int subcarrier_num;   	}slot_element;       (record_value * str_lookup(int address);    "record_value* create_new_insert();   3   2/*void op_pk_send2(Packet* pktptr, int stream_num)   	{   	   	Packet* 	pk;   	   &	FIN(op_pk_send2(pktptr, stream_num));       	//create and set MAC packet   "	pk=op_pk_create_fmt("nbiot_mac");   	   $	op_pk_nfd_set(pk,"DEST",dest_addr);   &	op_pk_nfd_set(pk,"SRC",node_address);   3	op_pk_nfd_set_pkt(pk, "DATA", pktptr);  //may fail   "	op_pk_nfd_set(pk,"Message ID",5);   	op_pk_send(pk, stream_num);   	   //	listen_times = 0;   6//	op_intrpt_schedule_self(op_sim_time()+FS_TIMES,FS);       	FOUT;   	}   */       (record_value * str_lookup(int address)     {         int st_size, i;         record_value * st_str;         FIN(str_lookup(address));     	   1    st_size = op_prg_list_size(record_UE_list);         for(i=0; i<st_size; i++)     	{     9        st_str = op_prg_list_access(record_UE_list, i);     +        if(st_str->UE_value == address)                   FRET(st_str);     	}         FRET(OPC_NIL);     }           !record_value* create_new_insert()   {   	record_value* st_str;   %	/*create a new connect table entry*/   B	st_str = (record_value *)op_prg_mem_alloc(sizeof(record_value));    	/*initializing variables*/   	st_str->UE_value = -1;    	   	   	return st_str;   }                                       Z            
   init   
       
      'node_id = op_topo_parent(op_id_self());       Zop_ima_obj_attr_get(node_id,"destination_address",&dest_addr);//get dest frome attributes;   :op_ima_obj_attr_get(node_id,"node_address",&node_address);   Brecord_UE_list = op_prg_list_create();//BS record the UE's address   4slot_table= op_prg_list_create();//create slot table       n=0;   cycle_time = 50E-3;//50ms   if(node_address == 0)//BS   4	op_intrpt_schedule_self(op_sim_time(),Beacon_code);   else//UE   C	op_intrpt_schedule_self(op_sim_time(),request_slot_resource_code);       slot_index = 0;       beacon_num =0;   7flag=0;//the lable to judge UE whether accrss BS or not    slot_number=0;//time slot number       ?slot_assignment=0;//the lable to judge UE whether get time slot       !sub_carrier_number=3;//subcarrier   
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
      //get pk from upper stream   "pkptr = op_pk_get(instrm_from_up);   if(node_address != 0)   	{   @	if (op_subq_pk_insert (1, pkptr, OPC_QPOS_TAIL) != OPC_QINS_OK)   		{   0		//if the insertion failed, discard the packet    		op_pk_destroy (pkptr);   		}     		else;      	}   else   "	op_pk_send(pkptr,instrm_to_low0);           
                     
   ����   
          pr_state        J  �          
   
lower_arvl   
       
   �   //get pk from lower stream   $pkptr = op_pk_get(op_intrpt_strm());       &op_pk_nfd_access(pkptr,"SRC",&source);   %op_pk_nfd_access(pkptr,"DEST",&dest);   %op_pk_nfd_access(pkptr,"Type",&type);       switch(type)   	{   %	case 10:  //receive BS beacon packet   		if(beacon_num == 0)   			{   �			op_intrpt_schedule_self(op_sim_time()+slot_time,tdma_code);//when UE receives the beacon packet firstly,the slot_time starts.   			}   		else;   		beacon_num=1;   		if(flag == 0)   			{   E			pk=op_pk_create_fmt("UE_request");	//in order to request access BS   #			op_pk_nfd_set(pk,"DEST",source);   (			op_pk_nfd_set(pk,"SRC",node_address);   "			op_pk_nfd_set(pk, "Type", 15);    \			if (op_subq_pk_insert (0, pk, OPC_QPOS_TAIL) != OPC_QINS_OK)//put the packet into buffer0   				{   2				//if the insertion failed, discard the packet    				op_pk_destroy (pk);   				}     				else;    4			op_intrpt_schedule_self(op_sim_time(),csma_code);   			}   !		else//flag=1,UE has accessed BS   			op_pk_destroy (pkptr);		   	break;   	   '	case 15://BS receive UE request packet   		if(node_address == dest)   		{   		str=str_lookup(source);	   		if(str == OPC_NIL)   			{   			str=create_new_insert();   			str->UE_value =source;   ;			op_prg_list_insert(record_UE_list,str,OPC_LISTPOS_TAIL);   			   T			pk=op_pk_create_fmt("ack_information");//tell UE that it accessed BS successfully   #			op_pk_nfd_set(pk,"DEST",source);   (			op_pk_nfd_set(pk,"SRC",node_address);   			op_pk_nfd_set(pk,"Type",12);   "			op_pk_send(pk, instrm_to_low0);   			}   		else;   		}   		else   			op_pk_destroy(pkptr);   	break;   				   ;	case 12://receive BS's ack information(UE has accessed BS)   		if(node_address == dest)   			{   
			flag=1;   '			op_subq_flush(0);//flush the queue 0   			}   		else   			op_pk_destroy(pkptr);   	break;   		   2	case 11://BS receive request slot resource packet   		if(node_address == dest)   		{   4		 pk=op_pk_create_fmt("uplink_assignment_message");   #		 op_pk_nfd_set(pk,"DEST",source);   (		 op_pk_nfd_set(pk,"SRC",node_address);   		 op_pk_nfd_set(pk,"Type",13);   6		 op_pk_nfd_set(pk,"MS_access_identity",slot_number);   <		 op_pk_nfd_set(pk,"PUSCH sub-carrier",sub_carrier_number);   "		 op_pk_send(pk, instrm_to_low0);   		 slot_number++;    		if(slot_number%4 == 0)   			{   			slot_number=0;   			sub_carrier_number++;   			}   		}   		else   			op_pk_destroy(pkptr);   	break;   	   1	case 13://UE receive time_slot_assignment packet   		if(node_address == dest)   		{   3		op_pk_nfd_get(pkptr,"MS_access_identity",&slot);    7		op_pk_nfd_get(pkptr,"PUSCH sub-carrier",&sub_number);   D		slot_str = (slot_element*)op_prg_mem_alloc(sizeof(slot_element));    $		slot_str->node_num = node_address;   		slot_str->slot_num = slot;   (		slot_str->subcarrier_num = sub_number;   <		op_prg_list_insert(slot_table,slot_str,OPC_LISTPOS_TAIL);    		slot_assignment=1;   &		op_subq_flush(0);//flush the queue 0   		}   		else   			op_pk_destroy(pkptr);   		   	break;   		   	case 100://receive data packet   !		op_pk_send(pkptr,instrm_to_up);   	break;   		   
	case 200:   		if(node_address == dest)   		{   "			op_pk_send(pkptr,instrm_to_up);   		}   		else   			op_pk_destroy(pkptr);   		   	break;   		   
	case 300:   		if(node_address == dest)   		{   "			op_pk_send(pkptr,instrm_to_up);   		}   		else   			op_pk_destroy(pkptr);   		   	break;   		   	default:  ;   	   	}           
                     
   ����   
          pr_state         �   Z          
   send_beacon   
       
   	   //create BS hello packet   "pk=op_pk_create_fmt("BS_beacon");	   op_pk_nfd_set(pk,"DEST",-1);   %op_pk_nfd_set(pk,"SRC",node_address);    op_pk_nfd_set(pk, "Type", 10);     op_pk_send(pk, instrm_to_low0);       //sending is cycle(10ms)   @op_intrpt_schedule_self(op_sim_time()+cycle_time,Beacon_code);     
                     
   ����   
          pr_state        �   Z          
   channel_idle   
       
      channel_busy = 0;   
                     
   ����   
          pr_state        :   �          
   channel_busy   
       
      channel_busy = 1;   
                     
   ����   
          pr_state      	  v            
   tdma   
       
      $if((slot_index>=0)&&(slot_index<=3))   <	op_intrpt_schedule_self(op_sim_time()+slot_time,tdma_code);   /*else if(slot_index == 3)   	{   <	op_intrpt_schedule_self(op_sim_time()+slot_time,tdma_code);   	slot_index = -1;	   	}*/       +for(i=0;i<op_prg_list_size(slot_table);i++)   	{   -	slot_str = op_prg_list_access(slot_table,i);   O	if((slot_str->node_num == node_address) && (slot_str->slot_num == slot_index))   		{   		if(!op_subq_empty(1))   			{   .			pkptr = op_subq_pk_remove(1,OPC_QPOS_HEAD);   )			sub_number = slot_str->subcarrier_num;    			op_pk_send(pkptr,sub_number);   			}   		else;   		}   	else;   	   	}       slot_index++;   if(slot_index == 4)   	{   	slot_index=0;   	}   else;   
                     
   ����   
          pr_state      
  v  �          
   csma   
       
      if(channel_busy == 0)   	{   	if(!op_subq_empty (0))   		   		{   		t =(int)op_dist_uniform(4);   		time=t*slot_time;   8		op_intrpt_schedule_self(op_sim_time()+time,send_code);   2		//pktptr = op_subq_pk_remove (0, OPC_QPOS_HEAD);   	   F		//op_pk_send(pktptr,instrm_to_low2);//send to stream 2 to low layer;   		}   	else;   	}   else//channel_busy =1   	{   	if(!op_subq_empty (0))   		{   =		op_intrpt_schedule_self(op_sim_time()+slot_time,csma_code);   		}   	}           
                     
   ����   
          pr_state        �  �          
   	send_csma   
       
      if(channel_busy == 0)   	{   	if(!op_subq_empty (0))   		{   0		pktptr = op_subq_pk_remove (0, OPC_QPOS_HEAD);   $		op_pk_send(pktptr,instrm_to_low2);   		}   	else;   	}   else   	{   	if(!op_subq_empty (0))   		{   =		op_intrpt_schedule_self(op_sim_time()+slot_time,csma_code);   		}   	}   
                     
   ����   
          pr_state         �  �          
   request_slot_resource   
       
      8if((flag== 1) && (!op_subq_empty(1)))//request slot time   	{   	if(slot_assignment == 0)   		{	   0		pk=op_pk_create_fmt("REQUEST_slot_resource");	   		op_pk_nfd_set(pk,"DEST",0);   '		op_pk_nfd_set(pk,"SRC",node_address);   "		op_pk_nfd_set(pk, "Type", 11);     [		if (op_subq_pk_insert (0, pk, OPC_QPOS_TAIL) != OPC_QINS_OK)//put the packet into buffer0   			{   1			//if the insertion failed, discard the packet    			op_pk_destroy (pk);   			}     		else;    3		op_intrpt_schedule_self(op_sim_time(),csma_code);   		}   9	else;//slot_assignment=1 this label UE has got time slot   (//		op_subq_flush(0);//flush the queue 0   	   	}   else;   `op_intrpt_schedule_self(op_sim_time()+cycle_time,request_slot_resource_code);//cycle time=10ms         	   	   	   	   
                     
   ����   
          pr_state                     �        W    K            
   tr_0   
       ����          ����          
    ����   
          ����                       pr_transition              C   t     E    E             
   tr_1   
       
   UP_ARVL   
       ����          
    ����   
          ����                       pr_transition              M   �     M     M            
   tr_2   
       ����          ����          
    ����   
          ����                       pr_transition              C  �     E    E  �          
   tr_10   
       
   LOW_ARVL   
       ����          
    ����   
          ����                       pr_transition              P  �     O  �  O  
          
   tr_11   
       ����          ����          
    ����   
          ����                       pr_transition      	         �  7     >      8      8            
   tr_14   
       
   default   
       ����          
    ����   
          ����                       pr_transition               �   �     7     �   e          
   tr_18   
       
   SEND_BEACON   
       ����          
    ����   
          ����                       pr_transition               �   �      �   h  D   �          
   tr_19   
       ����          ����          
    ����   
          ����                       pr_transition              �   �     P   �  �   ^          
   tr_20   
       
   RX_IDLE	   
       ����          
    ����   
          ����                       pr_transition              �   �     �   q  X            
   tr_23   
       ����          ����          
    ����   
          ����                       pr_transition              �   �     3   �  _            
   tr_22_1   
       ����          ����          
    ����   
          ����                       pr_transition              �   �     _   �  )   �          
   tr_24   
       
   RX_BUSY   
       ����          
    ����   
          ����                       pr_transition            	  �   �     ^    l            
   tr_25   
       
   	SEND_TDMA   
       ����          
    ����   
          ����                       pr_transition         	     �       c    \            
   tr_26   
       ����          ����          
    ����   
          ����                       pr_transition            
  �  K     \    q  y          
   tr_27   
       
   	SEND_CSMA   
       ����          
    ����   
          ����                       pr_transition         
     �  J     _  y  G            
   tr_29   
       ����          ����          
    ����   
          ����                       pr_transition              �  r     R  "  �  �          
   tr_30   
       
   send   
       ����          
    ����   
          ����                       pr_transition              �  f     �  �  Y  !          
   tr_31   
       ����          ����          
    ����   
          ����                       pr_transition      !         �  �     >  %   �  �          
   tr_33   
       
   REQUEST_SLOT_RESOURCE   
       ����          
    ����   
          ����                       pr_transition      "         �  e      �  �  <            
   tr_34   
       ����          ����          
    ����   
          ����                       pr_transition         #                  
link_delay           +   General Process Description:   ----------------------------        �The pc_fifo queueing process model accepts packets from any number of sources and holds them until it receives a request from another module to forward the next packet in the queue. The packets are forwarded in a first-in-first-out (FIFO) manner.        �Note that the request to forward the packets should come in the form of an "access interrupt" delivered by the module which is the destination module for the concerned packets.               ICI Interfaces:   ---------------        None                Packet Formats:   ---------------        None                Statistic Wires:   ----------------        None                Process Registry:   -----------------        Not Applicable               Restrictions:   -------------        F1. The pc_fifo process model must be contained within a queue module.        c2. The source stream index of the output packet stream of the surrounding queue module should be 0.        