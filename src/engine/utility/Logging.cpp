#include "Logging.h"

void Utility::Logging::setup_logger()
{
    // std::vector<spdlog::sink_ptr> sinks;

    // // create console colored log sink
    // sinks.push_back(std::make_shared<spdlog::sinks::stdout_color_sink_st>());

    // // create filename for log file
    // time_t timer;
    // struct tm* timeinfo;
    // time(&timer);
    // timeinfo = localtime(&timer);
    // char time_buffer[100];
    // auto time_str = strftime(time_buffer, 100, "%F_%X", timeinfo);

    // std::string filename =
    //     std::string("logs/") + time_buffer + std::string(".log");

    // // create file log sink
    // sinks.push_back(std::make_shared<spdlog::sinks::basic_file_sink_mt>(
    //     filename.c_str(), true));

    // // create logger object from sinks
    // auto file_conlsole_logger =
    //     std::make_shared<spdlog::logger>("TtG_logs", begin(sinks), end(sinks));

    // // make it global
    // spdlog::register_logger(file_conlsole_logger);

    // // set as default
    // spdlog::set_default_logger(file_conlsole_logger);
}