// BionicSX2 iOS stub
#include "GSMTLDeviceInfo.h"

GSMTLDevice GSMTLDevice::GetForMTLDevice(MRCOwned<id<MTLDevice>> dev)
{
    GSMTLDevice result;
    result.features.max_texsize = 16384;
    result.features.slow_color_compression = false;
    result.dev = std::move(dev);
    return result;
}

const char* to_string(GSMTLDevice::MetalVersion ver) { return "iOS"; }
