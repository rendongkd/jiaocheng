/* Process model C form file: olsr_gaijing_4.pr.c */
/* Portions of this file copyright 1986-2008 by OPNET Technologies, Inc. */



/* This variable carries the header into the object file */
const char olsr_gaijing_4_pr_c [] = "MIL_3_Tfile_Hdr_ 145A 30A op_runsim 7 5DB69693 5DB69693 1 USER-20151017SA Administrator 0 0 none none 0 0 none 0 0 0 0 0 0 0 0 1bcc 1                                                                                                                                                                                                                                                                                                                                                                                          ";
#include <string.h>



/* OPNET system definitions */
#include <opnet.h>



/* Header Block */

#include <malloc.h>
#include <stdio.h>
#include "stdlib.h"
#include <string.h>

/*****************************/
long int	send_number;

long int	rcv_number;

long int	control_number;

double	rcv_bit;

double	success_rate;

double data_throughout_bit;

double  delay;
/*****定义流方向*********/
#define  OLSR_to_INTERFACE   0
#define  OLSR_to_TRANSPORT   1
#define  INTERFACE_TO_OLSR   0
#define  TRANSPORT_TO_OLSR   1
/********************/
#define  JIEDIAN_NUMBER   100
#define  INF 1000
#define    MAX  1000//丢失
/******************消息类型***************/
#define  HELLO  0
#define  TC     1
#define  DATA   2
#define send_frame 1000
/**************定义中断类型******************/
#define self_hello  (op_intrpt_type()==OPC_INTRPT_SELF&&op_intrpt_code()==0)
#define self_tc  (op_intrpt_type()==OPC_INTRPT_SELF&&op_intrpt_code()==1)
#define SEND_FRAME  (op_intrpt_type()==OPC_INTRPT_SELF&&op_intrpt_code()==send_frame)

#define INTRPT_STRM_DATA  (op_intrpt_type()==OPC_INTRPT_STRM && op_intrpt_strm()==TRANSPORT_TO_OLSR)
#define INTRPT_STRM_RECEIVOR  (op_intrpt_type()==OPC_INTRPT_STRM && op_intrpt_strm()==INTERFACE_TO_OLSR)
#define self_topu  (op_intrpt_type()==OPC_INTRPT_SELF&&op_intrpt_code()==2)
#define  save_pk_send (op_intrpt_type()==OPC_INTRPT_SELF&&op_intrpt_code()==3)
/************链路状态****************************/
#define ASYS_LINK     0    //单向链路
#define   SYS_LINK    1    //对称链路
#define   MPR_LINK    2     //MPR链路

/*************转发意愿***************************/

#define    WILL_NEVER    0
#define    WILL_LOW      1
#define    WILL_DEFAULT  2
#define    WILL_HIGH     3
#define    WILL_ALWAYS   4

#define    TC_TIME   5     //tc消息
#define    HELLO_TIME   2   //hello消息

#define    HELLO_SEND_TIME    HELLO_TIME   //hello消息发送间隔
#define    SYS_TIME   3*HELLO_TIME     //对称链路保持时间
#define    ASYS_TIME   4*HELLO_TIME   //非对称链路保持时间
#define    DELETE_TIME   HELLO_TIME*5  //删除节点时间
#define    MPR_HOLD_TIME    HELLO_TIME*3  //MPR  selector链表保持时间
#define    TWO_HOP_TIME   3*HELLO_TIME  //两跳链表保持时间
#define    TC_SEND_TIME   TC_TIME   //tc消息发送间隔
#define    TC_HILD_TIME   TC_TIME*3//tc消息保持时间
#define    SUIJI  0.5
void data_send();
void save_packet_send();
void hello_send(int type,int path_addr);
void tc_send();
void recv();
void priority_send();
void data_recv(Packet *pkptr);
void hello_recv(Packet* pkptr);
void tc_recv(Packet* pkptr);
void delete_topu_time();
void delete_topu_repeat(int src);
void compute_topu();
int check_tc_repeat(int src,int seq);
void delete_tc_time();
void one_hop_message_update();
void two_hop_message_update();
static void mpr_compute();
int check_member(int temp);
void delete_one_mpr(int temp);
void creat_two_hop(struct TWO_HOP_TABLE* temp_two_hop);
void creat_two_hop_1(struct TWO_HOP_TABLE* temp_two_hop);
struct TWO_HOP_ADDR* copy_two_addr(struct TWO_HOP_ADDR* temp);//复制两跳子链表
void  delete_repeat_mpr(struct ONE_HOP_TABLE *temp);
static struct TWO_HOP_TABLE* copy_list(struct TWO_HOP_TABLE* temp);//复制两跳
int check_two_addr(int temp);
int check_two_addr_1(int temp);
static void free_list(struct TWO_HOP_TABLE* temp);
static int gudan_jiedian(int temp,int temp_addr);
void insert_mpr(int temp_addr);
void delete_mpr(int temp_addr,struct TWO_HOP_TABLE* temp_two_hop,int moshi);
void delete_point(int temp_addr,struct TWO_HOP_TABLE*temp_two_hop);
void check_mpr_time();
/*********本地链路信息表*****************/
struct LOCAL_MESSAGE_TABLE
	{
	  int neighbor_addr; // 邻居节点地址
	  int willness;
	  double sys_time ;    //对称到期时间
	  double asys_time;   //非对称到期时间
	  double delete_time;        //必须删除时间
	  struct LOCAL_MESSAGE_TABLE*next;
	 } ;

/*******一跳邻居表***************/
struct ONE_HOP_TABLE
	{
	    int neighbor_addr ;       //邻居节点地址
		//int willingness;     //愿意转发意愿
		struct ONE_HOP_TABLE* next;
	};

/*********两条邻居表******************************/
struct TWO_HOP_ADDR
	{
		int addr;            //两跳地址
		struct TWO_HOP_ADDR*next;
	};
struct TWO_HOP_TABLE
	{
	  int  one_hop_addr;                 //邻居节点地址
	  int willness;    // 转发意愿
	  struct TWO_HOP_ADDR *two_addr_head; // 两跳节点地址链表地址
	  int son_number;  //两跳节点的数量
	  double delete_time ;                   //到期删除 
	  struct TWO_HOP_TABLE *next;
	 } ;
/**********mpr selector表*****************/
struct MPR_SELECTOR
	{
	   int ms_main_addr;  
	   double ms_time;
	   struct MPR_SELECTOR*next;
	};
/********TC分表重复记录表***************/
struct TC_REPEAT_TABLE
	{
	   int addr;   //tc消息地址
	   int seq_number; //发送序列号
	   double time;//到期删除时间
	   struct TC_REPEAT_TABLE *next;
	};
/************拓扑表*******************/
struct TOPU_TABLE
{
    int dst_addr;   //目的地址
	int src_addr;   //源地址
	float willness;  //转发意愿
	double time;  //到期删除
	struct TOPU_TABLE* next;   
};
struct SAVE_PACKET
{
   double delete_time;
   int  dst;
   Packet*  temp_packet_ptr;
   struct SAVE_PACKET* next;
};



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
	Stathandle	             		pk_send_number                                  ;
	int	                    		two_hop_number                                  ;
	int	                    		own_source                                      ;
	Objid	                  		node_id                                         ;
	Distribution *	         		t_dst                                           ;
	struct LOCAL_MESSAGE_TABLE*			local_message_head                              ;
	struct ONE_HOP_TABLE*	  		one_hop_asys_head                               ;
	struct TWO_HOP_TABLE*	  		two_hop_head                                    ;
	struct TWO_HOP_ADDR*	   		two_all_hop_head                                ;
	struct TWO_HOP_ADDR*	   		temp_two_all_hop_head                           ;
	struct ONE_HOP_TABLE*	  		one_hop_sys_head                                ;
	struct ONE_HOP_TABLE*	  		one_hop_mpr_head                                ;
	struct MPR_SELECTOR*	   		mpr_selector                                    ;
	struct TC_REPEAT_TABLE*			tc_repeat_head                                  ;
	struct TOPU_TABLE*	     		topu_head                                       ;
	short	                  		tc_number                                       ;
	int	                    		temp_number                                     ;
	int	                    		topu[JIEDIAN_NUMBER][JIEDIAN_NUMBER]            ;
	int	                    		path[JIEDIAN_NUMBER][JIEDIAN_NUMBER]            ;
	int	                    		distance[JIEDIAN_NUMBER]                        ;
	int	                    		s[JIEDIAN_NUMBER]                               ;
	int	                    		v[JIEDIAN_NUMBER]                               ;
	Stathandle	             		pk_rcv_number                                   ;
	Stathandle	             		pk_success_rate                                 ;
	Stathandle	             		ete_delay                                       ;
	Ici*	                   		ici_ptr                                         ;
	int	                    		DBG_flag                                        ;
	int	                    		local_dbg_flag                                  ;
	struct SAVE_PACKET*	    		save_packet_head                                ;
	int	                    		hello_path[JIEDIAN_NUMBER]                      ;
	double	                 		hello_path_time[JIEDIAN_NUMBER]                 ;
	int	                    		flag_send_dbg                                   ;
	Evhandle	               		hello_ev                                        ;
	int	                    		hello_send_flag                                 ;
	Evhandle	               		save_ev                                         ;
	int	                    		save_send_flag                                  ;
	int	                    		sequence                                        ;
	Stathandle	             		data_throughput                                 ;
	Stathandle	             		control_message_overhead                        ;
	List*	                  		priority[8]                                     ;
	} olsr_gaijing_4_state;

#define pk_send_number          		op_sv_ptr->pk_send_number
#define two_hop_number          		op_sv_ptr->two_hop_number
#define own_source              		op_sv_ptr->own_source
#define node_id                 		op_sv_ptr->node_id
#define t_dst                   		op_sv_ptr->t_dst
#define local_message_head      		op_sv_ptr->local_message_head
#define one_hop_asys_head       		op_sv_ptr->one_hop_asys_head
#define two_hop_head            		op_sv_ptr->two_hop_head
#define two_all_hop_head        		op_sv_ptr->two_all_hop_head
#define temp_two_all_hop_head   		op_sv_ptr->temp_two_all_hop_head
#define one_hop_sys_head        		op_sv_ptr->one_hop_sys_head
#define one_hop_mpr_head        		op_sv_ptr->one_hop_mpr_head
#define mpr_selector            		op_sv_ptr->mpr_selector
#define tc_repeat_head          		op_sv_ptr->tc_repeat_head
#define topu_head               		op_sv_ptr->topu_head
#define tc_number               		op_sv_ptr->tc_number
#define temp_number             		op_sv_ptr->temp_number
#define topu                    		op_sv_ptr->topu
#define path                    		op_sv_ptr->path
#define distance                		op_sv_ptr->distance
#define s                       		op_sv_ptr->s
#define v                       		op_sv_ptr->v
#define pk_rcv_number           		op_sv_ptr->pk_rcv_number
#define pk_success_rate         		op_sv_ptr->pk_success_rate
#define ete_delay               		op_sv_ptr->ete_delay
#define ici_ptr                 		op_sv_ptr->ici_ptr
#define DBG_flag                		op_sv_ptr->DBG_flag
#define local_dbg_flag          		op_sv_ptr->local_dbg_flag
#define save_packet_head        		op_sv_ptr->save_packet_head
#define hello_path              		op_sv_ptr->hello_path
#define hello_path_time         		op_sv_ptr->hello_path_time
#define flag_send_dbg           		op_sv_ptr->flag_send_dbg
#define hello_ev                		op_sv_ptr->hello_ev
#define hello_send_flag         		op_sv_ptr->hello_send_flag
#define save_ev                 		op_sv_ptr->save_ev
#define save_send_flag          		op_sv_ptr->save_send_flag
#define sequence                		op_sv_ptr->sequence
#define data_throughput         		op_sv_ptr->data_throughput
#define control_message_overhead		op_sv_ptr->control_message_overhead
#define priority                		op_sv_ptr->priority

/* These macro definitions will define a local variable called	*/
/* "op_sv_ptr" in each function containing a FIN statement.	*/
/* This variable points to the state variable data structure,	*/
/* and can be used from a C debugger to display their values.	*/
#undef FIN_PREAMBLE_DEC
#undef FIN_PREAMBLE_CODE
#define FIN_PREAMBLE_DEC	olsr_gaijing_4_state *op_sv_ptr;
#define FIN_PREAMBLE_CODE	\
		op_sv_ptr = ((olsr_gaijing_4_state *)(OP_SIM_CONTEXT_PTR->_op_mod_state_ptr));


/* Function Block */

#if !defined (VOSD_NO_FIN)
enum { _op_block_origin = __LINE__ + 2};
#endif

void compute_topu()  //D算法
{
   int i,j,mini,k,m,n=0;
   struct ONE_HOP_TABLE *temp_one_hop=NULL;
   struct TOPU_TABLE* temp_topu=NULL;
   FIN(compute_topu());
   k=MAX;
   temp_one_hop=one_hop_sys_head;
   temp_topu=topu_head;
   i=0;
   j=0;
   for(;i<JIEDIAN_NUMBER;i++)
	   for(j=0;j<JIEDIAN_NUMBER;j++)
		   topu[i][j]=MAX;
   for(i=0;i<JIEDIAN_NUMBER;i++)
	   {
	       s[i]=MAX;//保持矩阵
		   v[i]=1;  //删除矩阵
		   distance[i]=MAX;
	   }
   for(i=0,j=0;i<JIEDIAN_NUMBER;i++)
	   {
	      for(j=0;j<JIEDIAN_NUMBER;j++)
			  {
			     path[i][j]=INF;
			  }
	   }
   for(;temp_one_hop!=NULL;temp_one_hop=temp_one_hop->next)
	   {
	        topu[temp_one_hop->neighbor_addr][own_source]=1;
		    topu[own_source][temp_one_hop->neighbor_addr]=1;
	   }

   for(;temp_topu!=NULL;temp_topu=temp_topu->next)
	   {
	       if(topu[temp_topu->dst_addr][temp_topu->src_addr]==MAX)
			   {
			       topu[temp_topu->dst_addr][temp_topu->src_addr]=1;
			   }
		    if(topu[temp_topu->src_addr][temp_topu->dst_addr]==MAX)
				{
				   topu[temp_topu->src_addr][temp_topu->dst_addr]=1;
				}
			
	   }  
   s[own_source]=1;
   v[own_source]=MAX;
   for(i=0;i<JIEDIAN_NUMBER;i++)
	   {
	       distance[i]=topu[i][own_source];
		   path[i][0]=own_source;
		   if(topu[i][own_source]<MAX&&i!=own_source)
			   {
			      path[i][1]=i;
			   }
	   }
   mini=MAX;

   for(i=0;i<JIEDIAN_NUMBER;i++)
	   {   
		   
	       mini=MAX;
		   k=MAX;
	       for(j=0;j<JIEDIAN_NUMBER;j++)
			   {

			      if(v[j]==1&&(distance[j]<mini))
					  {
					     k=j;
						 mini=distance[j];
						
					  }
			   }
		   if(k!=MAX)
			   {
			       s[k]=1;
				   v[k]=MAX;
			      
		           for(j=0;j<JIEDIAN_NUMBER;j++)
			         {
			             if(v[j]==1&&(distance[k]+topu[k][j])<distance[j])
							 {
							     
								  distance[j]=distance[k]+topu[k][j];
							 
								   m=0;
					              while(path[k][m]!=INF)
					                {
					                    path[j][m]=path[k][m];
						                 m++;
					                }
					                 path[j][m]=j;

								      
							  }
						 }
				}
	
 
		   
	   }
    
   FOUT;
}


