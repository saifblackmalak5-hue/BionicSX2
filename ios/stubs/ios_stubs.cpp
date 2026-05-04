// iOS stubs for PCSX2 platform-specific functions
// These stubs provide minimal implementations for iOS where
// macOS-specific functionality is not available.

#include <string>
#include <vector>
#include <cstdint>
#include <mach/mach.h>
#include <mach/mach_host.h>
#include <sys/sysctl.h>

// CPU tick count for timing
extern "C" uint64_t GetCPUTicks() {
    return mach_absolute_time();
}

// Tick frequency for timing calculations
extern "C" uint64_t GetTickFrequency() {
    mach_timebase_info_data_t timebase;
    mach_timebase_info(&timebase);
    return 1000000000ULL * timebase.denom / timebase.numer;
}

// Total physical memory
extern "C" uint64_t GetPhysicalMemory() {
    int mib[2] = {CTL_HW, HW_MEMSIZE};
    uint64_t memsize = 0;
    size_t len = sizeof(memsize);
    sysctl(mib, 2, &memsize, &len, NULL, 0);
    return memsize;
}

// Available physical memory
extern "C" uint64_t GetAvailablePhysicalMemory() {
    vm_statistics_data_t vm_stats;
    mach_msg_type_number_t count = HOST_VM_INFO_COUNT;
    host_statistics(mach_host_self(), HOST_VM_INFO, (host_info_t)&vm_stats, &count);
    return vm_stats.free_count * PAGE_SIZE;
}

// OS version string
extern "C" std::string GetOSVersionString() {
    return "iOS 16.0";
}

// Validate drive path (iOS uses sandbox paths)
extern "C" std::string GetValidDrive(const std::string& path) {
    return path;
}

// Optical drive list (not available on iOS)
struct DriveInfo {};
extern "C" std::vector<DriveInfo> GetOpticalDriveList() {
    return {};
}

// Metal device creation (stub - Metal disabled for iOS)
class GSDevice {};
extern "C" GSDevice* MakeGSDeviceMTL() {
    return nullptr;
}

// Metal adapter list (stub)
extern "C" std::string GetMetalAdapterList() {
    return "";
}
