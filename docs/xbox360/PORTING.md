# Xbox 360 port: initial technical assessment

Status: **research and scaffolding only**. No Xbox 360 executable has been built or tested.

## Verified upstream facts
- Root CMake config currently requests C++20 (despite the README describing C++17).
- The iOS port uses an interpreter fallback when JIT is unavailable; this is a useful precedent for a non-JIT PowerPC target, but does **not** prove PowerPC compatibility.
- The project includes numerous Git submodules (including Dynarmic, SDL-related components, FFmpeg, and LuaJIT). A direct cross-compile is unlikely to work.

## Engineering milestones
1. Inventory all platform-specific code paths and dependencies, including compiler intrinsics, assembly, endian assumptions, memory mapping, thread primitives, and graphics/audio interfaces.
2. Establish an Xbox 360 homebrew toolchain and produce a standalone minimal hello-world XEX. Do not claim success without a reproducible build.
3. Create a platform abstraction for filesystem, input, clocks, threading, graphics, and audio.
4. Select and validate an ARM interpreter on PowerPC; disable unsupported host-specific JIT code.
5. Add a minimal headless boot path and controlled logs, then display, input, audio, and game-loading support.
6. Run tests on actual hardware and document compatibility and performance.

## Risks
- Xbox 360 PowerPC is big-endian; serialized data, pointer casts, memory access, and binary formats require careful review.
- Upstream C++20 support may be limited in available homebrew compilers.
- Graphics/audio backends and upstream dependencies may require significant replacement.
- Homebrew execution capabilities depend on the specific console environment.

## First audit checkpoints
- `CMakeLists.txt`: root build settings, platform branches, and toolchain assumptions.
- `.gitmodules`: external dependency inventory.
- `README.md`: project capabilities and supported platforms.

## Project rules
- Keep upstream `master` unchanged until explicitly approved.
- Work in development branches; use draft PRs for review.
- Do not advertise a working emulator or `default.xex` until actually built and tested.
