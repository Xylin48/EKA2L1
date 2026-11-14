# Original Xbox / nxdk memory diagnostic

This is a **toolchain and runtime memory probe**, not a functioning EKA2L1 emulator.

## Verified API basis

XboxDev/nxdk's `lib/xboxkrnl/xboxkrnl.h` declares `MmQueryStatistics(PMM_STATISTICS)` and the `MM_STATISTICS` fields `Length`, `TotalPhysicalPages`, and `AvailablePages`. The header defines `PAGE_SIZE` as 4096. The probe uses these public kernel interfaces rather than guessing XeFu-specific addresses or modifying XeFu.

The nxdk README documents installing prerequisites, cloning recursively, activating with `bin/activate`, and running Make in the project directory.

```sh
# Run from a shell created by nxdk's bin/activate
cd /path/to/EKA2L1/platform/xbox
make
```

## Runtime behavior

`main.cpp` calls `query_runtime_memory(16 MiB)`, then prints the total physical memory, currently available memory, and bounded usable budget to the nxdk debug output. It remains running for inspection. It does not yet load a game.

The kernel-reported total determines the 64/128/256 MiB classification; current available pages cap the usable allocation budget. The 16 MiB reserve is a provisional engineering policy, not a measured XeFu requirement. Kernel statistics may not capture every memory-map constraint, fragmentation, or per-title allocation limit; actual allocation testing remains necessary.

A failure of `MmQueryStatistics` results in an invalid snapshot and zero budget. The probe does not request extra memory, patch XeFu, or write to unverified addresses.

## Status and limitations

- Source and nxdk API signatures have been inspected.
- The XBE has **not** been cross-compiled or executed in this session.
- Expanded RAM has been reported by the user but not validated by this diagnostic.
- The emulator's CPU, graphics, audio, input, filesystem, and Symbian service components are **not** integrated.
- Existing EKA2L1 source and CMake configuration remain unchanged.

## Next validation

Build the XBE with an installed nxdk, inspect any compiler/linker errors, execute it through modified XeFu, and compare the reported physical/available memory under each XeFu configuration. Then add safe allocation verification and integrate the budget with the complete emulator runtime.
