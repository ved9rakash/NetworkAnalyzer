#pragma once

#include "packet_capture.h"

#include "pcapplusplus/PcapLiveDevice.h"
#include "pcapplusplus/PcapLiveDeviceList.h"

#include <string>

class NetworkAnalyzer {
public:
    NetworkAnalyzer(const std::string& interface);
    void start();

private:
    std::string interface;
    pcpp::PcapLiveDevice* dev;
    PacketHandler packetHandler;
};
