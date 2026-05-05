// iOS stubs for PCSX2 platform-specific functions
// These stubs provide minimal implementations for iOS where
// macOS-specific functionality is not available.

#include <string>
#include <vector>
#include <cstdint>
#include <ctime>
#include <cstddef>
#include <optional>
#include <functional>
#include <mutex>
#include <memory>

// Include necessary PCSX2 headers for proper type definitions
#include "common/Pcsx2Defs.h"
#include "common/WindowInfo.h"

// Forward declarations for types we need
struct SettingsInterface;
struct ProgressCallback;
struct Error;
struct AudioStreamParameters;

// Host namespace stubs - from Host.h
namespace Host {
    const char* TranslateToCString(const std::string_view, const std::string_view) { return ""; }
    std::string_view TranslateToStringView(const std::string_view, const std::string_view) { return ""; }
    std::string TranslateToString(const std::string_view, const std::string_view) { return ""; }
    std::string TranslatePluralToString(const char*, const char*, const char*, int) { return ""; }
    void ClearTranslationCache() {}
    void AddOSDMessage(std::string, float) {}
    void AddKeyedOSDMessage(std::string, std::string, float) {}
    void AddIconOSDMessage(std::string, const char*, const std::string_view, float) {}
    void RemoveKeyedOSDMessage(std::string) {}
    void ClearOSDMessages() {}
    void ReportInfoAsync(const std::string_view, const std::string_view) {}
    void ReportFormattedInfoAsync(const std::string_view, const char*, ...) {}
    void ReportErrorAsync(const std::string_view, const std::string_view) {}
    void ReportFormattedErrorAsync(const std::string_view, const char*, ...) {}
    bool ConfirmMessage(const std::string_view, const std::string_view) { return false; }
    bool ConfirmFormattedMessage(const std::string_view, const char*, ...) { return false; }
    bool InBatchMode() { return true; }
    bool InNoGUIMode() { return true; }
    void OpenURL(const std::string_view) {}
    bool CopyTextToClipboard(const std::string_view) { return false; }
    bool EnsureResourceSubdirectory(const char*) { return true; }
    bool RequestResetSettings(bool, bool, bool, bool, bool) { return false; }
    void RequestResizeHostDisplay(s32, s32) {}
    void RunOnCPUThread(std::function<void()>, bool) {}
    void RefreshGameListAsync(bool) {}
    void CancelGameListRefresh() {}
    void RequestVMShutdown(bool, bool, bool) {}
    std::string GetHTTPUserAgent() { return "BionicSX2/1.0"; }
    std::string GetBaseStringSettingValue(const char*, const char*, const char* d = "") { return d; }
    std::string GetBaseSmallStringSettingValue(const char*, const char*, const char* d = "") { return d; }
    std::string GetBaseTinyStringSettingValue(const char*, const char*, const char* d = "") { return d; }
    bool GetBaseBoolSettingValue(const char*, const char*, bool d = false) { return d; }
    int GetBaseIntSettingValue(const char*, const char*, int d = 0) { return d; }
    uint GetBaseUIntSettingValue(const char*, const char*, uint d = 0) { return d; }
    float GetBaseFloatSettingValue(const char*, const char*, float d = 0.0f) { return d; }
    double GetBaseDoubleSettingValue(const char*, const char*, double d = 0.0) { return d; }
    std::vector<std::string> GetBaseStringListSetting(const char*, const char*) { return {}; }
    void SetBaseBoolSettingValue(const char*, const char*, bool) {}
    void SetBaseIntSettingValue(const char*, const char*, int) {}
    void SetBaseUIntSettingValue(const char*, const char*, uint) {}
    void SetBaseFloatSettingValue(const char*, const char*, float) {}
    void SetBaseStringSettingValue(const char*, const char*, const char*) {}
    void SetBaseStringListSettingValue(const char*, const char*, const std::vector<std::string>&) {}
    bool AddBaseValueToStringList(const char*, const char*, const char*) { return false; }
    bool RemoveBaseValueFromStringList(const char*, const char*, const char*) { return false; }
    bool ContainsBaseSettingValue(const char*, const char*) { return false; }
    void RemoveBaseSettingValue(const char*, const char*) {}
    void CommitBaseSettingChanges() {}
    std::string GetStringSettingValue(const char*, const char*, const char* d = "") { return d; }
    bool GetBoolSettingValue(const char*, const char*, bool d = false) { return d; }
    int GetIntSettingValue(const char*, const char*, int d = 0) { return d; }
    uint GetUIntSettingValue(const char*, const char*, uint d = 0) { return d; }
    float GetFloatSettingValue(const char*, const char*, float d = 0.0f) { return d; }
    double GetDoubleSettingValue(const char*, const char*, double d = 0.0) { return d; }
    std::vector<std::string> GetStringListSetting(const char*, const char*) { return {}; }
    std::unique_lock<std::mutex> GetSettingsLock() { return std::unique_lock<std::mutex>(); }
    SettingsInterface* GetSettingsInterface() { return nullptr; }
    void SetDefaultUISettings(SettingsInterface&) {}
    std::unique_ptr<ProgressCallback> CreateHostProgressCallback() { return nullptr; }

