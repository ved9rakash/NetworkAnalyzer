#pragma once

#include "packet_capture.h"

#include <QObject>
#include <QMainWindow>
#include <pcapplusplus/RawPacket.h>

#include <string>
#include <vector>

class NetworkAnalyzer : public QObject {
    // Defining the Q_Object macro for enabling features like 
    // slots, signals and other metaobject capabilities.
    Q_OBJECT

public:
    NetworkAnalyzer(QObject* parent=nullptr);

    // Getting the list of interfaces
    static std::vector<std::string> listInterfaces();
    // Setting the required interface
    void setInterface(const std::string& interface);

    void start();
    void stop();

signals:
    void packetCaptured(const QString& info);

private:
    std::string interface;
    pcpp::PcapLiveDevice* dev;
    PacketHandler packetHandler;

    // Callback function for packet capture
    static void packetCallback(pcpp::RawPacket* packet, pcpp::PcapLiveDevice* dev, void* cookie);
};
