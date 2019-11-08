#include <ctime>
// logging
#include "spdlog/sinks/basic_file_sink.h"
#include "spdlog/sinks/daily_file_sink.h"
#include "spdlog/sinks/stdout_color_sinks.h"
#include "spdlog/spdlog.h"

namespace Utility
{
namespace Logging
{

void setup_logger();

}; // namespace Logging
}; // namespace Utility