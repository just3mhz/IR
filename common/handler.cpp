#include "handler.h"

#include <chrono>

#include <boost/log/trivial.hpp>

namespace common {

Handler::Handler(std::function<void(void)> callback)
    : callback_(std::move(callback))
{
}

Handler::~Handler()
{
    callback_();
}

PerformanceHandler::PerformanceHandler(std::string eventName)
    : Handler([start = std::chrono::steady_clock::now(), eventName = std::move(eventName)] {
        auto end = std::chrono::steady_clock::now();
        auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();
        BOOST_LOG_TRIVIAL(trace) << "{event_type: \"performance\", event_name: \""
                                 << eventName << "\", event_value: \"" << duration << " ms\"}";
    })
{}

} // namespace common
