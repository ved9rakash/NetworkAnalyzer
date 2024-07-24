#include "packet_capture.h"

#include <iostream>

void PacketHandler::packetCallback(pcpp::RawPacket* packet, pcpp::PcapLiveDevice* dev, void* cookie) {
    pcpp::RawPacket* parsedPacket(packet);
    std::cout << "Packet captured: " << parsedPacket->getRawDataLen() << " bytes" << std::endl;
}
