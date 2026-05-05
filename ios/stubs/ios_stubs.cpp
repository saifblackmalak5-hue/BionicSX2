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

// Forward declarations for PCSX2 types
namespace Pcsx2 {
    struct Config;
}
using Pcsx2Config = Pcsx2::Config;

struct SettingsInterface;
struct ProgressCallback;
struct Error;
struct AudioStreamParameters;

// WindowInfo forward declaration
struct WindowInfo {
    enum class Type { Surfaceless, Win32, X11, Wayland, MacOS, Android };
    Type type = Type::Surfaceless;
    void* display_connection = nullptr;
    void* window_handle = nullptr;
    void* surface_handle = nullptr;
    uint32_t surface_width = 0;
    uint32_t surface_height = 0;
    float surface_scale = 1.0f;
    float surface_refresh_rate = 0.0f;
    static std::optional<float> QueryRefreshRateForWindow(const WindowInfo& wi) { return std::nullopt; }
};

// Host namespace stubs
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
    bool RequestResetSettings(bool, bool, bool, bool) { return false; }
    void RequestResizeHostDisplay(int32_t, int32_t) {}
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
    uint32_t GetBaseUIntSettingValue(const char*, const char*, uint32_t d = 0) { return d; }
    float GetBaseFloatSettingValue(const char*, const char*, float d = 0.0f) { return d; }
    double GetBaseDoubleSettingValue(const char*, const char*, double d = 0.0) { return d; }
    std::vector<std::string> GetBaseStringListSetting(const char*, const char*) { return {}; }
    void SetBaseBoolSettingValue(const char*, const char*, bool) {}
    void SetBaseIntSettingValue(const char*, const char*, int) {}
    void SetBaseUIntSettingValue(const char*, const char*, uint32_t) {}
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
    uint32_t GetUIntSettingValue(const char*, const char*, uint32_t d = 0) { return d; }
    float GetFloatSettingValue(const char*, const char*, float d = 0.0f) { return d; }
    double GetDoubleSettingValue(const char*, const char*, double d = 0.0) { return d; }
    std::vector<std::string> GetStringListSetting(const char*, const char*) { return {}; }
    std::unique_lock<std::mutex> GetSettingsLock() { return std::unique_lock<std::mutex>(); }
    SettingsInterface* GetSettingsInterface() { return nullptr; }
    void SetDefaultUISettings(SettingsInterface& si) {}
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
                       const std::string& serial, uint32_t crc, uint32_t) {}
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

// CPU tick count for timing
uint64_t GetCPUTicks() {
    return (uint64_t)std::time(nullptr) * 1000ULL;
}

uint64_t GetTickFrequency() {
    return 1000ULL;
}

uint64_t GetPhysicalMemory() {
    return 8ULL * 1024 * 1024 * 1024;
}

uint64_t GetAvailablePhysicalMemory() {
    return 4ULL * 1024 * 1024 * 1024;
}

std::string GetOSVersionString() {
    return "iOS 16.0";
}

// Fix: GetValidDrive takes a non-const reference
std::string GetValidDrive(std::string& path) {
    return path;
}

struct DriveInfo {};
std::vector<DriveInfo> GetOpticalDriveList() {
    return {};
}

// CocoaTools stubs
namespace CocoaTools {
    std::string GetBundlePath() { return ""; }
    std::string GetResourcePath() { return ""; }
    void* CreateMetalLayer(WindowInfo*) { return nullptr; }
    void DestroyMetalLayer(WindowInfo*) {}
    float GetViewRefreshRate(const WindowInfo&) { return 60.0f; }
    std::string GetNonTranslocatedBundlePath() { return ""; }
}

namespace DarwinMisc {
    std::string GetCPUClasses() { return "arm64"; }
}

namespace FileSystem {
    void* OpenFDFileContent(const char* s) { return nullptr; }
}

// x86Emitter stubs (x86-specific, should not be called on ARM64)
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

namespace AudioStream {
    void* CreateOboeAudioStream(unsigned int, const AudioStreamParameters&, bool, Error*) {
        return nullptr;
    }
}

namespace InputManager {
    std::string ConvertHostKeyboardCodeToIcon(unsigned int) { return ""; }
    std::string ConvertHostKeyboardStringToCode(std::string_view) { return ""; }
    std::string ConvertHostKeyboardCodeToString(unsigned int) { return ""; }
}

extern "C" const char* SDL_SYS_GetPreferredLocales() {
    return "en_US";
}

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
