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
  
  // Create 4 nodes: Client (0), Router (1), Server1 (2), Server2 (3) 
  NodeContainer nodes; 
  nodes.Create(4); // Link: Client (0) <-> Router (1) 
  
  PointToPointHelper c2r;
  c2r.SetDeviceAttribute("DataRate", StringValue("8Mbps"));
  c2r.SetChannelAttribute("Delay", StringValue("5ms"));
  
  NetDeviceContainer d01 = c2r.Install(nodes.Get(0), nodes.Get(1)); 
  // Link: Router (1) <-> Server1 (2)  
  
  PointToPointHelper r2s1;
  r2s1.SetDeviceAttribute("DataRate", StringValue("8Mbps")); 
  r2s1.SetChannelAttribute("Delay", StringValue("4ms")); 
  NetDeviceContainer d12 = r2s1.Install(nodes.Get(1), nodes.Get(2));
  
  // Link: Router (1) <-> Server2 (3)  
  PointToPointHelper r2s2; 
  r2s2.SetDeviceAttribute("DataRate", StringValue("8Mbps")); 
  r2s2.SetChannelAttribute("Delay", StringValue("4ms")); 
  NetDeviceContainer d13 = r2s2.Install(nodes.Get(1), nodes.Get(3)); 
  
  // Install Internet stack 
  InternetStackHelper stack;
  stack.Install(nodes); // Assign IP addresses
  
  Ipv4AddressHelper addr; 
  addr.SetBase("192.168.40.0", "255.255.255.0"); 
  Ipv4InterfaceContainer if01 = addr.Assign(d01); 
  
  addr.SetBase("192.168.41.0", "255.255.255.0"); 
  Ipv4InterfaceContainer if12 = addr.Assign(d12);
  
  addr.SetBase("192.168.42.0", "255.255.255.0"); 
  Ipv4InterfaceContainer if13 = addr.Assign(d13);
  
  // Populate routing tables  
  Ipv4GlobalRoutingHelper::PopulateRoutingTables();
  // ---- SERVERS ---- 10. 
  // Server1 on Node2 (port 93) 11. 
  UdpEchoServerHelper echoServer1(93);
  ApplicationContainer s1 = echoServer1.Install(nodes.Get(2)); 
  s1.Start(Seconds(1.0)); 
  s1.Stop(Seconds(20.0)); 
  // Server2 on Node3 (port 94) 
  UdpEchoServerHelper echoServer2(94); 
  ApplicationContainer s2 = echoServer2.Install(nodes.Get(3)); 
  s2.Start(Seconds(1.0)); 
  s2.Stop(Seconds(20.0)); 
  // ---- CLIENTS ----  
  
     // Client1 on Node0 -> Server1 
     UdpEchoClientHelper c1(Ipv4Address("192.168.41.2"), 93); 
     c1.SetAttribute("MaxPackets", UintegerValue(6)); 
     c1.SetAttribute("Interval", TimeValue(Seconds(1.0)));
     c1.SetAttribute("PacketSize", UintegerValue(512)); 
     ApplicationContainer ca1 = c1.Install(nodes.Get(0));
     ca1.Start(Seconds(5.0)); 
     ca1.Stop(Seconds(19.0)); 
     
     // Client2 on Node0 -> Server2  
     UdpEchoClientHelper c2(Ipv4Address("192.168.42.2"), 94); 
     c2.SetAttribute("MaxPackets", UintegerValue(6));
     c2.SetAttribute("Interval", TimeValue(Seconds(1.0))); 
     c2.SetAttribute("PacketSize", UintegerValue(512)); 
     ApplicationContainer ca2 = c2.Install(nodes.Get(0)); 
     ca2.Start(Seconds(5.0)); 
     ca2.Stop(Seconds(20.0)); 
     
     Simulator::Run(); 
     Simulator::Destroy(); 
     return 0; 
     }   
