#include "ns3/applications-module.h"
#include "ns3/core-module.h"
#include "ns3/internet-module.h"
#include "ns3/netanim-module.h"
#include "ns3/network-module.h"
#include "ns3/point-to-point-layout-module.h"
#include "ns3/point-to-point-module.h"

using namespace ns3;

NS_LOG_COMPONENT_DEFINE("Star");

int main(int argc, char* argv[])
{
    LogComponentEnable("Star", LOG_LEVEL_INFO);
    LogComponentEnable("PacketSink", LOG_LEVEL_INFO);
    LogComponentEnable("OnOffApplication", LOG_LEVEL_INFO);
    NS_LOG_INFO("Modified Star Topology Simulation");

    Config::SetDefault("ns3::OnOffApplication::PacketSize", UintegerValue(137));
    Config::SetDefault("ns3::OnOffApplication::DataRate", StringValue("14kb/s"));


    uint32_t nSpokes = 7;

    CommandLine cmd(__FILE__);
    cmd.AddValue("nSpokes", "Number of nodes to place in the star", nSpokes);
    cmd.Parse(argc, argv);

    PointToPointHelper pointToPoint;
    pointToPoint.SetDeviceAttribute("DataRate", StringValue("5Mbps"));
    pointToPoint.SetChannelAttribute("Delay", StringValue("2ms"));

    // Build star
    PointToPointStarHelper star(nSpokes, pointToPoint);

    // Create extra node n9 and connect to n5
    NodeContainer extra;
    extra.Create(2); // n5 and n9
    InternetStackHelper internet;
    star.InstallStack(internet);
    internet.Install(extra);

   
    NetDeviceContainer d0n5 = pointToPoint.Install(star.GetHub(), extra.Get(0));
    NetDeviceContainer d5n9 = pointToPoint.Install(extra.Get(0), extra.Get(1));
   
    // Assign addresses
    star.AssignIpv4Addresses(Ipv4AddressHelper("10.1.1.0", "255.255.255.0"));
   
    Ipv4AddressHelper address1,address2;
    address1.SetBase("10.2.1.0", "255.255.255.0");
    Ipv4InterfaceContainer if0n5 = address1.Assign(d0n5);
    address2.SetBase("10.2.2.0", "255.255.255.0");
    Ipv4InterfaceContainer if5n9 = address2.Assign(d5n9);
   
    // Install packet sink on n9
    uint16_t port = 50000;
    Address sinkLocalAddress(InetSocketAddress(Ipv4Address::GetAny(), port));
    PacketSinkHelper sinkHelper("ns3::TcpSocketFactory", sinkLocalAddress);
    ApplicationContainer sinkApp = sinkHelper.Install(extra.Get(1));
    sinkApp.Start(Seconds(1.0));
    sinkApp.Stop(Seconds(10.0));

    // OnOff apps on spoke nodes except n5
    OnOffHelper onOffHelper("ns3::TcpSocketFactory", Address());
    onOffHelper.SetAttribute("OnTime", StringValue("ns3::ConstantRandomVariable[Constant=1]"));
    onOffHelper.SetAttribute("OffTime", StringValue("ns3::ConstantRandomVariable[Constant=0]"));

    ApplicationContainer spokeApps;
    for (uint32_t i = 0; i < star.SpokeCount(); ++i)
    {
        if (i == 5) continue; // skip n5 (forwarder only)
        AddressValue remoteAddress(InetSocketAddress(if5n9.GetAddress(1), port)); // sink at n9
        onOffHelper.SetAttribute("Remote", remoteAddress);
        spokeApps.Add(onOffHelper.Install(star.GetSpokeNode(i)));
    }
    spokeApps.Start(Seconds(1.0));
    spokeApps.Stop(Seconds(10.0));

    // Enable routing so n0 and n5 act as forwarders
    Ipv4GlobalRoutingHelper::PopulateRoutingTables();

    pointToPoint.EnablePcapAll("star_forwarding");

    Simulator::Run();
    Simulator::Destroy();
    return 0;
}
