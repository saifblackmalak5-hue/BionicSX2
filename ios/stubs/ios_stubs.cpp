// iOS stubs for PCSX2 platform-specific functions
// These stubs provide minimal implementations for iOS where
// macOS-specific functionality is not available.

#include <string>
#include <vector>
#include <cstdint>
#include <ctime>

// CPU tick count for timing - stub returns time in milliseconds
extern "C" uint64_t GetCPUTicks() {
    return (uint64_t)std::time(nullptr) * 1000ULL;
}

// Tick frequency for timing calculations (milliseconds)
extern "C" uint64_t GetTickFrequency() {
    return 1000ULL;
}

// Total physical memory - stub returns 8GB for iPad M4
extern "C" uint64_t GetPhysicalMemory() {
    return 8ULL * 1024 * 1024 * 1024;
}

// Available physical memory - stub
extern "C" uint64_t GetAvailablePhysicalMemory() {
    return 4ULL * 1024 * 1024 * 1024;
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
