#include "analysis_engine.h"

NetworkAnalyzer::NetworkAnalyzer(const std::string& interface) : interface(interface) {
    dev = pcpp::PcapLiveDeviceList::getInstance().getPcapLiveDeviceByName(interface);
    if (dev == nullptr) {
        throw std::runtime_error("Could not find network interface: " + interface);
    }
}

void NetworkAnalyzer::start() {
    if (!dev->open()) {
        throw std::runtime_error("Could not open device: " + interface);
    }
    dev->startCapture(PacketHandler::packetCallback, nullptr);
}
