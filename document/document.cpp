#include "document.h"

#include <iostream>

namespace document {

namespace {

template <class T>
std::ostream& operator<<(std::ostream& os, const std::vector<T>& v)
{
    os << "[";
    bool first = true;
    for (const T& t: v) {
        if (!first) {
            os << ", ";
        }
        first = false;
        os << t;
    }
    os << "]";
    return os;
}

}

Document::Document(uint64_t id, std::string url, std::vector<std::string> title, std::vector<std::string> text)
    : id_(id)
    , url_(std::move(url))
    , title_(std::move(title))
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

std::vector<std::string>& Document::text()
{
    return text_;
}

const std::vector<std::string>& Document::text() const
{
    return text_;
}
std::vector<std::string>& Document::title()
{
    return title_;
}

const std::vector<std::string>& Document::title() const
{
    return title_;
}

std::ostream& operator<<(std::ostream& os, const Document& document)
{
    os << "DocId: " << document.id() << '\n';
    os << "Url: " << document.url() << '\n';
    os << "Title: " << document.title() << '\n';
    os << "Text: " << document.text() << '\n';
    return os;
}

} // namespace document