void recv()
{
   Packet *pkptr;
   int type;
   FIN(recv());
   pkptr=op_pk_get(INTERFACE_TO_OLSR);
   op_pk_nfd_get(pkptr,"type",&type);//根据收到的类型交给相应的包接收函数处理
   if(type==HELLO||type==3||type==4)
	   {
	      
	      hello_recv(pkptr);//hello消息处理函数
	   }
   if(type==TC)
	   {
	       tc_recv(pkptr);//tc消息处理函数
	   }
   if(type==DATA)
	   {   
	       data_recv(pkptr);//上层数据包处理函数
	   };

   FOUT;
};
void save_packet_send()
{
    int save_flag;
    struct SAVE_PACKET*   temp_save;
    int seq;

    FIN(save_packet_send());
	save_flag=1;
    while(save_packet_head!=NULL&&save_flag==1)
  	{
	  if(path[save_packet_head->dst][1]>100&&hello_path[save_packet_head->dst]>100)
			{
			
			    op_pk_destroy(save_packet_head->temp_packet_ptr);
				temp_save=save_packet_head->next;
				free(save_packet_head);
				save_packet_head=temp_save;
				printf("找不到\n!!!!!!!!!!!");
			}else if(path[save_packet_head->dst][1]<100)
							{
							   op_pk_nfd_get(save_packet_head->temp_packet_ptr,"sequence", &seq);
							   printf("存储的包号%d\n!!!!!!!!!!!!!!!",seq);
							 //  op_ici_attr_set(ici_ptr, "nexthop_mac_addr",path[save_packet_head->dst][1]);
                               //op_ici_install(ici_ptr);
							   op_pk_nfd_set(save_packet_head->temp_packet_ptr,"next_addr",path[save_packet_head->dst][1]);
		                       op_pk_send(save_packet_head->temp_packet_ptr, OLSR_to_INTERFACE );
							   temp_save=save_packet_head->next;
				               free(save_packet_head);
				               save_packet_head=temp_save;
							   
							}else{
						                op_pk_nfd_get(save_packet_head->temp_packet_ptr,"sequence", &seq);
							            printf("存储的包号%d\n!!!!!!!!!!!!!!!",seq);
							           // hello_path_time[save_packet_head->dst]=op_sim_time()+2*HELLO_TIME;
						               // op_ici_attr_set(ici_ptr, "nexthop_mac_addr",hello_path[save_packet_head->dst]);
                                        //op_ici_install(ici_ptr);
										op_pk_nfd_set(save_packet_head->temp_packet_ptr,"next_addr",hello_path[save_packet_head->dst]);
		                                op_pk_send(save_packet_head->temp_packet_ptr, OLSR_to_INTERFACE ); 
										temp_save=save_packet_head->next;
				                        free(save_packet_head);
				                        save_packet_head=temp_save;
										
						        }

	}


	FOUT;
}
/*
void data_send()
{
   Packet *pkptr;
   Packet *p1;
   int dest,time0,type;
   int next_addr;
   int priority=0;
   List* priority0;
   List* priority1;
   List* priority2;
   List* priority3;
   List* priority4;
   List* priority5;
   List* priority6;
   List* priority7;
   struct SAVE_PACKET* temp_save=NULL;
   FIN(data_send());
   priority0=op_prg_list_create();
   priority1=op_prg_list_create();
   priority2=op_prg_list_create();
   priority3=op_prg_list_create();
   priority4=op_prg_list_create();
   priority5=op_prg_list_create();
   priority6=op_prg_list_create();
   priority7=op_prg_list_create();
   p1=op_pk_get(TRANSPORT_TO_OLSR);
   op_pk_nfd_get(p1,"Type",&type);
if(type==55)
	   {
	   op_pk_nfd_access(p1,"priority",&priority);
	   }
   else	
	   priority=0;
   
   switch(priority)
	   {
	   case 0:
	   op_prg_list_insert(priority0,p1,OPC_LISTPOS_TAIL);
	   op_intrpt_schedule_self(op_sim_time(),send_frame);
	   break;
	   case 1:
	   op_prg_list_insert(priority1,p1,OPC_LISTPOS_TAIL);
	   op_intrpt_schedule_self(op_sim_time(),send_frame);
	   break;
 	   case 2:
	   op_prg_list_insert(priority2,p1,OPC_LISTPOS_TAIL);
	   op_intrpt_schedule_self(op_sim_time(),send_frame);
	   break;
	   case 3:
	   op_prg_list_insert(priority3,p1,OPC_LISTPOS_TAIL);
	   op_intrpt_schedule_self(op_sim_time(),send_frame);
	   break;
	   case 4:
	   op_prg_list_insert(priority4,p1,OPC_LISTPOS_TAIL);
	   op_intrpt_schedule_self(op_sim_time(),send_frame);
	   break;
	   case 5:
	   op_prg_list_insert(priority5,p1,OPC_LISTPOS_TAIL);
	   op_intrpt_schedule_self(op_sim_time(),send_frame);
	   break;
	   case 6:
	   op_prg_list_insert(priority6,p1,OPC_LISTPOS_TAIL);
	   op_intrpt_schedule_self(op_sim_time(),send_frame);
	   break;
	   case 7:
	   op_prg_list_insert(priority7,p1,OPC_LISTPOS_TAIL);
	   op_intrpt_schedule_self(op_sim_time(),send_frame);
	   break;

	   default:
	   break;	   
	   }

   dest = 100;
   op_pk_nfd_get(p1,"Destination Address", &dest);
   pkptr=op_pk_create_fmt("date_message");
   op_pk_nfd_set(pkptr,"pro_addr",own_source);
   op_pk_nfd_set(pkptr,"app_data",p1);
   op_pk_nfd_set(pkptr,"type",2);
   op_pk_nfd_set(pkptr,"source",own_source);
   op_pk_nfd_set(pkptr,"destination",dest);
   op_pk_nfd_set(pkptr,"sequence",sequence);
   next_addr=path[dest][1];
   if(next_addr>100&&hello_path_time[dest]<op_sim_time())
	   {
	      next_addr=hello_path[dest];
	   }
   op_pk_nfd_set(pkptr,"next_addr",next_addr);
   if(flag_send_dbg==1)
   printf("这是源节点：%d,目的节点: %d,next addr:%d,时间是：%f，包号:%d\n",own_source,dest,next_addr,op_sim_time(),sequence);
   send_number=send_number+1;
   op_stat_write(pk_send_number,send_number);
   if(next_addr<100)
	  {
	     // send_number=send_number+1;
         //op_stat_write(pk_send_number,send_number);

		  //op_ici_attr_set(ici_ptr, "nexthop_mac_addr",next_addr);
         // op_ici_install(ici_ptr);
		  op_pk_send(pkptr, OLSR_to_INTERFACE );
	  }
   else{
          if(hello_send_flag==1)
		     {
				 hello_send(3,dest);  //寻路HELLO消息，类型3
				 time0=op_ev_time(hello_ev);
		         op_ev_cancel(hello_ev);
		         hello_ev=op_intrpt_schedule_self(time0+HELLO_SEND_TIME,0);
				 hello_send_flag=0;
			 }
         // p1=op_pk_copy(pkptr);
		 // temp_save=(struct SAVE_PACKET*)malloc(sizeof(struct SAVE_PACKET));
		 // temp_save->delete_time=op_sim_time()+HELLO_TIME;
		 // op_pk_stamp(p1);
		 // temp_save->temp_packet_ptr=p1;
		 // temp_save->dst=dest;
		 // temp_save->next=save_packet_head;
		 // save_packet_head=temp_save;
		 // printf("源节点保存包\n");
       }
   sequence++;
   FOUT;
}
*/
void data_recv(Packet *pkptr)
{
   int temp_dst_addr,time0;
   int next_addr,pro_addr,seq,priority4;
   Packet* p1;
   struct SAVE_PACKET* temp_save=NULL;                                                         
   FIN(data_recv(Packet *pkptr));
   op_pk_nfd_get(pkptr,"destination",&temp_dst_addr);
   op_pk_nfd_get(pkptr,"next_addr",&next_addr);
   op_pk_nfd_get(pkptr,"sequence", &seq);
   op_pk_nfd_access(pkptr,"priority",&priority4);
   //op_pk_nfd_get(pkptr,"priority", &priority4);
   if((temp_dst_addr==own_source)&&(next_addr==own_source))
	   {
	       if(flag_send_dbg==1)
	       printf("这是结束节点，接收到了,包号:%d!!!!\n\n\n",seq);
		   rcv_bit=rcv_bit+(double)op_pk_total_size_get(pkptr)*8; 
		   data_throughout_bit=rcv_bit/(op_sim_time()-20); //开始时间必须大于20
		   if(op_sim_time()>30)
		   op_stat_write(data_throughput,data_throughout_bit);
		   rcv_number= rcv_number+1;
		   op_stat_write(pk_rcv_number,rcv_number);
		   success_rate=(double)rcv_number/send_number;
		   op_stat_write(pk_success_rate,success_rate);
		   op_pk_nfd_get(pkptr,"app_data",&p1);
		   op_pk_send(p1,OLSR_to_TRANSPORT);
		   delay=op_sim_time()-op_pk_creation_time_get(pkptr);
		   if(op_sim_time()>30)
		   op_stat_write(ete_delay,delay);
		   op_pk_destroy(pkptr);
		  
	   }
   else if(next_addr==own_source){
      
          op_pk_nfd_get(pkptr,"next_addr",&next_addr);
		   op_pk_nfd_get(pkptr,"pro_addr",&pro_addr);
		   if(next_addr==own_source)
			   {
				   op_pk_nfd_set(pkptr,"next_addr",path[temp_dst_addr][1]);
				   op_pk_nfd_set(pkptr,"pro_addr",own_source);
				   if(flag_send_dbg==1)
				   printf("这是中继节点，目的节点：%d,本节点：%d,前一个节点：%d,后一个节点：%d,包号：%d\n",temp_dst_addr,own_source,pro_addr,path[temp_dst_addr][1],seq);
				   if(path[temp_dst_addr][1]<100||hello_path[temp_dst_addr]<100)
					   {  
					      
						     op_pk_send(pkptr,OLSR_to_INTERFACE );
					   }
				   else{
				          if(hello_send_flag==1)
							  {
							     hello_send(3,temp_dst_addr); //寻路HELLO消息，类型3
						         time0=op_ev_time(hello_ev);
		                         op_ev_cancel(hello_ev);
		                         hello_ev=op_intrpt_schedule_self(time0+HELLO_SEND_TIME,0);
								 hello_send_flag=0;
							  }
                          
                         // p1=op_pk_copy(pkptr);
						 // op_pk_stamp(p1);
		                  //temp_save=(struct SAVE_PACKET*)malloc(sizeof(struct SAVE_PACKET));
		                 // temp_save->delete_time=op_sim_time()+HELLO_TIME;
		                 // temp_save->temp_packet_ptr=p1;
		                  //temp_save->dst=temp_dst_addr;
		                  //temp_save->next=save_packet_head;
		                  //save_packet_head=temp_save;
						  
       
				       }

			   }
       }

   FOUT;
};
/***********tc消息发送函数*****************/
void tc_send()
{
  Packet *p1,*temp_pk;
  char mpr_select[20]={"MPR_selector_"};
  int i=1,j,length;
  struct MPR_SELECTOR *temp_mpr_selector=NULL;
  FIN(tc_send());
  check_mpr_time();    //删除过期的节点
  p1=op_pk_create_fmt("tc_message");
  op_pk_nfd_set(p1,"source",own_source);
  op_pk_nfd_set(p1,"MSSN",tc_number);
  op_pk_nfd_set(p1,"type",TC);

  length=0;
  temp_mpr_selector=mpr_selector;
  i=1;
  for(;temp_mpr_selector!=NULL;temp_mpr_selector=temp_mpr_selector->next)
	  {
	    
	     for(j=13;j<20;j++)
	       { 
		        mpr_select[j]='\0'; 
	       };
	     sprintf(mpr_select,"MPR_selector_%d",i);
	     i++;
	     length++;
	     op_pk_nfd_set(p1,mpr_select,temp_mpr_selector->ms_main_addr);
	  }
  if(length!=0)
	  {
	      temp_pk=op_pk_create(32*length);
          op_pk_nfd_set(p1,"TC_length", temp_pk);
		//  op_ici_attr_set(ici_ptr, "nexthop_mac_addr",-1);
         // op_ici_install(ici_ptr);
		  op_pk_send(p1, OLSR_to_INTERFACE);
		 
	  }
   if(own_source==1)
	  {
	     own_source=1;
	  }
    // op_pk_destroy(p1);
  FOUT;
};
/**********hello消息发送函数****************/
void hello_send(int type,int path_addr)
{
    Packet * p1,*temp_pk1,*temp_pk2,*temp_pk3;
	char f_duicheng[15]={"f_duicheng_"};
	char duicheng[15]={"duicheng_"};
	char mpr[15]={"mpr_"};
	int i=1,j,length=0;
	struct ONE_HOP_TABLE *temp_one_hop=NULL;
	
	FIN(hello_send(int type,int path_addr));
	one_hop_message_update();
	mpr_compute();
	/*************创建一个待发送的包，并设置包参数****************/
	p1=op_pk_create_fmt("hello_message");
	op_pk_nfd_set(p1,"destination_address",1000);
	op_pk_nfd_set(p1,"source_address",own_source);
	op_pk_nfd_set(p1,"type",type);
    op_pk_nfd_set(p1,"temp",path_addr);
	
	/**************************设置非对称内容***********************************/
	i=1;	
	for(j=11;j<15;j++)
	   { 
		  f_duicheng[j]='\0'; 
	   };
    sprintf(f_duicheng,"f_duicheng_%d",i);
    length=0;
    for(temp_one_hop=one_hop_asys_head;temp_one_hop!=NULL;temp_one_hop=temp_one_hop->next)
		{
		   op_pk_nfd_set(p1,f_duicheng,temp_one_hop->neighbor_addr);
		   length++;
		   i++;	
	       for(j=0;j<15;j++)
	          { 
		          f_duicheng[j]='\0'; 
	          };
		   sprintf(f_duicheng,"f_duicheng_%d",i);
		}
   temp_pk1=op_pk_create(32*length);
   op_pk_nfd_set(p1,"fei_duicheng_length", temp_pk1);
   /***********************设置对称内容****************************/
    i=1;	 
	for(j=0;j<15;j++)
	   { 
		  duicheng[j]='\0'; 
	   };
    sprintf(duicheng,"duicheng_%d",i);
    length=0;
   
    for(temp_one_hop=one_hop_sys_head;temp_one_hop!=NULL;temp_one_hop=temp_one_hop->next)
		{
		    op_pk_nfd_set(p1,duicheng,temp_one_hop->neighbor_addr);
			i++;
			length++;
	       for(j=0;j<15;j++)
	          { 
		          duicheng[j]='\0'; 
	          };
		    sprintf(duicheng,"duicheng_%d",i);
		}
   temp_pk2=op_pk_create(32*length);
   op_pk_nfd_set(p1,"duicheng_length", temp_pk2);

	/***********************设置mpr内容*************************************/
    i=1;	
	for(j=0;j<15;j++)
	   { 
		  mpr[j]='\0'; 
	   };
    sprintf(mpr,"mpr_%d",i);
    length=0;
    for(temp_one_hop=one_hop_mpr_head;temp_one_hop!=NULL;temp_one_hop=temp_one_hop->next)
		{
		    op_pk_nfd_set(p1,mpr,temp_one_hop->neighbor_addr);
			i++;
			length++;
	        for(j=0;j<15;j++)
	          { 
		          mpr[j]='\0'; 
	          };
		    sprintf(mpr,"mpr_%d",i);
		}
    temp_pk3=op_pk_create(32*length);
    op_pk_nfd_set(p1,"MPR_length", temp_pk3);
    //op_ici_attr_set(ici_ptr, "nexthop_mac_addr",-1);
    //op_ici_install(ici_ptr);
	op_pk_send(p1, OLSR_to_INTERFACE);
	//op_pk_destroy(p1);
//if(own_source==1)
		//{
		    //own_source=1;
		//}
	FOUT;
};
/**********tc消息处理函数*********************/
void tc_recv(Packet* pkptr)
{
    int src;
	char mpr_select[20]={"MPR_selector_"};
	int i,j,temp_addr=0,seq;
    struct TC_REPEAT_TABLE *temp_tc_repeat=NULL;
	struct TOPU_TABLE* temp_topu=NULL;
    FIN(tc_recv(Packet* pkptr));
	op_pk_nfd_get(pkptr,"source",&src);
	op_pk_nfd_get(pkptr,"MSSN",&seq);
	if(src!=own_source)//不是自己发的包
		{
		    control_number=control_number+op_pk_total_size_get(pkptr)*8;
	        op_stat_write(control_message_overhead,control_number);
		    delete_tc_time();//删除过期节点
			delete_topu_time();
		    if(check_tc_repeat(src,seq)==0)//返回值0为没有转发过
				{
				     temp_tc_repeat=(struct TC_REPEAT_TABLE*)malloc(sizeof(struct TC_REPEAT_TABLE));
					 temp_tc_repeat->addr=src;
					 temp_tc_repeat->time=op_sim_time()+TC_HILD_TIME;
			    	 temp_tc_repeat->seq_number=seq;
					 temp_tc_repeat->next=tc_repeat_head;
					 tc_repeat_head= temp_tc_repeat;

                    i=1;
	                for(j=0;j<20;j++)
	                    { 
		                   mpr_select[j]='\0'; 
	                    };
                    sprintf(mpr_select,"MPR_selector_%d",i);
					delete_topu_repeat(src);//删除旧的拓扑
		            while(OPC_COMPCODE_FAILURE!=op_pk_nfd_get(pkptr,mpr_select,&temp_addr))
			        	{
						    i++;
	                        for(j=0;j<20;j++)
	                          { 
		                        mpr_select[j]='\0'; 
	                          };
	                     sprintf(mpr_select,"MPR_selector_%d",i);
				           temp_topu=(struct TOPU_TABLE*)malloc(sizeof(struct TOPU_TABLE));
							temp_topu->src_addr=temp_addr;
							temp_topu->dst_addr=src;
							temp_topu->time=op_sim_time()+TC_SEND_TIME *3;
						    temp_topu->willness=1;//********************	
						    temp_topu->next=topu_head;
							topu_head=temp_topu;
				        }
				
		             //op_ici_attr_set(ici_ptr, "nexthop_mac_addr",-1);
                     //op_ici_install(ici_ptr);
					 op_pk_send(pkptr, OLSR_to_INTERFACE);
				} 
			
			if(DBG_flag==1)
				{
				   temp_topu=topu_head;
				   printf("***********本地地址%d***********\n",own_source);
				   while(temp_topu!=NULL)
					   {
					       printf("%d-->%d\n",temp_topu->dst_addr,temp_topu->src_addr);
						   temp_topu=temp_topu->next;
					   }
				}
		}

	FOUT;
};
void delete_topu_time()
{
   int flag;
   struct TOPU_TABLE* temp_topu=NULL;
   struct TOPU_TABLE* temp_topu1=NULL;
   FIN(delete_topu_time());
   flag=1;
   while(topu_head!=NULL&&flag==1)
	   {
	      temp_topu=topu_head->next;
	      if(topu_head->time<op_sim_time())
			  {
			      free(topu_head);
				  topu_head=temp_topu;
			  }
		  else{
		         flag=0;
		      }
	   }
   temp_topu=topu_head;
   while(temp_topu!=NULL)
	   {
	      temp_topu1=temp_topu->next;
		  if(temp_topu1!=NULL)
			 {
	           if(temp_topu1->time<op_sim_time())
			     {
			         temp_topu->next=temp_topu1->next;
					 free(temp_topu1);
			     }
			   else
				 {
				     temp_topu=temp_topu1;
				 }
			 }
		  else{
		         temp_topu=temp_topu1;
		      }
	   }
   FOUT;
};
void delete_topu_repeat(int src)
{
   int flag;
   struct TOPU_TABLE* temp_topu=NULL;
   struct TOPU_TABLE* temp_topu1=NULL;
   FIN(delete_topu_repeat(int src));
   flag=1;
   while(topu_head!=NULL&&flag==1)
	   {
	      temp_topu=topu_head->next;
	      if(topu_head->src_addr==src||topu_head->dst_addr==src)
			  {
			      free(topu_head);
				  topu_head=temp_topu;
			  }
		  else{
		         flag=0;
		      }
	   }
   temp_topu=topu_head;
   while(temp_topu!=NULL)
	   {
	      temp_topu1=temp_topu->next;
		  if(temp_topu1!=NULL)
			 {
	           if(temp_topu1->src_addr==src||temp_topu1->dst_addr==src)
			     {
			         temp_topu->next=temp_topu1->next;
					 free(temp_topu1);
			     }
			   else
				 {
				     temp_topu=temp_topu1;
				 }
			 }
		  else{
		         temp_topu=temp_topu1;
		      }
	   }
   FOUT;
}
/******删除过期tc消息*********/
void delete_tc_time()
{
   int flag;
   struct TC_REPEAT_TABLE *temp_tc_repeat=NULL;
   struct TC_REPEAT_TABLE *temp_tc_repeat1=NULL;
   FIN(delete_tc_time());
   flag=1;
   while(flag==1&&tc_repeat_head!=NULL)//删除头结点
	   {
	      if(tc_repeat_head->time<op_sim_time())
			  {
			     temp_tc_repeat=tc_repeat_head->next;
				 free(tc_repeat_head);
				 tc_repeat_head=temp_tc_repeat;
			  }
		  else{
		         flag=0;
		      }
	   }
   temp_tc_repeat=tc_repeat_head;
   while(temp_tc_repeat!=NULL)
	   {
	       temp_tc_repeat1=temp_tc_repeat->next;
		   if(temp_tc_repeat1!=NULL)
			   {
	              if(temp_tc_repeat1->time<op_sim_time())
			         {
			            temp_tc_repeat->next=temp_tc_repeat1->next;
						 free(temp_tc_repeat1);
			         }
				  else{
				         temp_tc_repeat=temp_tc_repeat1;
				      }
			   }
		   else{
		          temp_tc_repeat=temp_tc_repeat1;
		       }
	   }
   FOUT;
}
/*********检查是否重传TC和删除旧的节点****************/
int check_tc_repeat(int src,int seq)
{
   int flag;
   struct TC_REPEAT_TABLE *temp_tc_repeat=NULL;
   FIN(check_tc_repeat(int src,int seq));
   temp_tc_repeat=tc_repeat_head;
   flag=0;
   while(temp_tc_repeat!=NULL)
	   {
	       
	      if(temp_tc_repeat->addr==src&&(temp_tc_repeat->seq_number==seq||temp_tc_repeat->seq_number>seq))
			  {
			     flag=1;//检查到重复发送过
			  }
		  temp_tc_repeat=temp_tc_repeat->next;
	   }
   	
   FRET(flag);
}
/**************hello消息处理函数****************************/
void hello_recv(Packet* pkptr)
{
	Packet *temp_pk;
	int src=0,dst=0,flag=0,i=0,j=0;
	int sys_flag=0,asys_flag=0,twohop_flag=0,flag2=0,flag1=0;
	char f_duicheng[15]={"f_duicheng_"};
	char duicheng[15]={"duicheng_"};
	char mpr[15]={"mpr_"};
	int temp_addr=0,temp,time0;
	struct LOCAL_MESSAGE_TABLE * temp_local=NULL;
    struct LOCAL_MESSAGE_TABLE * create_local=NULL;
	
	struct ONE_HOP_TABLE *temp_one_hop=NULL;
	struct TWO_HOP_TABLE*temp_two_hop=NULL;
	struct TWO_HOP_TABLE*guodu_two_hop=NULL;	
	struct TWO_HOP_ADDR *temp_two_addr=NULL;
	struct TWO_HOP_ADDR *create_two_addr=NULL;	
	struct MPR_SELECTOR *temp_mpr_selector=NULL;
	FIN(hello_recv(Packet* pkptr));
	temp_local=local_message_head;
	temp_two_hop=two_hop_head;

	if(pkptr != OPC_NIL)
	{
	       control_number=control_number+op_pk_total_size_get(pkptr)*8;
	       op_stat_write(control_message_overhead,control_number);
	       op_pk_nfd_get(pkptr,"destination_address",&dst);
	       op_pk_nfd_get(pkptr,"source_address",&src);
		   op_pk_nfd_get(pkptr,"MPR_length",&temp_pk);
		   op_pk_nfd_get(pkptr,"type",&flag);
           op_pk_nfd_get(pkptr,"temp",&temp);
		  if(src!=own_source)
			{
			
			  if(flag==3)//path请求消息
			   {
			     
			       op_pk_nfd_get(pkptr,"temp",&temp);
				   if(path[temp][1]<100)
					   {
					       if(hello_send_flag==1)
							  {
							     hello_send(4,temp);
						         time0=op_ev_time(hello_ev);
		                         op_ev_cancel(hello_ev);
		                         hello_ev=op_intrpt_schedule_self(time0+HELLO_SEND_TIME,0);
								 hello_send_flag=0;
							  }

					   }
			   }
		    if(flag==4)//path回复消息
				{
				
				   op_pk_nfd_get(pkptr,"temp",&temp);
				  if(hello_path[temp]>100)
					  {
					     
						 hello_path[temp]=src;
				         hello_path_time[temp]=op_sim_time()+3*HELLO_TIME;
				         save_ev=op_intrpt_schedule_self(op_sim_time(),3);
						 
					  }
				   
				    
				

				}
		   /*************邻居节点是否是新节点*************/
		     temp_local=local_message_head; 
		     for(sys_flag=0,flag=0;(temp_local!=NULL)&&flag==0;temp_local=temp_local->next)//sys_flag为0表示默认查不到，该节点为非对称节点，sys_flag=1节点为对称节点
			      {
			      
			   	       if(temp_local->neighbor_addr==src)
					      {
					   	   sys_flag=1; //查到在本地链路表存在此节点，将节点信息跟新为对称节点
						   temp_local->sys_time=op_sim_time()+SYS_TIME;
						   temp_local->asys_time=op_sim_time()+ASYS_TIME;
						   temp_local->delete_time=op_sim_time()+DELETE_TIME;
						   flag=1;;
					     }
				      
			      }
			if(sys_flag==0)
			{
			i=1;
    		for(j=0;j<15;j++)
			    {
				    duicheng[j]='\0';
				}
		    sprintf(duicheng,"duicheng_%d",i);
			flag=0;
		    while((OPC_COMPCODE_FAILURE!=op_pk_nfd_get(pkptr,duicheng,&temp_addr))&&flag==0)
			      {
		   
			          i++;
					  for(j=0;j<15;j++)
						{
				              duicheng[j]='\0';
				        }
					  sprintf(duicheng,"duicheng_%d",i);
					  if(temp_addr=own_source)
						  {
						     sys_flag=1;
							 create_local=(struct LOCAL_MESSAGE_TABLE*)malloc(sizeof(struct LOCAL_MESSAGE_TABLE));
							 create_local->neighbor_addr=src;
						     create_local->willness=1;    //暂时1
						     create_local->next=NULL;
							 create_local->sys_time=op_sim_time()+SYS_TIME;
							 create_local->asys_time=op_sim_time()+ASYS_TIME;
							 create_local->delete_time=op_sim_time()+DELETE_TIME;
							 temp_local=local_message_head;
							 local_message_head=create_local;
						     local_message_head->next=temp_local;
							 flag=1;
						  }
					   		        
				  }
					   
			}
			if(sys_flag==0)
			{
		       i=1;	
		       for(j=0;j<15;j++)
			     { 
			        f_duicheng[j]='\0'; 
			     };
               sprintf(f_duicheng,"f_duicheng_%d",i);
               flag=0;
		      /*******************查找是否本节点地址存在于包的非对称地址中，判断是否为对称节点*****************************/
		      while((OPC_COMPCODE_FAILURE!=op_pk_nfd_get(pkptr,f_duicheng,&temp_addr))&&flag==0)
			     {
			       i++;		           
				   for(j=0;j<15;j++)
				      { 
					       f_duicheng[j]='\0'; 
					  };
				    sprintf(f_duicheng,"f_duicheng_%d",i);
				    
	               if(own_source==temp_addr)//查到说明此节点为对称节点，将信息加入到本地信息表中
	                 {

								sys_flag=1;
								create_local=(struct LOCAL_MESSAGE_TABLE*)malloc(sizeof(struct LOCAL_MESSAGE_TABLE));
								create_local->neighbor_addr=src;
								create_local->willness=1;    //暂时1
								create_local->next=NULL;
								create_local->sys_time=op_sim_time()+SYS_TIME;
								create_local->asys_time=op_sim_time()+ASYS_TIME;
								create_local->delete_time=op_sim_time()+DELETE_TIME;
								temp_local=local_message_head;
								local_message_head=create_local;
								local_message_head->next=temp_local;
								flag=1;
								
				      };
		
			    };
			 }
		     if(sys_flag==0)
			     {
			        create_local=(struct LOCAL_MESSAGE_TABLE*)malloc(sizeof(struct LOCAL_MESSAGE_TABLE));
				    create_local->neighbor_addr=src;
				    create_local->willness=1; //暂时
		   		    create_local->next=NULL;
				    create_local->sys_time=op_sim_time()-2;
			        create_local->asys_time=op_sim_time()+SYS_TIME;
				    create_local->delete_time=op_sim_time()+DELETE_TIME;
				    temp_local=local_message_head;
				    local_message_head=create_local;
				    local_message_head->next=temp_local;
			     }
		  

		   
		   if(sys_flag==1)
			   {
			   /********************************************处理MPR selector部分*****************************************/
			    check_mpr_time();//删除过期的节点
			    i=1;	
	            for(j=0;j<15;j++)       
		           mpr[j]='\0'; 
                sprintf(mpr,"mpr_%d",i);
			    flag2=0;
				flag=0;
			    while((OPC_COMPCODE_FAILURE!=op_pk_nfd_get(pkptr,mpr,&temp_addr))&&flag==0)
			      {
			   
			          if(temp_addr==own_source)
				       {
				          flag2=1; //判断是否自己被选为MPR节点
						  flag=1;
				       }
			          i++;
	                  for(j=0;j<15;j++)       
		                mpr[j]='\0'; 
                      sprintf(mpr,"mpr_%d",i);
			  
			      }
			     if(flag2==1)
			     	{
			  	        flag1=0;
				        temp_mpr_selector=mpr_selector; 
		                for(;temp_mpr_selector!=NULL;temp_mpr_selector= temp_mpr_selector->next)
			              {
			                  if(temp_mpr_selector->ms_main_addr==src) //判断是否是被记录过
							     {
							        flag1=1;
								    temp_mpr_selector->ms_time=op_sim_time()+MPR_HOLD_TIME;
							     }
			              }
				       if(flag1==0)
					      {
					     
					         temp_mpr_selector=(struct MPR_SELECTOR*)malloc(sizeof(struct MPR_SELECTOR));
						     temp_mpr_selector->ms_main_addr=src;
						     temp_mpr_selector->ms_time=op_sim_time()+MPR_HOLD_TIME;
						     temp_mpr_selector->next=NULL;
						     temp_mpr_selector->next=mpr_selector;
						     mpr_selector=temp_mpr_selector;

					     }
			
	     }
				 
			   }	
		    one_hop_message_update();
		     /**********************跟新2跳邻居表********************************/
		    
		 
		     two_hop_message_update();     //检查要到期删除的节点
			 temp_two_hop=two_hop_head;
		     if(sys_flag==1)
	          {
		   		for(twohop_flag=0;temp_two_hop!=NULL;temp_two_hop=temp_two_hop->next)
					   {    
					   		if(temp_two_hop->one_hop_addr==src)
							 {
							      temp_two_hop->delete_time=op_sim_time()+TWO_HOP_TIME;
							      twohop_flag=1;//代表原来存在2跳邻居
								  temp_two_addr=temp_two_hop->two_addr_head;
								  /*********释放两跳节点内存*****************/
								  while(temp_two_addr!=NULL)//释放内存
									  {   
									      create_two_addr=temp_two_addr->next;
										  free(temp_two_addr);
										  temp_two_addr=create_two_addr;
									      
									  }
								   temp_two_hop->son_number=0;
								   temp_two_hop->two_addr_head=NULL;
							  
						          i=1;

								  for(j=0;j<15;j++)
									  {
				                         duicheng[j]='\0';
									  }
								   sprintf(duicheng,"duicheng_%d",i);
		                          while(OPC_COMPCODE_FAILURE!=op_pk_nfd_get(pkptr,duicheng,&temp_addr))
			                       {
			                         i++;
		                             for(j=0;j<15;j++)
									     {
				                             duicheng[j]='\0';
									     }
									 sprintf(duicheng,"duicheng_%d",i);
									 temp_one_hop=one_hop_sys_head;
									 flag=0;
									 while(temp_one_hop!=NULL)
										 {
										    if(temp_one_hop->neighbor_addr==temp_addr)
												{
												   flag=1;
												}
											temp_one_hop=temp_one_hop->next;
										 }
									 if(temp_addr==own_source)
										 {
										     flag=1;
										 }
									 if(flag==0)
										 {
				                             temp_two_addr=(struct TWO_HOP_ADDR*)malloc(sizeof(struct TWO_HOP_ADDR));
											 temp_two_hop->son_number++;
									         temp_two_addr->addr=temp_addr;
									         temp_two_addr->next=NULL;
									         create_two_addr=temp_two_hop->two_addr_head;
									         temp_two_hop->two_addr_head=temp_two_addr;
									         temp_two_hop->two_addr_head->next=create_two_addr;
										 }
			                        }; 
							  }
							   
					    }
		   
				    if(twohop_flag==0)//新节点，本地2跳邻居表不存在
						{
						    temp_two_hop=(struct TWO_HOP_TABLE*)malloc(sizeof(struct TWO_HOP_TABLE)); //创建新的
							temp_two_hop->one_hop_addr=src;
							temp_two_hop->son_number=0;
							temp_two_hop->willness=1;//暂时
							temp_two_hop->delete_time=op_sim_time()+TWO_HOP_TIME;
							temp_two_hop->next=NULL;
							temp_two_hop->two_addr_head=NULL;
							guodu_two_hop=two_hop_head;
							two_hop_head=temp_two_hop;
							two_hop_head->next=guodu_two_hop;
							
							
						  i=1;
						  for(j=0;j<15;j++)
							{
				                duicheng[j]='\0';
							}
                          sprintf(duicheng,"duicheng_%d",i);
		                  while(OPC_COMPCODE_FAILURE!=op_pk_nfd_get(pkptr,duicheng,&temp_addr))
			                     {
								 
								   
			                         i++;
		                             for(j=0;j<15;j++)
									     {
				                             duicheng[j]='\0';
									     }
									 sprintf(duicheng,"duicheng_%d",i);
									 temp_one_hop=one_hop_sys_head;
									 flag=0;
									 while(temp_one_hop!=NULL)
										 {
										    if(temp_one_hop->neighbor_addr==temp_addr)
												{
												   flag=1;
												}
											temp_one_hop=temp_one_hop->next;
										 }
									 if(temp_addr==own_source)
										 {
										     flag=1;
										 }
									 if(flag==0)
										 {
				                             temp_two_addr=(struct TWO_HOP_ADDR*)malloc(sizeof(struct TWO_HOP_ADDR));
											 temp_two_hop->son_number++;
									         temp_two_addr->addr=temp_addr;
									         temp_two_addr->next=NULL;
									         create_two_addr=two_hop_head->two_addr_head;
									         two_hop_head->two_addr_head=temp_two_addr;
									         two_hop_head->two_addr_head->next=create_two_addr;
									    }
			                     }; 
						
						  }
					
					
					}
		  if(DBG_flag==1)
		   {
		    temp_one_hop=one_hop_sys_head;

             printf("*********************************\n");
			       while(temp_one_hop!=NULL)
					   {
					       printf("本地：%d,一跳：%d\n",own_source,temp_one_hop->neighbor_addr);
						   temp_one_hop=temp_one_hop->next;
					   }
		  }

		   
		   	   
		}  
		   
	};
	FOUT;
};
/*****************检查MPR节点过期*****/
void check_mpr_time()
{
   struct MPR_SELECTOR *temp=NULL,*temp1=NULL;
   int flag;
   FIN(check_mpr_time());
   temp=mpr_selector;
   flag=0;
   while(mpr_selector!=NULL&&flag!=1)
	   {
	      if(mpr_selector->ms_time<op_sim_time())
			  {
			     temp=mpr_selector->next;
				 free(mpr_selector);
				 mpr_selector=temp;
			  }else{
		             flag=1;
		           }
	   }
   temp=mpr_selector;
   while(temp!=NULL)
	   {
	      temp1=temp->next;
		  if(temp1!=NULL)
			  {
			     if(temp1->ms_time<op_sim_time())
			      {
			          temp->next=temp1->next;
			          free(temp1); 
				     
				  }
				  else{
			               temp=temp1;
			           }
			  }
		      else{
		               temp=temp1;
		           }
	      
	   }
   FOUT;
}

