MIL_3_Tfile_Hdr_ 145A 140A modeler 6 5D6892E9 5DB90039 3A USER-20151017SA Administrator 0 0 none none 0 0 none 6D50C23E 2429 0 0 0 0 0 0 1d79 5                                                                                                                                                                                                                                                                                                                                                                                 ��g�      8   R   �  0  �  �  
=  :  �  �  !B  !F      node   
blue_tooth   	stn_wless   	stn_wless��������   Wireless LAN station    6   General Node Functions:    -----------------------        The wireless station node model    /represents an IEEE802.11 wireless LAN station.    %The node model consists of following    
processes:       *1. The MAC layer which has a wireless lan    !mac process model with following    attributes:       MAC address -- station address       *Fragmentation Threshold --- based on this    (threshold station decides wether or not    "to send data packets in fragments.       *Rts threshold --- based on this threshold    (station decides wether Rts/Cts exchange    *is needed for every data transmission.           "The wireless LAN MAC layer has an    "interface with higher layer which    &receives packet from higher layer and    "generates random address for them.           2. Wireless LAN interface       #This process model is an interface    )between MAC layer and higher layer.  The    &function of this process is to accept    'packets from higher layer and generate    &random destination address for them.     )This information is then sent to the MAC    layer.            3. Wireless LAN receiver       *This is a wireless receiver which accepts    (any incomming packets from the physical    &layer and pass it to the wireless MAC    process.           4. Wireless LAN transmitter       %This is a wireless transmitter which    #receives packet from MAC layer and    $transmits it to the physical medium.                node_address    �������    ����           ����          ����          ����           �Z             destination_address    �������    ����          d����          ����          ����           �Z             MAC_address   �������   ����               ����              ����              ����           �Z             Node Address    �������    ����           ����          ����          ����           �Z                   altitude      altitude����   ����               ����              ����              ����                        phase      phase����   ����               ����              ����              ����                        
TIM source            none      altitude         
        ����   
   altitude modeling            relative to subnet-platform      	condition         
   ����   
   financial cost            0.00      phase                 ����      priority              ����      user id              ����            fj  �   �          
   source   
       
   source_olsr   
          	processor                   Destination    ���   	   ����   	      fl  8   �          
   sink   
       
   	sink_olsr   
          	processor                   fn  
  $          
   olsr   
       
   olsr_gaijing_3   
          	processor                  f�    �          
   csma_mac   
       
   bluetooth_mac   
          queue                   begsim intrpt   ���   
   ����   
      doc file   ���   	   	nd_module   	      endsim intrpt   ���   
    ����   
      failure intrpts   ���   
   disabled   
      intrpt interval   ���   
ԲI�%��}����   
      priority    ���   
   ����   
      recovery intrpts   ���   
   disabled   
      subqueue   ���   
            count    ���   
   ����   
      list   	���   
                bit capacity   ���   
T�I�%��}����   
      pk capacity   ���   
T�I�%��}����   
         bit capacity   ���   
T�I�%��}����   
      pk capacity   ���   
T�I�%��}����   
         bit capacity   ���   
T�I�%��}����   
      pk capacity   ���   
T�I�%��}����   
         bit capacity   ���   
T�I�%��}����   
      pk capacity   ���   
T�I�%��}����   
         bit capacity   ���   
T�I�%��}����   
      pk capacity   ���   
T�I�%��}����   
         bit capacity   ���   
T�I�%��}����   
      pk capacity   ���   
T�I�%��}����   
         bit capacity   ���   
T�I�%��}����   
      pk capacity   ���   
T�I�%��}����   
   
   
      super priority   ���   
    ����   
     f�  �  
          
   tx   
       
            count    ���   
   ����   
      list   	���   
            	data rate   ���   
Ad�    ����   
      	bandwidth   ���   
Ac�    ����   
      min frequency   ���   
@��     ����   
      power   ���   
?�      ����   
   
   
          bpsk             dra_rxgroup             	dra_txdel             dra_closure             dra_chanmatch             
dra_tagain             dra_propdel             ra_tx                       nd_radio_transmitter      	  f�  8  
          
   rx   
       
            count    ���   
   ����   
      list   	���   
            	data rate   ���   
Ad�    ����   
      	bandwidth   ���   
Ac�    ����   
      min frequency   ���   
@��     ����   
   
   
          bpsk          ?�      ����                  ����             
dra_ragain             	dra_power             dra_bkgnoise             
dra_inoise             dra_snr             dra_ber             	dra_error             dra_ecc             ra_rx                       nd_radio_receiver               fn  f�       '    �   
       
   strm_14   
       
   src stream [1]   
       
   dest stream [1]   
          ����                  ����             ����                                           nd_packet_stream            f�  fn       {    (   
       
   strm_15   
       
   src stream [1]   
       
   dest stream [1]   
          ����                  ����          
@�  ����   
                                        nd_packet_stream          5  fj  fn     �   �  
   �  
  %   
       
   strm_16   
       
   src stream [0]   
       
   dest stream [0]   
          ����                  ����             ����                                           nd_packet_stream          6  fn  fl            �  7   �   
       
   strm_17   
       
   src stream [0]   
       
   dest stream [0]   
          ����                  ����          
@�����   
                                        nd_packet_stream          S  f�  f�     
    �     
       
   strm_18   
       
   src stream [0]   
       
   dest stream [0]   
          ����                  ����             ����                                           nd_packet_stream          T  f�  f�     9    
  �   
       
   strm_19   
       
   src stream [0]   
       
   dest stream [0]   
          ����                  ����          
@�  ����   
                                        nd_packet_stream         Z  f�  f�     >  �  ?                
   stat_0   
       
   channel [0]   
       
   busy   
       
   
instat [0]   
          ����                  ����             ����             ����              ����              ����          ԲI�%��}����          ԲI�%��}����          
@�  ����   
                                        nd_statistic_wire     f�   [      sink.End-to-End Delay (seconds)   End-to-End Delay (seconds)           Traffic Sink    bucket/default total/sample mean   linear   Traffic Sink    sink.Traffic Received (bits/sec)   Traffic Received (bits/sec)           Traffic Sink   bucket/default total/sum_time   linear   Traffic Sink   l2cap.free size (bits)   free size (bits)           queue   !bucket/default total/time average   linear   queue   'l2cap.subqueue [0].queue size (packets)   queue size (packets)           queue   !bucket/default total/time average   linear   queue   sink.Traffic Received (bits)   Traffic Received (bits)           Traffic Sink   bucket/default total/sum   linear   Traffic Sink   source.Traffic Sent (packets)   Traffic Sent (packets)           Traffic Source   bucket/default total/sum   linear   Traffic Source   l2cap.queue size (packets)   queue size (packets)           queue   !bucket/default total/time average   linear   queue   sink.Traffic Received (packets)   Traffic Received (packets)           Traffic Sink   bucket/default total/sum   linear   Traffic Sink          machine type       station   Model Attributes      14.5.A-January18-2008                interface type       
IEEE802.11   interface class       access           wlan_port_tx<n>   wlan_port_rx<n>           