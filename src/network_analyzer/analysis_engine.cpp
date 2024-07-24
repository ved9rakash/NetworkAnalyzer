#include "analysis_engine.h"

#include "pcapplusplus/RawPacket.h"
#include "QMetaObject"

NetworkAnalyzer::NetworkAnalyzer(const std::string& interface, QObject* parent) 
    : QObject(parent), interface(interface) {
    dev = pcpp::PcapLiveDeviceList::getInstance().getPcapLiveDeviceByName(interface);
    if (dev == nullptr) {
        throw std::runtime_error("Could not find network interface: " + interface);
    }
}

void NetworkAnalyzer::start() {
    if (!dev->open()) {
        throw std::runtime_error("Could not open device: " + interface);
    }
    dev->startCapture(packetCallback, this);
}

void NetworkAnalyzer::packetCallback(pcpp::RawPacket* packet, pcpp::PcapLiveDevice* dev, void* cookie) {
    NetworkAnalyzer* analyzer = static_cast<NetworkAnalyzer*>(cookie);
    pcpp::RawPacket* parsedPacket(packet);
    QString info = QString("Packet captured: %1 bytes").arg(parsedPacket->getRawDataLen());
    QMetaObject::invokeMethod(analyzer, "packetCaptured", Qt::QueuedConnection, Q_ARG(QString, info));
}