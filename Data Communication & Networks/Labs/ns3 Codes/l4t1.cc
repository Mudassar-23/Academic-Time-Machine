#include "ns3/core-module.h"
#include "ns3/network-module.h"
#include "ns3/csma-module.h"
#include "ns3/internet-module.h"
#include "ns3/point-to-point-module.h"
#include "ns3/applications-module.h"
#include "ns3/ipv4-global-routing-helper.h"

using namespace ns3;

NS_LOG_COMPONENT_DEFINE ("TwoLanExample");

int main (int argc, char *argv[])
{
  bool verbose = true;

  CommandLine cmd;
  cmd.AddValue ("verbose", "Tell echo applications to log if true", verbose);
  cmd.Parse (argc, argv);

  if (verbose)
    {
      LogComponentEnable ("UdpEchoClientApplication", LOG_LEVEL_INFO);
      LogComponentEnable ("UdpEchoServerApplication", LOG_LEVEL_INFO);
    }

  // ---------------- Node Creation ----------------
  NodeContainer p2pNodes;
 

  NodeContainer csmaNodes;  // right LAN 10.1.2.0 (n1, n2, n3, n4)
 
  csmaNodes.Create (4);            
 
  NodeContainer csmaNodes1; // left LAN 10.1.3.0 (n0, n5, n6, n7)

  csmaNodes1.Create (4);      
  p2pNodes.Add(csmaNodes.Get(3),csmaNodes1.Get(0));  

  // ---------------- Point-to-Point ----------------
  PointToPointHelper pointToPoint;
  pointToPoint.SetDeviceAttribute ("DataRate", StringValue ("5Mbps"));
  pointToPoint.SetChannelAttribute ("Delay", StringValue ("2ms"));

  NetDeviceContainer p2pDevices;
  p2pDevices = pointToPoint.Install (p2pNodes);

  // ---------------- CSMA LANs ----------------
  CsmaHelper csma;
  csma.SetChannelAttribute ("DataRate", StringValue ("100Mbps"));
  csma.SetChannelAttribute ("Delay", TimeValue (NanoSeconds (6560)));

  NetDeviceContainer csmaDevices;
  csmaDevices = csma.Install (csmaNodes); //right LAN

  CsmaHelper csma1;
  csma1.SetChannelAttribute ("DataRate", StringValue ("100Mbps"));
  csma1.SetChannelAttribute ("Delay", TimeValue (NanoSeconds (6560)));

  NetDeviceContainer csmaDevices1;
  csmaDevices1 = csma1.Install (csmaNodes1); //left LAN

  // ---------------- Internet Stack ----------------
  InternetStackHelper stack;
  stack.Install (csmaNodes);   // right LAN 10.1.2.0
  stack.Install (csmaNodes1);  // left LAN 10.1.3.0

  // ---------------- IP Addressing ----------------
  Ipv4AddressHelper address;

  address.SetBase ("10.1.1.0", "255.255.255.0");
  Ipv4InterfaceContainer p2pInterfaces = address.Assign (p2pDevices);

  address.SetBase ("10.1.2.0", "255.255.255.0"); // right LAN
  Ipv4InterfaceContainer csmaInterfaces = address.Assign (csmaDevices);

  address.SetBase ("10.1.3.0", "255.255.255.0"); // left LAN
  Ipv4InterfaceContainer csmaInterfaces1 = address.Assign (csmaDevices1);

  // ---------------- Applications ----------------
  // Server on n3 (index 2 in csmaNodes)
  UdpEchoServerHelper echoServer (93);
  ApplicationContainer serverApps = echoServer.Install (csmaNodes.Get (2));
  serverApps.Start (Seconds (1.0));
  serverApps.Stop (Seconds (10.0));

  // Client on n6 (index 2 in csmaNodes1), targeting n3
  UdpEchoClientHelper echoClient (csmaInterfaces.GetAddress (2), 93);
  echoClient.SetAttribute ("MaxPackets", UintegerValue (1));
  echoClient.SetAttribute ("Interval", TimeValue (Seconds (1.0)));
  echoClient.SetAttribute ("PacketSize", UintegerValue (1024));

  ApplicationContainer clientApps = echoClient.Install (csmaNodes1.Get (1));
  clientApps.Start (Seconds (2.0));
  clientApps.Stop (Seconds (10.0));

  // ---------------- Routing ----------------
  Ipv4GlobalRoutingHelper::PopulateRoutingTables ();

  // ---------------- Tracing ----------------
  pointToPoint.EnablePcapAll ("two-lan");
  csma.EnablePcap ("two-lan", csmaDevices.Get (1), true);
  csma1.EnablePcap ("two-lan", csmaDevices1.Get (1), true);

  // ---------------- Run Simulation ----------------
  Simulator::Run ();
  Simulator::Destroy ();
  return 0;
}


