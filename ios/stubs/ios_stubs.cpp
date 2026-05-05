// iOS stubs for PCSX2 platform-specific functions
// Complete set of stubs to resolve all linking issues at once

#include <string>
#include <vector>
#include <cstdint>
#include <ctime>
#include <cstddef>
#include <optional>
#include <functional>
#include <mutex>
#include <memory>
#include <string_view>
#include <cstring>
#include <time.h>

// Define PCSX2 types
using u8 = uint8_t;
using u16 = uint16_t;
using u32 = uint32_t;
using u64 = uint64_t;
using s8 = int8_t;
using s16 = int16_t;
using s32 = int32_t;
using s64 = int64_t;
using uint = unsigned int;

static const char DEFAULT_USER_AGENT[] = "BionicSX2/1.0";

// Forward declarations
struct Pcsx2Config;
struct SettingsInterface;
struct ProgressCallback;
struct Error;
struct AudioStreamParameters;

// WindowInfo
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

// InputBindingKey
union InputBindingKey {
    u64 bits;
    struct {
        u32 source_type : 4;
        u32 source_index : 8;
        u32 source_subtype : 3;
        u32 modifier : 2;
        u32 invert : 1;
        u32 needs_migration : 1;
        u32 unused : 13;
        u32 data;
    };
};

// HotkeyInfo
struct HotkeyInfo {
    const char* name = nullptr;
    const char* category = nullptr;
    const char* display_name = nullptr;
    void (*handler)(s32 pressed) = nullptr;
};

// GSTexture
struct GSTexture {};

// GSVector2i
struct GSVector2i { int x, y; GSVector2i() : x(0), y(0) {} };
// GSVector2T template (used by GSCapture)
template<typename T>
struct GSVector2T { T x, y; };

// PageProtectionMode
class PageProtectionMode {
public:
    bool CanRead() const { return false; }
    bool CanWrite() const { return false; }
    bool CanExecute() const { return false; }
    bool IsNone() const { return true; }
};

// Achievements
namespace Achievements { enum LoginRequestReason {}; }

// InputManager types
enum class InputSourceType : u32 { Keyboard, Pointer, SDL, Count };
enum class InputPointerAxis : u8 { X, Y, WheelX, WheelY, Count };
struct InputBindingInfo { enum Type { Button, Axis, Motor }; };
struct GenericInputBinding {};
struct InputSource {};

// Host namespace declarations
namespace Host {
    // OSD
    void AddOSDMessage(std::string message, float duration = 2.0f);
    void AddKeyedOSDMessage(std::string key, std::string message, float duration = 2.0f);
    void AddIconOSDMessage(std::string key, const char* icon, const std::string_view message, float duration = 2.0f);
    void RemoveKeyedOSDMessage(std::string key);
    void ClearOSDMessages();

    // Translation
    const char* TranslateToCString(const std::string_view context, const std::string_view msg);
    std::string_view TranslateToStringView(const std::string_view context, const std::string_view msg);
    std::string TranslateToString(const std::string_view context, const std::string_view msg);
    std::string TranslatePluralToString(const char* context, const char* msg, const char* disambiguation, int count);
    void ClearTranslationCache();

    // Reports
    void ReportInfoAsync(const std::string_view title, const std::string_view message);
    void ReportFormattedInfoAsync(const std::string_view title, const char* format, ...);
    void ReportErrorAsync(const std::string_view title, const std::string_view message);
    void ReportFormattedErrorAsync(const std::string_view title, const char* format, ...);
    bool ConfirmMessage(const std::string_view title, const std::string_view message);
    bool ConfirmFormattedMessage(const std::string_view title, const char* format, ...);

    // Mode
    bool InBatchMode();
    bool InNoGUIMode();

    // URL/Clipboard
    void OpenURL(const std::string_view url);
    bool CopyTextToClipboard(const std::string_view text);

    // Resources
    bool EnsureResourceSubdirectory(const char* relative_path);

    // Settings
    bool RequestResetSettings(bool folders, bool core, bool controllers, bool hotkeys, bool ui);
    void SetDefaultUISettings(SettingsInterface& si);
    void CommitBaseSettingChanges();

    // Display
    void RequestResizeHostDisplay(s32 width, s32 height);

    // CPU thread
    void RunOnCPUThread(std::function<void()> function, bool block = false);

    // Game list
    void RefreshGameListAsync(bool invalidate_cache);
    void CancelGameListRefresh();

    // VM
    void RequestVMShutdown(bool allow_confirm, bool allow_save_state, bool default_save_state);

    // HTTP
    std::string GetHTTPUserAgent();

    // Settings interface
    std::unique_lock<std::mutex> GetSettingsLock();
    SettingsInterface* GetSettingsInterface();

