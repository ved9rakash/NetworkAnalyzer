#include <pcap.h>
#include <netinet/in.h>
#include <netinet/if_ether.h>

#include <iostream>

void packet_handler(u_char *userData, const struct pcap_pkthdr *pkthdr, const u_char *packet) {
    // Do something with the packet
    const struct ether_header *eth_header;
    eth_header = (struct ether_header *) packet;

    if (ntohs(eth_header->ether_type) == ETHERTYPE_IP) {
        std::cout << "IP packet" << std::endl;
        // Further processing of the packet
    } else if (ntohs(eth_header->ether_type) == ETHERTYPE_ARP) {
        std::cout << "ARP packet" << std::endl;
        // Further processing of the packet
    } else {
        std::cout << "Other packet type" << std::endl;
        // Other processing
    }
}


int main() {
    char errbuf[PCAP_ERRBUF_SIZE];
    pcap_if_t *interfaces, *temp;
    int i = 0;

    // Find available devices for capturing
    if (pcap_findalldevs(&interfaces, errbuf) == -1) {
        std::cerr << "Error in pcap_findalldevs: " << errbuf << std::endl;
        return 1;
    }

    // Print available devices
    std::cout << "Available Devices are :" << std::endl;
    for (temp = interfaces; temp; temp = temp->next) {
        std::cout << ++i << ": " << temp->name << std::endl;
        if (temp->description)
            std::cout << " (" << temp->description << ")" << std::endl;
        else
            std::cout << " (No description available)" << std::endl;
    }

    // Assume we want to use the first available device. Adjust as needed.
    if (interfaces == nullptr) {
        std::cerr << "No devices found. Make sure you have the necessary permissions." << std::endl;
        return 1;
    }

    // Open the device for capturing
    pcap_t *handle = pcap_open_live(interfaces->name, BUFSIZ, 1, 1000, errbuf);
    if (handle == nullptr) {
        std::cerr << "Couldn't open device " << interfaces->name << ": " << errbuf << std::endl;
        return 1;
    }

    // Free the device list
    pcap_freealldevs(interfaces);

    // The actual packet capture loop
    pcap_loop(handle, 0, packet_handler, nullptr);

    // Close the handle
    pcap_close(handle);
    return 0;
}