/***********两跳信息更新********************/
void two_hop_message_update()
{
   int flag=0;
   struct TWO_HOP_TABLE*temp_two_hop=NULL;
   struct TWO_HOP_TABLE*guodu_two_hop=NULL;
   
   struct TWO_HOP_ADDR *temp_two_addr=NULL;
   struct TWO_HOP_ADDR *create_two_addr=NULL;
   FIN(two_hop_message_update());
   flag=0; 
   while((flag!=1)&&(two_hop_head!=NULL))
	   {
	      if(two_hop_head->delete_time<op_sim_time())
		   {
			     temp_two_addr=two_hop_head->two_addr_head;
				 while(temp_two_addr!=NULL)
					 {
					    create_two_addr=temp_two_addr->next;
						free(temp_two_addr);
						temp_two_addr=create_two_addr;
					 }
		         two_hop_head->two_addr_head=NULL;
				 
		         temp_two_hop=two_hop_head->next;
		         free(two_hop_head);
		         two_hop_head=temp_two_hop;
		   }else
			  {
			    flag=1;
			  }
	   }
   flag=0;
   temp_two_hop=two_hop_head;
   
   if(temp_two_hop!=NULL)
	 {
         guodu_two_hop=temp_two_hop->next; 
         while((guodu_two_hop!=NULL)&&(flag!=0))
             {
	            if(guodu_two_hop->delete_time<op_sim_time())
		            {
			            temp_two_addr=guodu_two_hop->two_addr_head;
				        while(temp_two_addr!=NULL)
					       {
					           create_two_addr=temp_two_addr->next;
						       free(temp_two_addr);
						       temp_two_addr=create_two_addr;
					       }
		                guodu_two_hop->two_addr_head=NULL;
				 
		                temp_two_hop->next=guodu_two_hop->next;
		                free(guodu_two_hop);
				        if(temp_two_hop->next==NULL)
				           {
					         flag=1;
					       }   
		                guodu_two_hop=temp_two_hop->next;
		             }else
					      {
	                         temp_two_hop=temp_two_hop->next;
					         if(temp_two_hop->next==NULL)
						        {
						            flag=1;
						        }else
								    {
					                  guodu_two_hop=temp_two_hop->next;
							         }
	                     }
				}
		 }   
  
   FOUT;
}
/********************************************更新一跳邻居表************************************************/

