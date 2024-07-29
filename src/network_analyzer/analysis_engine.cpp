#include "analysis_engine.h"

#include <pcapplusplus/IPv4Layer.h>
#include <pcapplusplus/TcpLayer.h>
#include <pcapplusplus/UdpLayer.h>
#include <pcapplusplus/IcmpLayer.h>

#include <pcapplusplus/RawPacket.h>
#include <QMetaObject>
#include <QDateTime>
#include "pcapplusplus/PcapLiveDeviceList.h"
#include <pcapplusplus/PcapLiveDevice.h>

#include <stdexcept>
#include <vector>

NetworkAnalyzer::NetworkAnalyzer(QObject* parent)
    : QObject(parent), dev(nullptr) {}

// Getting all the network interfaces
std::vector<std::string> NetworkAnalyzer::listInterfaces() {
    // Get the list of all available devices and 
    // putting it in interfaces vector and returning it.
    std::vector<std::string> interfaces;
    std::vector<pcpp::PcapLiveDevice*> devList = pcpp::PcapLiveDeviceList::getInstance().getPcapLiveDevicesList();
    for (auto& device : devList) {
        interfaces.push_back(device->getName());
    }
    return interfaces;
}

// Setting the required interface which is passed to 
// the function and handling exception.
void NetworkAnalyzer::setInterface(const std::string& interfaces) {
    this->interface = interfaces;
    dev = pcpp::PcapLiveDeviceList::getInstance().getPcapLiveDeviceByName(interface);
    if (dev == nullptr) {
        throw std::runtime_error("Could not find the network interface");
    }
}

// Starting the packet capture.
void NetworkAnalyzer::start() {
    if (dev == nullptr) {
        throw std::runtime_error("Network interface not set.");
    }
    if (!dev->open()) {
        throw std::runtime_error("Could not open device: " + interface);
    }
    dev->setFilter("ip"); // You can set filters as needed
    dev->startCapture(packetCallback, this);
    // dev->startCapture(packetCallback, this);
}

// Stoping the packet capture.
void NetworkAnalyzer::stop() {
    if (dev != nullptr) {
        dev->stopCapture();
        dev->clone();
    }
}

// Callback function for packet capture
void NetworkAnalyzer::packetCallback(pcpp::RawPacket* packet, pcpp::PcapLiveDevice* dev, void* cookie) {
    NetworkAnalyzer* analyzer = static_cast<NetworkAnalyzer*>(cookie);
    pcpp::Packet parsedPacket(packet);

    QString srcIp, dstIp, protocol;
    bool isOutgoing = false;
    int packetLength = packet->getRawDataLen();

    if (parsedPacket.isPacketOfType(pcpp::IPv4)) {
        pcpp::IPv4Layer* ipLayer = parsedPacket.getLayerOfType<pcpp::IPv4Layer>();
        srcIp = QString::fromStdString(ipLayer->getSrcIPAddress().toString());
        dstIp = QString::fromStdString(ipLayer->getDstIPAddress().toString());

        if (parsedPacket.isPacketOfType(pcpp::TCP)) {
            protocol = "TCP";
        } else if (parsedPacket.isPacketOfType(pcpp::TCP)) {
            protocol = "TCP";
        } else if (parsedPacket.isPacketOfType(pcpp::UDP)) {
            protocol = "UDP";
        } else if (parsedPacket.isPacketOfType(pcpp::ICMP)) {
            protocol = "ICMP";
        } else {
            protocol = "Other";
        }

        // Determine if the packet is outgoing
        if (ipLayer->getSrcIPAddress().toString() == dev->getIPv4Address().toString()) {
            isOutgoing = true;
        } 

        QString timestamp = QDateTime::currentDateTime().toString("yyyy-MM-dd HH:mm:ss");
        QString info = QString("%1, %2, %3, %4, %5 bytes")
            .arg(timestamp)
            .arg(srcIp)
            .arg(dstIp)
            .arg(protocol)
            .arg(packetLength);

        QMetaObject::invokeMethod(analyzer, "packetCaptured", Qt::QueuedConnection, Q_ARG(QString, info), Q_ARG(int, packetLength), Q_ARG(bool, isOutgoing));
    }
}