    // Settings accessors - Base
    std::string GetBaseStringSettingValue(const char* section, const char* key, const char* default_value = "");
    bool GetBaseBoolSettingValue(const char* section, const char* key, bool default_value = false);
    int GetBaseIntSettingValue(const char* section, const char* key, int default_value = 0);
    uint GetBaseUIntSettingValue(const char* section, const char* key, uint default_value = 0);
    float GetBaseFloatSettingValue(const char* section, const char* key, float default_value = 0.0f);
    double GetBaseDoubleSettingValue(const char* section, const char* key, double default_value = 0.0);
    std::vector<std::string> GetBaseStringListSetting(const char* section, const char* key);
    void SetBaseBoolSettingValue(const char* section, const char* key, bool value);
    void SetBaseIntSettingValue(const char* section, const char* key, int value);
    void SetBaseUIntSettingValue(const char* section, const char* key, uint value);
    void SetBaseFloatSettingValue(const char* section, const char* key, float value);
    void SetBaseStringSettingValue(const char* section, const char* key, const char* value);
    void SetBaseStringListSettingValue(const char* section, const char* key, const std::vector<std::string>& values);
    bool AddBaseValueToStringList(const char* section, const char* key, const char* value);
    bool RemoveBaseValueFromStringList(const char* section, const char* key, const char* value);
    bool ContainsBaseSettingValue(const char* section, const char* key);
    void RemoveBaseSettingValue(const char* section, const char* key);

    // Settings accessors - Regular
    std::string GetStringSettingValue(const char* section, const char* key, const char* default_value = "");
    bool GetBoolSettingValue(const char* section, const char* key, bool default_value = false);
    int GetIntSettingValue(const char* section, const char* key, int default_value = 0);
    uint GetUIntSettingValue(const char* section, const char* key, uint default_value = 0);
    float GetFloatSettingValue(const char* section, const char* key, float default_value = 0.0f);
    double GetDoubleSettingValue(const char* section, const char* key, double default_value = 0.0);
    std::vector<std::string> GetStringListSetting(const char* section, const char* key);

    // Progress callback
    std::unique_ptr<ProgressCallback> CreateHostProgressCallback();

    // File selector
    bool ShouldPreferHostFileSelector();
    void OpenHostFileSelectorAsync(std::string_view title, bool select_directory,
                                   std::function<void(const std::string&)> callback,
                                   std::vector<std::string> filters, std::string_view initial_directory);

    // Locale
    bool LocaleCircleConfirm();

    // Render window
    void* AcquireRenderWindow(bool recreate);
    void ReleaseRenderWindow();
    void BeginPresentFrame();

    // Text input
    void BeginTextInput();
    void EndTextInput();

    // Fullscreen
    bool IsFullscreen();
    void SetFullscreen(bool fullscreen);

    // Mouse mode
    void SetMouseMode(bool relative_mode, bool hide_cursor);

    // Window info
    std::optional<WindowInfo> GetTopLevelWindowInfo();

    // Input device callbacks
    void OnInputDeviceConnected(const std::string_view identifier, const std::string_view device_name);
    void OnInputDeviceDisconnected(const InputBindingKey key, const std::string_view identifier);

    // VMManager.h Host namespace
    void LoadSettings(SettingsInterface& si, std::unique_lock<std::mutex>& lock);
    void CheckForSettingsChanges(const Pcsx2Config& old_config);
    void OnVMStarting();
    void OnVMStarted();
    void OnVMDestroyed();
    void OnVMPaused();
    void OnVMResumed();
    void OnPerformanceMetricsUpdated();
    void OnSaveStateLoading(std::string_view filename);
    void OnSaveStateLoaded(std::string_view filename, bool was_successful);
    void OnSaveStateSaved(std::string_view filename);
    void OnGameChanged(const std::string& title, const std::string& elf_override, const std::string& disc_path,
                      const std::string& disc_serial, u32 disc_crc, u32 current_crc);
    void PumpMessagesOnCPUThread();

    // Achievements
    void OnAchievementsRefreshed();
    void OnAchievementsLoginSuccess(const char* display_name, u32 points, u32 sc_points, u32 unread_messages);
    void OnAchievementsLoginRequested(Achievements::LoginRequestReason reason);
    void OnAchievementsHardcoreModeChanged(bool enabled);
    void OnCoverDownloaderOpenRequested();
    void OnCreateMemoryCardOpenRequested();

    // Exit
    void RequestExitBigPicture();
    void RequestExitApplication(bool allow_confirm);

    // Internal
    namespace Internal {
        s32 GetTranslatedStringImpl(const std::string_view context, const std::string_view msg, char* tbuf, size_t tbuf_space);
        void EnsureAndroidResourceSubdirCopied(const char* relative_path);
        SettingsInterface* GetBaseSettingsLayer();
        SettingsInterface* GetGameSettingsLayer();
        SettingsInterface* GetInputSettingsLayer();
        void SetBaseSettingsLayer(SettingsInterface* sif);
        void SetGameSettingsLayer(SettingsInterface* sif, std::unique_lock<std::mutex>& settings_lock);
        void SetInputSettingsLayer(SettingsInterface* sif, std::unique_lock<std::mutex>& settings_lock);
    }
}

// ============================================================================
// Out-of-line definitions for Host namespace
// ============================================================================