void one_hop_message_update()
{  
    int flag=0;
    struct LOCAL_MESSAGE_TABLE * temp_local_1=NULL; 
	struct LOCAL_MESSAGE_TABLE * temp_local_2=NULL;
	struct ONE_HOP_TABLE * temp_one_hop=NULL;
	struct ONE_HOP_TABLE * temp_one_hop_1=NULL;
	struct MPR_SELECTOR *temp_mpr_selector=NULL;
	FIN(message_update());
	/************检查本地信息表到期删除**********************/
	flag=0;
	if(local_message_head==NULL)
		{
		    flag=1;
		}
	while(flag==0)
		{
		    if(local_message_head->delete_time<op_sim_time())
				{
		             temp_local_1=local_message_head->next;
					 free(local_message_head);
		             local_message_head= temp_local_1;
				}else{
			             flag=1;
			         }
				
		   if(local_message_head==NULL)
			   {
			      flag=1;
			   }
		}
	flag=0;	   
	temp_local_1=local_message_head;
	if(temp_local_1!=NULL)
    {		
	temp_local_2=temp_local_1->next;
	if(temp_local_2==NULL)
		{
			flag=1;
		}
	while(flag!=1)
		{
		    if(temp_local_2->delete_time<op_sim_time())
				{
				    temp_local_1->next=temp_local_2->next;
					free(temp_local_2);
				   temp_local_2=temp_local_1->next;
				}else{
			              temp_local_1=temp_local_2;
						  temp_local_2=temp_local_1->next;
			         }
			if(temp_local_2==NULL)
	       	{
			     flag=1;
		    }
		}
	}
	temp_local_1=local_message_head;
	if(local_dbg_flag==1)
	   {   printf("*****************%d*****************************\n",own_source);
	       while(temp_local_1!=NULL)
			   {
			        printf("**%d,时间%f******\n",temp_local_1->neighbor_addr,temp_local_1->sys_time);
					temp_local_1=temp_local_1->next;
					
			   }
	   }
	/*************释放本地一跳信息表内存******************/
	while(one_hop_asys_head!=NULL)
		{
		    temp_one_hop=one_hop_asys_head->next;
			free(one_hop_asys_head);
			one_hop_asys_head=temp_one_hop;
		}
	while(one_hop_sys_head!=NULL)
		{
		    temp_one_hop=one_hop_sys_head->next;
			free(one_hop_sys_head);
			one_hop_sys_head=temp_one_hop;
		}
	
    one_hop_asys_head=NULL;
    one_hop_sys_head=NULL;
    /***********通过本地信息表，计算一跳邻居表**************/
	
	temp_local_1=local_message_head;
	while(temp_local_1!=NULL)
		{
		   if(temp_local_1->sys_time>op_sim_time())
			   { 
			       temp_one_hop=(struct ONE_HOP_TABLE*)malloc(sizeof(struct ONE_HOP_TABLE));
				   temp_one_hop->next=NULL;
				   temp_one_hop->neighbor_addr=temp_local_1->neighbor_addr;
				   
				   temp_one_hop_1=one_hop_sys_head;
				   one_hop_sys_head=temp_one_hop;
				   one_hop_sys_head->next=temp_one_hop_1;
				  
			   }else if((temp_local_1->sys_time<op_sim_time())&&(temp_local_1->asys_time>op_sim_time()))
			          {
					      
					      temp_one_hop=(struct ONE_HOP_TABLE*)malloc(sizeof(struct ONE_HOP_TABLE));
				          temp_one_hop->next=NULL;
				          temp_one_hop->neighbor_addr=temp_local_1->neighbor_addr;
						  
				          temp_one_hop_1=one_hop_asys_head;
				          one_hop_asys_head=temp_one_hop;
				          one_hop_asys_head->next=temp_one_hop_1;
					  }
		    temp_local_1=temp_local_1->next;
			
		}
	
	 /*
	 printf( "***********************\n本地主机地址：%d\n",own_source);
	 while( temp_one_hop!=NULL)
		 {
		    printf("一跳：%d\n", temp_one_hop->neighbor_addr);
			 temp_one_hop= temp_one_hop->next;
		 }
	 */
	/*****************计算MPR节点*************************/   
	//mpr_compute();
	/*****************************************************/

	FOUT;
}
/**************************************计算MPR*************************************************/

