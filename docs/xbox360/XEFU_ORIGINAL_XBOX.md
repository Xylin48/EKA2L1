# Original Xbox target through XeFu

Target executable: `default.xbe` (not `default.xex`).

The user's modified XeFu setup reportedly exposes 128 MiB and 256 MiB configurations. These are **user-reported**, not validated by this repository.

## Memory negotiation reality

An Xbox executable cannot unilaterally instruct XeFu to expand its memory map. The Xbox runtime must first expose an expanded memory region. EKA2L1 should then query the memory actually available and adjust its budgets without assuming that a configuration flag guarantees usable RAM.

The first portable implementation is `src/xbox/memory_policy.h`: a pure, testable policy mapping a *verified* accessible byte count and reserved headroom to a memory tier. It does **not** probe hardware, allocate RAM, modify XeFu, or hook the emulator yet.

## Integration plan

1. Verify a usable original Xbox SDK/toolchain and compile a minimal `default.xbe`.
2. Identify a reliable runtime memory query or carefully bounded allocation probe, accounting for reserved regions and fragmentation.
3. Validate the result against the modified XeFu 64/128/256 MiB modes on actual hardware. Do not probe by writing to guessed addresses.
4. Connect the verified count to `choose_memory_budget` and configure EKA2L1's allocations, cache sizes, and graphics buffers.
5. Port CPU interpretation and required OS/graphics/audio/input dependencies.
6. Add boot, game-loading, performance, and stability tests.

## Acceptance criteria

- No memory is assumed accessible solely because a XeFu configuration advertises it.
- A failed probe does not crash or corrupt memory.
- Memory pressure yields controlled allocation failures or reduced cache usage, not out-of-bounds writes.
- No claim of a working XBE until it has been built and tested.
