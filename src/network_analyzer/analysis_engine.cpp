#include "analysis_engine.h"
#include <cstddef>
#include <stdexcept>
#include <vector>

#include "pcapplusplus/RawPacket.h"
#include "QMetaObject"

NetworkAnalyzer::NetworkAnalyzer(QObject* parent)
    : QObject(parent), dev(nullptr) {}


void NetworkAnalyzer::setInterface(const std::string& interface) {
    this->interface = interface;
    dev = pcpp::PcapLiveDeviceList::getInstance().getPcapLiveDeviceByName(interface);
    if (dev == nullptr) {
        throw std::runtime_error("Could not find the network interface");
    }
}

void NetworkAnalyzer::start() {
    if (dev == nullptr) {
        throw std::runtime_error("Network interface not set.");
    }
    if (!dev->open()) {
        throw std::runtime_error("Could not open device: " + interface);
    }
    dev->startCapture(packetCallback, this);
}

void NetworkAnalyzer::stop() {
    if (dev != nullptr) {
        dev->stopCapture();
        dev->clone();
    }
}

std::vector<std::string> NetworkAnalyzer::listInterfaces() {
    std::vector<std::string> interfaces;
    std::vector<pcpp::PcapLiveDevice*> devList = pcpp::PcapLiveDeviceList::getInstance().getPcapLiveDevicesList();
    for (auto& device : devList) {
        interfaces.push_back(device->getName());
    }
    return interfaces;
}

void NetworkAnalyzer::packetCallback(pcpp::RawPacket* packet, pcpp::PcapLiveDevice* dev, void* cookie) {
    NetworkAnalyzer* analyzer = static_cast<NetworkAnalyzer*>(cookie);
    QString info = QString("Packet captured: %1 bytes").arg(packet->getRawDataLen());
    QMetaObject::invokeMethod(analyzer, "packetCaptured", Qt::QueuedConnection, Q_ARG(QString, info));
}