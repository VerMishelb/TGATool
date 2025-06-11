/**
 * DebugLog.h, 25.04.2025
 * Implements log_print on top of std::print that prints as "file.cpp:line, func(): {fmt}".
 * Requires C++23 to work.
 * Copyright © 2025 VerMishelb <vermishelb535@gmail.com>.
 * Licensed under the MIT License. Please refer to an online copy.
 */
#ifndef MISH_DEBUGLOG_H
#define MISH_DEBUGLOG_H

#include <print>
#include <source_location>
#include <string_view>

std::string_view _get_filename(const std::string_view& path) {
    const size_t pos = path.find_last_of("/\\");
    return (pos == std::string_view::npos) ? path : path.substr(pos + 1);
}

template <typename... Args>
void _log_print_impl(const std::source_location& loc, FILE* descriptor, const char* log_level,
                     std::format_string<Args...> fmt, Args&&... args) {
    std::println(descriptor, "{}{}:{}, {}: {}", log_level, _get_filename(loc.file_name()), loc.line(),
                 loc.function_name(), std::format(fmt, std::forward<Args>(args)...));
}
#define log_print(...) _log_print_impl(std::source_location::current(), stdout, "", __VA_ARGS__)
#define log_perror(...) _log_print_impl(std::source_location::current(), stderr, "[Error] ", __VA_ARGS__)
#define log_pinfo(...) _log_print_impl(std::source_location::current(), stderr, "[Info] ", __VA_ARGS__)

#endif