// Translation
const char* Host::TranslateToCString(const std::string_view context, const std::string_view msg) {
    static char empty = '\0';
    return &empty;
}
std::string_view Host::TranslateToStringView(const std::string_view context, const std::string_view msg) { return msg; }
std::string Host::TranslateToString(const std::string_view context, const std::string_view msg) { return std::string(msg); }
std::string Host::TranslatePluralToString(const char* context, const char* msg, const char* disambiguation, int count) {
    return count == 1 ? (msg ? msg : "") : (disambiguation ? disambiguation : "");
}
void Host::ClearTranslationCache() {}

// OSD
void Host::AddOSDMessage(std::string message, float duration) {}
void Host::AddKeyedOSDMessage(std::string key, std::string message, float duration) {}
void Host::AddIconOSDMessage(std::string key, const char* icon, const std::string_view message, float duration) {}
void Host::RemoveKeyedOSDMessage(std::string key) {}
void Host::ClearOSDMessages() {}

// Reports
void Host::ReportInfoAsync(const std::string_view title, const std::string_view message) {}
void Host::ReportFormattedInfoAsync(const std::string_view title, const char* format, ...) {}
void Host::ReportErrorAsync(const std::string_view title, const std::string_view message) {}
void Host::ReportFormattedErrorAsync(const std::string_view title, const char* format, ...) {}
bool Host::ConfirmMessage(const std::string_view title, const std::string_view message) { return false; }
bool Host::ConfirmFormattedMessage(const std::string_view title, const char* format, ...) { return false; }

// Mode
bool Host::InBatchMode() { return true; }
bool Host::InNoGUIMode() { return true; }

// URL/Clipboard
void Host::OpenURL(const std::string_view url) {}
bool Host::CopyTextToClipboard(const std::string_view text) { return false; }

// Resources
bool Host::EnsureResourceSubdirectory(const char* relative_path) { return true; }

// Settings
bool Host::RequestResetSettings(bool folders, bool core, bool controllers, bool hotkeys, bool ui) { return false; }
void Host::SetDefaultUISettings(SettingsInterface& si) {}
void Host::CommitBaseSettingChanges() {}

// Display
void Host::RequestResizeHostDisplay(s32 width, s32 height) {}

// CPU thread
void Host::RunOnCPUThread(std::function<void()> function, bool block) { if (function) function(); }

// Game list
void Host::RefreshGameListAsync(bool invalidate_cache) {}
void Host::CancelGameListRefresh() {}

// VM
void Host::RequestVMShutdown(bool allow_confirm, bool allow_save_state, bool default_save_state) {}

// HTTP
std::string Host::GetHTTPUserAgent() { return "BionicSX2/1.0"; }

// Settings interface
std::unique_lock<std::mutex> Host::GetSettingsLock() { return std::unique_lock<std::mutex>(); }
SettingsInterface* Host::GetSettingsInterface() { return nullptr; }

// Settings accessors - Base
std::string Host::GetBaseStringSettingValue(const char* section, const char* key, const char* default_value) { return default_value ? default_value : ""; }
bool Host::GetBaseBoolSettingValue(const char* section, const char* key, bool default_value) { return default_value; }
int Host::GetBaseIntSettingValue(const char* section, const char* key, int default_value) { return default_value; }
uint Host::GetBaseUIntSettingValue(const char* section, const char* key, uint default_value) { return default_value; }
float Host::GetBaseFloatSettingValue(const char* section, const char* key, float default_value) { return default_value; }
double Host::GetBaseDoubleSettingValue(const char* section, const char* key, double default_value) { return default_value; }
std::vector<std::string> Host::GetBaseStringListSetting(const char* section, const char* key) { return {}; }
void Host::SetBaseBoolSettingValue(const char* section, const char* key, bool value) {}
void Host::SetBaseIntSettingValue(const char* section, const char* key, int value) {}
void Host::SetBaseUIntSettingValue(const char* section, const char* key, uint value) {}
void Host::SetBaseFloatSettingValue(const char* section, const char* key, float value) {}
void Host::SetBaseStringSettingValue(const char* section, const char* key, const char* value) {}
void Host::SetBaseStringListSettingValue(const char* section, const char* key, const std::vector<std::string>& values) {}
bool Host::AddBaseValueToStringList(const char* section, const char* key, const char* value) { return false; }
bool Host::RemoveBaseValueFromStringList(const char* section, const char* key, const char* value) { return false; }
bool Host::ContainsBaseSettingValue(const char* section, const char* key) { return false; }
void Host::RemoveBaseSettingValue(const char* section, const char* key) {}

// Settings accessors - Regular
std::string Host::GetStringSettingValue(const char* section, const char* key, const char* default_value) { return default_value ? default_value : ""; }
bool Host::GetBoolSettingValue(const char* section, const char* key, bool default_value) { return default_value; }
int Host::GetIntSettingValue(const char* section, const char* key, int default_value) { return default_value; }
uint Host::GetUIntSettingValue(const char* section, const char* key, uint default_value) { return default_value; }
float Host::GetFloatSettingValue(const char* section, const char* key, float default_value) { return default_value; }
double Host::GetDoubleSettingValue(const char* section, const char* key, double default_value) { return default_value; }
std::vector<std::string> Host::GetStringListSetting(const char* section, const char* key) { return {}; }

