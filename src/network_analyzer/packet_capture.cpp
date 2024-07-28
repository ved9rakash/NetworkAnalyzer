#include "packet_capture.h"

#include <iostream>

// Getting the raw packet and outputting packet data length in bytes
void PacketHandler::packetCallback(pcpp::RawPacket* packet, pcpp::PcapLiveDevice* dev, void* cookie) {
    pcpp::RawPacket* parsedPacket(packet);
    std::cout << "Packet captured: " << parsedPacket->getRawDataLen() << " bytes" << std::endl;
}
