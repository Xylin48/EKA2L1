#include "../src/xbox/memory_policy.h"

#include <cassert>
#include <cstddef>
#include <limits>

int main() {
    using namespace eka2l1::xbox;
    constexpr std::size_t MiB = 1024u * 1024u;

    const auto retail = choose_memory_budget(64u * MiB, 12u * MiB);
    assert(retail.tier == memory_tier::retail_64mb);
    assert(retail.usable_bytes == 52u * MiB);

    const auto expanded128 = choose_memory_budget(128u * MiB, 16u * MiB);
    assert(expanded128.tier == memory_tier::expanded_128mb);
    assert(expanded128.usable_bytes == 112u * MiB);

    const auto expanded256 = choose_memory_budget(256u * MiB, 24u * MiB);
    assert(expanded256.tier == memory_tier::expanded_256mb);
    assert(expanded256.usable_bytes == 232u * MiB);

    const auto below = choose_memory_budget(64u * MiB - 1u, 8u * MiB);
    assert(below.tier == memory_tier::unsupported);

    const auto reserved = choose_memory_budget(128u * MiB, 129u * MiB);
    assert(reserved.usable_bytes == 0u);

    const auto exact = choose_memory_budget(128u * MiB, 128u * MiB);
    assert(exact.usable_bytes == 0u);

    const auto zero = choose_memory_budget(0u, 0u);
    assert(zero.tier == memory_tier::unsupported);
    assert(zero.usable_bytes == 0u);

    const auto runtime = choose_runtime_budget(256u * MiB, 80u * MiB, 16u * MiB);
    assert(runtime.tier == memory_tier::expanded_256mb);
    assert(runtime.usable_bytes == 64u * MiB);

    const auto underpressure = choose_runtime_budget(128u * MiB, 8u * MiB, 16u * MiB);
    assert(underpressure.usable_bytes == 0u);

    const auto overreported = choose_runtime_budget(64u * MiB, 256u * MiB, 8u * MiB);
    assert(overreported.usable_bytes == 56u * MiB);

    const auto huge = choose_memory_budget(std::numeric_limits<std::size_t>::max(), 1u);
    assert(huge.usable_bytes == std::numeric_limits<std::size_t>::max() - 1u);
}
