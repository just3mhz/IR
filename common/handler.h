#pragma once

#include <string>
#include <functional>

namespace common {

class Handler {
public:
    explicit Handler(std::function<void(void)>);
    virtual ~Handler();

private:
    std::function<void(void)> callback_;
};

class PerformanceHandler final: Handler {
public:
    explicit PerformanceHandler(std::string eventName);
};

} // namespace common