// Progress callback
std::unique_ptr<ProgressCallback> Host::CreateHostProgressCallback() { return nullptr; }

// File selector
bool Host::ShouldPreferHostFileSelector() { return false; }
void Host::OpenHostFileSelectorAsync(std::string_view title, bool select_directory,
                                     std::function<void(const std::string&)> callback,
                                     std::vector<std::string> filters, std::string_view initial_directory) {
    if (callback) callback("");
}

// Locale
bool Host::LocaleCircleConfirm() { return false; }

// Render window
void* Host::AcquireRenderWindow(bool recreate) { return nullptr; }
void Host::ReleaseRenderWindow() {}
void Host::BeginPresentFrame() {}

// Text input
void Host::BeginTextInput() {}
void Host::EndTextInput() {}

// Fullscreen
bool Host::IsFullscreen() { return false; }
void Host::SetFullscreen(bool fullscreen) {}

// Mouse mode
void Host::SetMouseMode(bool relative_mode, bool hide_cursor) {}

// Window info
std::optional<WindowInfo> Host::GetTopLevelWindowInfo() { return std::nullopt; }

// Input device callbacks
void Host::OnInputDeviceConnected(const std::string_view identifier, const std::string_view device_name) {}
void Host::OnInputDeviceDisconnected(const InputBindingKey key, const std::string_view identifier) {}

// VMManager.h Host namespace
void Host::LoadSettings(SettingsInterface& si, std::unique_lock<std::mutex>& lock) {}
void Host::CheckForSettingsChanges(const Pcsx2Config&) {}
void Host::OnVMStarting() {}
void Host::OnVMStarted() {}
void Host::OnVMDestroyed() {}
void Host::OnVMPaused() {}
void Host::OnVMResumed() {}
void Host::OnPerformanceMetricsUpdated() {}
void Host::OnSaveStateLoading(std::string_view filename) {}
void Host::OnSaveStateLoaded(std::string_view filename, bool was_successful) {}
void Host::OnSaveStateSaved(std::string_view filename) {}
void Host::OnGameChanged(const std::string& title, const std::string& elf_override, const std::string& disc_path,
                         const std::string& disc_serial, u32 disc_crc, u32 current_crc) {}
void Host::PumpMessagesOnCPUThread() {}

// Achievements
void Host::OnAchievementsRefreshed() {}
void Host::OnAchievementsLoginSuccess(const char* display_name, u32 points, u32 sc_points, u32 unread_messages) {}
void Host::OnAchievementsLoginRequested(Achievements::LoginRequestReason reason) {}
void Host::OnAchievementsHardcoreModeChanged(bool enabled) {}
void Host::OnCoverDownloaderOpenRequested() {}
void Host::OnCreateMemoryCardOpenRequested() {}

// Exit
void Host::RequestExitBigPicture() {}
void Host::RequestExitApplication(bool allow_confirm) {}

// Internal
s32 Host::Internal::GetTranslatedStringImpl(const std::string_view context, const std::string_view msg, char* out_buf, size_t out_buf_size) {
    if (msg.size() <= out_buf_size && out_buf) {
        std::memcpy(out_buf, msg.data(), msg.size());
        out_buf[msg.size()] = '\0';
    }
    return static_cast<s32>(msg.size());
}
void Host::Internal::EnsureAndroidResourceSubdirCopied(const char*) {}
SettingsInterface* Host::Internal::GetBaseSettingsLayer() { return nullptr; }
SettingsInterface* Host::Internal::GetGameSettingsLayer() { return nullptr; }
SettingsInterface* Host::Internal::GetInputSettingsLayer() { return nullptr; }
void Host::Internal::SetBaseSettingsLayer(SettingsInterface* sif) {}
void Host::Internal::SetGameSettingsLayer(SettingsInterface* sif, std::unique_lock<std::mutex>& settings_lock) {}
void Host::Internal::SetInputSettingsLayer(SettingsInterface* sif, std::unique_lock<std::mutex>& settings_lock) {}

// ============================================================================
// VMManager::Internal stubs
// ============================================================================
namespace VMManager { namespace Internal {
    bool CheckSettingsVersion();
    void LoadStartupSettings();
    void SetFileLogPath(std::string path);
    void SetBlockSystemConsole(bool block);
    bool CPUThreadInitialize();
    void CPUThreadShutdown();
    void ResetVMHotkeyState();
    void UpdateEmuFolders();
    bool WasFastBooted();
    bool IsFastBootInProgress();
    void DisableFastBoot();
    bool HasBootedELF();
    u32 GetCurrentELFEntryPoint();
    void FrameRateChanged();
    void Throttle();
    void ClearCPUExecutionCaches();
    const std::vector<u32>& GetSoftwareRendererProcessorList();
    const std::string& GetELFOverride();
    bool IsExecutionInterrupted();
    void ELFLoadingOnCPUThread(std::string elf_path);
    void EntryPointCompilingOnCPUThread();
    void VSyncOnCPUThread();
    void PollInputOnCPUThread();
}}

