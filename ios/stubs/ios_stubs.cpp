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
#include <string_view>

// Define PCSX2 types needed for stubs
using u32 = uint32_t;
using u64 = uint64_t;

// Define DEFAULT_USER_AGENT at the top of the file
static const char DEFAULT_USER_AGENT[] = "BionicSX2/1.0";

// Forward declarations for PCSX2 types (avoid including headers with complex dependencies)
struct Pcsx2Config;  // defined in Config.h as a global namespace struct

struct SettingsInterface;
struct ProgressCallback;
struct Error;
struct AudioStreamParameters;

// Define s32 as int32_t (used in Host::Internal::GetTranslatedStringImpl)
using s32 = int32_t;

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

namespace Achievements { enum LoginRequestReason {}; }

// InputBindingKey must match the global namespace union in InputManager.h
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

// Host namespace stubs
namespace Host {
    using s32 = int32_t;
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
    void CheckForSettingsChanges(const Pcsx2Config& old_config);
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
    void OnInputDeviceDisconnected(InputBindingKey key, std::string_view identifier);
    void SetMouseMode(bool, bool) {}

    // From Achievements.h namespace Host
    void OnAchievementsRefreshed() {}
    void OnAchievementsLoginSuccess(const char*, unsigned int, unsigned int, unsigned int) {}
    void OnAchievementsLoginRequested(Achievements::LoginRequestReason) {}

    void OnAchievementsHardcoreModeChanged(bool) {}

    // Additional Host functions from undefined symbols
    bool LocaleCircleConfirm() { return false; }
    void RequestExitApplication(bool) {}
    void RequestExitBigPicture() {}
    bool ShouldPreferHostFileSelector() { return false; }
    void OnCoverDownloaderOpenRequested() {}
    void OnCreateMemoryCardOpenRequested() {}
    void OpenHostFileSelectorAsync(std::string_view, bool, std::function<void(const std::string&)>,
                                   std::vector<std::string>, std::string_view) {}

    namespace Internal {
        s32 GetTranslatedStringImpl(const std::string_view context, const std::string_view msg, char* tbuf, size_t tbuf_space) { return 0; }
    }
} // namespace Host
// Host::CheckForSettingsChanges out-of-line definition
void Host::CheckForSettingsChanges(const Pcsx2Config& old_config) {}


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
    // xmm0 is a global register variable referenced from recVTLB.cpp
    struct VRegister {};
    VRegister xmm0;
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

// Forward declaration
class PageProtectionMode;

// SharedMemoryMappingArea stubs
class SharedMemoryMappingArea {
	public:
	    SharedMemoryMappingArea();
	    ~SharedMemoryMappingArea();
	    void* Create(unsigned long);
	    void* Map(void* baseaddr, unsigned long baseaddr_size, void* mapaddr, unsigned long mapaddr_size, const PageProtectionMode& mode);
	    void Unmap(void*, unsigned long);
	    void Destroy();
};

// SharedMemoryMappingArea out-of-line definitions
void* SharedMemoryMappingArea::Create(unsigned long) { return nullptr; }
void* SharedMemoryMappingArea::Map(void* baseaddr, unsigned long baseaddr_size, void* mapaddr, unsigned long mapaddr_size, const PageProtectionMode& mode) { return nullptr; }
void SharedMemoryMappingArea::Unmap(void*, unsigned long) {}
void SharedMemoryMappingArea::Destroy() {}



// Out-of-line definitions to ensure symbols are emitted
SharedMemoryMappingArea::SharedMemoryMappingArea() = default;
SharedMemoryMappingArea::~SharedMemoryMappingArea() = default;

