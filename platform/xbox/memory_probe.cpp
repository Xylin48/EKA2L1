#include "memory_probe.h"
#include <xboxkrnl/xboxkrnl.h>

namespace eka2l1::xbox {
runtime_memory_snapshot query_runtime_memory(std::size_t reserve_bytes) noexcept {
    MM_STATISTICS statistics{};
    statistics.Length = sizeof(statistics);
    const NTSTATUS status = MmQueryStatistics(&statistics);
    if (!NT_SUCCESS(status)) {
        return {false, 0u, 0u, choose_memory_budget(0u, reserve_bytes)};
    }
    const auto total = static_cast<std::size_t>(statistics.TotalPhysicalPages) * PAGE_SIZE;
    const auto available = static_cast<std::size_t>(statistics.AvailablePages) * PAGE_SIZE;
    // Report total physical capacity, but limit allocatable budget by currently
    // available pages. Other processes/system allocations must retain headroom.
    const auto tier = choose_memory_budget(total, reserve_bytes);
    const auto bounded = available > reserve_bytes ? available - reserve_bytes : 0u;
    return {true, total, available,
            {tier.tier, total, reserve_bytes,
             bounded < tier.usable_bytes ? bounded : tier.usable_bytes}};
}
}
