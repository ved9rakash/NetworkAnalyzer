#include "analysis_engine.h"

#include <pcapplusplus/RawPacket.h>
#include <QMetaObject>
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
void NetworkAnalyzer::setInterface(const std::string& interface) {
    this->interface = interface;
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
    dev->startCapture(packetCallback, this);
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
    QString info = QString("Packet captured: %1 bytes").arg(packet->getRawDataLen());
    QMetaObject::invokeMethod(analyzer, "packetCaptured", Qt::QueuedConnection, Q_ARG(QString, info));
}