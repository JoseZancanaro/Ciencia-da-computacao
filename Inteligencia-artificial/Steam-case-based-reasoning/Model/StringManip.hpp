#ifndef STRINGMANIP_HPP
#define STRINGMANIP_HPP

#include <iostream>
#include <fstream>
#include <string>
#include <vector>

namespace util {

auto split(std::string const& text, std::string const& separator = ";") -> std::vector<std::string>;

auto readFromCSV(std::string const& filename) -> std::vector<std::vector<std::string>>;

}

#endif // STRINGMANIP_HPP
