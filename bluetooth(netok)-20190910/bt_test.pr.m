MIL_3_Tfile_Hdr_ 145A 140A modeler 9 5D677A8B 5D68DFFB 45 USER-20151017SA Administrator 0 0 none none 0 0 none 256B18A7 2491 0 0 0 0 0 0 1bcc 1                                                                                                                                                                                                                                                                                                                                                                                 ��g�      @   D   H      Y  o  s  w  {  �  "�  "�  M           	   begsim intrpt             ����      doc file            	nd_module      endsim intrpt             ����      failure intrpts            disabled      intrpt interval         ԲI�%��}����      priority              ����      recovery intrpts            disabled      subqueue         
            count    ���   
   ����   
      list   	���   
          
   
   super priority             ����             Objid	\node_id;       int	\listen_times;       double	\channel_status_value;       double	\cycle_time;       int	\dest_addr;       double	\node_address;       int	\n;       List*	\record_slave_list;       int	\beacon_num;       
int	\flag;       	int	\num;          /*declare variables*/   Packet*	pkptr;       int 	dest,source;   Packet*	pk;   	int type;       (   /*define symbolic constant*/   #define  instrm_from_low		0   #define  instrm_from_up 		1   #define  instrm_to_low		    0   #define  instrm_to_up 			1       	//cmh add   #define	 beacon_code					500   +#define  request_slot_resource_code     300   f#define  SEND_BEACON		        (op_intrpt_type() == OPC_INTRPT_SELF && op_intrpt_code() == beacon_code)   w#define  REQUEST_SLOT_RESOURCE		(op_intrpt_type() == OPC_INTRPT_SELF && op_intrpt_code() == request_slot_resource_code)               "#define  acl_code              700       /*define macros*/   d#define LOW_ARVL 			(op_intrpt_type() == OPC_INTRPT_STRM && (op_intrpt_strm() == instrm_from_low  ))   ^#define UP_ARVL 			(op_intrpt_type() == OPC_INTRPT_STRM && op_intrpt_strm() == instrm_from_up)   ^#define	SEND_DATA			((op_intrpt_type()== OPC_INTRPT_SELF) && (op_intrpt_code () == acl_code) )                   	//cmh add   3/*void op_pk_send2(Packet* pktptr, int stream_num);   typedef struct record_value   	{   	int SLAVE_value;   	}record_value;       typedef struct slot_element   	{   	int node_num;   	int slot_num;   	int subcarrier_num;   	}slot_element;       (record_value * str_lookup(int address);    "record_value* create_new_insert();              */*record_value * str_lookup(int address)     {         int st_size, i;         record_value * st_str;         FIN(str_lookup(address));     	   4    st_size = op_prg_list_size(record_slave_list);         for(i=0; i<st_size; i++)     	{     <        st_str = op_prg_list_access(record_slave_list, i);     .        if(st_str->SLAVE_value == address)                   FRET(st_str);     	}         FRET(OPC_NIL);     }           !record_value* create_new_insert()   {   	record_value* st_str;   %	/*create a new connect table entry*/   D	//st_str = (record_value *)op_prg_mem_alloc(sizeof(record_value));    	/*initializing variables*/   	//st_str->SLAVE_value = -1;    	   	   	//return st_str;   //}                                       Z            
   init   
       
   
   node_id =op_id_self();       W//op_ima_obj_attr_get(node_id,"Destination Address",&dest);//get dest frome attributes;   :op_ima_obj_attr_get(node_id,"node address",&node_address);   >op_ima_obj_attr_get(node_id,"destination_address",&dest_addr);   +//record_slave_list = op_prg_list_create();   cycle_time = 50E-3;//50ms               
                     
   ����   
          pr_state        J            
   idle   
       
       
                         ����             pr_state        J   Z          
   
upper_arvl   
       J      //get pk from upper stream    pkptr=op_pk_get(instrm_from_up);   if(node_address==0)   	{   >op_intrpt_schedule_self(op_sim_time()+cycle_time,beacon_code);   }   else   !	op_pk_send(pkptr,instrm_to_low);   	           J                     
   ����   
          pr_state        J  �          
   
lower_arvl   
       J   %   //get pk from lower stream   #pkptr = op_pk_get(instrm_from_low);   &op_pk_nfd_access(pkptr,"SRC",&source);   %op_pk_nfd_access(pkptr,"DEST",&dest);   %op_pk_nfd_access(pkptr,"Type",&type);   ?pk=op_pk_create_fmt("rest");	//in order to request access node0   #			op_pk_nfd_set(pk,"DEST",source);   (			op_pk_nfd_set(pk,"SRC",node_address);   !			op_pk_nfd_set(pk, "Type", 15);   op_pk_send(pk,instrm_to_low);   /*switch(type)   	{   case 10:   if(source!=0){   ?pk=op_pk_create_fmt("rest");	//in order to request access node0   #			op_pk_nfd_set(pk,"DEST",source);   (			op_pk_nfd_set(pk,"SRC",node_address);   !			op_pk_nfd_set(pk, "Type", 15);   3op_pk_send(pk,instrm_to_low);op_pk_destroy(pkptr);}   else   op_pk_destroy(pkptr);   break;       case 15:   if(source!=0&&node_address==0)    	{pk=op_pk_create_fmt("ack_re");   !	op_pk_nfd_set(pk,"DEST",source);   (			op_pk_nfd_set(pk,"SRC",node_address);   "			op_pk_nfd_set(pk, "Type", 20);}   else    op_pk_destroy(pkptr);   break;       };               J                     
   ����   
          pr_state         �   Z          
   send_beacon   
       
      //create MASTER hello packet       	   "pk=op_pk_create_fmt("MS_beacon");	   op_pk_nfd_set(pk,"DEST",-1);   %op_pk_nfd_set(pk,"SRC",node_address);   op_pk_nfd_set(pk, "Type", 10);        op_pk_send(pk, instrm_to_low);       	           
                     
   ����   
          pr_state        �   Z          
   channel_idle   
       
       
                     
   ����   
          pr_state         �  �          
   request_slot_resource   
       
       
                     
   ����   
          pr_state                     �        W    K            
   tr_0   
       ����          ����          
    ����   
          ����                       pr_transition              C   �     E    E   Y          
   tr_1   
       
   UP_ARVL   
       ����          
    ����   
          ����                       pr_transition              M   �     M   Z  M            
   tr_2   
       ����          ����          
    ����   
          ����                       pr_transition              C  u     E    E  �          
   tr_10   
       
   LOW_ARVL   
       ����          
    ����   
          ����                       pr_transition              Q  e     O  �  O  
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
          ����                       pr_transition                 �      �   h  D   �          
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
          ����                       pr_transition      !         �  �     >  %   �  �          
   tr_33   
       
   REQUEST_SLOT_RESOURCE   
       ����          
    ����   
          ����                       pr_transition      "         �  f      �  �  <            
   tr_34   
       ����          ����          
    ����   
          ����                       pr_transition         #                  
link_delay           +   General Process Description:   ----------------------------        �The pc_fifo queueing process model accepts packets from any number of sources and holds them until it receives a request from another module to forward the next packet in the queue. The packets are forwarded in a first-in-first-out (FIFO) manner.        �Note that the request to forward the packets should come in the form of an "access interrupt" delivered by the module which is the destination module for the concerned packets.               ICI Interfaces:   ---------------        None                Packet Formats:   ---------------        None                Statistic Wires:   ----------------        None                Process Registry:   -----------------        Not Applicable               Restrictions:   -------------        F1. The pc_fifo process model must be contained within a queue module.        c2. The source stream index of the output packet stream of the surrounding queue module should be 0.        