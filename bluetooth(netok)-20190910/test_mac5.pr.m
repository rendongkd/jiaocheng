MIL_3_Tfile_Hdr_ 145A 140A modeler 9 5D677CC5 5D677CC5 1 USER-20151017SA Administrator 0 0 none none 0 0 none 1C71C546 808A 0 0 0 0 0 0 1bcc 1                                                                                                                                                                                                                                                                                                                                                                                  ��g�      @   D   H        zh  zl  zp  zt  z�  ~�  ~�             	   begsim intrpt             ����      doc file            	nd_module      endsim intrpt             ����      failure intrpts            disabled      intrpt interval         ԲI�%��}����      priority              ����      recovery intrpts            disabled      subqueue         
            count    ���   
   ����   
      list   	���   
          
   
   super priority             ����          %   Objid	\node_id;       int	\listen_times;       int	\rx_busy;       List*	\time_buffer;       double	\channel_status_value;       int	\tx_busy;       int	\node_address;       /* communication range */   double	\comm_dist;       int	\dest_addr;       int	\cycle_time;       int	\beacon_num;       
int	\flag;       int	\node_number;       List*	\record_node_list;       List*	\slot_table;       int	\slot_index;       int	\slot_number;       int	\slot_assignment;          /*declare variables*/   Packet*	pkptr;   Packet*	pktptr;   Packet*	pk;   int 	dest, source,type;   Cint 	beacon_slot1=1, csma_slot1=6,tdma_slot1=15,bind_csma_slot1=20;   int i;   int	num = 0;   $double accept = 0.0, distance = 0.0;   slot_element* slot_str;   //int sub_number;   record_value* str;   	int slot;   //int sub_number;   int t;   double time;   >   /*define symbolic constant*/   #define  instrm_from_low 		0   #define  instrm_from_up 		1   #define  instrm_to_low 			0   #define  instrm_to_up 			1   //#define	 Time					100       #define	 back_off				0   #define	 send_csma				1000   #define	 bind_csma			2000   #define	 slot_control			3000   #define	 send_tdma				4000       %#define	 FS						1      //frame space   <#define	 FS_TIMES				10   //frame space times 60 microsecond    #define slot_time				10E-3//10MS       #define	 RX_INSTAT 			    0   //#define	 TX_INSTAT 			    1       +#define  DATA_RATE				1000000         //bps       /*define macros*/   `#define LOW_ARVL 			(op_intrpt_type() == OPC_INTRPT_STRM && op_intrpt_code() == instrm_from_low)   ^#define UP_ARVL 			(op_intrpt_type() == OPC_INTRPT_STRM && op_intrpt_code() == instrm_from_up)       Z#define BIND_CSMA			(op_intrpt_type() == OPC_INTRPT_SELF && op_intrpt_code() == bind_csma)   ^#define  SEND_BEACON		(op_intrpt_type() == OPC_INTRPT_SELF && op_intrpt_code() == Beacon_code)   Z#define SEND_CSMA			(op_intrpt_type() == OPC_INTRPT_SELF && op_intrpt_code() == send_csma)   `#define SLOT_CONTROL			(op_intrpt_type() == OPC_INTRPT_SELF && op_intrpt_code() == slot_control)   V#define TIME_BUFF 			(op_intrpt_type() == OPC_INTRPT_SELF && op_intrpt_code() == Time)   [#define SEND_TDMA 			(op_intrpt_type() == OPC_INTRPT_SELF && op_intrpt_code() == send_tdma)   �#define	RX_BUSY				((op_intrpt_type()== OPC_INTRPT_STAT) && (op_intrpt_stat () == RX_INSTAT ) && op_stat_local_read (RX_INSTAT) == 1.0)   �#define	RX_IDLE				((op_intrpt_type()== OPC_INTRPT_STAT) && (op_intrpt_stat () == RX_INSTAT ) && op_stat_local_read (RX_INSTAT) == 0.0)       �//#define	TX_BUSY				((op_intrpt_type()== OPC_INTRPT_STAT) && (op_intrpt_stat () == TX_INSTAT ) && op_stat_local_read (TX_INSTAT) == 1.0)   �//#define	TX_IDLE				((op_intrpt_type()== OPC_INTRPT_STAT) && (op_intrpt_stat () == TX_INSTAT ) && op_stat_local_read (TX_INSTAT) == 0.0)           	//cmh add   #define Beacon_code			500   ##define  tdma_code              600               	//cmh add   1void op_pk_send2(Packet* pktptr, int stream_num);   typedef struct record_value   	{   	int node_value;   	}record_value;       typedef struct slot_element   	{   	int node_num;   	int slot_num;   	int subcarrier_num;   	}slot_element;       (record_value * str_lookup(int address);    "record_value* create_new_insert();   ;//int 	beacon_slot1, csma_slot1,tdma_slot1,bind_csma_slot1;   E   0void op_pk_send2(Packet* pktptr, int stream_num)   	{   //	int 		dest,source;   //	Packet* 	pk;   	FILE*		fp;   	   &	FIN(op_pk_send2(pktptr, stream_num));   /*	   (	node_id = op_topo_parent(op_id_self());   	   V	op_ima_obj_attr_get(node_id,"Destination Address",&dest);//get dest frome attributes;   5	op_ima_obj_attr_get(node_id,"node_address",&source);       	//create and set MAC packet   !	pk=op_pk_create_fmt("spma_mac");   	   	op_pk_nfd_set(pk,"DEST",dest);    	op_pk_nfd_set(pk,"SRC",source);   /	op_pk_nfd_set(pk, "DATA", pktptr);  //may fail   <	op_pk_nfd_set(pk,"FCS",1);//for the time being meaningless;   	   	op_pk_send(pk, stream_num);   */   D	//op_pk_send_delayed(pktptr, stream_num,op_dist_uniform(FS_TIMES));    	op_pk_send(pktptr, stream_num);   '	fp = fopen("c:\\send_time.txt", "a+");   	if(fp != NULL)   		{   %		fprintf(fp, "\n%f", op_sim_time());   		fclose(fp);   		}   	else;   	   //	listen_times = 0;   6//	op_intrpt_schedule_self(op_sim_time()+FS_TIMES,FS);       	FOUT;   	}       (record_value * str_lookup(int address)     {         int st_size, i;         record_value * st_str;         FIN(str_lookup(address));     	   3    st_size = op_prg_list_size(record_node_list);         for(i=0; i<st_size; i++)     	{     ;        st_str = op_prg_list_access(record_node_list, i);     -        if(st_str->node_value == address)                   FRET(st_str) ;   	}         FRET(OPC_NIL);   }           !record_value* create_new_insert()   {   	record_value* st_str;   %	/*create a new connect table entry*/   B	st_str = (record_value *)op_prg_mem_alloc(sizeof(record_value));    	/*initializing variables*/   	st_str->node_value = -1;    	   	   	return st_str;   }                                               �            
   init   
       
      'node_id = op_topo_parent(op_id_self());       W//op_ima_obj_attr_get(node_id,"Destination Address",&dest);//get dest frome attributes;   :op_ima_obj_attr_get(node_id,"node address",&node_address);   >op_ima_obj_attr_get(node_id,"destination_address",&dest_addr);   channel_status_value = 1.0;           rx_busy = 1;   	   H//op_intrpt_schedule_self(op_sim_time(), Time); //collect channel status   cycle_time=50E-3;//50ms   if( node_address==0)   5	op_intrpt_schedule_self(op_sim_time(),slot_control);   //else;   beacon_num=0;   flag=0;    slot_number=0;//time slot number   (record_node_list = op_prg_list_create();   "slot_table = op_prg_list_create();   node_number=1;       
                     
   ����   
          pr_state        J            
   idle   
       
       
                         ����             pr_state        J   Z          
   
