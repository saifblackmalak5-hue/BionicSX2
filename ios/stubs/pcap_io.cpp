// SPDX-FileCopyrightText: 2002-2025 PCSX2 Dev Team
// SPDX-License-Identifier: GPL-3.0+
// BionicSX2 iOS stub for pcap_io.cpp

#include "pcap_io.h"
#include "DEV9.h"
#include "PacketReader/EthernetFrame.h"

// Stub implementations of pcap functions to resolve linker errors
extern "C" {
    struct pcap_t* pcap_open_live(const char*, int, int, int, char*) { return nullptr; }
    void pcap_close(pcap_t*) {}
    int pcap_compile(pcap_t*, bpf_program*, const char*, int, uint32_t) { return -1; }
    int pcap_setfilter(pcap_t*, bpf_program*) { return -1; }
    int pcap_sendpacket(pcap_t*, const uint8_t*, int) { return -1; }
    int pcap_dispatch(pcap_t*, int, void(*)(u_char*, const struct pcap_pkthdr*, const u_char*), u_char*) { return 0; }
    int pcap_next_ex(pcap_t*, struct pcap_pkthdr**, const u_char**) { return -1; }
    void pcap_freealldevs(pcap_if_t*) {}
    int pcap_findalldevs(pcap_if_t**, char*) { return -1; }
    pcap_t* pcap_open_offline(const char*, char*) { return nullptr; }
    int pcap_loop(pcap_t*, int, void(*)(u_char*, const struct pcap_pkthdr*, const u_char*), u_char*) { return -1; }
    void pcap_perror(pcap_t*, const char*) {}
    const char* pcap_geterr(pcap_t*) { return "pcap disabled on iOS"; }
    int pcap_setnonblock(pcap_t*, int, char*) { return -1; }
    int pcap_datalink(pcap_t*) { return 1; }
    const char* pcap_datalink_val_to_name(int) { return "null"; }
}