static void mpr_compute()
{
   struct TWO_HOP_TABLE* temp_two_hop_1=NULL;
   struct TWO_HOP_TABLE* temp_two_hop_2=NULL;
   struct TWO_HOP_TABLE* temp_two_hop_3=NULL;
   
   struct ONE_HOP_TABLE* temp_one_hop=NULL;
   struct ONE_HOP_TABLE* temp_one_hop1=NULL;
   struct ONE_HOP_TABLE* temp_one_hop2=NULL;
   
   struct TWO_HOP_ADDR* temp_two_addr=NULL;
   struct TWO_HOP_ADDR* temp_two_addr_1=NULL;
   int temp_addr,flag;
   FIN(mpr_compute());
   /*********释放mpr链表内存**************/
   while(one_hop_mpr_head!=NULL)
	   {
	        temp_one_hop=one_hop_mpr_head->next;
			free(one_hop_mpr_head);
			one_hop_mpr_head=temp_one_hop;
	   }
   /*********************************************/
   flag=0;  //检查是否为孤单节点标志
   temp_two_hop_1=copy_list(two_hop_head);//重新复制一个两跳节点表
   temp_two_hop_2= temp_two_hop_1;
   if(temp_two_hop_1!=NULL)
	   {
          temp_two_hop_2=temp_two_hop_1;
          while(temp_two_hop_2!=NULL)
	          {
	             temp_two_addr=temp_two_hop_2->two_addr_head;
		         flag=1;//默认为非孤单节点
	             while(temp_two_addr!=NULL)
			         {
			            temp_addr=temp_two_addr->addr;
				        flag=gudan_jiedian(temp_two_hop_2->one_hop_addr,temp_addr);//判断孤单节点,0为孤单,一旦发现有重复的，返回1
						 /********加入mpr节点**************/
						 if(flag==0) //发现是孤单节点，结束节点
						   {  
						       insert_mpr( temp_two_hop_2->one_hop_addr);
							   delete_mpr(temp_two_hop_2->one_hop_addr,temp_two_hop_1,0);//删除重复节点,使用模式0
							   break;
						   }	 							
					     temp_two_addr=temp_two_addr->next;		         
			         }
				 if(flag==0)
					 {
					     temp_two_addr=temp_two_hop_2->two_addr_head;
						 while( temp_two_hop_2->two_addr_head!=NULL)
							 {
							      temp_two_addr=temp_two_hop_2->two_addr_head->next;
								  free(temp_two_hop_2->two_addr_head);
								  temp_two_hop_2->son_number--;
								  two_hop_number--;
								  temp_two_hop_2->two_addr_head= temp_two_addr;
							 }
					 }
		         temp_two_hop_2=temp_two_hop_2->next;
	          }
		 }
  
   while( two_hop_number!=0)
	   {
	       temp_two_hop_2=temp_two_hop_1;
		   flag=temp_two_hop_2->son_number;
		   temp_two_hop_3=temp_two_hop_2;
		   while(temp_two_hop_2!=NULL)
			   {
			       if(temp_two_hop_2->son_number>flag)
					   {
					       flag=temp_two_hop_2->son_number;
					       temp_two_hop_3=temp_two_hop_2;
					   }
				   temp_two_hop_2=temp_two_hop_2->next;
			   }
		   
		   if(temp_two_hop_3->son_number!=0)
			   {
			       insert_mpr( temp_two_hop_3->one_hop_addr);
				   delete_mpr(temp_two_hop_3->one_hop_addr,temp_two_hop_1,1);//删除重复节点，使用模式1
			   }
	   }
   free_list( temp_two_hop_1);
   
   
   
   
  
   /***********删除冗余mpr**************/
  
   while(two_all_hop_head!=NULL)//释放内存
	   {
 
	       temp_two_addr=two_all_hop_head->next;
		   free(two_all_hop_head);
		   two_all_hop_head=temp_two_addr;  
	   }
   temp_two_hop_1=copy_list(two_hop_head);//重新复制一个两跳节点表
   two_hop_number=0;
   creat_two_hop(temp_two_hop_1);//创建两跳所有节点链表two_all_hop_head
   temp_two_hop_2=temp_two_hop_1;
   temp_one_hop=one_hop_mpr_head;
   temp_one_hop2=NULL;
   while(temp_one_hop!=NULL)
	   {
			temp_two_hop_2=temp_two_hop_1;
	        while(temp_two_hop_2!=NULL)
	         {
			      
	              if(temp_one_hop->neighbor_addr==temp_two_hop_2->one_hop_addr)
					  {

						  temp_two_addr=copy_two_addr(temp_two_hop_2->two_addr_head);//保存子链表
						  while(temp_two_hop_2->two_addr_head!=NULL)
							  {
							      temp_two_addr_1=temp_two_hop_2->two_addr_head->next;
								  free(temp_two_hop_2->two_addr_head);
								  temp_two_hop_2->two_addr_head=temp_two_addr_1;
							  }

				        creat_two_hop_1(temp_two_hop_1);
				        temp_two_hop_2->two_addr_head= temp_two_addr;
				        if(temp_number==two_hop_number)
					       {
					          temp_one_hop1=(struct ONE_HOP_TABLE*)malloc(sizeof(struct ONE_HOP_TABLE));
							  temp_one_hop1->neighbor_addr=temp_one_hop->neighbor_addr;
							  temp_one_hop1->next=temp_one_hop2;
							  temp_one_hop2=temp_one_hop1;
					       };
						  
					  }
				  
				  
				  temp_two_hop_2=temp_two_hop_2->next;
	         }
			  temp_one_hop=temp_one_hop->next;
	   }
   
   
   delete_repeat_mpr(temp_one_hop2);
   while(temp_one_hop2!=NULL)
	   {
	      temp_one_hop1=temp_one_hop2->next;
		  free(temp_one_hop2);
		  temp_one_hop2=temp_one_hop1;
	   }
   free_list( temp_two_hop_1);
   temp_one_hop=one_hop_mpr_head;
   if(DBG_flag==1)
	   {
	       printf("*********本地地址%d**********\n",own_source);
	       while(temp_one_hop!=NULL)
			   {
			      printf("mpr节点：%d\n",temp_one_hop->neighbor_addr);
				  temp_one_hop=temp_one_hop->next;
			   }
	   }
  
   FOUT;
}
void delete_repeat_mpr(struct ONE_HOP_TABLE *temp)
{
   struct ONE_HOP_TABLE *temp_one_hop=NULL;
   struct ONE_HOP_TABLE *temp_one_hop1=NULL;
   FIN(delete_repeat_mpr(struct ONE_HOP_TABLE *temp));
   temp_one_hop1=temp;
   while(temp_one_hop1!=NULL)
	   {
	       delete_one_mpr(temp_one_hop1->neighbor_addr);
	       temp_one_hop1=temp_one_hop1->next;
	   }
   FOUT;
};
void delete_one_mpr(int temp)
{
   struct ONE_HOP_TABLE *temp_one_hop=NULL;
   struct ONE_HOP_TABLE *temp_one_hop1=NULL;
   int flag=1;
   FIN(delete_one_mpr(int temp));
   temp_one_hop=one_hop_mpr_head;
   flag=1;
   if(one_hop_mpr_head!=NULL&&flag==1)
	   {
	       if(one_hop_mpr_head->neighbor_addr==temp)
			   {
			       temp_one_hop=one_hop_mpr_head->next;
				   free(one_hop_mpr_head);
				   one_hop_mpr_head=temp_one_hop;
				   flag=0;
			   }
		   else{
		           temp_one_hop1=one_hop_mpr_head;
				   temp_one_hop=temp_one_hop1->next;
				   while(temp_one_hop!=NULL&&flag==1)
					   {
					       if(temp_one_hop->neighbor_addr==temp)
							   {
							       temp_one_hop1->next=temp_one_hop->next;
								   free(temp_one_hop);
								   flag=0;
							   }
						   temp_one_hop1=temp_one_hop;
						   temp_one_hop=temp_one_hop->next;
					   }
		       }
	   }
   
   FOUT;
}
struct TWO_HOP_ADDR* copy_two_addr(struct TWO_HOP_ADDR* temp)
{
   struct TWO_HOP_ADDR* temp1=NULL;
   struct TWO_HOP_ADDR* temp2=NULL;
   FIN(copy_two_addr(struct TWO_HOP_ADDR* temp));
   while(temp!=NULL)
	   {
	       temp1=(struct TWO_HOP_ADDR*)malloc(sizeof(struct TWO_HOP_ADDR));
		   temp1->addr=temp->addr;
		   temp1->next=temp2;
		   temp2=temp1;
		   temp=temp->next;
	   }
   
   FRET(temp2);
}
/************************************/
void creat_two_hop_1(struct TWO_HOP_TABLE* temp_two_hop)
{
    struct TWO_HOP_ADDR* temp_two_addr1=NULL;
	struct TWO_HOP_ADDR* temp_two_addr2=NULL;
	struct TWO_HOP_ADDR* temp_two_addr=NULL;
	struct TWO_HOP_TABLE* temp_two_hop1=NULL;
    FIN(creat_two_hop_1(struct TWO_HOP_TABLE* temp_two_hop));
	temp_two_hop1=temp_two_hop;
	temp_number=0;
	while(temp_two_all_hop_head!=NULL)//释放内存
	   {
	       temp_two_addr=temp_two_all_hop_head->next;
		   free(temp_two_all_hop_head);
		   temp_two_all_hop_head=temp_two_addr;  
	   }
	while(temp_two_hop1!=NULL)
		{ 
		   temp_two_addr2=temp_two_hop1->two_addr_head;
		   while(temp_two_addr2!=NULL)
			  {
			        if(check_two_addr_1(temp_two_addr2->addr)==0)
						{
						    temp_number++;
						    temp_two_addr1=(struct TWO_HOP_ADDR*)malloc(sizeof(struct TWO_HOP_ADDR));
				    		temp_two_addr1->next=temp_two_all_hop_head;
							temp_two_addr1->addr=temp_two_addr2->addr;
							temp_two_all_hop_head=temp_two_addr1;
						};
					temp_two_addr2=temp_two_addr2->next;
			  } 
		   temp_two_hop1=temp_two_hop1->next;
		}
	
	FOUT;
}

