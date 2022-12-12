#ifndef POELITE_LOGGER_HPP
#define POELITE_LOGGER_HPP

#include <string>
#include <fstream>

class Logger {
    static std::ofstream open_log_file();
    static std::string current_timestamp();

public:
    static const char* const LOG_FILE;
    static void warn(std::string const& msg);
    static void log(std::string const& msg);

};

#endif
