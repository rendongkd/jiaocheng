MIL_3_Tfile_Hdr_ 145A 140A modeler 6 5D64EE8A 5D69E79F 2D USER-20151017SA Administrator 0 0 none none 0 0 none 9DCEDD2E 440C 0 0 0 0 0 0 1bcc 1                                                                                                                                                                                                                                                                                                                                                                                 ��g�      8   L   �  *  �  �  �  �  %�  %�  A%  A)      node   WLAN   	stn_wless   	stn_wless��������   Wireless LAN station    6   General Node Functions:    -----------------------        The wireless station node model    /represents an IEEE802.11 wireless LAN station.    %The node model consists of following    
processes:       *1. The MAC layer which has a wireless lan    !mac process model with following    attributes:       MAC address -- station address       *Fragmentation Threshold --- based on this    (threshold station decides wether or not    "to send data packets in fragments.       *Rts threshold --- based on this threshold    (station decides wether Rts/Cts exchange    *is needed for every data transmission.           "The wireless LAN MAC layer has an    "interface with higher layer which    &receives packet from higher layer and    "generates random address for them.           2. Wireless LAN interface       #This process model is an interface    )between MAC layer and higher layer.  The    &function of this process is to accept    'packets from higher layer and generate    &random destination address for them.     )This information is then sent to the MAC    layer.            3. Wireless LAN receiver       *This is a wireless receiver which accepts    (any incomming packets from the physical    &layer and pass it to the wireless MAC    process.           4. Wireless LAN transmitter       %This is a wireless transmitter which    #receives packet from MAC layer and    $transmits it to the physical medium.                node_address    �������    ����          d����          ����          ����           �Z             destination_address    �������    ����           ����          ����          ����           �Z             
d2d_switch    �������    ����          ����          ����          ����         ON      ����      OFF       ����       �Z                    Destination Address      !wlan_mac_intf.Destination Address����    ����           ����          ����          ����                        Traffic Generation Parameters      $source.Traffic Generation Parameters����   ����                                             count    �������    ����          ����          ����          ����           �Z             list   	�������   	����                                              �Z                        Traffic Type of Service      wlan_mac_intf.Type of Service����    ����           ����          ����          ����                         Wireless LAN MAC Address      wireless_lan_mac.Address����    ����           ����          ����          ����                        Wireless LAN Parameters      (wireless_lan_mac.Wireless LAN Parameters����   ����                                             count    �������    ����          ����          ����          ����           �Z             list   	�������   	����                                              �Z                       altitude      altitude����   ����               ����              ����              ����                        phase      phase����   ����               ����              ����              ����                        Destination Address          
       Random   
   
TIM source            none      Traffic Generation Parameters         
      None   
   Traffic Type of Service                 Best Effort (0)      Wireless LAN MAC Address          
       Auto Assigned   
   Wireless LAN Parameters         
      Default   
   altitude         
        ����   
   altitude modeling            relative to subnet-platform      	condition         
   ����   
   financial cost            0.00      phase                 ����      priority              ����      role         ����      user id              ����            fj  �   l          
   source   
       
   bursty_source_d2d   
          	processor                   fl  8   l          
   sink   
       
   sink_d2d   
          	processor                   fn    $          
   d2d_intf   
       
   d2d_intf   
          	processor                	  f|  f  �          
   d2d_rx   
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
   d2d_tx   
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
   d2d_mac   
       J   l2cap   J          queue                   begsim intrpt   ���   
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
   
  f�  
  8   
       
   a_0   
          	isotropic                  ����          @f�     ����                  ����                  ����                  ����             antenna                       
nd_antenna        f�  
   �          
   D2D   
       
   D2D   
          queue                   subqueue   ���   
            count    ���   
   ����   
      list   	���   
                bit capacity   ���   
T�I�%��}����   
      pk capacity   ���   
T�I�%��}����   
   
   
   
       	  f�  f�     
    �  �   
       
   strm_12   
       
   src stream [0]   
       
   dest stream [0]   
          ����                  ����             ����                                           nd_packet_stream          
  f|  f�     e  �       
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
                                        nd_packet_stream            f�  f�     �  �  	  7   
       J   strm_16   J       
   src stream [0]   
       
   dest stream [0]   
          ����                  ����             ����                                           nd_packet_stream            f�  f|     
  6  e  �   
       
   strm_17   
       
   src stream [0]   
       
   dest stream [0]   
          ����                  ����          