/***********************************/
void creat_two_hop(struct TWO_HOP_TABLE* temp_two_hop)
{
    struct TWO_HOP_ADDR* temp_two_addr1=NULL;
	struct TWO_HOP_ADDR* temp_two_addr2=NULL;
	
	struct TWO_HOP_TABLE* temp_two_hop1=NULL;
    FIN(creat_two_hop(struct TWO_HOP_TABLE* temp_two_hop));
	temp_two_hop1=temp_two_hop;
	while(temp_two_hop1!=NULL)
		{  
		   temp_two_addr2=temp_two_hop1->two_addr_head;
		   while(temp_two_addr2!=NULL)
			  {   
			        if(check_two_addr(temp_two_addr2->addr)==0)
						{
						    two_hop_number++;
						    temp_two_addr1=(struct TWO_HOP_ADDR*)malloc(sizeof(struct TWO_HOP_ADDR));
				    		temp_two_addr1->next=two_all_hop_head;
							temp_two_addr1->addr=temp_two_addr2->addr;
							two_all_hop_head=temp_two_addr1;
						};
					temp_two_addr2=temp_two_addr2->next;
			  }
		   temp_two_hop1=temp_two_hop1->next;
		}
	
	FOUT;
}
/****************************/
int check_two_addr_1(int temp)
{
   int flag;
   struct TWO_HOP_ADDR* temp_two_addr=NULL;
   FIN(check_two_addr_1(int temp));
   flag=0;  //默认为不重复
   temp_two_addr=temp_two_all_hop_head;
   while(temp_two_addr!=NULL)
	   {
	      if(temp_two_addr->addr==temp)
			  {
			      flag=1;
			  }
		  temp_two_addr=temp_two_addr->next;
	   }
   FRET(flag);
}
/**************************/
int check_two_addr(int temp)
{
   int flag;
   struct TWO_HOP_ADDR* temp_two_addr=NULL;
   FIN(check_two_addr(int temp));
   flag=0;  //默认为不重复
   temp_two_addr=two_all_hop_head;
   while(temp_two_addr!=NULL)
	   {
	      if(temp_two_addr->addr==temp)
			  {
			      flag=1;
			  }
		  temp_two_addr=temp_two_addr->next;
	   }
   FRET(flag);
}
/*************删除一跳邻居节点的所有两跳节点***********************/
void delete_mpr(int temp_addr,struct TWO_HOP_TABLE* temp_two_hop,int moshi)
{
   struct TWO_HOP_TABLE* temp_two_hop_next=NULL;
   struct TWO_HOP_ADDR* temp_two_addr=NULL;
   FIN(delete_mpr(int temp_addr,struct TWO_HOP_TABLE* temp_two_hop,int moshi));
   if(moshi==0)
	 {
      for(;temp_two_hop!=NULL;temp_two_hop=temp_two_hop->next)
	     {    
	       if(temp_two_hop->one_hop_addr==temp_addr)
			   {
			       temp_two_addr=temp_two_hop->two_addr_head;
			       for(;temp_two_addr!=NULL;temp_two_addr=temp_two_addr->next)
					   {
					        delete_point(temp_two_addr->addr,temp_two_hop->next); //删除两跳节点		
					   }
			   }
	     }
    }
   
   if(moshi==1)
	   {
	      temp_two_hop_next=temp_two_hop;
	      for(;temp_two_hop!=NULL;temp_two_hop=temp_two_hop->next)
			  {
			      
			      if(temp_two_hop->one_hop_addr==temp_addr)
					  {
					       while(temp_two_hop->two_addr_head!=NULL)
					          {
					              delete_point(temp_two_hop->two_addr_head->addr,temp_two_hop_next);
					          }
					  }
			  }
	   }
   FOUT;
}
/***********删除所有两跳节点**************************/
void delete_point(int temp_addr,struct TWO_HOP_TABLE*temp_two_hop)
{
   struct TWO_HOP_TABLE*temp_two_hop_next=NULL;
   struct TWO_HOP_ADDR* temp_two_addr=NULL;
   struct TWO_HOP_ADDR* temp_two_addr_next=NULL;
   int flag=0;
   FIN(delete_point(int temp_addr,struct TWO_HOP_TABLE*temp_two_hop));
   for(;temp_two_hop!=NULL;temp_two_hop=temp_two_hop->next)
	   {    
	       flag=0;
	       temp_two_addr=temp_two_hop->two_addr_head;
		   if(temp_two_hop->two_addr_head!=NULL)
			   {   
		           if(temp_two_hop->two_addr_head->addr==temp_addr)
			            {   
			                  flag=1;
							  temp_two_addr=temp_two_hop->two_addr_head->next;
							  free(temp_two_hop->two_addr_head);
				              temp_two_hop->two_addr_head=temp_two_addr;
							  temp_two_hop->son_number--;
							  two_hop_number--;
			            }
			   }
		   if(flag==0)
			   {   
		          while(temp_two_addr!=NULL)
			           { 
					       temp_two_addr_next=temp_two_addr->next;
						   if(temp_two_addr_next!=NULL)
							   {
			                    if(temp_two_addr_next->addr==temp_addr)
					                {
									     temp_two_addr->next=temp_two_addr_next->next;
					                   free(temp_two_addr_next);
										 temp_two_hop->son_number--;
							            two_hop_number--;
					                }else{   
								               temp_two_addr=temp_two_addr_next;
								          }
							  }else{
						               temp_two_addr=temp_two_addr_next;
						          }
			          }
		     }
	   }	  
   FOUT;
}
/**********将MPR节点加入mpr链表********************/
void insert_mpr(int temp_addr)
{
    struct ONE_HOP_TABLE* temp_one_hop=NULL;
	FIN(insert_mpr(int temp_addr));
	temp_one_hop=(struct ONE_HOP_TABLE*)malloc(sizeof(struct ONE_HOP_TABLE));
	temp_one_hop->neighbor_addr=temp_addr;
	temp_one_hop->next=NULL;
							 
	temp_one_hop->next=one_hop_mpr_head;
    one_hop_mpr_head=temp_one_hop;
	FOUT;
}
/***********默认节点是孤立节点为0，非孤立节点1***********************/
static int gudan_jiedian(int temp,int temp_addr)
{
    int flag;
	struct TWO_HOP_ADDR *temp_two_addr=NULL;
	struct TWO_HOP_TABLE* temp_two_hop=NULL;
	FIN(copy_list(struct TWO_HOP_TABLE* temp));
	flag=0;
	temp_two_hop=two_hop_head;
	while(temp_two_hop!=NULL)
		{   
		if(temp!=temp_two_hop->one_hop_addr)
			{
		    temp_two_addr= temp_two_hop->two_addr_head;
			if(temp_two_addr!=NULL)
				{
		            if(temp_two_addr->addr==temp_addr)
			            {   
				           flag=1;
					       break;
			            }
			   
				}	
			
			}
		  temp_two_hop=temp_two_hop->next;
		}
	FRET(flag);
}
/*************复制一个两跳信息表*************************/
static struct TWO_HOP_TABLE* copy_list(struct TWO_HOP_TABLE* temp)
	{
	    struct TWO_HOP_TABLE* temp_two_hop_1=NULL;
		struct TWO_HOP_TABLE* temp_two_hop_2=NULL;
		struct TWO_HOP_TABLE* temp_two_hop_3=NULL;
	
	    struct TWO_HOP_ADDR* temp_two_addr=NULL;
		struct TWO_HOP_ADDR* temp_two_addr_1=NULL;
		struct TWO_HOP_ADDR* temp_two_addr_2=NULL;
	    FIN(copy_list(struct TWO_HOP_TABLE* temp));
		two_hop_number=0;//复制子节点数量置0
	    while(temp!=NULL)
			{   
			   
			    temp_two_hop_1=(struct TWO_HOP_TABLE*)malloc(sizeof(struct TWO_HOP_TABLE));
				temp_two_hop_1->next=NULL;
				temp_two_hop_1->two_addr_head=NULL;
				temp_two_hop_1->one_hop_addr=temp->one_hop_addr;
				temp_two_hop_1->son_number=temp->son_number;
				temp_two_hop_1->willness=temp->willness;
				temp_two_hop_1->delete_time=temp->delete_time;
				
				temp_two_addr_2=temp->two_addr_head;
			    while(temp_two_addr_2!=NULL)
					 {  
					    temp_two_addr=(struct TWO_HOP_ADDR*)malloc(sizeof(struct TWO_HOP_ADDR));
						two_hop_number++;  //子节点数量加1
					    temp_two_addr->next=NULL;
						temp_two_addr->addr=temp_two_addr_2->addr;
						temp_two_addr_1=temp_two_hop_1->two_addr_head;
						temp_two_hop_1->two_addr_head=temp_two_addr;
						temp_two_addr->next=temp_two_addr_1;
						temp_two_addr_2=temp_two_addr_2->next;
					 }
				temp_two_hop_3=temp_two_hop_2;
				temp_two_hop_2=temp_two_hop_1;
				temp_two_hop_1->next=temp_two_hop_3;
				temp=temp->next;
			}
		
		FRET(temp_two_hop_2);
		
	}
/************释放一个两跳内存表内存****************************/
static void free_list(struct TWO_HOP_TABLE* temp)
{
    struct TWO_HOP_TABLE* temp_two_hop=NULL;
	struct TWO_HOP_ADDR* temp_two_addr=NULL;
    FIN(free_list(struct TWO_HOP_TABLE* temp));
	    while(temp!=NULL)
			{
			    while(temp->two_addr_head!=NULL)
					{
					    temp_two_addr=temp->two_addr_head->next;
						free(temp->two_addr_head);
						temp->two_addr_head=temp_two_addr;
					}
				temp_two_hop=temp->next;
				free(temp);
				temp=temp_two_hop;
			}
	FOUT;
}
void show()
{
	struct TWO_HOP_TABLE*temp_two_hop=NULL;
	struct TWO_HOP_ADDR*temp_two_addr=NULL;
	struct ONE_HOP_TABLE* temp_one_hop=NULL;
	FIN(show());
	temp_two_hop=two_hop_head;
	temp_one_hop=one_hop_mpr_head;
    printf("################本地地址为:%d###############################\n",own_source);
    for(;temp_two_hop!=NULL;temp_two_hop=temp_two_hop->next)
	   {
	       temp_two_addr=temp_two_hop->two_addr_head;
		   printf("*********************一跳主节点：%d数量%d*****************\n",temp_two_hop->one_hop_addr,temp_two_hop->son_number);
		   for(;temp_two_addr!=NULL;temp_two_addr=temp_two_addr->next)
			   {
			      printf("**********两跳内容：%d*****************\n",temp_two_addr->addr);
			   }
	   }
    for(;temp_one_hop!=NULL;temp_one_hop=temp_one_hop->next)
		 printf("**********MPR为：%d*****************\n",temp_one_hop->neighbor_addr);
	FOUT;
	
};
/*
void priority_send()
	{
	 Packet *pkptr;
	List* priority0;
   List* priority1;
   List* priority2;
   List* priority3;
   List* priority4;
   List* priority5;
   List* priority6;
   List* priority7;
	FIN(priority_send());
   priority0=op_prg_list_create();
   priority1=op_prg_list_create();
   priority2=op_prg_list_create();
   priority3=op_prg_list_create();
   priority4=op_prg_list_create();
   priority5=op_prg_list_create();
   priority6=op_prg_list_create();
   priority7=op_prg_list_create();
	if(op_prg_list_size(priority0))
	{
	pkptr=op_prg_list_remove(priority0,OPC_LISTPOS_HEAD);
	op_pk_send(pkptr,OLSR_to_TRANSPORT);
	}
else if(op_prg_list_size(priority1))
	{
	pkptr=op_prg_list_remove(priority1,OPC_LISTPOS_HEAD);
	op_pk_send(pkptr,OLSR_to_TRANSPORT);
	}
else if(op_prg_list_size(priority2))
	{
	pkptr=op_prg_list_remove(priority2,OPC_LISTPOS_HEAD);
	op_pk_send(pkptr,OLSR_to_TRANSPORT);
	}
else if(op_prg_list_size(priority3))
	{
	pkptr=op_prg_list_remove(priority3,OPC_LISTPOS_HEAD);
	op_pk_send(pkptr,OLSR_to_TRANSPORT);
	}
else if(op_prg_list_size(priority4))
	{
	pkptr=op_prg_list_remove(priority4,OPC_LISTPOS_HEAD);
	op_pk_send(pkptr,OLSR_to_TRANSPORT);
	}
else if(op_prg_list_size(priority5))
	{
	pkptr=op_prg_list_remove(priority5,OPC_LISTPOS_HEAD);
	op_pk_send(pkptr,OLSR_to_TRANSPORT);
	}
else if(op_prg_list_size(priority6))
	{
	pkptr=op_prg_list_remove(priority6,OPC_LISTPOS_HEAD);
	op_pk_send(pkptr,OLSR_to_TRANSPORT);
	}
else if(op_prg_list_size(priority7))
	{
	pkptr=op_prg_list_remove(priority7,OPC_LISTPOS_HEAD);
	op_pk_send(pkptr,OLSR_to_TRANSPORT);
	}
else;

	FOUT;
	}
*/

/* End of Function Block */

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
	void olsr_gaijing_4 (OP_SIM_CONTEXT_ARG_OPT);
	VosT_Obtype _op_olsr_gaijing_4_init (int * init_block_ptr);
	void _op_olsr_gaijing_4_diag (OP_SIM_CONTEXT_ARG_OPT);
	void _op_olsr_gaijing_4_terminate (OP_SIM_CONTEXT_ARG_OPT);
	VosT_Address _op_olsr_gaijing_4_alloc (VosT_Obtype, int);
	void _op_olsr_gaijing_4_svar (void *, const char *, void **);


#if defined (__cplusplus)
} /* end of 'extern "C"' */
#endif




/* Process model interrupt handling procedure */


