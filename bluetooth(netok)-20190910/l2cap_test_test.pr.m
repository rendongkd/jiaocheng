MIL_3_Tfile_Hdr_ 145A 140A modeler 9 5D6F7F98 5D6FBC39 6 USER-20151017SA Administrator 0 0 none none 0 0 none B209673F 2DB6 0 0 0 0 0 0 1bcc 1                                                                                                                                                                                                                                                                                                                                                                                  ��g�      @   D   H        '�  '�  '�  '�  '�  +�  +�  
�           	   begsim intrpt             ����      doc file            	nd_module      endsim intrpt             ����      failure intrpts            disabled      intrpt interval         ԲI�%��}����      priority              ����      recovery intrpts            disabled      subqueue         
            count    ���   
   ����   
      list   	���   
          
   
   super priority             ����          (   Objid	\node_id;       int	\listen_times;       double	\channel_status_value;       double	\cycle_time;       int	\dest_addr;       int	\node_address;       int	\n;       List*	\record_slave_list;       int	\beacon_num;       
int	\flag;       int	\i;       List*	\data_packet;       List*	\record_node;       List*	\slot_table;       int	\node_number;       int	\slot_number;       int	\channel;       int	\setout;       List*	\record_node_list;       double	\MAC_address;       
   /*declare variables*/   Packet*	pkptr;       int 	dest,source;   Packet*	pk;   Packet* bt;   	int type;   //double t;              /*define symbolic constant*/   #define  instrm_from_low		0   #define  instrm_from_up 		1   #define  instrm_to_low		    0   #define  instrm_to_up 			1       	//cmh add   #define	 beacon_code					500   +#define  request_slot_resource_code     300   +#define  csma_code                      800   f#define  SEND_BEACON		        (op_intrpt_type() == OPC_INTRPT_SELF && op_intrpt_code() == beacon_code)   b#define  SEND_CSMA		        (op_intrpt_type() == OPC_INTRPT_SELF && op_intrpt_code() == csma_code)   "#define  acl_code              700       /*define macros*/   c#define LOW_ARVL 			(op_intrpt_type() == OPC_INTRPT_STRM &&(op_intrpt_strm() == instrm_from_low  ))   ^#define UP_ARVL 			(op_intrpt_type() == OPC_INTRPT_STRM && op_intrpt_strm() == instrm_from_up)   ^#define	SEND_DATA			((op_intrpt_type()== OPC_INTRPT_SELF) && (op_intrpt_code () == acl_code) )                          */*record_value * str_lookup(int address)     {         int st_size, i;         record_value * st_str;         FIN(str_lookup(address));     	   4    st_size = op_prg_list_size(record_slave_list);         for(i=0; i<st_size; i++)     	{     <        st_str = op_prg_list_access(record_slave_list, i);     .        if(st_str->SLAVE_value == address)                   FRET(st_str);     	}         FRET(OPC_NIL);     }           !record_value* create_new_insert()   {   	record_value* st_str;   %	/*create a new connect table entry*/   D	//st_str = (record_value *)op_prg_mem_alloc(sizeof(record_value));    	/*initializing variables*/   	//st_str->SLAVE_value = -1;    	   	   	//return st_str;   //}                                       Z            
   init   
       
      'node_id = op_topo_parent(op_id_self());       Zop_ima_obj_attr_get(node_id,"destination_address",&dest_addr);//get dest frome attributes;   8op_ima_obj_attr_get(node_id,"MAC_address",&MAC_address);   :op_ima_obj_attr_get(node_id,"node_address",&node_address);       +//record_slave_list = op_prg_list_create();   cycle_time = 500E-3;//50ms   flag=0;   if(node_address!=0)     {   beacon_num=0;   	setout=1;   
channel=0;   &record_node_list=op_prg_list_create();    slot_table=op_prg_list_create();   node_number=1;   1op_intrpt_schedule_self(op_sim_time(),csma_code);       };       
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
      //get pk from upper stream   "pkptr = op_pk_get(instrm_from_up);    op_pk_send(pkptr,instrm_to_low);               
                     
   ����   
          pr_state        J  �          
   
