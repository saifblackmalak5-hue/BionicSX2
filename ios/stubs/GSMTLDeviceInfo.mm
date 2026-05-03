// BionicSX2 iOS stub
#include "GSMTLDeviceInfo.h"

GSMTLDevice::GSMTLDevice(MRCOwned<id<MTLDevice>> dev)
    : dev(std::move(dev))
{
    features.max_texsize = 16384;
    features.slow_color_compression = false;
    features.unified_memory = true;
    features.texture_swizzle = true;
    features.framebuffer_fetch = false;
    features.primid = false;
    features.has_fast_half = true;
    features.shader_version = GSMTLDevice::MetalVersion::Metal23;
}

const char* to_string(GSMTLDevice::MetalVersion ver) { return "iOS"; }