void
olsr_gaijing_4 (OP_SIM_CONTEXT_ARG_OPT)
	{
#if !defined (VOSD_NO_FIN)
	int _op_block_origin = 0;
#endif
	FIN_MT (olsr_gaijing_4 ());

		{
		/* Temporary Variables */
		int n,i;
		int priority1,dest,next_addr,time0;
		Packet* p1;
		Packet* pkptr;
		//int priority4;
		/* End of Temporary Variables */


		FSM_ENTER ("olsr_gaijing_4")

		FSM_BLOCK_SWITCH
			{
			/*---------------------------------------------------------*/
			/** state (init) enter executives **/
			FSM_STATE_ENTER_FORCED_NOLABEL (0, "init", "olsr_gaijing_4 [init enter execs]")
				FSM_PROFILE_SECTION_IN ("olsr_gaijing_4 [init enter execs]", state0_enter_exec)
				{
				/***********设置一个自中断********************************/
				op_intrpt_schedule_self(op_sim_time()+op_dist_uniform(2)+HELLO_SEND_TIME,0);//hello消息定时
				op_intrpt_schedule_self(op_sim_time()+op_dist_uniform(5)+TC_SEND_TIME ,1);//tc消息定时
				op_intrpt_schedule_self(op_sim_time()+2 ,2);//到期删除定时
				/******从节点获得源地址和目的地址********************/
				node_id = op_topo_parent (op_id_self()); 
				rcv_number=1;
				send_number=1;
				delay=0;
				rcv_bit=0;
				sequence=0;
				flag_send_dbg=1;
				DBG_flag=0;
				local_dbg_flag=0;
				control_number=0;
				for(i=0;i<8;i++)
					{
				 priority[i]=op_prg_list_create();
				    }
				
				node_id = op_topo_parent (op_id_self()); 
				op_ima_obj_attr_get(node_id,"Node Address",&own_source);
				ici_ptr=op_ici_create("nexthop_mac_addr");
				/***********定义统计量********************/
				pk_rcv_number=op_stat_reg("pk rcv number",OPC_STAT_INDEX_NONE,OPC_STAT_GLOBAL );
				pk_success_rate=op_stat_reg("pk success rate",OPC_STAT_INDEX_NONE,OPC_STAT_GLOBAL );
				pk_send_number=op_stat_reg("pk send number",OPC_STAT_INDEX_NONE,OPC_STAT_GLOBAL );
				ete_delay=op_stat_reg("ETE delay",OPC_STAT_INDEX_NONE,OPC_STAT_GLOBAL );
				data_throughput=op_stat_reg("data throughput",OPC_STAT_INDEX_NONE,OPC_STAT_GLOBAL );
				control_message_overhead=op_stat_reg("control message overhead",OPC_STAT_INDEX_NONE,OPC_STAT_GLOBAL );
				two_hop_number=0;  //两跳节点数量
				tc_number=0;    //tc消息的MSSN序列号
				two_hop_number=0;  //两跳节点数量
				/*****初始化本地OLSR表*******/
				local_message_head=NULL;  //本地信息表
				one_hop_asys_head=NULL;   //一跳非对称节点表
				one_hop_sys_head=NULL;    //一跳对称节点表
				one_hop_mpr_head=NULL;     //一跳MPR节点表
				two_hop_head=NULL;        //两跳节点表
				two_all_hop_head=NULL;   //所有两跳节点表
				temp_two_all_hop_head=NULL; 
				mpr_selector=NULL;      //mpr selector链表，也就是tc消息填充内容
				tc_repeat_head=NULL;    //tc消息重复表
				topu_head=NULL;  //拓扑表
				save_packet_head=NULL;
				temp_number=0;
				for(n=0;n<JIEDIAN_NUMBER;n++)
				   {
				       hello_path[n]=1000;
					   hello_path_time[n]=0.0;
				   }
				}
				FSM_PROFILE_SECTION_OUT (state0_enter_exec)

			/** state (init) exit executives **/
			FSM_STATE_EXIT_FORCED (0, "init", "olsr_gaijing_4 [init exit execs]")


			/** state (init) transition processing **/
			FSM_TRANSIT_FORCE (1, state1_enter_exec, ;, "default", "", "init", "st_1", "tr_0", "olsr_gaijing_4 [init -> st_1 : default / ]")
				/*---------------------------------------------------------*/



			/** state (st_1) enter executives **/
			FSM_STATE_ENTER_UNFORCED (1, "st_1", state1_enter_exec, "olsr_gaijing_4 [st_1 enter execs]")
				FSM_PROFILE_SECTION_IN ("olsr_gaijing_4 [st_1 enter execs]", state1_enter_exec)
				{
				
				}
				FSM_PROFILE_SECTION_OUT (state1_enter_exec)

			/** blocking after enter executives of unforced state. **/
			FSM_EXIT (3,"olsr_gaijing_4")


			/** state (st_1) exit executives **/
			FSM_STATE_EXIT_UNFORCED (1, "st_1", "olsr_gaijing_4 [st_1 exit execs]")


			/** state (st_1) transition processing **/
			FSM_PROFILE_SECTION_IN ("olsr_gaijing_4 [st_1 trans conditions]", state1_trans_conds)
			FSM_INIT_COND (self_hello)
			FSM_TEST_COND (self_tc)
			FSM_TEST_COND (INTRPT_STRM_RECEIVOR)
			FSM_TEST_COND (self_topu)
			FSM_TEST_COND (INTRPT_STRM_DATA)
			FSM_TEST_COND (save_pk_send)
			FSM_TEST_COND (SEND_FRAME)
			FSM_DFLT_COND
			FSM_TEST_LOGIC ("st_1")
			FSM_PROFILE_SECTION_OUT (state1_trans_conds)

			FSM_TRANSIT_SWITCH
				{
				FSM_CASE_TRANSIT (0, 2, state2_enter_exec, ;, "self_hello", "", "st_1", "hello_message_send", "tr_11", "olsr_gaijing_4 [st_1 -> hello_message_send : self_hello / ]")
				FSM_CASE_TRANSIT (1, 3, state3_enter_exec, ;, "self_tc", "", "st_1", "tc_message", "tr_15", "olsr_gaijing_4 [st_1 -> tc_message : self_tc / ]")
				FSM_CASE_TRANSIT (2, 4, state4_enter_exec, ;, "INTRPT_STRM_RECEIVOR", "", "st_1", "message_rcv", "rcv", "olsr_gaijing_4 [st_1 -> message_rcv : INTRPT_STRM_RECEIVOR / ]")
				FSM_CASE_TRANSIT (3, 5, state5_enter_exec, ;, "self_topu", "", "st_1", "topu_computer", "tr_20", "olsr_gaijing_4 [st_1 -> topu_computer : self_topu / ]")
				FSM_CASE_TRANSIT (4, 6, state6_enter_exec, ;, "INTRPT_STRM_DATA", "", "st_1", "data_send", "tr_22", "olsr_gaijing_4 [st_1 -> data_send : INTRPT_STRM_DATA / ]")
				FSM_CASE_TRANSIT (5, 7, state7_enter_exec, ;, "save_pk_send", "", "st_1", "save_send", "tr_24", "olsr_gaijing_4 [st_1 -> save_send : save_pk_send / ]")
				FSM_CASE_TRANSIT (6, 8, state8_enter_exec, ;, "SEND_FRAME", "", "st_1", "send", "tr_26", "olsr_gaijing_4 [st_1 -> send : SEND_FRAME / ]")
				FSM_CASE_TRANSIT (7, 1, state1_enter_exec, ;, "default", "", "st_1", "st_1", "tr_2", "olsr_gaijing_4 [st_1 -> st_1 : default / ]")
				}
				/*---------------------------------------------------------*/



			/** state (hello_message_send) enter executives **/
			FSM_STATE_ENTER_FORCED (2, "hello_message_send", state2_enter_exec, "olsr_gaijing_4 [hello_message_send enter execs]")
				FSM_PROFILE_SECTION_IN ("olsr_gaijing_4 [hello_message_send enter execs]", state2_enter_exec)
				{
				hello_send(HELLO,0);
				}
				FSM_PROFILE_SECTION_OUT (state2_enter_exec)

			/** state (hello_message_send) exit executives **/
			FSM_STATE_EXIT_FORCED (2, "hello_message_send", "olsr_gaijing_4 [hello_message_send exit execs]")
				FSM_PROFILE_SECTION_IN ("olsr_gaijing_4 [hello_message_send exit execs]", state2_exit_exec)
				{
				hello_send_flag=1;
				hello_ev=op_intrpt_schedule_self(op_sim_time()+op_dist_uniform(SUIJI)+HELLO_SEND_TIME,0);
				
				for(n=0;n<JIEDIAN_NUMBER;n++)
				   {
				       if(hello_path_time[n]<op_sim_time())
						   {
						      hello_path[n]=1000;
					          hello_path_time[n]=0.0;
						   }
				   }
				}
				FSM_PROFILE_SECTION_OUT (state2_exit_exec)


			/** state (hello_message_send) transition processing **/
			FSM_TRANSIT_FORCE (1, state1_enter_exec, ;, "default", "", "hello_message_send", "st_1", "tr_14", "olsr_gaijing_4 [hello_message_send -> st_1 : default / ]")
				/*---------------------------------------------------------*/



			/** state (tc_message) enter executives **/
			FSM_STATE_ENTER_FORCED (3, "tc_message", state3_enter_exec, "olsr_gaijing_4 [tc_message enter execs]")
				FSM_PROFILE_SECTION_IN ("olsr_gaijing_4 [tc_message enter execs]", state3_enter_exec)
				{
				tc_send();
				}
				FSM_PROFILE_SECTION_OUT (state3_enter_exec)

			/** state (tc_message) exit executives **/
			FSM_STATE_EXIT_FORCED (3, "tc_message", "olsr_gaijing_4 [tc_message exit execs]")
				FSM_PROFILE_SECTION_IN ("olsr_gaijing_4 [tc_message exit execs]", state3_exit_exec)
				{
				op_intrpt_schedule_self(op_sim_time()+op_dist_uniform(SUIJI)+TC_SEND_TIME ,1);
				}
				FSM_PROFILE_SECTION_OUT (state3_exit_exec)


			/** state (tc_message) transition processing **/
			FSM_TRANSIT_FORCE (1, state1_enter_exec, ;, "default", "", "tc_message", "st_1", "tr_17", "olsr_gaijing_4 [tc_message -> st_1 : default / ]")
				/*---------------------------------------------------------*/



			/** state (message_rcv) enter executives **/
			FSM_STATE_ENTER_FORCED (4, "message_rcv", state4_enter_exec, "olsr_gaijing_4 [message_rcv enter execs]")
				FSM_PROFILE_SECTION_IN ("olsr_gaijing_4 [message_rcv enter execs]", state4_enter_exec)
				{
				recv();
				}
				FSM_PROFILE_SECTION_OUT (state4_enter_exec)

			/** state (message_rcv) exit executives **/
			FSM_STATE_EXIT_FORCED (4, "message_rcv", "olsr_gaijing_4 [message_rcv exit execs]")


			/** state (message_rcv) transition processing **/
			FSM_TRANSIT_FORCE (1, state1_enter_exec, ;, "default", "", "message_rcv", "st_1", "tr_19", "olsr_gaijing_4 [message_rcv -> st_1 : default / ]")
				/*---------------------------------------------------------*/



			/** state (topu_computer) enter executives **/
			FSM_STATE_ENTER_FORCED (5, "topu_computer", state5_enter_exec, "olsr_gaijing_4 [topu_computer enter execs]")
				FSM_PROFILE_SECTION_IN ("olsr_gaijing_4 [topu_computer enter execs]", state5_enter_exec)
				{
				compute_topu();
				}
				FSM_PROFILE_SECTION_OUT (state5_enter_exec)

			/** state (topu_computer) exit executives **/
			FSM_STATE_EXIT_FORCED (5, "topu_computer", "olsr_gaijing_4 [topu_computer exit execs]")
				FSM_PROFILE_SECTION_IN ("olsr_gaijing_4 [topu_computer exit execs]", state5_exit_exec)
				{
				 op_intrpt_schedule_self(op_sim_time()+2 ,2);
				}
				FSM_PROFILE_SECTION_OUT (state5_exit_exec)


			/** state (topu_computer) transition processing **/
			FSM_TRANSIT_FORCE (1, state1_enter_exec, ;, "default", "", "topu_computer", "st_1", "tr_21", "olsr_gaijing_4 [topu_computer -> st_1 : default / ]")
				/*---------------------------------------------------------*/



			/** state (data_send) enter executives **/
			FSM_STATE_ENTER_FORCED (6, "data_send", state6_enter_exec, "olsr_gaijing_4 [data_send enter execs]")
				FSM_PROFILE_SECTION_IN ("olsr_gaijing_4 [data_send enter execs]", state6_enter_exec)
				{
				 p1=op_pk_get(TRANSPORT_TO_OLSR);
				 dest = 100;
				   op_pk_nfd_get(p1,"Destination Address", &dest);
				 	op_pk_nfd_access(p1,"priority",&priority1);
				   pkptr=op_pk_create_fmt("date_message");
				   op_pk_nfd_set(pkptr,"pro_addr",own_source);
				   op_pk_nfd_set(pkptr,"app_data",p1);
				   op_pk_nfd_set(pkptr,"type",2);
				   op_pk_nfd_set(pkptr,"source",own_source);
				   op_pk_nfd_set(pkptr,"destination",dest);
				   op_pk_nfd_set(pkptr,"sequence",sequence);
					op_pk_nfd_set(pkptr,"priority",priority1);
				   next_addr=path[dest][1];
				   if(next_addr>100&&hello_path_time[dest]<op_sim_time())
					   {
					      next_addr=hello_path[dest];
					   }
				   op_pk_nfd_set(pkptr,"next_addr",next_addr);
				   if(flag_send_dbg==1)
				   printf("这是源节点：%d,目的节点: %d,next addr:%d,时间是：%f，包号:%d\n",own_source,dest,next_addr,op_sim_time(),sequence);
				   send_number=send_number+1;
				   op_stat_write(pk_send_number,send_number);
				   if(next_addr<100)
					  {
				
						  switch(priority1)
					   {
				 
					   case 0:
					   op_prg_list_insert(priority[0],pkptr,OPC_LISTPOS_TAIL);
					   op_intrpt_schedule_self(op_sim_time(),send_frame);
					   break;
					   case 1:
					   op_prg_list_insert(priority[1],pkptr,OPC_LISTPOS_TAIL);
					   op_intrpt_schedule_self(op_sim_time(),send_frame);
					   break;
				 	   case 2:
					   op_prg_list_insert(priority[2],pkptr,OPC_LISTPOS_TAIL);
					   op_intrpt_schedule_self(op_sim_time(),send_frame);
					   break;
					   case 3:
					   op_prg_list_insert(priority[3],pkptr,OPC_LISTPOS_TAIL);
					   op_intrpt_schedule_self(op_sim_time(),send_frame);
					   break;
					   case 4:
					   op_prg_list_insert(priority[4],pkptr,OPC_LISTPOS_TAIL);
					   op_intrpt_schedule_self(op_sim_time(),send_frame);
					   break;
					   case 5:
					   op_prg_list_insert(priority[5],pkptr,OPC_LISTPOS_TAIL);
					   op_intrpt_schedule_self(op_sim_time(),send_frame);
					   break;
					   case 6:
					   op_prg_list_insert(priority[6],pkptr,OPC_LISTPOS_TAIL);
					   op_intrpt_schedule_self(op_sim_time(),send_frame);
					   break;
					   case 7:
					   op_prg_list_insert(priority[7],pkptr,OPC_LISTPOS_TAIL);
					   op_intrpt_schedule_self(op_sim_time(),send_frame);
					   break;
				
					   default:
					   break;	   
					   }
					  }
				   else{
				          if(hello_send_flag==1)
						     {
								 hello_send(3,dest);  //寻路HELLO消息，类型3
								 time0=op_ev_time(hello_ev);
						         op_ev_cancel(hello_ev);
						         hello_ev=op_intrpt_schedule_self(time0+HELLO_SEND_TIME,0);
								 hello_send_flag=0;
							 }
				
				       }
				   sequence++;
				 /*
				   op_pk_nfd_get(p1,"Type",&type);
				if(type==55)
					   {
					   op_pk_nfd_access(p1,"priority",&priority1);
					   }
				   else	
					   priority1=0;
				   
				   switch(priority1)
					   {
				 
					   case 0:
					   op_prg_list_insert(priority[0],p1,OPC_LISTPOS_TAIL);
					   op_intrpt_schedule_self(op_sim_time(),send_frame);
					   break;
					   case 1:
					   op_prg_list_insert(priority[1],p1,OPC_LISTPOS_TAIL);
					   op_intrpt_schedule_self(op_sim_time(),send_frame);
					   break;
				 	   case 2:
					   op_prg_list_insert(priority[2],p1,OPC_LISTPOS_TAIL);
					   op_intrpt_schedule_self(op_sim_time(),send_frame);
					   break;
					   case 3:
					   op_prg_list_insert(priority[3],p1,OPC_LISTPOS_TAIL);
					   op_intrpt_schedule_self(op_sim_time(),send_frame);
					   break;
					   case 4:
					   op_prg_list_insert(priority[4],p1,OPC_LISTPOS_TAIL);
					   op_intrpt_schedule_self(op_sim_time(),send_frame);
					   break;
					   case 5:
					   op_prg_list_insert(priority[5],p1,OPC_LISTPOS_TAIL);
					   op_intrpt_schedule_self(op_sim_time(),send_frame);
					   break;
					   case 6:
					   op_prg_list_insert(priority[6],p1,OPC_LISTPOS_TAIL);
					   op_intrpt_schedule_self(op_sim_time(),send_frame);
					   break;
					   case 7:
					   op_prg_list_insert(priority[7],p1,OPC_LISTPOS_TAIL);
					   op_intrpt_schedule_self(op_sim_time(),send_frame);
					   break;
				
					   default:
					   break;	   
					   }
				
				   dest = 100;
				   op_pk_nfd_get(p1,"Destination Address", &dest);
				   pkptr=op_pk_create_fmt("date_message");
				   op_pk_nfd_set(pkptr,"pro_addr",own_source);
				   op_pk_nfd_set(pkptr,"app_data",p1);
				   op_pk_nfd_set(pkptr,"type",2);
				   op_pk_nfd_set(pkptr,"source",own_source);
				   op_pk_nfd_set(pkptr,"destination",dest);
				   op_pk_nfd_set(pkptr,"sequence",sequence);
				   next_addr=path[dest][1];
				   if(next_addr>100&&hello_path_time[dest]<op_sim_time())
					   {
					      next_addr=hello_path[dest];
					   }
				   op_pk_nfd_set(pkptr,"next_addr",next_addr);
				   if(flag_send_dbg==1)
				   printf("这是源节点：%d,目的节点: %d,next addr:%d,时间是：%f，包号:%d\n",own_source,dest,next_addr,op_sim_time(),sequence);
				   send_number=send_number+1;
				   op_stat_write(pk_send_number,send_number);
				   if(next_addr<100)
					  {
				
						  op_pk_send(pkptr, OLSR_to_INTERFACE );
					  }
				   else{
				          if(hello_send_flag==1)
						     {
								 hello_send(3,dest);  //寻路HELLO消息，类型3
								 time0=op_ev_time(hello_ev);
						         op_ev_cancel(hello_ev);
						         hello_ev=op_intrpt_schedule_self(time0+HELLO_SEND_TIME,0);
								 hello_send_flag=0;
							 }
				
				       }
				   sequence++;
				*/
				}
				FSM_PROFILE_SECTION_OUT (state6_enter_exec)

			/** state (data_send) exit executives **/
			FSM_STATE_EXIT_FORCED (6, "data_send", "olsr_gaijing_4 [data_send exit execs]")


			/** state (data_send) transition processing **/
			FSM_TRANSIT_FORCE (1, state1_enter_exec, ;, "default", "", "data_send", "st_1", "tr_23", "olsr_gaijing_4 [data_send -> st_1 : default / ]")
				/*---------------------------------------------------------*/



			/** state (save_send) enter executives **/
			FSM_STATE_ENTER_FORCED (7, "save_send", state7_enter_exec, "olsr_gaijing_4 [save_send enter execs]")
				FSM_PROFILE_SECTION_IN ("olsr_gaijing_4 [save_send enter execs]", state7_enter_exec)
				{
				save_packet_send();
				save_send_flag=1;
				}
				FSM_PROFILE_SECTION_OUT (state7_enter_exec)

			/** state (save_send) exit executives **/
			FSM_STATE_EXIT_FORCED (7, "save_send", "olsr_gaijing_4 [save_send exit execs]")


			/** state (save_send) transition processing **/
			FSM_TRANSIT_FORCE (1, state1_enter_exec, ;, "default", "", "save_send", "st_1", "tr_25", "olsr_gaijing_4 [save_send -> st_1 : default / ]")
				/*---------------------------------------------------------*/



			/** state (send) enter executives **/
			FSM_STATE_ENTER_FORCED (8, "send", state8_enter_exec, "olsr_gaijing_4 [send enter execs]")
				FSM_PROFILE_SECTION_IN ("olsr_gaijing_4 [send enter execs]", state8_enter_exec)
				{
				//priority_send();
				for(i=0;i<8;i++)
					{
					while(op_prg_list_size(priority[i]))
						{
						pkptr=op_prg_list_remove(priority[i],OPC_LISTPOS_HEAD);
						op_pk_send(pkptr,OLSR_to_INTERFACE);
						}
					}
				
				/*
				if(op_prg_list_size(priority[0]))
					{
					pkptr=op_prg_list_remove(priority[0],OPC_LISTPOS_HEAD);
					op_pk_send(pkptr,OLSR_to_TRANSPORT);
					}
				else if(op_prg_list_size(priority[1]))
					{
					pkptr=op_prg_list_remove(priority[1],OPC_LISTPOS_HEAD);
					op_pk_send(pkptr,OLSR_to_TRANSPORT);
					}
				else if(op_prg_list_size(priority[2]))
					{
					pkptr=op_prg_list_remove(priority[2],OPC_LISTPOS_HEAD);
					op_pk_send(pkptr,OLSR_to_TRANSPORT);
					}
				else if(op_prg_list_size(priority[3]))
					{
					pkptr=op_prg_list_remove(priority[3],OPC_LISTPOS_HEAD);
					op_pk_send(pkptr,OLSR_to_TRANSPORT);
					}
				else if(op_prg_list_size(priority[4]))
					{
					pkptr=op_prg_list_remove(priority[4],OPC_LISTPOS_HEAD);
					op_pk_send(pkptr,OLSR_to_TRANSPORT);
					}
				else if(op_prg_list_size(priority[5]))
					{
					pkptr=op_prg_list_remove(priority[5],OPC_LISTPOS_HEAD);
					op_pk_send(pkptr,OLSR_to_TRANSPORT);
					}
				else if(op_prg_list_size(priority[6]))
					{
					pkptr=op_prg_list_remove(priority[6],OPC_LISTPOS_HEAD);
					op_pk_send(pkptr,OLSR_to_TRANSPORT);
					}
				else if(op_prg_list_size(priority[7]))
					{
					pkptr=op_prg_list_remove(priority[7],OPC_LISTPOS_HEAD);
					op_pk_send(pkptr,OLSR_to_TRANSPORT);
					}
				else;
				*/
				}
				FSM_PROFILE_SECTION_OUT (state8_enter_exec)

			/** state (send) exit executives **/
			FSM_STATE_EXIT_FORCED (8, "send", "olsr_gaijing_4 [send exit execs]")


			/** state (send) transition processing **/
			FSM_TRANSIT_FORCE (1, state1_enter_exec, ;, "default", "", "send", "st_1", "tr_27", "olsr_gaijing_4 [send -> st_1 : default / ]")
				/*---------------------------------------------------------*/



			}


		FSM_EXIT (0,"olsr_gaijing_4")
		}
	}




