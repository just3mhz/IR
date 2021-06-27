#pragma once

#include <string>

namespace document {

class Document {
public:
    Document() = default;
    Document(uint64_t id, std::string url, std::string title, std::string text);

    uint64_t& id();
    const uint64_t& id() const;

    std::string& url();
    const std::string& url() const;

    std::string& title();
    const std::string& title() const;

    std::string& text();
    const std::string& text() const;
private:
    uint64_t id_{0};
    std::string url_;
    std::string title_;
    std::string text_;
};

} // namespace document
