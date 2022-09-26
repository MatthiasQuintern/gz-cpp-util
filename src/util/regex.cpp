#include "regex.hpp"

namespace gz::re {
    const std::regex types::intT(R"([+\-]?(0x|0X)?\d+)");
    const std::regex types::uintT(R"(\+?(0x|0X)?\d+)");
    const std::regex types::floatT(R"([+\-]?(((\d+\.?\d*)|(\d*\.?\d+))(e[+\-]?\d+)?)|(inf(inity)?)|(nan\w*)|((0x|0X)((\d+\.?\d*)|(\d*\.?\d+))(p[+\-]?\d+)?))", std::regex::icase);
}
