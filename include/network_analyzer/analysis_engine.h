#pragma once

#include "packet_capture.h"

#include "QObject"
#include "QMainWindow"
#include "pcapplusplus/RawPacket.h"
#include "pcapplusplus/PcapLiveDevice.h"
#include "pcapplusplus/PcapLiveDeviceList.h"

#include <string>
#include <vector>

class NetworkAnalyzer : public QObject {
    Q_OBJECT

public:
    NetworkAnalyzer(QObject* parent=nullptr);
    void start();
    void stop();

    void setInterface(const std::string& interface);
    static std::vector<std::string> listInterfaces();

signals:
    void packetCaptured(const QString& info);

private:
    std::string interface;
    pcpp::PcapLiveDevice* dev;
    PacketHandler packetHandler;


    static void packetCallback(pcpp::RawPacket* packet, pcpp::PcapLiveDevice* dev, void* cookie);
};
