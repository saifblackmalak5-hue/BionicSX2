// BionicSX2 iOS stub for DEV9/AdapterUtils
#include "AdapterUtils.h"

namespace AdapterUtils
{
    Adapter* GetAllAdapters(AdapterBuffer* buffer, bool includeHidden) { return nullptr; }
    Adapter* GetAllAdapters(AdapterBuffer* buffer) { return nullptr; }
    bool GetAdapter(const std::string& name, Adapter* adapter, AdapterBuffer* buffer) { return false; }
    bool GetAdapterAuto(Adapter* adapter, AdapterBuffer* buffer) { return false; }
    std::optional<PacketReader::MAC_Address> GetAdapterMAC(const Adapter* adapter) { return std::nullopt; }
    std::optional<PacketReader::IP_Address> GetAdapterIP(const Adapter* adapter) { return std::nullopt; }
    std::optional<PacketReader::IP_Address> GetAdapterNetmask(const Adapter* adapter) { return std::nullopt; }
    std::optional<PacketReader::IP_Address> GetAdapterGateway(const Adapter* adapter) { return std::nullopt; }
    std::optional<PacketReader::IP_Address> GetAdapterDNS1(const Adapter* adapter) { return std::nullopt; }
    std::optional<PacketReader::IP_Address> GetAdapterDNS2(const Adapter* adapter) { return std::nullopt; }
}
