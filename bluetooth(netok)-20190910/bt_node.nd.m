MIL_3_Tfile_Hdr_ 145A 140A modeler 6 5D73270E 5D73270E 1 USER-20151017SA Administrator 0 0 none none 0 0 none 15B4E472 22DC 0 0 0 0 0 0 1bcc 1                                                                                                                                                                                                                                                                                                                                                                                  ��g�      8   R   �  0  �  �  	�  �  �  �  �  �      node   
blue_tooth   	stn_wless   	stn_wless��������   Wireless LAN station    6   General Node Functions:    -----------------------        The wireless station node model    /represents an IEEE802.11 wireless LAN station.    %The node model consists of following    
processes:       *1. The MAC layer which has a wireless lan    !mac process model with following    attributes:       MAC address -- station address       *Fragmentation Threshold --- based on this    (threshold station decides wether or not    "to send data packets in fragments.       *Rts threshold --- based on this threshold    (station decides wether Rts/Cts exchange    *is needed for every data transmission.           "The wireless LAN MAC layer has an    "interface with higher layer which    &receives packet from higher layer and    "generates random address for them.           2. Wireless LAN interface       #This process model is an interface    )between MAC layer and higher layer.  The    &function of this process is to accept    'packets from higher layer and generate    &random destination address for them.     )This information is then sent to the MAC    layer.            3. Wireless LAN receiver       *This is a wireless receiver which accepts    (any incomming packets from the physical    &layer and pass it to the wireless MAC    process.           4. Wireless LAN transmitter       %This is a wireless transmitter which    #receives packet from MAC layer and    $transmits it to the physical medium.                node_address    �������    ����           ����          ����          ����           �Z             destination_address    �������    ����          d����          ����          ����           �Z             MAC_address   �������   ����               ����              ����              ����           �Z                   altitude      altitude����   ����               ����              ����              ����                        phase      phase����   ����               ����              ����              ����                     	   
TIM source            none      altitude         
        ����   
   altitude modeling            relative to subnet-platform      	condition         
   ����   
   financial cost            0.00      phase                 ����      priority              ����      role         ����      user id              ����            fj  �   �          
   source   
       J   	bt_source   J          	processor                   fl  �   �          
   sink   
       J   bt_zink   J          	processor                   fn    $          
   up_layer   
       J   blue_tooth_ts   J          	processor                	  f|  �  �          
   bt_rx   
       
            count    ���   
   ����   
      list   	���   
            	data rate   ���   
A.��    ����   
      packet formats   ���   
   unformatted,all formatted   
      	bandwidth   ���   
Aj     ����   
      min frequency   ���   
@�X     ����   
   
   
       
   qam64   
       ?�      ����                  ����          
   NONE   
       
   	dra_power   
          dra_bkgnoise          
   wlan_inoise   
          dra_snr          
   wlan_ber   
       
   
wlan_error   
       
   dra_ecc   
          ra_rx                       nd_radio_receiver        f�  �  �          
   bt_tx   
       
            count    ���   
   ����   
      list   	���   
            	data rate   ���   
A.��    ����   
      packet formats   ���   
   unformatted,all formatted   
      	bandwidth   ���   
Aj     ����   
      min frequency   ���   
@�X     ����   
      spreading code   ���   
ԲI�%��}����   
      power   ���   
?�      ����   
   
   
       
   qam64   
       
   dra_rxgroup   
       
   	dra_txdel   
       
   dra_closure_all   
       
   dra_chanmatch   
       
   
dra_tagain   
       
   dra_propdel   
          ra_tx                       nd_radio_transmitter        f�    �          
   l2cap   
       
   
l2cap_test   
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
   ����   
      list   	���   
                bit capacity   ���   
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
          	  f�  f�     
    �  �   
       
   strm_12   
       
   src stream [0]   
       
   dest stream [0]   
          ����                  ����             ����                                           nd_packet_stream          
  f|  f�     �  �       
       
   strm_13   
       
   src stream [0]   
       
   dest stream [0]   
          ����                  ����          
@�  ����   
                                        nd_packet_stream            fn  f�       '    �   
       
   strm_14   
       
   src stream [1]   
       
   dest stream [1]   
          ����                  ����             ����                                           nd_packet_stream            f�  fn       {    (   
       
   strm_15   
       
   src stream [1]   
       
   dest stream [1]   
          ����                  ����          
@�  ����   
                                        nd_packet_stream          5  fj  fn     }   �     �    %   
       
   strm_16   
       
   src stream [0]   
       
   dest stream [0]   
          ����                  ����             ����                                           nd_packet_stream          6  fn  fl            �  �   �   
       
   strm_17   
       
   src stream [0]   
       
   dest stream [0]   
          ����                  ����          
@�����   
                                        nd_packet_stream         :  f|  f�     �  �  �  }    �          
   stat_1   
       
   channel [0]   
       
   busy   
       
   
instat [1]   
          ����                  ����             ����             ����              ����              ����          ԲI�%��}����          ԲI�%��}����             0����                                           nd_statistic_wire     f�   ;      sink.End-to-End Delay (seconds)   End-to-End Delay (seconds)           Traffic Sink    bucket/default total/sample mean   linear   Traffic Sink    sink.Traffic Received (bits/sec)   Traffic Received (bits/sec)           Traffic Sink   bucket/default total/sum_time   linear   Traffic Sink   l2cap.free size (bits)   free size (bits)           queue   !bucket/default total/time average   linear   queue   'l2cap.subqueue [0].queue size (packets)   queue size (packets)           queue   !bucket/default total/time average   linear   queue   sink.Traffic Received (bits)   Traffic Received (bits)           Traffic Sink   bucket/default total/sum   linear   Traffic Sink   source.Traffic Sent (packets)   Traffic Sent (packets)           Traffic Source   bucket/default total/sum   linear   Traffic Source   l2cap.queue size (packets)   queue size (packets)           queue   !bucket/default total/time average   linear   queue   sink.Traffic Received (packets)   Traffic Received (packets)           Traffic Sink   bucket/default total/sum   linear   Traffic Sink          machine type       station   Model Attributes      14.5.A-January18-2008                interface type       
IEEE802.11   interface class       access           wlan_port_tx<n>   wlan_port_rx<n>           