bool VMManager::Internal::CheckSettingsVersion() { return true; }
void VMManager::Internal::LoadStartupSettings() {}
void VMManager::Internal::SetFileLogPath(std::string path) {}
void VMManager::Internal::SetBlockSystemConsole(bool block) {}
bool VMManager::Internal::CPUThreadInitialize() { return true; }
void VMManager::Internal::CPUThreadShutdown() {}
void VMManager::Internal::ResetVMHotkeyState() {}
void VMManager::Internal::UpdateEmuFolders() {}
bool VMManager::Internal::WasFastBooted() { return false; }
bool VMManager::Internal::IsFastBootInProgress() { return false; }
void VMManager::Internal::DisableFastBoot() {}
bool VMManager::Internal::HasBootedELF() { return false; }
u32 VMManager::Internal::GetCurrentELFEntryPoint() { return 0; }
void VMManager::Internal::FrameRateChanged() {}
void VMManager::Internal::Throttle() {}
void VMManager::Internal::ClearCPUExecutionCaches() {}
const std::vector<u32>& VMManager::Internal::GetSoftwareRendererProcessorList() { static std::vector<u32> empty; return empty; }
const std::string& VMManager::Internal::GetELFOverride() { static std::string empty; return empty; }
bool VMManager::Internal::IsExecutionInterrupted() { return false; }
void VMManager::Internal::ELFLoadingOnCPUThread(std::string elf_path) {}
void VMManager::Internal::EntryPointCompilingOnCPUThread() {}
void VMManager::Internal::VSyncOnCPUThread() {}
void VMManager::Internal::PollInputOnCPUThread() {}

// ============================================================================
// InputManager stubs
// ============================================================================
namespace InputManager {
    InputSource* GetInputSourceInterface(InputSourceType type);
    const char* InputSourceToString(InputSourceType clazz);
    bool GetInputSourceDefaultEnabled(InputSourceType type);
    std::optional<InputSourceType> ParseInputSourceString(const std::string_view str);
    std::optional<u32> GetIndexFromPointerBinding(const std::string_view str);
    std::string GetPointerDeviceName(u32 pointer_index);
    std::optional<u32> ConvertHostKeyboardStringToCode(const std::string_view str);
    std::optional<std::string> ConvertHostKeyboardCodeToString(u32 code);
    const char* ConvertHostKeyboardCodeToIcon(u32 code);
    InputBindingKey MakeHostKeyboardKey(u32 key_code);
    InputBindingKey MakePointerButtonKey(u32 index, u32 button_index);
    InputBindingKey MakePointerAxisKey(u32 index, InputPointerAxis axis);
    std::optional<InputBindingKey> ParseInputBindingKey(const std::string_view binding);
    std::string ConvertInputBindingKeyToString(InputBindingInfo::Type binding_type, InputBindingKey key, bool migration = false);
    std::string ConvertInputBindingKeysToString(InputBindingInfo::Type binding_type, const InputBindingKey* keys, size_t num_keys, bool migration = false);
    bool PrettifyInputBinding(std::string& binding, bool use_icons = true);
    std::vector<std::string_view> SplitChord(const std::string_view binding);
    std::vector<const HotkeyInfo*> GetHotkeyList();
    std::vector<std::pair<std::string, std::string>> EnumerateDevices();
    std::vector<InputBindingKey> EnumerateMotors();
    std::vector<std::pair<GenericInputBinding, std::string>> GetGenericBindingMapping(const std::string_view device);
    bool IsInputSourceEnabled(SettingsInterface& si, InputSourceType type);
    void ReloadBindings(SettingsInterface& si, SettingsInterface& binding_si, SettingsInterface& hotkey_binding_si, bool is_binding_profile, bool is_hotkey_profile);
    void ReloadSources(SettingsInterface& si, std::unique_lock<std::mutex>& settings_lock);
    bool ReloadDevices();
    void CloseSources();
    void PollSources();
    bool HasAnyBindingsForKey(InputBindingKey key);
    bool HasAnyBindingsForSource(InputBindingKey key);
    bool InvokeEvents(InputBindingKey key, float value, GenericInputBinding generic_key = GenericInputBinding{});
    void ClearBindStateFromSource(InputBindingKey key);
    void SetHook(std::function<int(InputBindingKey, float)> callback);
    void RemoveHook();
    bool HasHook();
    void SetUSBVibrationIntensity(u32 port, float large_or_single_motor_intensity, float small_motor_intensity);
    void SetPadVibrationIntensity(u32 pad_index, float large_or_single_motor_intensity, float small_motor_intensity);
    void PauseVibration();
    std::pair<float, float> GetPointerAbsolutePosition(u32 index);
    void UpdatePointerAbsolutePosition(u32 index, float x, float y);
    void UpdatePointerRelativeDelta(u32 index, InputPointerAxis axis, float d, bool raw_input = false);
    void UpdateHostMouseMode();
    void OnInputDeviceConnected(const std::string_view identifier, const std::string_view device_name);
    void OnInputDeviceDisconnected(const InputBindingKey key, const std::string_view identifier);
}

