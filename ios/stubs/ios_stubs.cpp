// iOS stubs for PCSX2 platform-specific functions
// Auto-generated based on nm symbol analysis of libPCSX2.a

#include <string>
#include <string_view>
#include <vector>
#include <memory>
#include <mutex>
#include <functional>
#include <cstring>

// Forward declarations
struct SettingsInterface;
struct InputBindingKey;
struct GSTexture;
struct Pcsx2Config;
struct ProgressCallback;
struct BaseProgressCallback;

namespace Achievements { enum class LoginRequestReason; }

template<typename T> struct GSVector2T { T x, y; };

static const char DEFAULT_USER_AGENT[] = "BionicSX2/1.0";

// =====================
// SharedMemoryMappingArea
// =====================
struct SharedMemoryMappingArea {
    static SharedMemoryMappingArea* Create(size_t size);
    void* Map(void* baseaddr, size_t baseaddr_size, void* mapaddr, size_t mapaddr_size, int mode);
    void Unmap(void* ptr, size_t size);
    void Destroy();
    ~SharedMemoryMappingArea();
};
SharedMemoryMappingArea* SharedMemoryMappingArea::Create(size_t size) { return nullptr; }
void* SharedMemoryMappingArea::Map(void* baseaddr, size_t baseaddr_size, void* mapaddr, size_t mapaddr_size, int mode) { return nullptr; }
void SharedMemoryMappingArea::Unmap(void* ptr, size_t size) {}
void SharedMemoryMappingArea::Destroy() {}
SharedMemoryMappingArea::~SharedMemoryMappingArea() {}

// =====================
// GSCapture stubs
// =====================
namespace GSCapture {
    bool BeginCapture(float fps, GSVector2T<int> resolution, float aspect, std::string filename) { return false; }
    void DeliverAudioPacket(const short* data) {}
    void DeliverVideoFrame(GSTexture* tex) {}
    void EndCapture() {}
    void Flush() {}
    double GetElapsedTime() { return 0.0; }
    void* GetEncoderThreadHandle() { return nullptr; }
    std::string GetNextCaptureFileName() { return ""; }
    GSVector2T<int> GetSize() { return {0, 0}; }
    bool IsCapturing() { return false; }
    bool IsCapturingVideo() { return false; }
}

// =====================
// Host stubs
// =====================
namespace Host {
    // Settings
    bool GetBaseBoolSettingValue(const char* section, const char* key, bool default_value) { return default_value; }
    int GetBaseIntSettingValue(const char* section, const char* key, int default_value) { return default_value; }
    std::string GetBaseSmallStringSettingValue(const char* section, const char* key, const char* default_value) { return default_value ? default_value : ""; }
    std::vector<std::string> GetBaseStringListSetting(const char* section, const char* key) { return {}; }
    std::string GetBaseStringSettingValue(const char* section, const char* key, const char* default_value) { return default_value ? default_value : ""; }
    bool GetBoolSettingValue(const char* section, const char* key, bool default_value) { return default_value; }
    int GetIntSettingValue(const char* section, const char* key, int default_value) { return default_value; }
    std::string GetSmallStringSettingValue(const char* section, const char* key, const char* default_value) { return default_value ? default_value : ""; }
    std::vector<std::string> GetStringListSetting(const char* section, const char* key) { return {}; }
    std::string GetStringSettingValue(const char* section, const char* key, const char* default_value) { return default_value ? default_value : ""; }
    SettingsInterface* GetSettingsInterface() { return nullptr; }
    std::unique_lock<std::mutex> GetSettingsLock() { static std::mutex m; return std::unique_lock<std::mutex>(m); }
    bool ContainsBaseSettingValue(const char* section, const char* key) { return false; }
    void LoadSettings(SettingsInterface& si, std::unique_lock<std::mutex>& lock) {}
    void CommitBaseSettingChanges() {}
    void CheckForSettingsChanges(const Pcsx2Config& old_config) {}
    std::string GetHTTPUserAgent() { return DEFAULT_USER_AGENT; }

    // Display
    void* AcquireRenderWindow(bool recreate) { return nullptr; }
    void ReleaseRenderWindow() {}
    void BeginPresentFrame() {}
    bool IsFullscreen() { return false; }
    void SetFullscreen(bool fullscreen) {}
    void BeginTextInput() {}
    void EndTextInput() {}
    void SetMouseMode(bool relative, bool hide_cursor) {}