void
_op_olsr_gaijing_4_diag (OP_SIM_CONTEXT_ARG_OPT)
	{
#if defined (OPD_ALLOW_ODB)
#if !defined (VOSD_NO_FIN)
	int _op_block_origin = __LINE__+1;
#endif

	FIN_MT (_op_olsr_gaijing_4_diag ())

	if (1)
		{

		/* Diagnostic Block */

		BINIT
		{
		
			show();
		
		
		 
		}

		/* End of Diagnostic Block */

		}

	FOUT
#endif /* OPD_ALLOW_ODB */
	}




void
_op_olsr_gaijing_4_terminate (OP_SIM_CONTEXT_ARG_OPT)
	{
#if !defined (VOSD_NO_FIN)
	int _op_block_origin = __LINE__;
#endif

	FIN_MT (_op_olsr_gaijing_4_terminate ())

	if (1)
		{

		/* Termination Block */

		BINIT
		{
		//op_stat_write(pk_count,count);
		
		}

		/* End of Termination Block */

		}
	Vos_Poolmem_Dealloc (op_sv_ptr);

	FOUT
	}


/* Undefine shortcuts to state variables to avoid */
/* syntax error in direct access to fields of */
/* local variable prs_ptr in _op_olsr_gaijing_4_svar function. */
#undef pk_send_number
#undef two_hop_number
#undef own_source
#undef node_id
#undef t_dst
#undef local_message_head
#undef one_hop_asys_head
#undef two_hop_head
#undef two_all_hop_head
#undef temp_two_all_hop_head
#undef one_hop_sys_head
#undef one_hop_mpr_head
#undef mpr_selector
#undef tc_repeat_head
#undef topu_head
#undef tc_number
#undef temp_number
#undef topu
#undef path
#undef distance
#undef s
#undef v
#undef pk_rcv_number
#undef pk_success_rate
#undef ete_delay
#undef ici_ptr
#undef DBG_flag
#undef local_dbg_flag
#undef save_packet_head
#undef hello_path
#undef hello_path_time
#undef flag_send_dbg
#undef hello_ev
#undef hello_send_flag
#undef save_ev
#undef save_send_flag
#undef sequence
#undef data_throughput
#undef control_message_overhead
#undef priority

#undef FIN_PREAMBLE_DEC
#undef FIN_PREAMBLE_CODE

#define FIN_PREAMBLE_DEC
#define FIN_PREAMBLE_CODE

VosT_Obtype
_op_olsr_gaijing_4_init (int * init_block_ptr)
	{
	VosT_Obtype obtype = OPC_NIL;
	FIN_MT (_op_olsr_gaijing_4_init (init_block_ptr))

	obtype = Vos_Define_Object_Prstate ("proc state vars (olsr_gaijing_4)",
		sizeof (olsr_gaijing_4_state));
	*init_block_ptr = 0;

	FRET (obtype)
	}

VosT_Address
_op_olsr_gaijing_4_alloc (VosT_Obtype obtype, int init_block)
	{
#if !defined (VOSD_NO_FIN)
	int _op_block_origin = 0;
#endif
	olsr_gaijing_4_state * ptr;
	FIN_MT (_op_olsr_gaijing_4_alloc (obtype))

	ptr = (olsr_gaijing_4_state *)Vos_Alloc_Object (obtype);
	if (ptr != OPC_NIL)
		{
		ptr->_op_current_block = init_block;
#if defined (OPD_ALLOW_ODB)
		ptr->_op_current_state = "olsr_gaijing_4 [init enter execs]";
#endif
		}
	FRET ((VosT_Address)ptr)
	}



void
_op_olsr_gaijing_4_svar (void * gen_ptr, const char * var_name, void ** var_p_ptr)
	{
	olsr_gaijing_4_state		*prs_ptr;

	FIN_MT (_op_olsr_gaijing_4_svar (gen_ptr, var_name, var_p_ptr))

	if (var_name == OPC_NIL)
		{
		*var_p_ptr = (void *)OPC_NIL;
		FOUT
		}
	prs_ptr = (olsr_gaijing_4_state *)gen_ptr;

	if (strcmp ("pk_send_number" , var_name) == 0)
		{
		*var_p_ptr = (void *) (&prs_ptr->pk_send_number);
		FOUT
		}
	if (strcmp ("two_hop_number" , var_name) == 0)
		{
		*var_p_ptr = (void *) (&prs_ptr->two_hop_number);
		FOUT
		}
	if (strcmp ("own_source" , var_name) == 0)
		{
		*var_p_ptr = (void *) (&prs_ptr->own_source);
		FOUT
		}
	if (strcmp ("node_id" , var_name) == 0)
		{
		*var_p_ptr = (void *) (&prs_ptr->node_id);
		FOUT
		}
	if (strcmp ("t_dst" , var_name) == 0)
		{
		*var_p_ptr = (void *) (&prs_ptr->t_dst);
		FOUT
		}
	if (strcmp ("local_message_head" , var_name) == 0)
		{
		*var_p_ptr = (void *) (&prs_ptr->local_message_head);
		FOUT
		}
	if (strcmp ("one_hop_asys_head" , var_name) == 0)
		{
		*var_p_ptr = (void *) (&prs_ptr->one_hop_asys_head);
		FOUT
		}
	if (strcmp ("two_hop_head" , var_name) == 0)
		{
		*var_p_ptr = (void *) (&prs_ptr->two_hop_head);
		FOUT
		}
	if (strcmp ("two_all_hop_head" , var_name) == 0)
		{
		*var_p_ptr = (void *) (&prs_ptr->two_all_hop_head);
		FOUT
		}
	if (strcmp ("temp_two_all_hop_head" , var_name) == 0)
		{
		*var_p_ptr = (void *) (&prs_ptr->temp_two_all_hop_head);
		FOUT
		}
	if (strcmp ("one_hop_sys_head" , var_name) == 0)
		{
		*var_p_ptr = (void *) (&prs_ptr->one_hop_sys_head);
		FOUT
		}
	if (strcmp ("one_hop_mpr_head" , var_name) == 0)
		{
		*var_p_ptr = (void *) (&prs_ptr->one_hop_mpr_head);
		FOUT
		}
	if (strcmp ("mpr_selector" , var_name) == 0)
		{
		*var_p_ptr = (void *) (&prs_ptr->mpr_selector);
		FOUT
		}
	if (strcmp ("tc_repeat_head" , var_name) == 0)
		{
		*var_p_ptr = (void *) (&prs_ptr->tc_repeat_head);
		FOUT
		}
	if (strcmp ("topu_head" , var_name) == 0)
		{
		*var_p_ptr = (void *) (&prs_ptr->topu_head);
		FOUT
		}
	if (strcmp ("tc_number" , var_name) == 0)
		{
		*var_p_ptr = (void *) (&prs_ptr->tc_number);
		FOUT
		}
	if (strcmp ("temp_number" , var_name) == 0)
		{
		*var_p_ptr = (void *) (&prs_ptr->temp_number);
		FOUT
		}
	if (strcmp ("topu" , var_name) == 0)
		{
		*var_p_ptr = (void *) (prs_ptr->topu);
		FOUT
		}
	if (strcmp ("path" , var_name) == 0)
		{
		*var_p_ptr = (void *) (prs_ptr->path);
		FOUT
		}
	if (strcmp ("distance" , var_name) == 0)
		{
		*var_p_ptr = (void *) (prs_ptr->distance);
		FOUT
		}
	if (strcmp ("s" , var_name) == 0)
		{
		*var_p_ptr = (void *) (prs_ptr->s);
		FOUT
		}
	if (strcmp ("v" , var_name) == 0)
		{
		*var_p_ptr = (void *) (prs_ptr->v);
		FOUT
		}
	if (strcmp ("pk_rcv_number" , var_name) == 0)
		{
		*var_p_ptr = (void *) (&prs_ptr->pk_rcv_number);
		FOUT
		}
	if (strcmp ("pk_success_rate" , var_name) == 0)
		{
		*var_p_ptr = (void *) (&prs_ptr->pk_success_rate);
		FOUT
		}
	if (strcmp ("ete_delay" , var_name) == 0)
		{
		*var_p_ptr = (void *) (&prs_ptr->ete_delay);
		FOUT
		}
	if (strcmp ("ici_ptr" , var_name) == 0)
		{
		*var_p_ptr = (void *) (&prs_ptr->ici_ptr);
		FOUT
		}
	if (strcmp ("DBG_flag" , var_name) == 0)
		{
		*var_p_ptr = (void *) (&prs_ptr->DBG_flag);
		FOUT
		}
	if (strcmp ("local_dbg_flag" , var_name) == 0)
		{
		*var_p_ptr = (void *) (&prs_ptr->local_dbg_flag);
		FOUT
		}
	if (strcmp ("save_packet_head" , var_name) == 0)
		{
		*var_p_ptr = (void *) (&prs_ptr->save_packet_head);
		FOUT
		}
	if (strcmp ("hello_path" , var_name) == 0)
		{
		*var_p_ptr = (void *) (prs_ptr->hello_path);
		FOUT
		}
	if (strcmp ("hello_path_time" , var_name) == 0)
		{
		*var_p_ptr = (void *) (prs_ptr->hello_path_time);
		FOUT
		}
	if (strcmp ("flag_send_dbg" , var_name) == 0)
		{
		*var_p_ptr = (void *) (&prs_ptr->flag_send_dbg);
		FOUT
		}
	if (strcmp ("hello_ev" , var_name) == 0)
		{
		*var_p_ptr = (void *) (&prs_ptr->hello_ev);
		FOUT
		}
	if (strcmp ("hello_send_flag" , var_name) == 0)
		{
		*var_p_ptr = (void *) (&prs_ptr->hello_send_flag);
		FOUT
		}
	if (strcmp ("save_ev" , var_name) == 0)
		{
		*var_p_ptr = (void *) (&prs_ptr->save_ev);
		FOUT
		}
	if (strcmp ("save_send_flag" , var_name) == 0)
		{
		*var_p_ptr = (void *) (&prs_ptr->save_send_flag);
		FOUT
		}
	if (strcmp ("sequence" , var_name) == 0)
		{
		*var_p_ptr = (void *) (&prs_ptr->sequence);
		FOUT
		}
	if (strcmp ("data_throughput" , var_name) == 0)
		{
		*var_p_ptr = (void *) (&prs_ptr->data_throughput);
		FOUT
		}
	if (strcmp ("control_message_overhead" , var_name) == 0)
		{
		*var_p_ptr = (void *) (&prs_ptr->control_message_overhead);
		FOUT
		}
	if (strcmp ("priority" , var_name) == 0)
		{
		*var_p_ptr = (void *) (prs_ptr->priority);
		FOUT
		}
	*var_p_ptr = (void *)OPC_NIL;

	FOUT
	}