    // From VMManager.h namespace Host
    void LoadSettings(SettingsInterface&, std::unique_lock<std::mutex>&) {}
    void CheckForSettingsChanges(const Pcsx2Config&) {}
    void OnVMStarting() {}
    void OnVMStarted() {}
    void OnVMDestroyed() {}
    void OnVMPaused() {}
    void OnVMResumed() {}
    void OnPerformanceMetricsUpdated() {}
    void OnSaveStateLoading(std::string_view) {}
    void OnSaveStateLoaded(std::string_view, bool) {}
    void OnSaveStateSaved(std::string_view) {}
    void OnGameChanged(const std::string& title, const std::string& elf, const std::string& path,
                       const std::string& serial, u32 crc, u32) {}
    void PumpMessagesOnCPUThread() {}

    // From GS.h namespace Host
    std::optional<WindowInfo> AcquireRenderWindow(bool) { return std::nullopt; }
    void BeginPresentFrame() {}
    void ReleaseRenderWindow() {}
    bool IsFullscreen() { return false; }
    void SetFullscreen(bool) {}
    void OnCaptureStarted(const std::string&) {}
    void OnCaptureStopped() {}

    // From ImGuiManager.h namespace Host
    void BeginTextInput() {}
    void EndTextInput() {}

    // From InputManager.h namespace Host
    std::optional<WindowInfo> GetTopLevelWindowInfo() { return std::nullopt; }
    void OnInputDeviceConnected(const std::string_view, const std::string_view) {}
    void OnInputDeviceDisconnected(const void*, const std::string_view) {}
    void SetMouseMode(bool, bool) {}

    // From Achievements.h namespace Host
    void OnAchievementsRefreshed() {}

    // Additional Host functions from undefined symbols
    bool LocaleCircleConfirm() { return false; }
    void RequestExitApplication(bool) {}
    void RequestExitBigPicture() {}
} // namespace Host

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
// Note: CDVDdiscReader.cpp calls GetValidDrive with a non-const reference
std::string GetValidDrive(std::string& path) {
    return path;
}

// Optical drive list (not available on iOS)
struct DriveInfo {};
std::vector<DriveInfo> GetOpticalDriveList() {
    return {};
}

// CocoaTools stubs - use WindowInfo* instead of void*
namespace CocoaTools {
    std::string GetBundlePath() { return ""; }
    std::string GetResourcePath() { return ""; }
    void* CreateMetalLayer(WindowInfo*) { return nullptr; }
    void DestroyMetalLayer(WindowInfo*) {}
    float GetViewRefreshRate(const WindowInfo&) { return 60.0f; }
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
// Only used if x86 code is incorrectly compiled for ARM64
namespace x86Emitter {
    class xRegisterInt {};
    class SimdPrefix {};
    void SimdPrefix(unsigned char, unsigned short) {}
    void _g1_EmitOp(int, const xRegisterInt&, const xRegisterInt&) {}
    void xADD() {}
    void xMOV() {}
    void xSHL() {}
    void xMOV64() {}
    void xMOVDQA() {}
    void _xMovRtoR(const xRegisterInt&, const xRegisterInt&) {}
}

// AudioStream stub
namespace AudioStream {
    void* CreateOboeAudioStream(unsigned int, const AudioStreamParameters&, bool, Error*) {
        return nullptr;
    }
}

// InputManager stubs
namespace InputManager {
    std::string ConvertHostKeyboardCodeToIcon(unsigned int) { return ""; }
    std::string ConvertHostKeyboardStringToCode(std::string_view) { return ""; }
    std::string ConvertHostKeyboardCodeToString(unsigned int) { return ""; }
}

// SDL stub for GetPreferredLocales
extern "C" const char* SDL_SYS_GetPreferredLocales() {
    return "en_US";
}

// PageFaultHandler stub
namespace PageFaultHandler {
    bool Install(Error*) { return false; }
}

// SharedMemoryMappingArea stubs
class SharedMemoryMappingArea {
public:
    void* Create(unsigned long) { return nullptr; }
    void* Map(void*, unsigned long, void*, unsigned long, void*) { return nullptr; }
    void Unmap(void*, unsigned long) {}
    void Destroy() {}
};

// GSDeviceMTL stubs (Metal disabled for iOS)
class GSDeviceMTL {
public:
    void* GetSpinFence() { return nullptr; }
    void EndRenderPass() {}
    void* BeginRenderPass(void*, void*, int, void*, int, void*, int) { return nullptr; }
    void* GetRenderCmdBuf() { return nullptr; }
    void* GetTextureUploadEncoder() { return nullptr; }
    void FlushEncodersForReadback() {}
    void* GetLateTextureUploadEncoder() { return nullptr; }
    void* GetRenderCmdBufWithoutCreate() { return nullptr; }
    void Allocate(void*, unsigned long) {}
};
