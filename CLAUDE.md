# BionicSX2 Development Guidelines

## Project Context
BionicSX2 is a port of the PS2 emulator (ARMSX2/PCSX2) from Android to iOS. It uses the ARMSX2 fork as a submodule at `src/armsx2`, with 17 patches applied at build time to resolve iOS compatibility issues.

## Mandatory Development Guidelines
1. **Preserve Existing Patches**: Maintain all 17 existing patches applied to the ARMSX2 submodule. Do NOT modify, "fix", or revert stubs in the `ios/stubs/` directory — these are intentional workarounds for iOS compatibility.
2. **Linking Stage Priority**: The current top priority is resolving the linking stage: link all generated static libraries (.a) into a self-contained iOS executable. Strictly avoid using any macOS-specific dylibs from Homebrew, as these are built for macOS and incompatible with iOS.
3. **iOS Compatibility Methodology**: Follow the established three-part approach for resolving iOS/macOS incompatibilities:
   - **Stubbing**: Replace entire macOS-only files (e.g., CoreAudio, Cocoa, IOKit, Discord RPC) with empty stubs in `ios/stubs/`
   - **TARGET_OS_IOS Guards**: Wrap macOS-only code blocks with `#if !TARGET_OS_IOS` / `#endif` to preserve macOS compatibility while disabling irrelevant code on iOS
   - **Sed Patching**: Use `sed` to modify source files at build time for minor adjustments (e.g., removing unavailable Metal APIs, fixing register types)

## Patches Reference
All 17 patches are applied in `.github/workflows/build-ipa.yml` at build time. They cover:
- iOS platform/architecture support in CMake
- Dependency injection (ZLIB, Freetype, SDL3, etc.)
- Stubbing macOS-only features (cubeb, CocoaTools, IOKit, Discord RPC)
- Metal API compatibility fixes
- ARM64 register type corrections

## Next Steps (Post-Linking)
1. Add iOS-native `main()` entry point linking SDL3 to the emulator core
2. Build minimal iOS UI (SwiftUI/UIKit)
3. Configure JIT entitlements
4. Package and distribute via TestFlight
