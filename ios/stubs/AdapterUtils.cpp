// BionicSX2 iOS stub for DEV9/AdapterUtils
#include "AdapterUtils.h"
#include <vector>
#include <string>

namespace AdapterUtils
{
    std::vector<Adapter> GetAdapters() { return {}; }
    std::optional<Adapter> GetAdapterAuto() { return std::nullopt; }
    bool GetAdapterIPV4(const Adapter& adapter, IP_ADAPTER_UNICAST_ADDRESS_LH* info) { return false; }
    bool GetAdapterIPV4Netmask(const Adapter& adapter, IP_ADAPTER_UNICAST_ADDRESS_LH* info) { return false; }
    std::optional<std::vector<u8>> GetAdapterMAC(const Adapter& adapter) { return std::nullopt; }
    std::optional<IP_ADAPTER_UNICAST_ADDRESS_LH> GetAdapterGateway(const Adapter& adapter) { return std::nullopt; }
}