    // OSD Messages
    void AddOSDMessage(std::string message, float duration) {}
    void AddKeyedOSDMessage(std::string key, std::string message, float duration) {}
    void AddIconOSDMessage(std::string key, const char* icon, std::string_view message, float duration) {}
    void RemoveKeyedOSDMessage(std::string key) {}
    void ClearOSDMessages() {}

    // VM
    void OnVMStarting() {}
    void OnVMStarted() {}
    void OnVMPaused() {}
    void OnVMResumed() {}
    void OnVMDestroyed() {}
    void OnGameChanged(const std::string& path, const std::string& elf, const std::string& title, const std::string& serial, unsigned int disc_crc, unsigned int crc) {}
    void RequestVMShutdown(bool allow_confirm, bool allow_save_state, bool default_save_state) {}
    void RunOnCPUThread(std::function<void()> func, bool block) { func(); }
    void PumpMessagesOnCPUThread() {}

    // Save states
    void OnSaveStateLoading(std::string_view filename) {}
    void OnSaveStateLoaded(std::string_view filename, bool was_successful) {}
    void OnSaveStateSaved(std::string_view filename) {}

    // Input
    void OnInputDeviceConnected(std::string_view identifier, std::string_view device_name) {}
    void OnInputDeviceDisconnected(uint64_t key, std::string_view identifier) {}

    // UI
    bool InNoGUIMode() { return true; }
    bool LocaleCircleConfirm() { return false; }
    bool ConfirmMessage(std::string_view title, std::string_view message) { return false; }
    void ReportErrorAsync(std::string_view title, std::string_view message) {}
    void ReportInfoAsync(std::string_view title, std::string_view message) {}
    void CopyTextToClipboard(std::string_view text) {}
    void OpenURL(std::string_view url) {}
    bool ShouldPreferHostFileSelector() { return false; }
    void OpenHostFileSelectorAsync(std::string_view title, bool select_directory, std::function<void(std::string)> callback, std::vector<std::string> filters, std::string_view initial_directory) { callback(""); }
    std::string EnsureResourceSubdirectory(const char* name) { return ""; }

    // Game list
    void RefreshGameListAsync(bool invalidate_cache) {}
    void CancelGameListRefresh() {}
    void OnCoverDownloaderOpenRequested() {}
    void OnCreateMemoryCardOpenRequested() {}

    // Performance
    void OnPerformanceMetricsUpdated() {}

    // Request
    void RequestResizeHostDisplay(int width, int height) {}
    void RequestExitApplication(bool save_state) {}
    void RequestExitBigPicture() {}
    void RequestResetSettings(bool a, bool b, bool c, bool d, bool e) {}
    void SetDefaultUISettings(SettingsInterface& si) {}

    // Achievements
    void OnAchievementsRefreshed() {}
    void OnAchievementsLoginSuccess(const char* username, unsigned int points, unsigned int sc_points, unsigned int gold_points) {}
    void OnAchievementsLoginRequested(Achievements::LoginRequestReason reason) {}
    void OnAchievementsHardcoreModeChanged(bool enabled) {}

    // Progress
    std::unique_ptr<ProgressCallback> CreateHostProgressCallback() { return nullptr; }

    // Translation
    std::string TranslatePluralToString(const char* ctx, const char* msg, const char* plural, int count) { return count == 1 ? msg : plural; }

    namespace Internal {
        SettingsInterface* GetBaseSettingsLayer() { return nullptr; }
        SettingsInterface* GetInputSettingsLayer() { return nullptr; }
        void SetGameSettingsLayer(SettingsInterface* layer, std::unique_lock<std::mutex>& lock) {}
        void SetInputSettingsLayer(SettingsInterface* layer, std::unique_lock<std::mutex>& lock) {}
        size_t GetTranslatedStringImpl(std::string_view ctx, std::string_view msg, char* out_buf, size_t out_buf_size) {
            if (msg.size() <= out_buf_size) std::memcpy(out_buf, msg.data(), msg.size());
            return msg.size();
        }
    }
}

// HTTPDownloader stub
namespace HTTPDownloader {
    std::unique_ptr<void> Create(std::string user_agent = DEFAULT_USER_AGENT) { return nullptr; }
}
