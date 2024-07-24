#pragma once

#include "pcapplusplus/PcapLiveDevice.h"

class PacketHandler {
public:
    static void packetCallback(pcpp::RawPacket* packet, pcpp::PcapLiveDevice* dev, void* cookie);
};