upper_arvl   
       
   S   //get pk from upper stream   "pkptr = op_pk_get(instrm_from_up);       //num=(int)op_dist_uniform(4);   num = 0;       switch(num)   	{   	case 0:   A		if (op_subq_pk_insert (0, pkptr, OPC_QPOS_TAIL) != OPC_QINS_OK)   			{   4			/* if the insertion failed, discard the packet */   			op_pk_destroy (pkptr);   			}   		else;   	break;   			   	case 1:   A		if (op_subq_pk_insert (1, pkptr, OPC_QPOS_TAIL) != OPC_QINS_OK)   			{   2			// if the insertion failed, discard the packet    			op_pk_destroy (pkptr);   			}   		else;   	break;   			   	case 2:   A		if (op_subq_pk_insert (2, pkptr, OPC_QPOS_TAIL) != OPC_QINS_OK)   			{   1			//if the insertion failed, discard the packet    			op_pk_destroy (pkptr);   			}   		else;   	break;   			   	case 3:   A		if (op_subq_pk_insert (3, pkptr, OPC_QPOS_TAIL) != OPC_QINS_OK)   			{   4			// if the insertion failed, discard the packet //   			op_pk_destroy (pkptr);   			}   		else;       	break;       		default:   	break;   	}   7op_intrpt_schedule_self(op_sim_time() , slot_control);    B//self intrupt to send pks, add a random period to avoid collision   R//op_intrpt_schedule_self(op_sim_time() + op_dist_uniform(FS_TIMES), send_frame);        ://op_intrpt_schedule_self(op_sim_time() + 20, send_frame);   "//put the data pk into a mac frame   /*   &pkptr  = op_pk_create_fmt("spma_mac");   %op_pk_nfd_set(pkptr, "DATA", pktptr);   */   //send pk to lower layer   #//op_pk_send(pkptr, instrm_to_low);           /*   //allocate a list    5list_ptr = (List *) op_prg_mem_alloc (sizeof (List));       //initialize a list    op_prg_list_init (list_ptr);       1//move the contents of subqueue #0 into the list        2//determine the number of packets in the subqueue    /subq_size = op_subq_stat (0, OPC_QSTAT_PKSIZE);       for (i = 0; i < subq_size; i++)   	{   .	//take a single packet from the subqueue head   .	pkptr = op_subq_pk_remove (0, OPC_QPOS_HEAD);       (	//insert the packet onto the list tail    8	op_prg_list_insert (list_ptr, pkptr, OPC_LISTPOS_TAIL);   	}    */   
                     
   ����   
          pr_state        J  �          
   