@�  ����   
                                        nd_packet_stream            fj  f�     �   k  �   l     �   
       
   strm_18   
       
   src stream [0]   
       
   dest stream [0]   
          ����                  ����             ����                                           nd_packet_stream            f�  fl        �     n  0   n   
       
   strm_19   
       
   src stream [0]   
       
   dest stream [0]   
          ����                  ����          
@�  ����   
                                        nd_packet_stream             f�  fn        �       
       
   strm_20   
       
   src stream [1]   
       
   dest stream [0]   
          ����                  ����             ����                                           nd_packet_stream          !  fn  f�            �   
       
   strm_21   
       
   src stream [0]   
       
   dest stream [1]   
          ����                  ����          
@�  ����   
                                        nd_packet_stream     f�   4   '   &wireless_lan_mac.Backoff Slots (slots)   Backoff Slots (slots)           Wireless Lan   bucket/default total/sum   linear   Wireless Lan   0wireless_lan_mac.Control Traffic Rcvd (bits/sec)   Control Traffic Rcvd (bits/sec)           Wireless Lan   bucket/default total/sum_time   linear   Wireless Lan   3wireless_lan_mac.Control Traffic Rcvd (packets/sec)   "Control Traffic Rcvd (packets/sec)           Wireless Lan   bucket/default total/sum_time   linear   Wireless Lan   0wireless_lan_mac.Control Traffic Sent (bits/sec)   Control Traffic Sent (bits/sec)           Wireless Lan   bucket/default total/sum_time   linear   Wireless Lan   3wireless_lan_mac.Control Traffic Sent (packets/sec)   "Control Traffic Sent (packets/sec)           Wireless Lan   bucket/default total/sum_time   linear   Wireless Lan   3wireless_lan_mac.Management Traffic Rcvd (bits/sec)   "Management Traffic Rcvd (bits/sec)           Wireless Lan   bucket/default total/sum_time   linear   Wireless Lan   6wireless_lan_mac.Management Traffic Rcvd (packets/sec)   %Management Traffic Rcvd (packets/sec)           Wireless Lan   bucket/default total/sum_time   linear   Wireless Lan   3wireless_lan_mac.Management Traffic Sent (bits/sec)   "Management Traffic Sent (bits/sec)           Wireless Lan   bucket/default total/sum_time   linear   Wireless Lan   6wireless_lan_mac.Management Traffic Sent (packets/sec)   %Management Traffic Sent (packets/sec)           Wireless Lan   bucket/default total/sum_time   linear   Wireless Lan   -wireless_lan_mac.Data Traffic Rcvd (bits/sec)   Data Traffic Rcvd (bits/sec)           Wireless Lan   bucket/default total/sum_time   linear   Wireless Lan   0wireless_lan_mac.Data Traffic Rcvd (packets/sec)   Data Traffic Rcvd (packets/sec)           Wireless Lan   bucket/default total/sum_time   linear   Wireless Lan   -wireless_lan_mac.Data Traffic Sent (bits/sec)   Data Traffic Sent (bits/sec)           Wireless Lan   bucket/default total/sum_time   linear   Wireless Lan   0wireless_lan_mac.Data Traffic Sent (packets/sec)   Data Traffic Sent (packets/sec)           Wireless Lan   bucket/default total/sum_time   linear   Wireless Lan    wireless_lan_mac.Load (bits/sec)   Load (bits/sec)           Wireless Lan   bucket/default total/sum_time   linear   Wireless Lan   #wireless_lan_mac.Load (packets/sec)   Load (packets/sec)           Wireless Lan   bucket/default total/sum_time   linear   Wireless Lan   &wireless_lan_mac.Throughput (bits/sec)   Throughput (bits/sec)           Wireless Lan   bucket/default total/sum_time   linear   Wireless Lan   2wireless_lan_mac.Retransmission Attempts (packets)   !Retransmission Attempts (packets)           Wireless Lan   bucket/default total/sum   linear   Wireless Lan   )wireless_lan_mac.Media Access Delay (sec)   Media Access Delay (sec)           Wireless Lan    bucket/default total/sample mean   linear   Wireless Lan   wireless_lan_mac.Delay (sec)   Delay (sec)           Wireless Lan    bucket/default total/sample mean   linear   Wireless Lan    wireless_lan_mac.AP Connectivity   AP Connectivity           Wireless Lan   normal   square-wave   Wireless Lan   :wireless_lan_mac.Data Dropped (Buffer Overflow) (bits/sec)   )Data Dropped (Buffer Overflow) (bits/sec)           Wireless Lan   bucket/default total/sum_time   linear   Wireless Lan   =wireless_lan_mac.Data Dropped (Buffer Overflow) (packets/sec)   ,Data Dropped (Buffer Overflow) (packets/sec)           Wireless Lan   bucket/default total/sum_time   linear   Wireless Lan   Cwireless_lan_mac.Data Dropped (Retry Threshold Exceeded) (bits/sec)   2Data Dropped (Retry Threshold Exceeded) (bits/sec)           Wireless Lan   bucket/default total/sum_time   linear   Wireless Lan   %wireless_lan_mac.Queue Size (packets)   Queue Size (packets)           Wireless Lan   !bucket/default total/time average   linear   Wireless Lan   Fwireless_lan_mac.Data Dropped (Retry Threshold Exceeded) (packets/sec)   5Data Dropped (Retry Threshold Exceeded) (packets/sec)           Wireless Lan   bucket/default total/sum_time   linear   Wireless Lan   6wireless_lan_mac.Management Traffic Dropped (bits/sec)   %Management Traffic Dropped (bits/sec)           Wireless Lan   bucket/default total/sum_time   linear   Wireless Lan   9wireless_lan_mac.Management Traffic Dropped (packets/sec)   (Management Traffic Dropped (packets/sec)           Wireless Lan   bucket/default total/sum_time   linear   Wireless Lan    wireless_lan_mac.Load (bits/sec)   Load (bits/sec)           WLAN (Per HCF Access Category)   bucket/default total/sum_time   linear   WLAN (Per HCF Access Category)   #wireless_lan_mac.Load (packets/sec)   Load (packets/sec)           WLAN (Per HCF Access Category)   bucket/default total/sum_time   linear   WLAN (Per HCF Access Category)   (wireless_lan_mac.AC Queue Size (packets)   AC Queue Size (packets)           WLAN (Per HCF Access Category)   !bucket/default total/time average   linear   WLAN (Per HCF Access Category)   :wireless_lan_mac.Data Dropped (Buffer Overflow) (bits/sec)   )Data Dropped (Buffer Overflow) (bits/sec)           WLAN (Per HCF Access Category)   bucket/default total/sum_time   linear   WLAN (Per HCF Access Category)   =wireless_lan_mac.Data Dropped (Buffer Overflow) (packets/sec)   ,Data Dropped (Buffer Overflow) (packets/sec)           WLAN (Per HCF Access Category)   bucket/default total/sum_time   linear   WLAN (Per HCF Access Category)   &wireless_lan_mac.Backoff Slots (slots)   Backoff Slots (slots)           WLAN (Per HCF Access Category)   bucket/default total/sum   linear   WLAN (Per HCF Access Category)   )wireless_lan_mac.Internal Collision Count   Internal Collision Count           WLAN (Per HCF Access Category)   bucket/default total/sum   linear   WLAN (Per HCF Access Category)   )wireless_lan_mac.Media Access Delay (sec)   Media Access Delay (sec)           WLAN (Per HCF Access Category)    bucket/default total/sample mean   linear   WLAN (Per HCF Access Category)   Cwireless_lan_mac.Data Dropped (Retry Threshold Exceeded) (bits/sec)   2Data Dropped (Retry Threshold Exceeded) (bits/sec)           WLAN (Per HCF Access Category)   bucket/default total/sum_time   linear   WLAN (Per HCF Access Category)   Fwireless_lan_mac.Data Dropped (Retry Threshold Exceeded) (packets/sec)   5Data Dropped (Retry Threshold Exceeded) (packets/sec)           WLAN (Per HCF Access Category)   bucket/default total/sum_time   linear   WLAN (Per HCF Access Category)   wireless_lan_mac.Delay (sec)   Delay (sec)           WLAN (Per HCF Access Category)    bucket/default total/sample mean   linear   WLAN (Per HCF Access Category)   &wireless_lan_mac.Throughput (bits/sec)   Throughput (bits/sec)           WLAN (Per HCF Access Category)   bucket/default total/sum_time   linear   WLAN (Per HCF Access Category)          machine type       station   Model Attributes      14.5.A-January18-2008                interface type       
IEEE802.11   interface class       access           wlan_port_tx<n>   wlan_port_rx<n>           