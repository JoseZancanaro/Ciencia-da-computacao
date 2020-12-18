#include <string>
#include <array>
#include <iostream>

template <typename T>
auto to_key(T&& arg) -> std::string {
    return std::string{"\""} + arg + std::string{"\": #, "};
}

auto to_value(std::string & value) -> std::string {
    return std::string{"\""} + value + std::string{"\""};
}

template <typename T>
auto to_value(T&& value) -> std::string {
    return std::to_string(value);
}

template <typename T>
auto replace_next(std::string& base, T&& value) -> void {
    auto idx = base.find('#');
    base.replace(idx, 1, to_value(value));
}

template <typename ... T>
auto to_serial_json(std::string base, T&& ... args) -> std::string {
    (replace_next(base, args), ...);
    base.erase(base.find_last_of(','), 1);
    return base;
}

template <typename ... T>
auto json_keys(T&& ... args) -> std::string {
    auto serial = std::string{"{ "};
    return (serial + ... + to_key(args)) + std::string{"}"};
}