// InputManager function stubs
namespace InputManager {
    InputSource* GetInputSourceInterface(InputSourceType type) { return nullptr; }
    const char* InputSourceToString(InputSourceType clazz) { return ""; }
    bool GetInputSourceDefaultEnabled(InputSourceType type) { return false; }
    std::optional<InputSourceType> ParseInputSourceString(const std::string_view str) { return std::nullopt; }
    std::optional<u32> GetIndexFromPointerBinding(const std::string_view str) { return std::nullopt; }
    std::string GetPointerDeviceName(u32 pointer_index) { return ""; }
    std::optional<u32> ConvertHostKeyboardStringToCode(const std::string_view str) { return std::nullopt; }
    std::optional<std::string> ConvertHostKeyboardCodeToString(u32 code) { return std::nullopt; }
    const char* ConvertHostKeyboardCodeToIcon(u32 code) { return ""; }
    InputBindingKey MakeHostKeyboardKey(u32 key_code) { InputBindingKey k; k.bits = 0; return k; }
    InputBindingKey MakePointerButtonKey(u32 index, u32 button_index) { InputBindingKey k; k.bits = 0; return k; }
    InputBindingKey MakePointerAxisKey(u32 index, InputPointerAxis axis) { InputBindingKey k; k.bits = 0; return k; }
    std::optional<InputBindingKey> ParseInputBindingKey(const std::string_view binding) { return std::nullopt; }
    std::string ConvertInputBindingKeyToString(InputBindingInfo::Type binding_type, InputBindingKey key, bool migration) { return ""; }
    std::string ConvertInputBindingKeysToString(InputBindingInfo::Type binding_type, const InputBindingKey* keys, size_t num_keys, bool migration) { return ""; }
    bool PrettifyInputBinding(std::string& binding, bool use_icons) { return false; }
    std::vector<std::string_view> SplitChord(const std::string_view binding) { return {}; }
    std::vector<const HotkeyInfo*> GetHotkeyList() { return {}; }
    std::vector<std::pair<std::string, std::string>> EnumerateDevices() { return {}; }
    std::vector<InputBindingKey> EnumerateMotors() { return {}; }
    std::vector<std::pair<GenericInputBinding, std::string>> GetGenericBindingMapping(const std::string_view device) { return {}; }
    bool IsInputSourceEnabled(SettingsInterface& si, InputSourceType type) { return false; }
    void ReloadBindings(SettingsInterface& si, SettingsInterface& binding_si, SettingsInterface& hotkey_binding_si, bool is_binding_profile, bool is_hotkey_profile) {}
    void ReloadSources(SettingsInterface& si, std::unique_lock<std::mutex>& settings_lock) {}
    bool ReloadDevices() { return false; }
    void CloseSources() {}
    void PollSources() {}
    bool HasAnyBindingsForKey(InputBindingKey key) { return false; }
    bool HasAnyBindingsForSource(InputBindingKey key) { return false; }
    bool InvokeEvents(InputBindingKey key, float value, GenericInputBinding generic_key) { return false; }
    void ClearBindStateFromSource(InputBindingKey key) {}
    void SetHook(std::function<int(InputBindingKey, float)> callback) {}
    void RemoveHook() {}
    bool HasHook() { return false; }
    void SetUSBVibrationIntensity(u32 port, float large_or_single_motor_intensity, float small_motor_intensity) {}
    void SetPadVibrationIntensity(u32 pad_index, float large_or_single_motor_intensity, float small_motor_intensity) {}
    void PauseVibration() {}
    std::pair<float, float> GetPointerAbsolutePosition(u32 index) { return {0.0f, 0.0f}; }
    void UpdatePointerAbsolutePosition(u32 index, float x, float y) {}
    void UpdatePointerRelativeDelta(u32 index, InputPointerAxis axis, float d, bool raw_input) {}
    void UpdateHostMouseMode() {}
    void OnInputDeviceConnected(const std::string_view identifier, const std::string_view device_name) {}
    void OnInputDeviceDisconnected(const InputBindingKey key, const std::string_view identifier) {}
}

// ============================================================================
// Hotkey arrays
// ============================================================================
HotkeyInfo g_common_hotkeys[] = {{nullptr, nullptr, nullptr, nullptr}};
HotkeyInfo g_gs_hotkeys[] = {{nullptr, nullptr, nullptr, nullptr}};
HotkeyInfo g_host_hotkeys[] = {{nullptr, nullptr, nullptr, nullptr}};

