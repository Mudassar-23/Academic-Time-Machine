 #include "ns3/core-module.h" 
 #include "ns3/network-module.h" 
 #include "ns3/internet-module.h" 
 #include "ns3/point-to-point-module.h" 
 #include "ns3/applications-module.h" 
 using namespace ns3; 
 NS_LOG_COMPONENT_DEFINE ("FirstScriptExample"); 
 
 int main (int argc, char *argv[]) { 
 Time::SetResolution (Time::NS); 
 LogComponentEnable("UdpEchoClientApplication", LOG_LEVEL_INFO); 
 LogComponentEnable("UdpEchoServerApplication", LOG_LEVEL_INFO); 
 
 NodeContainer nodes; 
 nodes.Create (2); 
 
 PointToPointHelper pointToPoint; 
 pointToPoint.SetDeviceAttribute ("DataRate", StringValue ("8Mbps")); 
 pointToPoint.SetChannelAttribute ("Delay", StringValue ("4ms")); 
 
 NetDeviceContainer devices; 
 devices = pointToPoint.Install (nodes); 
 
 InternetStackHelper stack; 
 stack.Install (nodes); 
 
 Ipv4AddressHelper address; 
 address.SetBase ("192.168.40.0" , "255.255.255.0"); 
 Ipv4InterfaceContainer interfaces = address.Assign (devices);
 
 UdpEchoServerHelper echoServer (93); 
 ApplicationContainer serverApps = echoServer.Install (nodes.Get (1)); 
 serverApps.Start (Seconds (1.0)); 
 serverApps.Stop (Seconds (10.0));

UdpEchoClientHelper echoClient (interfaces.GetAddress (1), 93); 
echoClient.SetAttribute ("MaxPackets", UintegerValue (4)); 
echoClient.SetAttribute ("Interval", TimeValue (Seconds (1.0))); 
echoClient.SetAttribute ("PacketSize", UintegerValue (512)); 

ApplicationContainer clientApps = echoClient.Install (nodes.Get (0)); 
clientApps.Start (Seconds (1.0)); 
clientApps.Stop (Seconds (10.0)); 
Simulator::Run(); 
Simulator::Destroy (); 
return 0; }   
