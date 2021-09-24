#include "utils.h"

namespace common {

void throwIf(bool condition, const std::string& message) {
    if (condition) {
        throw std::runtime_error(message);
    }
}

}