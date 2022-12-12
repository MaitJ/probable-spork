#include "logger.hpp"
#include <fmt/core.h>
#include <chrono>
#include <iomanip>
#include <cassert>

const char* const Logger::LOG_FILE = "log.txt";

std::ofstream Logger::open_log_file() {
    std::ofstream log_file(Logger::LOG_FILE);
    if (log_file.fail()) {
        fmt::print("[ERROR]: Failed to open log file");
    }
    assert(!log_file.fail());
    return log_file;
}

std::string Logger::current_timestamp() {
    const auto now = std::chrono::system_clock::now();
    const auto time_t = std::chrono::system_clock::to_time_t(now);
    std::stringstream str_s;
    str_s.imbue(std::locale("en_US.utf8"));
    str_s << std::put_time(std::localtime(&time_t), "%F %T");

    return str_s.str();
}

void Logger::warn(std::string const& msg) {
    std::ofstream log_file = open_log_file();
    std::string log_row = fmt::format("[WARN] ({}): {}\n", current_timestamp(), msg);

    log_file << log_row;
    log_file.close();
}
void Logger::log(std::string const& msg) {
    std::ofstream log_file = open_log_file();
    std::string log_row = fmt::format("[LOG] ({}): {}", current_timestamp(), msg);

    log_file << log_row;
    log_file.close();
}
