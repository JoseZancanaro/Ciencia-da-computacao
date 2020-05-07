#include "StringManip.hpp"

namespace util {

auto split(std::string const& text, std::string const& separator) -> std::vector<std::string> {
    std::vector<std::string> values {};
    std::size_t begin = 0;

    while (begin != std::string::npos) {
        auto next = text.find_first_of(separator, begin);
        auto value = text.substr(begin, next - begin);

        if (!value.empty()) {
            values.push_back(std::move(value));
        }

        if (next == std::string::npos || next == std::size(text)) {
            begin = std::string::npos;
        } else {
            begin = next + 1;
        }
    }

    return values;
}

auto readFromCSV(std::string const& filename) -> std::vector<std::vector<std::string>> {
    std::vector<std::vector<std::string>> data {};
    std::ifstream input (filename);

    if (input.is_open()) {
        while (input.good()) {
            if (std::string read {}; std::getline(input, read).good()) {
                data.push_back(split(read, ","));
            }
        }
    }

    return data;
}

}
