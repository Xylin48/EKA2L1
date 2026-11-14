#include "memory_probe.h"
#include <xboxkrnl/xboxkrnl.h>

namespace eka2l1::xbox {
runtime_memory_snapshot query_runtime_memory(std::size_t reserve_bytes) noexcept {
    MM_STATISTICS statistics{};
    statistics.Length = sizeof(statistics);
    const NTSTATUS status = MmQueryStatistics(&statistics);
    if (!NT_SUCCESS(status)) {
        return {false, 0u, 0u, choose_runtime_budget(0u, 0u, reserve_bytes)};
    }
    const auto total = static_cast<std::size_t>(statistics.TotalPhysicalPages) * PAGE_SIZE;
    const auto available = static_cast<std::size_t>(statistics.AvailablePages) * PAGE_SIZE;
    return {true, total, available,
            choose_runtime_budget(total, available, reserve_bytes)};
}
}