// GSDeviceMTL stubs (Metal disabled for iOS) - using void* for Objective-C types
struct GSTexture;
struct MTLLoadAction {};
class GSDeviceMTL {
public:
    void* GetSpinFence() { return nullptr; }
    void EndRenderPass() {}
    void* BeginRenderPass(void* /*colorFormat*/, GSTexture* /*colorTex*/, MTLLoadAction /*colorLoad*/,
                          GSTexture* /*depthTex*/, MTLLoadAction /*depthLoad*/,
                          GSTexture* /*stencilTex*/, MTLLoadAction /*stencilLoad*/) { return nullptr; }
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

// MakeGSDeviceMTL and GetMetalAdapterList stubs (need C++ linkage, not extern "C")
void* MakeGSDeviceMTL() { return nullptr; }
void* GetMetalAdapterList() { return nullptr; }

// JPEG stub functions (libjpeg not available on iOS)
struct jpeg_error_mgr {};
struct jpeg_compress_struct {};
struct jpeg_decompress_struct {};
struct jpeg_source_mgr {};
struct jpeg_destination_mgr {};
struct JSAMPARRAY__ { unsigned char** data; };
typedef JSAMPARRAY__* JSAMPARRAY;
typedef unsigned char* JSAMPROW;

// Define JPEG boolean type (normally from jmorecfg.h)
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

// Threading stubs (normally in DarwinMisc.cpp)
namespace Threading {
    void Sleep(int ms) { if (ms > 0) {} }
    void SleepUntil(uint64_t ticks) {}
}

// Common namespace stubs
namespace Common {
    void PlaySoundAsync(const char*) {}
    void InhibitScreensaver(bool) {}
}

// HTTPDownloader stub
class HTTPDownloader {
public:
    static std::unique_ptr<HTTPDownloader> Create(std::string user_agent = DEFAULT_USER_AGENT);
};

// Out-of-line definition
std::unique_ptr<HTTPDownloader> HTTPDownloader::Create(std::string) { return nullptr; }

// DEFAULT_USER_AGENT constant
static const char DEFAULT_USER_AGENT[] = "BionicSX2/1.0";


// GSVector2i, GSVector2T, and PageProtectionMode stubs
template<typename T>
struct GSVector2T {};
struct GSVector2i { int x, y; GSVector2i() : x(0), y(0) {} };
struct GSTexture {};

// Forward declaration for PageProtectionMode
class PageProtectionMode {
public:
    bool CanRead() const { return false; }
    bool CanWrite() const { return false; }
    bool CanExecute() const { return false; }
};

// GSCapture namespace stubs (must match GSCapture.h)
namespace GSCapture {
    bool BeginCapture(float fps, GSVector2T<int>, float aspect, std::string filename) { return false; }
    bool DeliverVideoFrame(GSTexture* stex) { return false; }
    void DeliverAudioPacket(const short* frames) {}
    void EndCapture() {}
    bool IsCapturing() { return false; }
    bool IsCapturingVideo() { return false; }
    bool IsCapturingAudio() { return false; }
    std::string GetElapsedTime() { return ""; }
    void* GetEncoderThreadHandle() { return nullptr; }
    GSVector2i GetSize() { return GSVector2i(); }
    std::string GetNextCaptureFileName() { return ""; }
    void Flush() {}
    using CodecName = std::pair<std::string, std::string>;
    using CodecList = std::vector<CodecName>;
    CodecList GetVideoCodecList(const char*) { return {}; }
    CodecList GetAudioCodecList(const char*) { return {}; }
    using FormatName = std::pair<int, std::string>;
    using FormatList = std::vector<FormatName>;
    FormatList GetVideoFormatList(const char*) { return {}; }
}

// VMManager::Internal::ResetVMHotkeyState stub
namespace VMManager { namespace Internal {
    void ResetVMHotkeyState() {}
}}

// HotkeyInfo - must match InputManager.h definition
struct HotkeyInfo {
    const char* name = nullptr;
    const char* category = nullptr;
    const char* display_name = nullptr;
    void (*handler)(int32_t pressed) = nullptr;
};

// Hotkey arrays - must have external linkage for C++ (no const, no extern "C" for C++ types)
HotkeyInfo g_common_hotkeys[] = {{nullptr, nullptr, nullptr, nullptr}};
HotkeyInfo g_gs_hotkeys[] = {{nullptr, nullptr, nullptr, nullptr}};
HotkeyInfo g_host_hotkeys[] = {{nullptr, nullptr, nullptr, nullptr}};

// HostSys namespace stubs (must match HostSys.h)
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
    void FlushInstructionCache(void* address, uint32_t size) {}
    size_t GetRuntimePageSize() { return 4096; }
    size_t GetRuntimeCacheLineSize() { return 64; }
}

// x86Emitter stubs (not used on ARM64, but needed for linking)
enum XMMSSEType {
    XMMT_INT = 0,
    XMMT_FPS = 1,
};

thread_local XMMSSEType g_xmmtypes[16] = {XMMT_INT};

// Host::OnInputDeviceDisconnected out-of-line definition
void Host::OnInputDeviceDisconnected(InputBindingKey key, std::string_view identifier) {}

