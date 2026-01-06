
#include "ns3/core-module.h"
#include "ns3/network-module.h"
#include "ns3/internet-module.h"
#include "ns3/point-to-point-module.h"
#include "ns3/wifi-module.h"
#include "ns3/mobility-module.h"
#include "ns3/applications-module.h"

using namespace ns3;

NS_LOG_COMPONENT_DEFINE ("WifiToWifiExample");

int main (int argc, char *argv[])
{
  Time::SetResolution (Time::NS);
  LogComponentEnable ("UdpEchoClientApplication", LOG_LEVEL_INFO);
  LogComponentEnable ("UdpEchoServerApplication", LOG_LEVEL_INFO);

  // ---------------- Nodes ----------------
  NodeContainer p2pNodes;
  p2pNodes.Create (2); // n0 (AP left), n1 (AP right)

  NodeContainer wifiStaLeft;
  wifiStaLeft.Create (3); // n5, n6, n7

  NodeContainer wifiStaRight;
  wifiStaRight.Create (3); // n2, n3, n4

  // ---------------- Point-to-Point ----------------
  PointToPointHelper p2p;
  p2p.SetDeviceAttribute ("DataRate", StringValue ("5Mbps"));
  p2p.SetChannelAttribute ("Delay", StringValue ("2ms"));
  NetDeviceContainer p2pDevices = p2p.Install (p2pNodes);

  // ---------------- WiFi Left ----------------
  WifiHelper wifiLeft;
  wifiLeft.SetRemoteStationManager ("ns3::MinstrelHtWifiManager");

  YansWifiChannelHelper channelLeft = YansWifiChannelHelper::Default ();
  YansWifiPhyHelper phyLeft;
  phyLeft.SetChannel (channelLeft.Create ());

  WifiMacHelper macLeft;
  Ssid ssidLeft = Ssid ("wifi-left");

  macLeft.SetType ("ns3::StaWifiMac",
                   "Ssid", SsidValue (ssidLeft),
                   "ActiveProbing", BooleanValue (false));
  NetDeviceContainer staDevicesLeft = wifiLeft.Install (phyLeft, macLeft, wifiStaLeft);

  macLeft.SetType ("ns3::ApWifiMac",
                   "Ssid", SsidValue (ssidLeft));
  NetDeviceContainer apDeviceLeft = wifiLeft.Install (phyLeft, macLeft, p2pNodes.Get (0));

  // ---------------- WiFi Right ----------------
  WifiHelper wifiRight;
  wifiRight.SetRemoteStationManager ("ns3::MinstrelHtWifiManager");

  YansWifiChannelHelper channelRight = YansWifiChannelHelper::Default ();
  YansWifiPhyHelper phyRight;
  phyRight.SetChannel (channelRight.Create ());

  WifiMacHelper macRight;
  Ssid ssidRight = Ssid ("wifi-right");

  macRight.SetType ("ns3::StaWifiMac",
                    "Ssid", SsidValue (ssidRight),
                    "ActiveProbing", BooleanValue (false));
  NetDeviceContainer staDevicesRight = wifiRight.Install (phyRight, macRight, wifiStaRight);

  macRight.SetType ("ns3::ApWifiMac",
                    "Ssid", SsidValue (ssidRight));
  NetDeviceContainer apDeviceRight = wifiRight.Install (phyRight, macRight, p2pNodes.Get (1));

  // ---------------- Mobility ----------------
  MobilityHelper mobility;
  mobility.SetPositionAllocator ("ns3::GridPositionAllocator",
                                 "MinX", DoubleValue (0.0),
                                 "MinY", DoubleValue (0.0),
                                 "DeltaX", DoubleValue (5.0),
                                 "DeltaY", DoubleValue (10.0),
                                 "GridWidth", UintegerValue (3),
                                 "LayoutType", StringValue ("RowFirst"));

  mobility.SetMobilityModel ("ns3::RandomWalk2dMobilityModel",
                             "Bounds", RectangleValue (Rectangle (-50, 50, -50, 50)));
  mobility.Install (wifiStaLeft);
  mobility.Install (wifiStaRight);

  mobility.SetMobilityModel ("ns3::ConstantPositionMobilityModel");
  mobility.Install (p2pNodes);

  // ---------------- Internet Stack ----------------
  InternetStackHelper stack;
  stack.Install (wifiStaLeft);
  stack.Install (wifiStaRight);
  stack.Install (p2pNodes);

  // ---------------- IP Addressing ----------------
  Ipv4AddressHelper address;

  // P2P (between APs)
  address.SetBase ("10.1.1.0", "255.255.255.0");
  Ipv4InterfaceContainer p2pInterfaces = address.Assign (p2pDevices);

  // Left WiFi
  address.SetBase ("10.1.3.0", "255.255.255.0");
  Ipv4InterfaceContainer staIfLeft = address.Assign (staDevicesLeft);
  Ipv4InterfaceContainer apIfLeft = address.Assign (apDeviceLeft);

  // Right WiFi
  address.SetBase ("10.1.2.0", "255.255.255.0");
  Ipv4InterfaceContainer staIfRight = address.Assign (staDevicesRight);
  Ipv4InterfaceContainer apIfRight = address.Assign (apDeviceRight);

  // ---------------- Applications ----------------
  // Server on n3 (STA of right WiFi)
  UdpEchoServerHelper echoServer (93);
  ApplicationContainer serverApps = echoServer.Install (wifiStaRight.Get (2)); // n3
  serverApps.Start (Seconds (1.0));
  serverApps.Stop (Seconds (10.0));

  // Client on n6 (STA of left WiFi) → server n3
  UdpEchoClientHelper echoClient (staIfRight.GetAddress (2), 93);
  echoClient.SetAttribute ("MaxPackets", UintegerValue (1));
  echoClient.SetAttribute ("Interval", TimeValue (Seconds (1.0)));
  echoClient.SetAttribute ("PacketSize", UintegerValue (1024));

  ApplicationContainer clientApps = echoClient.Install (wifiStaLeft.Get (1)); // n6
  clientApps.Start (Seconds (2.0));
  clientApps.Stop (Seconds (10.0));

  // ---------------- Routing ----------------
  Ipv4GlobalRoutingHelper::PopulateRoutingTables ();

  // ---------------- Run Simulation ----------------
  Simulator::Run ();
  Simulator::Destroy ();
  return 0;
}

	

