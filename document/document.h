#pragma once

#include <string>
#include <vector>

namespace document {

class Document {
public:
    Document() = default;
    Document(uint64_t id, std::string url, std::vector<std::string> title, std::vector<std::string> text);

    uint64_t& id();
    const uint64_t& id() const;

    std::string& url();
    const std::string& url() const;

    std::vector<std::string>& title();
    const std::vector<std::string>& title() const;

    std::vector<std::string>& text();
    const std::vector<std::string>& text() const;
private:
    uint64_t id_{0};
    std::string url_;
    std::vector<std::string> title_;
    std::vector<std::string> text_;
};

std::ostream& operator<<(std::ostream& os, const Document& document);

} // namespace document
