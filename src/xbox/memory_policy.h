#pragma once

// Original Xbox / XeFu memory policy. Platform-independent and deliberately
// independent of undocumented XeFu interfaces.
#include <cstddef>
#include <cstdint>

namespace eka2l1::xbox {
enum class memory_tier : std::uint8_t {
    unsupported,
    retail_64mb,
    expanded_128mb,
    expanded_256mb
};

struct memory_budget {
    memory_tier tier;
    std::size_t detected_bytes;
    std::size_t reserved_bytes;
    std::size_t usable_bytes;
};

// This policy does not request additional memory from XeFu. The caller must
// provide the memory actually reported by the Xbox runtime. Leave headroom
// for the dashboard/runtime, graphics, stack, and other allocations.
constexpr memory_budget choose_memory_budget(std::size_t accessible_bytes,
                                             std::size_t reserve_bytes) noexcept {
    constexpr std::size_t mib = 1024u * 1024u;
    const std::size_t usable = accessible_bytes > reserve_bytes
        ? accessible_bytes - reserve_bytes : 0u;
    const auto tier = accessible_bytes >= 256u * mib
        ? memory_tier::expanded_256mb
        : accessible_bytes >= 128u * mib
            ? memory_tier::expanded_128mb
            : accessible_bytes >= 64u * mib
                ? memory_tier::retail_64mb
                : memory_tier::unsupported;
    return {tier, accessible_bytes, reserve_bytes, usable};
}
} // namespace eka2l1::xbox
