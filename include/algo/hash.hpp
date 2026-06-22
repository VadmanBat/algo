#pragma once

#include <cstdint>
#include <string>

namespace algo {
constexpr uint16_t const_hash(const std::string& s) noexcept {
    const auto n = static_cast<uint32_t>(s.size());
    uint32_t h = n;
    for (size_t i = 0; i < n; ++i)
        (h *= 37) += s[i];
    h ^= h >> 16;
    h *= 0x85ebca6bU;
    h ^= h >> 13;
    h *= 0xc2b2ae35U;
    h ^= h >> 16;
    return static_cast<uint16_t>(h);
}
}