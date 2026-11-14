#pragma once
#include "../../src/xbox/memory_policy.h"
#include <cstddef>

namespace eka2l1::xbox {
struct runtime_memory_snapshot {
    bool valid;
    std::size_t total_physical_bytes;
    std::size_t available_physical_bytes;
    memory_budget budget;
};

// Queries the Xbox kernel; no guessed addresses and no XeFu patching.
// A failed query yields valid=false and an unsupported budget.
runtime_memory_snapshot query_runtime_memory(std::size_t reserve_bytes) noexcept;
}
