// iOS stubs for PCSX2 platform-specific functions
// These stubs provide minimal implementations for iOS where
// macOS-specific functionality is not available.
// NOTE: These use C++ linkage to match how PCSX2 calls them.

#include <string>
#include <vector>
#include <cstdint>
#include <ctime>
#include <cstddef>

// CPU tick count for timing - stub returns time in milliseconds
uint64_t GetCPUTicks() {
    return (uint64_t)std::time(nullptr) * 1000ULL;
}

// Tick frequency for timing calculations (milliseconds)
uint64_t GetTickFrequency() {
    return 1000ULL;
}

// Total physical memory - stub returns 8GB for iPad M4
uint64_t GetPhysicalMemory() {
    return 8ULL * 1024 * 1024 * 1024;
}

// Available physical memory - stub
uint64_t GetAvailablePhysicalMemory() {
    return 4ULL * 1024 * 1024 * 1024;
}

// OS version string
std::string GetOSVersionString() {
    return "iOS 16.0";
}

// Validate drive path (iOS uses sandbox paths)
std::string GetValidDrive(const std::string& path) {
    return path;
}

// Optical drive list (not available on iOS)
struct DriveInfo {};
std::vector<DriveInfo> GetOpticalDriveList() {
    return {};
}

// Metal device creation (stub - Metal disabled for iOS)
class GSDevice {};
GSDevice* MakeGSDeviceMTL() {
    return nullptr;
}

// Metal adapter list (stub)
std::string GetMetalAdapterList() {
    return "";
}

// CocoaTools stubs
namespace CocoaTools {
    std::string GetBundlePath() { return ""; }
    std::string GetResourcePath() { return ""; }
    void* CreateMetalLayer(void* wi) { return nullptr; }
    void DestroyMetalLayer(void* wi) {}
    float GetViewRefreshRate(const void* wi) { return 60.0f; }
    std::string GetNonTranslocatedBundlePath() { return ""; }
}

// DarwinMisc stubs
namespace DarwinMisc {
    std::string GetCPUClasses() { return "arm64"; }
}

// FileSystem stubs
namespace FileSystem {
    void* OpenFDFileContent(const char* s) { return nullptr; }
}

// x86Emitter stubs (these are x86-specific, should not be called on ARM64)
namespace x86Emitter {
    class xRegisterInt {};
    class SimdPrefix {};
    void SimdPrefix(unsigned char, unsigned short) {}
    void _g1_EmitOp(int, xRegisterInt const&, xRegisterInt const&) {}
    void xADD() {}
    void xMOV() {}
    void xSHL() {}
    void xMOV64() {}
    void xMOVDQA() {}
    void _xMovRtoR(xRegisterInt const&, xRegisterInt const&) {}
}

// AudioStream stub
class AudioStreamParameters;
class Error;
namespace AudioStream {
    void* CreateOboeAudioStream(unsigned int, const AudioStreamParameters&, bool, Error*) {
        return nullptr;
    }
}

// GSDeviceMTL stubs
class GSDeviceMTL {
public:
    void* GetSpinFence() { return nullptr; }
    void EndRenderPass() {}
    void* BeginRenderPass(void*, void*, int, void*, int) { return nullptr; }
    void* GetRenderCmdBuf() { return nullptr; }
    void* GetTextureUploadEncoder() { return nullptr; }
    void FlushEncodersForReadback() {}
    void* GetLateTextureUploadEncoder() { return nullptr; }
    void* GetRenderCmdBufWithoutCreate() { return nullptr; }
    void Allocate(void* ptr, unsigned long size) {}
};

// InputManager stubs
namespace InputManager {
    std::string ConvertHostKeyboardCodeToIcon(unsigned int) { return ""; }
    std::string ConvertHostKeyboardCodeToString(unsigned int) { return ""; }
}

// SDL stub for GetPreferredLocales
extern "C" const char* SDL_SYS_GetPreferredLocales() {
    return "en_US";
}