// ============================================================================
// System/Platform stubs
// ============================================================================
uint64_t GetCPUTicks() {
    struct timespec ts;
    clock_gettime(CLOCK_MONOTONIC, &ts);
    return static_cast<uint64_t>(ts.tv_sec) * 1000000000ULL + static_cast<uint64_t>(ts.tv_nsec);
}
uint64_t GetTickFrequency() { return 1000000000ULL; }
uint64_t GetPhysicalMemory() { return 8ULL * 1024 * 1024 * 1024; }
uint64_t GetAvailablePhysicalMemory() { return 4ULL * 1024 * 1024 * 1024; }
std::string GetOSVersionString() { return "iOS 16.0"; }
std::string GetValidDrive(std::string& path) { return path; }
struct DriveInfo {};
std::vector<DriveInfo> GetOpticalDriveList() { return {}; }
u32 ShortSpin() { return 0; }
const u32 SPIN_TIME_NS = 1000000;
void AbortWithMessage(const char* msg) {}

// ============================================================================
// CocoaTools stubs
// ============================================================================
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

// ============================================================================
// x86Emitter stubs
// ============================================================================
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
    struct VRegister {};
    VRegister xmm0;
}
enum XMMSSEType { XMMT_INT = 0, XMMT_FPS = 1 };
thread_local XMMSSEType g_xmmtypes[16] = {XMMT_INT};

// ============================================================================
// AudioStream stubs
// ============================================================================
namespace AudioStream {
    void* CreateOboeAudioStream(unsigned int, const AudioStreamParameters&, bool, Error*) { return nullptr; }
}

// ============================================================================
// HTTPDownloader stub
// ============================================================================
class HTTPDownloader {
public:
    static std::unique_ptr<HTTPDownloader> Create(std::string user_agent = DEFAULT_USER_AGENT);
};
std::unique_ptr<HTTPDownloader> HTTPDownloader::Create(std::string) { return nullptr; }

// ============================================================================
// SharedMemoryMappingArea stubs
// ============================================================================
class SharedMemoryMappingArea {
public:
    static std::unique_ptr<SharedMemoryMappingArea> Create(size_t size);
    ~SharedMemoryMappingArea();
    size_t GetSize() const { return 0; }
    size_t GetNumPages() const { return 0; }
    u8* BasePointer() const { return nullptr; }
    u8* OffsetPointer(size_t offset) const { return nullptr; }
    u8* PagePointer(size_t page) const { return nullptr; }
    u8* Map(void* file_handle, size_t file_offset, void* map_base, size_t map_size, const PageProtectionMode& mode);
    bool Unmap(void* map_base, size_t map_size);
};
std::unique_ptr<SharedMemoryMappingArea> SharedMemoryMappingArea::Create(size_t size) { return nullptr; }
SharedMemoryMappingArea::~SharedMemoryMappingArea() = default;
u8* SharedMemoryMappingArea::Map(void* file_handle, size_t file_offset, void* map_base, size_t map_size, const PageProtectionMode& mode) { return nullptr; }
bool SharedMemoryMappingArea::Unmap(void* map_base, size_t map_size) { return false; }

// ============================================================================
// GSDeviceMTL stubs
// ============================================================================
struct MTLLoadAction {};
class GSDeviceMTL {
public:
    void* GetSpinFence() { return nullptr; }
    void EndRenderPass() {}
    void* BeginRenderPass(void* colorFormat, GSTexture* colorTex, MTLLoadAction colorLoad,
                          GSTexture* depthTex, MTLLoadAction depthLoad,
                          GSTexture* stencilTex, MTLLoadAction stencilLoad) { return nullptr; }
    void* GetRenderCmdBuf() { return nullptr; }
    void* GetTextureUploadEncoder() { return nullptr; }
    void FlushEncodersForReadback() {}
    void* GetLateTextureUploadEncoder() { return nullptr; }
    void* GetRenderCmdBufWithoutCreate() { return nullptr; }
    struct BufferPair {};
    struct UploadBuffer {};
    void Allocate(BufferPair&, unsigned long) {}
    void Allocate(UploadBuffer&, unsigned long) {}
};
void* MakeGSDeviceMTL() { return nullptr; }
void* GetMetalAdapterList() { return nullptr; }

// ============================================================================
// JPEG stubs
// ============================================================================
struct jpeg_error_mgr {};
struct jpeg_compress_struct {};
struct jpeg_decompress_struct {};
struct jpeg_source_mgr {};
struct jpeg_destination_mgr {};
struct JSAMPARRAY__ { unsigned char** data; };
typedef JSAMPARRAY__* JSAMPARRAY;
typedef unsigned char* JSAMPROW;
typedef int boolean;
#define FALSE 0
#define TRUE 1

