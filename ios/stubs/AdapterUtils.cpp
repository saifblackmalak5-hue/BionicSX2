// BionicSX2 iOS stub for DEV9/AdapterUtils
#include "AdapterUtils.h"

namespace AdapterUtils
{
    u16 ReadAddressFamily(const sockaddr* unknownAddr) { return 0; }
    Adapter* GetAllAdapters(AdapterBuffer* buffer) { return nullptr; }
    bool GetAdapter(const std::string& name, Adapter* adapter, AdapterBuffer* buffer) { return false; }
    bool GetAdapterAuto(Adapter* adapter, AdapterBuffer* buffer) { return false; }
    std::optional<PacketReader::MAC_Address> GetAdapterMAC(const Adapter* adapter) { return std::nullopt; }
    std::optional<PacketReader::IP::IP_Address> GetAdapterIP(const Adapter* adapter) { return std::nullopt; }
    std::vector<PacketReader::IP::IP_Address> GetGateways(const Adapter* adapter) { return {}; }
    std::vector<PacketReader::IP::IP_Address> GetDNS(const Adapter* adapter) { return {}; }
}
