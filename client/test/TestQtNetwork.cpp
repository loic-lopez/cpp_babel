// ██████╗  █████╗ ██████╗     ███████╗██╗          ██████╗ ██╗   ██╗███████╗██████╗ 
// ██╔══██╗██╔══██╗██╔══██╗    ██╔════╝██║         ██╔═══██╗██║   ██║██╔════╝██╔══██╗
// ██████╔╝███████║██████╔╝    █████╗  ██║         ██║   ██║██║   ██║█████╗  ██║  ██║
// ██╔══██╗██╔══██║██╔══██╗    ██╔══╝  ██║         ██║   ██║██║   ██║██╔══╝  ██║  ██║
// ██████╔╝██║  ██║██████╔╝    ███████╗███████╗    ╚██████╔╝╚██████╔╝███████╗██████╔╝
// ╚═════╝ ╚═╝  ╚═╝╚═════╝     ╚══════╝╚══════╝     ╚═════╝  ╚═════╝ ╚══════╝╚═════╝ 
// TestQtNetwork.cpp created 30/09/2017

#include <gtest/gtest.h>
#include <fstream>
#include <boost/chrono.hpp>
#include <boost/thread/thread.hpp>
#include "qtNetwork.hpp"

void createNetcatThread()
{
    try
    {
        std::system("touch netcat.txt; chmod 777 netcat.txt");
        std::system("nc -l -p 22222 > netcat.txt 2>&1");
    }
    catch (boost::thread_interrupted &)
    {
    }

}

TEST(CONNECT_WITH_QNETWORK, CONNECT_WITH_QNETWORK)
{
    boost::thread   netcat{ createNetcatThread };

    boost::this_thread::sleep_for(boost::chrono::milliseconds(3000));

    Network::INetworkClient *client = new Network::qtNetwork();

    testing::internal::CaptureStdout();
    client->Connect("127.0.0.1", 22222);
    ASSERT_EQ(testing::internal::GetCapturedStdout(), "Connected!\n");

    Protocol::ProtocolData data;
    Protocol::PacketHeader  header = {};

    header.magiccode = Protocol::MAGIC_CODE_PACKET_HEADER;
    header.data_size =  5;

    data.header = header;
    data.data = "\nHi!\n";

    client->Send(data);
    boost::this_thread::sleep_for(boost::chrono::milliseconds(1000));

    std::ifstream   log("netcat.txt");
    std::string     line;

    std::getline(log, line);
    std::getline(log, line);
    ASSERT_EQ(line, "Hi!");
    netcat.interrupt();
}
