// Xbox kernel memory-statistics probe; not yet the EKA2L1 emulator.
#include "memory_probe.h"
#include <hal/debug.h>
#include <hal/video.h>
#include <windows.h>

int main() {
    XVideoSetMode(640, 480, 32, REFRESH_DEFAULT);
    constexpr std::size_t reserve = 16u * 1024u * 1024u;
    const auto snapshot = eka2l1::xbox::query_runtime_memory(reserve);
    if (!snapshot.valid) {
        debugPrint("EKA2L1 Xbox probe: MmQueryStatistics failed.\n");
    } else {
        const auto mib = 1024u * 1024u;
        debugPrint("EKA2L1 Xbox probe: total=%lu MiB available=%lu MiB budget=%lu MiB\n",
                   static_cast<unsigned long>(snapshot.total_physical_bytes / mib),
                   static_cast<unsigned long>(snapshot.available_physical_bytes / mib),
                   static_cast<unsigned long>(snapshot.budget.usable_bytes / mib));
    }
    debugPrint("This is a diagnostic probe, not a playable emulator.\n");
    while (true) Sleep(2000);
}
