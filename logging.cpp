#include "logging.h"

#include <boost/log/core.hpp>
#include <boost/log/expressions.hpp>
#include <boost/log/trivial.hpp>
#include <boost/log/utility/setup/common_attributes.hpp>
#include <boost/log/utility/setup/file.hpp>

namespace {

static const std::string messageFormat = "[%TimeStamp%] [%Severity%] [%LineID%] %Message%";

}

void initLogging(const std::filesystem::path& logPath)
{
    namespace logging = boost::log;
    namespace keywords = boost::log::keywords;
    namespace attrs = boost::log::attributes;

    logging::register_simple_formatter_factory<logging::trivial::severity_level, char>("Severity");

//    logging::add_file_log(
//        keywords::file_name = logPath,
//        keywords::format = messageFormat);

    logging::core::get()->set_filter(
        logging::trivial::severity >= logging::trivial::trace);

    logging::add_common_attributes();
}