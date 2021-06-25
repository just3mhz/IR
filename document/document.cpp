#include "document.h"

namespace document {

Document::Document(uint64_t id, std::string url, std::string text)
    : id_(id)
    , url_(std::move(url))
    , text_(std::move(text))
{
}

uint64_t& Document::id()
{
    return id_;
}

const uint64_t& Document::id() const
{
    return id_;
}

std::string& Document::url()
{
    return url_;
}

const std::string& Document::url() const
{
    return url_;
}

std::string& Document::text()
{
    return text_;
}

const std::string& Document::text() const
{
    return text_;
}
std::string& Document::title()
{
    return title_;
}

const std::string& Document::title() const
{
    return title_;
}

} // namespace document