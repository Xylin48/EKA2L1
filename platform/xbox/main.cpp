// Original Xbox nxdk entrypoint smoke test.
// This only validates the toolchain and a shared memory-policy header.
#include "../../src/xbox/memory_policy.h"
#include <cstddef>
#include <cstdio>

int main() {
    constexpr std::size_t mib = 1024u * 1024u;
    constexpr auto sample = eka2l1::xbox::choose_memory_budget(128u * mib, 16u * mib);
    static_assert(sample.usable_bytes == 112u * mib,
                  "Memory budget policy regression");
    std::printf("EKA2L1 Xbox platform probe; no emulator runtime loaded.\n");
    std::printf("Example policy only: 128 MiB - 16 MiB = %lu MiB.\n",
                static_cast<unsigned long>(sample.usable_bytes / mib));
    return 0;
}