lower_arvl   
       J   j   //get pk from lower stream   #//if((op_q_empty (0) == OPC_FALSE))   	//{   (if(op_stat_local_read(CH_BUSY_STAT)==0))   	{   #pkptr = op_pk_get(instrm_from_low);   &op_pk_nfd_access(pkptr,"SRC",&source);   %op_pk_nfd_access(pkptr,"DEST",&dest);   &op_pk_nfd_access(pkptr,"Type",&type);}   .//op_subq_pk_insert (0, pkptr, OPC_QPOS_HEAD);   //};   switch(type)   	{   	case 10 :{   	if(node_address==0)   	{   (	//op_subq_pk_access (0, OPC_QPOS_HEAD);   	pk=op_pk_create_fmt("rest");	   !	op_pk_nfd_set(pk,"DEST",source);   &	op_pk_nfd_set(pk,"SRC",node_address);   	op_pk_nfd_set(pk, "Type", 15);   )	if(op_stat_local_read(CH_BUSY_STAT)==0))   	{   	op_pk_send(pk,instrm_to_low);   	}   )	//op_subq_pk_insert(0,pk,OPC_QPOS_HEAD);   	//_pk_send(pk,instrm_to_low);}   	else op_pk_destroy(pkptr);   		break;};   
	case 15 :   '	{//op_subq_pk_remove(0,OPC_QPOS_HEAD);   (	if(node_address==dest&&node_address!=0)   -	{ //if(op_stat_local_read(CH_BUSY_STAT)==0))   	flag=1;   	//if(!op_strm_empty (0);   '		//op_subq_pk_remove(0,,OPC_QPOS_HEAD)   B	pk=op_pk_create_fmt("re_ack");	//in order to request access node0   !	op_pk_nfd_set(pk,"DEST",source);   &	op_pk_nfd_set(pk,"SRC",node_address);   	op_pk_nfd_set(pk, "Type", 20);   )	if(op_stat_local_read(CH_BUSY_STAT)==0))   	{   	op_pk_send(pk,instrm_to_low);}   else    '	op_subq_pk_insert(0,pk,OPC_QPOS_HEAD);   }   	else    	op_pk_destroy(pkptr);   		break;};   
	case 20 :   	{   	if(node_address==0)   	{		   B	pk=op_pk_create_fmt("rv_ack");	//in order to request access node0   !	op_pk_nfd_set(pk,"DEST",source);   &	op_pk_nfd_set(pk,"SRC",node_address);   	op_pk_nfd_set(pk, "Type", 25);   )	if(op_stat_local_read(CH_BUSY_STAT)==0))   	op_pk_send(pk,instrm_to_low);}   	else    	op_pk_destroy(pkptr);   		break;};       case 25 :   	{   (	if(node_address==dest&&node_address!=0)   	{           printf("matched sucess");   	printf("flag=%d",flag);   	//t=op_dist_uniform(300E-3);   1	op_intrpt_schedule_self(op_sim_time(),acl_code);   	}   	else   	op_pk_destroy(pkptr);       break;};   	case 100 :   	{   	if(node_address==0)   		{   (//	n=op_prg_list_size(record_node_list);    	op_pk_send(pkptr,instrm_to_up);   	bt=op_pk_create_fmt("data");	   !	op_pk_nfd_set(bt,"DEST",source);   	op_pk_nfd_set(bt,"SRC",0);   !	op_pk_nfd_set(bt, "Type", 150);	   )	if(op_stat_local_read(CH_BUSY_STAT)==0))   	{   	op_pk_send(pk,instrm_to_low);}   else    '	op_subq_pk_insert(0,pk,OPC_QPOS_HEAD);   	   		}   	else    		op_pk_destroy(pkptr);break;};   	case 150 :   	{   )		if(node_address==dest&&node_address!=0)   			{   3			op_intrpt_schedule_self(op_sim_time(),acl_code);   			op_pk_destroy(pkptr);   5			//op_intrpt_schedule_self(op_sim_time(),acl_code);   			};break;};   	}               J                     
   ����   
          pr_state         �   Z          
   send_beacon   
       J   
   //create MASTER hello packet   //if(flag==0)   *//if(op_stat_local_read(CH_BUSY_STAT)==0))   "pk=op_pk_create_fmt("MS_beacon");	   op_pk_nfd_set(pk,"DEST",0);   %op_pk_nfd_set(pk,"SRC",node_address);    op_pk_nfd_set(pk, "Type", 10);     op_pk_send(pk, instrm_to_low);           J                     
   ����   
          pr_state        �   Z          
   	DATA_SEND   
       
          $	op_prg_list_init(record_node_list);   %	//pf=fopen("node_address.txt","a+");   A	//&source=op_prg_list_access(record_node_list,OPC_LISTPOS_TAIL);   $	bt=op_pk_create_fmt("data_slave");	   	op_pk_nfd_set(bt,"DEST",0);   &	op_pk_nfd_set(bt,"SRC",node_address);    	op_pk_nfd_set(bt, "Type", 100);   !    op_pk_send(bt,instrm_to_low);   $	op_prg_list_size(record_node_list);       
                     
   ����   
          pr_state      	   �  �          
   	bind_csma   
       
      if(channel==0&&setout==1)   A	{op_intrpt_schedule_self(op_sim_time()+cycle_time,beacon_code);}           
                     
   ����   
          pr_state                     �        W    K            
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
          ����                       pr_transition              R  �     O  �  O  
          
   tr_11   
       ����          ����          
    ����   
          ����                       pr_transition      	        �   �     >    �    �   �  8            
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
   	SEND_DATA   
       ����          
    ����   
          ����                       pr_transition              �   �     �   q  X            
   tr_23   
       ����          ����          
    ����   
          ����                       pr_transition      %      	   �  G     =     �            
   tr_25   
       
   	SEND_CSMA   
       ����          
    ����   
          ����                       pr_transition      &   	      �  V      �  �  D            
   tr_26   
       ����          ����          
    ����   
          ����                       pr_transition      
   +                  
link_delay           +   General Process Description:   ----------------------------        �The pc_fifo queueing process model accepts packets from any number of sources and holds them until it receives a request from another module to forward the next packet in the queue. The packets are forwarded in a first-in-first-out (FIFO) manner.        �Note that the request to forward the packets should come in the form of an "access interrupt" delivered by the module which is the destination module for the concerned packets.               ICI Interfaces:   ---------------        None                Packet Formats:   ---------------        None                Statistic Wires:   ----------------        None                Process Registry:   -----------------        Not Applicable               Restrictions:   -------------        F1. The pc_fifo process model must be contained within a queue module.        c2. The source stream index of the output packet stream of the surrounding queue module should be 0.        