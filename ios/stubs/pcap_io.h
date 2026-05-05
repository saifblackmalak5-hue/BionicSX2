// SPDX-FileCopyrightText: 2002-2025 PCSX2 Dev Team
// SPDX-License-Identifier: GPL-3.0+
// BionicSX2 iOS stub for pcap_io.h

#pragma once

#include "net.h"
#include "PacketReader/MAC_Address.h"

// Stub out pcap types for iOS
struct pcap_t;
struct pcap_if_t;
struct bpf_program;

class PCAPAdapter : public NetAdapter
{
public:
	PCAPAdapter() = default;
	virtual bool blocks() { return false; }
	virtual bool isInitialised() { return false; }
	virtual bool recv(NetPacket* pkt) { return false; }
	virtual bool send(NetPacket* pkt) { delete pkt; return false; }
	virtual void reloadSettings() {}
	virtual ~PCAPAdapter() = default;
	static std::vector<AdapterEntry> GetAdapters() { return {}; }
	static AdapterOptions GetAdapterOptions() { return {}; }
};
