#pragma once

#include "packet_capture.h"

#include "QObject"
#include "QMainWindow"
#include "pcapplusplus/RawPacket.h"
#include "pcapplusplus/PcapLiveDevice.h"
#include "pcapplusplus/PcapLiveDeviceList.h"

#include <string>

class NetworkAnalyzer : public QObject {
    Q_OBJECT

public:
    NetworkAnalyzer(const std::string& interface, QObject* parent=nullptr);
    void start();

signals:
    void packetCaptured(const QString& info);

private:
    std::string interface;
    pcpp::PcapLiveDevice* dev;
    PacketHandler packetHandler;

    static void packetCallback(pcpp::RawPacket* packet, pcpp::PcapLiveDevice* dev, void* cookie);
};
