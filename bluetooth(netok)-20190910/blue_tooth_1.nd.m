MIL_3_Tfile_Hdr_ 145A 140A modeler 6 5D7327F4 5D732902 2 USER-20151017SA Administrator 0 0 none none 0 0 none 40A9792C 1E0A 0 0 0 0 0 0 1bcc 1                                                                                                                                                                                                                                                                                                                                                                                  ��g�      8   R   �  0    	  	v  o      #  '      node   
blue_tooth   	stn_wless   	stn_wless��������   Wireless LAN station    6   General Node Functions:    -----------------------        The wireless station node model    /represents an IEEE802.11 wireless LAN station.    %The node model consists of following    
processes:       *1. The MAC layer which has a wireless lan    !mac process model with following    attributes:       MAC address -- station address       *Fragmentation Threshold --- based on this    (threshold station decides wether or not    "to send data packets in fragments.       *Rts threshold --- based on this threshold    (station decides wether Rts/Cts exchange    *is needed for every data transmission.           "The wireless LAN MAC layer has an    "interface with higher layer which    &receives packet from higher layer and    "generates random address for them.           2. Wireless LAN interface       #This process model is an interface    )between MAC layer and higher layer.  The    &function of this process is to accept    'packets from higher layer and generate    &random destination address for them.     )This information is then sent to the MAC    layer.            3. Wireless LAN receiver       *This is a wireless receiver which accepts    (any incomming packets from the physical    &layer and pass it to the wireless MAC    process.           4. Wireless LAN transmitter       %This is a wireless transmitter which    #receives packet from MAC layer and    $transmits it to the physical medium.                node_address    �������    ����          d����          ����          ����           �Z             destination_address    �������    ����           ����          ����          ����           �Z                   altitude      altitude����   ����               ����              ����              ����                        phase      phase����   ����               ����              ����              ����                     	   
TIM source            none      altitude         
        ����   
   altitude modeling            relative to subnet-platform      	condition         
   ����   
   financial cost            0.00      phase                 ����      priority              ����      role         ����      user id              ����            fj  �   �          
   source   
       
   simple_source   
          	processor                   fl  8   �          
   sink   
       
   sink   
          	processor                   fn    $          
   up_layer   
       
   d2d_intf   
          	processor                	  f|  �  �          
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
   l2cap33   
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
                                        nd_packet_stream          5  fj  fn     �   �     �    %   
       
   strm_16   
       
   src stream [0]   
       
   dest stream [0]   
          ����                  ����             ����                                           nd_packet_stream          6  fn  fl            �  7   �   
       
   strm_17   
       
   src stream [0]   
       
   dest stream [0]   
          ����                  ����          
@�����   
                                        nd_packet_stream         ;  f|  f�     �  �  �  �    ~          
   stat_1   
       
   channel [0]   
       
   busy   
       
   
instat [1]   
          ����                  ����             ����             ����              ����              ����          ԲI�%��}����          ԲI�%��}����             0����                                           nd_statistic_wire     f�   <              machine type       station   Model Attributes      14.5.A-January18-2008                interface type       
IEEE802.11   interface class       access           wlan_port_tx<n>   wlan_port_rx<n>           