#pragma once

#include "pcapplusplus/PcapLiveDevice.h"

// Handling of captured packet
class PacketHandler {
public:
    // Getting raw packet data length in bytes
    static void packetCallback(pcpp::RawPacket* packet, pcpp::PcapLiveDevice* dev, void* cookie);
};