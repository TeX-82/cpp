#pragma once

#include <stdint.h>

#include <string>
#include <vector>
#include <optional>
#include <string_view>

extern const std::vector<std::string>& tex_pool();
extern std::optional<uint64_t> string_number(const std::string_view&);