extern "C" {
    jpeg_error_mgr* jpeg_std_error(jpeg_error_mgr* err) { return err; }
    void jpeg_create_compress(jpeg_compress_struct*) {}
    void jpeg_set_defaults(jpeg_compress_struct*) {}
    void jpeg_set_quality(jpeg_compress_struct*, int, int) {}
    void jpeg_start_compress(jpeg_compress_struct*, int) {}
    void jpeg_write_scanlines(jpeg_compress_struct*, JSAMPARRAY, unsigned int) {}
    void jpeg_finish_compress(jpeg_compress_struct*) {}
    void jpeg_destroy_compress(jpeg_compress_struct*) {}
    void jpeg_create_decompress(jpeg_decompress_struct*) {}
    void jpeg_destroy_decompress(jpeg_decompress_struct*) {}
    int jpeg_read_header(jpeg_decompress_struct*, int) { return 0; }
    void jpeg_start_decompress(jpeg_decompress_struct*) {}
    void jpeg_read_scanlines(jpeg_decompress_struct*, JSAMPARRAY, unsigned int) {}
    void jpeg_finish_decompress(jpeg_decompress_struct*) {}
    void jpeg_mem_src(jpeg_decompress_struct*, unsigned char*, unsigned long) {}
    void jpeg_mem_dest(jpeg_compress_struct*, unsigned char**, unsigned long*) {}
    int jpeg_resync_to_restart(jpeg_decompress_struct*, int) { return 0; }
    void jpeg_set_colorspace(jpeg_compress_struct*, int) {}
    void jpeg_default_colorspace(jpeg_compress_struct*) {}
    void jpeg_set_linear_quality(jpeg_compress_struct*, int, int) {}
    boolean jpeg_has_multiple_scans(jpeg_decompress_struct*) { return FALSE; }
    boolean jpeg_start_output(jpeg_decompress_struct*, int) { return FALSE; }
    boolean jpeg_finish_output(jpeg_decompress_struct*) { return FALSE; }
}

// ============================================================================
// Threading stubs
// ============================================================================
namespace Threading {
    void Sleep(int ms) { if (ms > 0) {} }
    void SleepUntil(uint64_t ticks) {}
    class ThreadHandle {};
}

// ============================================================================
// Common namespace stubs
// ============================================================================
namespace Common {
    void PlaySoundAsync(const char*) {}
    bool InhibitScreensaver(bool) { return false; }
    void SetMousePosition(int x, int y) {}
    bool AttachMousePositionCb(std::function<void(int,int)> cb) { return false; }
    void DetachMousePositionCb() {}
}

// ============================================================================
// HostSys namespace stubs
// ============================================================================
namespace HostSys {
    void* Mmap(void* base, size_t size, const PageProtectionMode& mode) { return nullptr; }
    void Munmap(void* base, size_t size) {}
    void MemProtect(void* baseaddr, size_t size, const PageProtectionMode& mode) {}
    std::string GetFileMappingName(const char* prefix) { return ""; }
    void* CreateSharedMemory(const char* name, size_t size) { return nullptr; }
    void DestroySharedMemory(void* ptr) {}
    void* MapSharedMemory(void* handle, size_t offset, void* baseaddr, size_t size, const PageProtectionMode& mode) { return nullptr; }
    void UnmapSharedMemory(void* baseaddr, size_t size) {}
    void BeginCodeWrite() {}
    void EndCodeWrite() {}
    void FlushInstructionCache(void* address, u32 size) {}
    size_t GetRuntimePageSize() { return 4096; }
    size_t GetRuntimeCacheLineSize() { return 64; }
}

// ============================================================================
// GSCapture namespace stubs
// ============================================================================
namespace GSCapture {
    bool BeginCapture(float fps, GSVector2i recommendedResolution, float aspect, std::string filename) { return false; }
    bool BeginCapture(float fps, GSVector2T<int> resolution, float aspect, std::string filename) { return false; }
    bool DeliverVideoFrame(GSTexture* stex) { return false; }
    void DeliverAudioPacket(const s16* frames) {}
    void EndCapture() {}
    bool IsCapturing() { return false; }
    bool IsCapturingVideo() { return false; }
    bool IsCapturingAudio() { return false; }
    std::string GetElapsedTime() { return ""; }
    const Threading::ThreadHandle& GetEncoderThreadHandle() { static Threading::ThreadHandle h; return h; }
    GSVector2i GetSize() { return GSVector2i(); }
    std::string GetNextCaptureFileName() { return ""; }
    void Flush() {}
    using CodecName = std::pair<std::string, std::string>;
    using CodecList = std::vector<CodecName>;
    CodecList GetVideoCodecList(const char* container) { return {}; }
    CodecList GetAudioCodecList(const char* container) { return {}; }
    using FormatName = std::pair<int , std::string>;
    using FormatList = std::vector<FormatName>;
    FormatList GetVideoFormatList(const char* codec) { return {}; }
}

// ============================================================================
// PageFaultHandler stubs
// ============================================================================
namespace PageFaultHandler {
    enum class HandlerResult { ContinueExecution, ExecuteNextHandler };
    HandlerResult HandlePageFault(void* exception_pc, void* fault_address, bool is_write) { return HandlerResult::ContinueExecution; }
    bool Install(Error* error = nullptr) { return false; }
}

// ============================================================================
// extern "C" stubs
// ============================================================================
extern "C" const char* SDL_SYS_GetPreferredLocales() { return "en_US"; }

// ============================================================================
// SmallString/TinyString stubs
// ============================================================================
struct SmallString : public std::string {};
struct TinyString : public std::string {};
