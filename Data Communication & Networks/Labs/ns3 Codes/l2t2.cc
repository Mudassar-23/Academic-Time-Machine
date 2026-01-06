 #include "ns3/core-module.h" 
 #include "ns3/network-module.h" 
 #include "ns3/internet-module.h" 
 #include "ns3/point-to-point-module.h" 
 #include "ns3/applications-module.h" 
 using namespace ns3; 
 NS_LOG_COMPONENT_DEFINE("FirstScriptExample"); 
 int main(int argc, char *argv[]) { 
 
 Time::SetResolution(Time::NS); 

 LogComponentEnable("UdpEchoClientApplication", LOG_LEVEL_INFO);
 LogComponentEnable("UdpEchoServerApplication", LOG_LEVEL_INFO);
 NodeContainer nodes; 
 nodes.Create(3);   

  // Create a point-to-point link between nodes 0 and 1 
  PointToPointHelper pointToPoint1; 
  pointToPoint1.SetDeviceAttribute("DataRate", StringValue("8Mbps"));
  pointToPoint1.SetChannelAttribute("Delay", StringValue("8ms")); 
  
  NetDeviceContainer devices1; 
  devices1 = pointToPoint1.Install(nodes.Get(0), nodes.Get(1)); 
  
  
  PointToPointHelper pointToPoint2; 
  pointToPoint2.SetDeviceAttribute("DataRate", StringValue("8Mbps"));
  pointToPoint2.SetChannelAttribute("Delay", StringValue("4ms")); 
  
  NetDeviceContainer devices2; 
  devices2 = pointToPoint2.Install(nodes.Get(1), nodes.Get(2)); 
  
  InternetStackHelper stack; 
  stack.Install(nodes); 
  
  Ipv4AddressHelper address1; 
  address1.SetBase("192.168.1.0", "255.255.255.0"); 
  Ipv4InterfaceContainer interfaces1 = address1.Assign(devices1); 
  
  Ipv4AddressHelper address2; 
  address2.SetBase("192.168.5.0", "255.255.255.0"); 
  Ipv4InterfaceContainer interfaces2 = address2.Assign(devices2);
  
  UdpEchoServerHelper echoServer(93);
  ApplicationContainer serverApps = echoServer.Install(nodes.Get(1));
  serverApps.Start(Seconds(1.0)); 
  serverApps.Stop(Seconds(20.0)); 
  
  UdpEchoClientHelper echoClient1(interfaces1.GetAddress(1), 93); 
  echoClient1.SetAttribute("MaxPackets", UintegerValue(1)); 
  echoClient1.SetAttribute("Interval", TimeValue(Seconds(1.0)));
  echoClient1.SetAttribute("PacketSize", UintegerValue(512)); 
  
  ApplicationContainer clientApps1 = echoClient1.Install(nodes.Get(0));
  clientApps1.Start(Seconds(5.0)); 
  clientApps1.Stop(Seconds(10.0)); 
  
  UdpEchoClientHelper echoClient2(interfaces2.GetAddress(0), 93); 
  echoClient2.SetAttribute("MaxPackets", UintegerValue(1)); 
  echoClient2.SetAttribute("Interval", TimeValue(Seconds(1.0))); 
  echoClient2.SetAttribute("PacketSize", UintegerValue(512)); 
  
  ApplicationContainer clientApps2 = echoClient2.Install(nodes.Get(2));
  clientApps2.Start(Seconds(11.0)); 
  clientApps2.Stop(Seconds(15.0));  
  
  Simulator::Run();  
  Simulator::Destroy(); 
  return 0;
  }    