lower_arvl   
       
   �   //get pk from lower stream       #pkptr = op_pk_get(instrm_from_low);   &op_pk_nfd_access(pkptr,"SRC",&source);   %op_pk_nfd_access(pkptr,"DEST",&dest);   %op_pk_nfd_access(pkptr,"Type",&type);       if(type==10)   	{   5	op_pk_nfd_access(pkptr,"beacon_slot",&beacon_slot1);   1	op_pk_nfd_access(pkptr,"csma_slot",&csma_slot1);   1	op_pk_nfd_access(pkptr,"tdma_slot",&tdma_slot1);   ;	op_pk_nfd_access(pkptr,"bind_csma_slot",&bind_csma_slot1);   	}   $//////////////abz, consider distance   Xdistance = op_td_get_dbl (pkptr, OPC_TDA_BU_DISTANCE);  //get distance between tx and rx   if(distance == 0.0)    9	op_pk_destroy (pkptr);  //if distance = 0, do not accept       else   	   {       switch(type)   	{   	   	//receive node0 beacon packet   
	case 10:        		if(beacon_num == 0)   			{   ?			//beacon_num++;//to know how many becon packet has receive		   			beacon_num=1;   A			op_intrpt_schedule_self(op_sim_time()+slot_time,slot_control);   			}    		else//beacon_num==1   			{   A			op_intrpt_schedule_self(op_sim_time()+slot_time,slot_control);   			}   		   <	case 11:  // the second floor sta receive pco beacon packet   		   		if(flag == 0)   			{   J			pk=op_pk_create_fmt("node_request");	//in order to request access node0   #			op_pk_nfd_set(pk,"DEST",source);   (			op_pk_nfd_set(pk,"SRC",node_address);   "			op_pk_nfd_set(pk, "Type", 15);    #			//op_pk_send(pk, instrm_to_low);   \			if (op_subq_pk_insert (2, pk, OPC_QPOS_TAIL) != OPC_QINS_OK)//put the packet into buffer0   				{   2				//if the insertion failed, discard the packet    				op_pk_destroy (pk);   				}     			   				else;    			   >			op_intrpt_schedule_self(op_sim_time()+slot_time,send_csma);   			}   			   			   #		else//flag=1,node has accessed BS   			{   			op_pk_destroy (pkptr);		   			}   		   		break;        		//cco receive other sta packet   
		case 15:   		   M		if(node_address == 0)//&&(source >= 0 && source <= 5))//write  list approve   		{   ;			if(source >= 1 && source <= 15)//write node list approve   					{   					str=str_lookup(source);   					if(str == OPC_NIL)    						{   						str=create_new_insert();   						str->node_value =source;   @						op_prg_list_insert(record_node_list,str,OPC_LISTPOS_TAIL);   			   Y						pk=op_pk_create_fmt("ack_information");//tell node that it accessed BS successfully   &						op_pk_nfd_set(pk,"DEST",source);   +						op_pk_nfd_set(pk,"SRC",node_address);   9						op_pk_nfd_set(pk,"MS_access_identity",slot_number);   "						op_pk_nfd_set(pk,"Type",16);   $						op_pk_send(pk, instrm_to_low);   						slot_number++;   						}   
					else;   					}   g		//if the node is not belong to the write list ,it will not send req packet to network for 150 seconds   			else   				{   L				pk=op_pk_create_fmt("node_request2");	//in order to request access node0   				op_pk_nfd_set(pk,"DEST",0);   )				op_pk_nfd_set(pk,"SRC",node_address);   #				op_pk_nfd_set(pk, "Type", 17);    2				op_pk_send_delayed(pk, instrm_to_low,1);//150s   _				/*if (op_subq_pk_insert (1, pk, OPC_QPOS_TAIL) != OPC_QINS_OK)//put the packet into buffer0   				{   2				//if the insertion failed, discard the packet    				op_pk_destroy (pk);   				}     
				else;    				slot_index=slot_index+5;   A				op_intrpt_schedule_self(op_sim_time()+5*slot_time,send_csma);   				}   				*/	   				//else;   				}   		}   		else   			op_pk_destroy(pkptr);   		break;   		   4		case 16://node receive time_slot_assignment packet   		if(node_address == dest)   		{   3		op_pk_nfd_get(pkptr,"MS_access_identity",&slot);    9		//op_pk_nfd_get(pkptr,"PUSCH sub-carrier",&sub_number);   D		slot_str = (slot_element*)op_prg_mem_alloc(sizeof(slot_element));    $		slot_str->node_num = node_address;   		slot_str->slot_num = slot;   *		//slot_str->subcarrier_num = sub_number;   <		op_prg_list_insert(slot_table,slot_str,OPC_LISTPOS_TAIL);    		slot_assignment=1;   2		flag=1;//to show this node had input the network   9		node_number++;//to show if the gorup network has finish   &		op_subq_flush(0);//flush the queue 0   		}   		else   			op_pk_destroy(pkptr);   		   		break;   	   
		case 17:   		   Q		if(node_address == 0)//&&(source >= 0 && source <= 5))//write node list approve   		{   ;			if(source >= 1 && source <= 15)//write node list approve   					{   					str=str_lookup(source);   					if(str == OPC_NIL)    						{   						str=create_new_insert();   						str->node_value =source;   @						op_prg_list_insert(record_node_list,str,OPC_LISTPOS_TAIL);   			   Y						pk=op_pk_create_fmt("ack_information");//tell node that it accessed BS successfully   &						op_pk_nfd_set(pk,"DEST",source);   +						op_pk_nfd_set(pk,"SRC",node_address);   9						op_pk_nfd_set(pk,"MS_access_identity",slot_number);   "						op_pk_nfd_set(pk,"Type",16);   $						op_pk_send(pk, instrm_to_low);   						slot_number++;   						}   
					else;   					}   g		//if the node is not belong to the write list ,it will not send req packet to network for 150 seconds   			else   				{   L				pk=op_pk_create_fmt("node_request3");	//in order to request access node0   				op_pk_nfd_set(pk,"DEST",0);   )				op_pk_nfd_set(pk,"SRC",node_address);   #				op_pk_nfd_set(pk, "Type", 18);    2				op_pk_send_delayed(pk, instrm_to_low,1);//150s   _				/*if (op_subq_pk_insert (1, pk, OPC_QPOS_TAIL) != OPC_QINS_OK)//put the packet into buffer0   				{   2				//if the insertion failed, discard the packet    				op_pk_destroy (pk);   				}     
				else;    				slot_index=slot_index+5;   A				op_intrpt_schedule_self(op_sim_time()+5*slot_time,send_csma);   				}   				*/	   				//else;   		   				}   		}   		else   			op_pk_destroy(pkptr);   		break;    		case 100://receive data packet   !		op_pk_send(pkptr,instrm_to_up);   	break;   		   
	case 200:   		if(node_address == dest)   		{   "			op_pk_send(pkptr,instrm_to_up);   		}   		else   			op_pk_destroy(pkptr);   		   	break;   		   
	case 300:   		if(node_address == dest)   		{   "			op_pk_send(pkptr,instrm_to_up);   		}   		else   			op_pk_destroy(pkptr);   		   	break;   		   	default:  ;   		}   }   
                     
   ����   
          pr_state        :            
   	send_csma   
       
   �   		if(flag == 0 )   			{   			   J			pk=op_pk_create_fmt("node_request");	//in order to request access node0   			op_pk_nfd_set(pk,"DEST",0);   (			op_pk_nfd_set(pk,"SRC",node_address);   "			op_pk_nfd_set(pk, "Type", 15);    #			//op_pk_send(pk, instrm_to_low);   \			if (op_subq_pk_insert (1, pk, OPC_QPOS_TAIL) != OPC_QINS_OK)//put the packet into buffer0   				{   2				//if the insertion failed, discard the packet    				op_pk_destroy (pk);   				}     				else;    			 //slot_index=slot_index+5;   B			//op_intrpt_schedule_self(op_sim_time()+5*slot_time,send_csma);   			}   		/*	   			else;   #		else//flag=1,node has accessed BS   			{   			op_pk_destroy (pkptr);		   			}   		*/   4	if(rx_busy == 0 )  //if channel is idle, send frame   	{       		if(!op_subq_empty (0))   			{   2				pktptr = op_subq_pk_remove (0, OPC_QPOS_HEAD);   F				op_pk_send2(pktptr,instrm_to_low);//send to stream 0 to low layer;   			}   	   	else if(!op_subq_empty (1))   			{   2				pktptr = op_subq_pk_remove (1, OPC_QPOS_HEAD);   &				op_pk_send2(pktptr,instrm_to_low);   			}   		else if(!op_subq_empty (2))   			{   2				pktptr = op_subq_pk_remove (2, OPC_QPOS_HEAD);   &				op_pk_send2(pktptr,instrm_to_low);   			}   		else if(!op_subq_empty (3))   			{   2				pktptr = op_subq_pk_remove (3, OPC_QPOS_HEAD);   &				op_pk_send2(pktptr,instrm_to_low);   			}       	}   else   {   /*   <else     //channel is busy, judge channel status value, spma   	{   \	if(channel_status_value <= 0.75 && channel_status_value > 0.5) //send frame with priority 0   		{   		if(!op_subq_empty (0))   			{   2				pktptr = op_subq_pk_remove (0, OPC_QPOS_HEAD);   F				op_pk_send2(pktptr,instrm_to_low);//send to stream 0 to low layer;   			}   		}       g	else if(channel_status_value <= 0.5 && channel_status_value > 0.25) //send frame with priority 0 and 1   		{   		if(!op_subq_empty (0))   			{   2				pktptr = op_subq_pk_remove (0, OPC_QPOS_HEAD);   F				op_pk_send2(pktptr,instrm_to_low);//send to stream 0 to low layer;   			}   		else if(!op_subq_empty (1))   			{   2				pktptr = op_subq_pk_remove (1, OPC_QPOS_HEAD);   &				op_pk_send2(pktptr,instrm_to_low);   			}   		else;   		}   	   i	else if(channel_status_value <= 0.25 && channel_status_value > 0) //send frame with priority 0, 1, and 2   		{   		if(!op_subq_empty (0))   			{   2				pktptr = op_subq_pk_remove (0, OPC_QPOS_HEAD);   F				op_pk_send2(pktptr,instrm_to_low);//send to stream 0 to low layer;   			}   		else if(!op_subq_empty (1))   			{   2				pktptr = op_subq_pk_remove (1, OPC_QPOS_HEAD);   &				op_pk_send2(pktptr,instrm_to_low);   			}   		else if(!op_subq_empty (2))   			{   2				pktptr = op_subq_pk_remove (2, OPC_QPOS_HEAD);   &				op_pk_send2(pktptr,instrm_to_low);   			}   		else;   		}   	   J	else if(channel_status_value <= 0) //send frame with priority 0, 1, and 2   		{   		if(!op_subq_empty (0))   			{   2				pktptr = op_subq_pk_remove (0, OPC_QPOS_HEAD);   F				op_pk_send2(pktptr,instrm_to_low);//send to stream 0 to low layer;   			}   		else if(!op_subq_empty (1))   			{   2				pktptr = op_subq_pk_remove (1, OPC_QPOS_HEAD);   &				op_pk_send2(pktptr,instrm_to_low);   			}   		else if(!op_subq_empty (2))   			{   2				pktptr = op_subq_pk_remove (2, OPC_QPOS_HEAD);   &				op_pk_send2(pktptr,instrm_to_low);   			}   		else if(!op_subq_empty (3))   			{   2				pktptr = op_subq_pk_remove (3, OPC_QPOS_HEAD);   &				op_pk_send2(pktptr,instrm_to_low);   			}   		else;   		}   	else;   	}   */	   //	listen_times = 0;       3//if a frame waits to be sent, re-enter send status   if(!op_subq_empty (1) )//flag=1   B//	op_intrpt_schedule_self(op_sim_time() + 0.001 + FS_TIMES, FS);    [	op_intrpt_schedule_self(op_sim_time() + FS_TIMES + op_dist_uniform(FS_TIMES), send_csma);    else;   	   }	   slot_index=slot_index+4;	   ?op_intrpt_schedule_self(op_sim_time()+slot_time,slot_control);	   /*			if(listen_times == 10)   				{   '					if(op_prg_list_size(pk_buffer[0]))   						{   2						pktptr = op_prg_list_remove(pk_buffer[0],0);   						op_pk_destroy(pktptr);   						}   ,					else if(op_prg_list_size(pk_buffer[1]))   						{   2						pktptr = op_prg_list_remove(pk_buffer[1],0);   						op_pk_destroy(pktptr);   						}   ,					else if(op_prg_list_size(pk_buffer[2]))   						{   2						pktptr = op_prg_list_remove(pk_buffer[2],0);   						op_pk_destroy(pktptr);   						}   ,					else if(op_prg_list_size(pk_buffer[3]))   						{   2						pktptr = op_prg_list_remove(pk_buffer[3],0);   						op_pk_destroy(pktptr);   						}   				}   		   		else   				{   )				back_off_time = op_dist_uniform(1.0);   D				op_intrpt_schedule_self(op_sim_time() + back_off_time,back_off);   				listen_times++;   V				op_intrpt_schedule_self(op_sim_time(),instrm_from_up);//self intrupt back send FSM   				}   */   
                     
   ����   
          pr_state        �   �          
   rx_idle   
       
      rx_busy = 0;  //rx idle   
                     
   ����   
          pr_state        �  �          
   rx_busy   
       
      rx_busy = 1;  //rx busy   
                     
   ����   
          pr_state         �   �          
   send_beacon   
       
   &   //create BS hello packet   switch(beacon_num)   	{   case 0:   	{   &	pk=op_pk_create_fmt("node0_beacon");	   	op_pk_nfd_set(pk,"DEST",-1);   &	op_pk_nfd_set(pk,"SRC",node_address);   !	op_pk_nfd_set(pk, "Type", 10);     '	op_pk_nfd_set(pk, "beacon_slot", 5);     &	op_pk_nfd_set(pk, "csma_slot", 10);     &	op_pk_nfd_set(pk, "tdma_slot", 15);     +	op_pk_nfd_set(pk, "bind_csma_slot", 20);     	op_pk_send(pk, instrm_to_low);   }   break;   //slot_index=slot_index+4;   /*beacon_slot_number++;   if(beacon_slot_number%5 == 0)   	{   	beacon_slot_number=0;   	}   else   	op_pk_destroy(pk);   */   //sending is cycle(50ms)   9//op_intrpt_schedule_self(op_sim_time()+5,Beacon_code);     case 1:   	{    %	pk= op_pk_create_fmt ("pco_beacon");   '	op_pk_nfd_set(pk,"SRC" ,node_address);   %	op_pk_nfd_set(pk,"DEST" ,dest_addr);   	op_pk_nfd_set(pk,"Type", 11);   	op_pk_send(pk,instrm_to_low);   	}   	break;   
default: ;   }   
                     
   ����   
          pr_state      	   �  �          
   slot_control   
       
   1   /*if(!op_subq_empty(1))   	{   *	pkptr=op_subq_pk_remove(1,OPC_QPOS_HEAD);   !	op_pk_send(pkptr,instrm_to_low);       	}      else;   */   !t=op_dist_uniform(150E-3);//150ms   time=t*slot_time;   *if(slot_index>=0&&slot_index<beacon_slot1)   4	op_intrpt_schedule_self(op_sim_time(),Beacon_code);       3if(slot_index>=beacon_slot1&&slot_index<csma_slot1)   7op_intrpt_schedule_self(op_sim_time()+time,send_csma);	       1if(slot_index>=csma_slot1&&slot_index<tdma_slot1)   1op_intrpt_schedule_self(op_sim_time(),send_tdma);       6if(slot_index>=tdma_slot1&&slot_index<bind_csma_slot1)   7op_intrpt_schedule_self(op_sim_time()+time,bind_csma);	   /*else if(slot_index == 3)   	{   <	op_intrpt_schedule_self(op_sim_time()+slot_time,tdma_code);   	slot_index = -1;	   	}*/   //if(slot_index>0)   -/*for(i=0;i<op_prg_list_size(slot_table);i++)   	{   -	slot_str = op_prg_list_access(slot_table,i);   O	if((slot_str->node_num == node_address) && (slot_str->slot_num == slot_index))   		{   		if(!op_subq_empty(0))   			{   .			pkptr = op_subq_pk_remove(0,OPC_QPOS_HEAD);   #			op_pk_send(pkptr,instrm_to_low);   			}   		else;   		}   	else;   	   	}   */   slot_index++;   if(slot_index == 20)   	{   	slot_index=0;   	}   else;   
                     
   ����   
          pr_state      
   �  �          
   	bind_csma   
       
   �   3if(rx_busy == 0 )  //if channel is idle, send frame   	{   		if(!op_subq_empty (0))   			{   2				pktptr = op_subq_pk_remove (0, OPC_QPOS_HEAD);   F				op_pk_send2(pktptr,instrm_to_low);//send to stream 0 to low layer;   			}   	else if(!op_subq_empty (1))   			{   2				pktptr = op_subq_pk_remove (1, OPC_QPOS_HEAD);   &				op_pk_send2(pktptr,instrm_to_low);   			}   		else if(!op_subq_empty (2))   			{   2				pktptr = op_subq_pk_remove (2, OPC_QPOS_HEAD);   &				op_pk_send2(pktptr,instrm_to_low);   			}   		else if(!op_subq_empty (3))   			{   2				pktptr = op_subq_pk_remove (3, OPC_QPOS_HEAD);   &				op_pk_send2(pktptr,instrm_to_low);   			}       	}   else   {   /*   <else     //channel is busy, judge channel status value, spma   	{   \	if(channel_status_value <= 0.75 && channel_status_value > 0.5) //send frame with priority 0   		{   		if(!op_subq_empty (0))   			{   2				pktptr = op_subq_pk_remove (0, OPC_QPOS_HEAD);   F				op_pk_send2(pktptr,instrm_to_low);//send to stream 0 to low layer;   			}   		}       g	else if(channel_status_value <= 0.5 && channel_status_value > 0.25) //send frame with priority 0 and 1   		{   		if(!op_subq_empty (0))   			{   2				pktptr = op_subq_pk_remove (0, OPC_QPOS_HEAD);   F				op_pk_send2(pktptr,instrm_to_low);//send to stream 0 to low layer;   			}   		else if(!op_subq_empty (1))   			{   2				pktptr = op_subq_pk_remove (1, OPC_QPOS_HEAD);   &				op_pk_send2(pktptr,instrm_to_low);   			}   		else;   		}   	   i	else if(channel_status_value <= 0.25 && channel_status_value > 0) //send frame with priority 0, 1, and 2   		{   		if(!op_subq_empty (0))   			{   2				pktptr = op_subq_pk_remove (0, OPC_QPOS_HEAD);   F				op_pk_send2(pktptr,instrm_to_low);//send to stream 0 to low layer;   			}   		else if(!op_subq_empty (1))   			{   2				pktptr = op_subq_pk_remove (1, OPC_QPOS_HEAD);   &				op_pk_send2(pktptr,instrm_to_low);   			}   		else if(!op_subq_empty (2))   			{   2				pktptr = op_subq_pk_remove (2, OPC_QPOS_HEAD);   &				op_pk_send2(pktptr,instrm_to_low);   			}   		else;   		}   	   J	else if(channel_status_value <= 0) //send frame with priority 0, 1, and 2   		{   		if(!op_subq_empty (0))   			{   2				pktptr = op_subq_pk_remove (0, OPC_QPOS_HEAD);   F				op_pk_send2(pktptr,instrm_to_low);//send to stream 0 to low layer;   			}   		else if(!op_subq_empty (1))   			{   2				pktptr = op_subq_pk_remove (1, OPC_QPOS_HEAD);   &				op_pk_send2(pktptr,instrm_to_low);   			}   		else if(!op_subq_empty (2))   			{   2				pktptr = op_subq_pk_remove (2, OPC_QPOS_HEAD);   &				op_pk_send2(pktptr,instrm_to_low);   			}   		else if(!op_subq_empty (3))   			{   2				pktptr = op_subq_pk_remove (3, OPC_QPOS_HEAD);   &				op_pk_send2(pktptr,instrm_to_low);   			}   		else;   		}   	else;   	}   */	   //	listen_times = 0;       3//if a frame waits to be sent, re-enter send status   if(!op_subq_empty (0) )   B//	op_intrpt_schedule_self(op_sim_time() + 0.001 + FS_TIMES, FS);    P	op_intrpt_schedule_self(op_sim_time() + op_dist_uniform(FS_TIMES), bind_csma);    else;   	   }       @op_intrpt_schedule_self(op_sim_time()+slot_time,slot_control);		   /*			if(listen_times == 10)   				{   '					if(op_prg_list_size(pk_buffer[0]))   						{   2						pktptr = op_prg_list_remove(pk_buffer[0],0);   						op_pk_destroy(pktptr);   						}   ,					else if(op_prg_list_size(pk_buffer[1]))   						{   2						pktptr = op_prg_list_remove(pk_buffer[1],0);   						op_pk_destroy(pktptr);   						}   ,					else if(op_prg_list_size(pk_buffer[2]))   						{   2						pktptr = op_prg_list_remove(pk_buffer[2],0);   						op_pk_destroy(pktptr);   						}   ,					else if(op_prg_list_size(pk_buffer[3]))   						{   2						pktptr = op_prg_list_remove(pk_buffer[3],0);   						op_pk_destroy(pktptr);   						}   				}   		   		else   				{   )				back_off_time = op_dist_uniform(1.0);   D				op_intrpt_schedule_self(op_sim_time() + back_off_time,back_off);   				listen_times++;   V				op_intrpt_schedule_self(op_sim_time(),instrm_from_up);//self intrupt back send FSM   				}   */   
                     
   ����   
          pr_state        �   Z          
   	send_tdma   
       
      //if(slot_index>0)   +for(i=0;i<op_prg_list_size(slot_table);i++)   	{   -	slot_str = op_prg_list_access(slot_table,i);   O	if((slot_str->node_num == node_address) && (slot_str->slot_num == slot_index))   		{   		if(!op_subq_empty(0))   			{   .			pkptr = op_subq_pk_remove(0,OPC_QPOS_HEAD);   #			op_pk_send(pkptr,instrm_to_low);   			}   		else;   		}   	else;   	   	}   ?op_intrpt_schedule_self(op_sim_time()+slot_time,slot_control);	   //slot_index++;   
                     
   ����   
          pr_state                     �        �    K            
   tr_0   
       ����          ����          
    ����   
          ����                       pr_transition              &   �     E    E   Y          
   tr_1   
       
   UP_ARVL   
       ����          
    ����   
          ����                       pr_transition              M   �     M   Z  M            
   tr_2   
       ����          ����          
    ����   
          ����                       pr_transition              +  r     E    E  �          
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
          ����                       pr_transition      	        }  Y     R    X  T  q  D  V            
   tr_14   
       
   default   
       ����          
    ����   
          ����                       pr_transition      
        �   �     S     �   �          
   tr_19   
       
   RX_IDLE   
       ����          
    ����   
          ����                       pr_transition              �   �        �  ]  
          
   tr_20   
       ����          ����          
    ����   
          ����                       pr_transition              �   �     Y    9            
   tr_21   
       
   	SEND_CSMA   
       ����          
    ����   
          ����                       pr_transition              �       C    R            
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
          ����                       pr_transition               �   �     A   �   �   �          
   tr_22_0   
       
   SEND_BEACON   
       ����          
    ����   
          ����                       pr_transition               �   �      �   �  4            
   tr_22_1   
       ����          ����          
    ����   
          ����                       pr_transition            	   �  G     7     �  |          
   tr_24_0   
       
   SLOT_CONTROL   
       ����          
    ����   
          ����                       pr_transition         	      �  W      �  �  <  #          
   tr_24_1   
       ����          ����          
    ����   
          ����                       pr_transition            
    m     ?     �  �          
   tr_25   
       
   	BIND_CSMA   
       ����          
    ����   
          ����                       pr_transition         
       t      �  �  G            
   tr_26   
       ����          ����          
    ����   
          ����                       pr_transition                 �     T   �  �   ]          
   tr_28   
       
   	SEND_TDMA   
       ����          
    ����   
          ����                       pr_transition              �   �     �   j  X   �          
   tr_29   
       ����          ����          
    ����   
          ����                       pr_transition                           
link_delay           +   General Process Description:   ----------------------------        �The pc_fifo queueing process model accepts packets from any number of sources and holds them until it receives a request from another module to forward the next packet in the queue. The packets are forwarded in a first-in-first-out (FIFO) manner.        �Note that the request to forward the packets should come in the form of an "access interrupt" delivered by the module which is the destination module for the concerned packets.               ICI Interfaces:   ---------------        None                Packet Formats:   ---------------        None                Statistic Wires:   ----------------        None                Process Registry:   -----------------        Not Applicable               Restrictions:   -------------        F1. The pc_fifo process model must be contained within a queue module.        c2. The source stream index of the output packet stream of the surrounding queue module should be 0.        