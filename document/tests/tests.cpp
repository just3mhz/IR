#include "tests.h"

#include "../document.h"
#include "../document_reader.h"
#include "../document_reader_iterator.h"

#include <regex>

namespace document::tests {

namespace {

void TestDocumentClass() {
    Document document(1, "1", "Some text");
    ASSERT_EQUAL(document.id(), 1);
    ASSERT_EQUAL(document.url(), "1");
    ASSERT_EQUAL(document.text(), "Some text");
}

void TestDocBeginRegex() {
    const std::regex docBeginRegex = DocumentReaderIterator::DOC_BEGIN_REGEX;

    {
        const string line = "This string doesn't match";
        ASSERT(!std::regex_match(line, docBeginRegex))
    }

    {
        std::string line = R"(<doc id="1" url="2" title="It's a match"> and junk)";
        ASSERT(!std::regex_match(line, docBeginRegex))
    }

    {
        std::string line = R"(<doc id="1" url="2" title="It's a match">)";
        std::smatch match;
        ASSERT(std::regex_match(line, match, docBeginRegex))
        ASSERT_EQUAL(match[1], "1")
        ASSERT_EQUAL(match[2], "2")
        ASSERT_EQUAL(match[3], "It's a match")
    }
}

void TestDocEndRegex() {
    const std::regex docEndRegex = DocumentReaderIterator::DOC_END_REGEX;

    {
        const string line = "This string doesn't match";
        ASSERT(!std::regex_match(line, docEndRegex))
    }

    {
        const string line = "</doc>";
        ASSERT(std::regex_match(line, docEndRegex))
    }

    {
        const string line = "</doc> and junk";
        ASSERT(!std::regex_match(line, docEndRegex))
    }
}

void TestDocumentReader() {
    const int64_t id[] = {1, 2, 3, 4, 5};
    const std::string url[] = {"1", "2", "3", "4", "5"};
    const std::string title[] = {
        "Let America Be America Again",
        "A Birthday Poem",
        "A Dream Within A Dream",
        "A Girl",
        "A Poet To His Beloved"
    };

    int idx = 0;
    DocumentReader reader("/home/just3mhz/IR/test_data/block01.xml");
    for(auto docIt = reader.begin(); docIt != reader.end(); ++docIt) {
        ASSERT_EQUAL((*docIt)->id(), id[idx])
        ASSERT_EQUAL((*docIt)->url(), url[idx])
        ASSERT_EQUAL((*docIt)->title(), title[idx])
        ++idx;
    }
}

} // namespace

void TestAll(const TestRunner& testRunner)
{
    RUN_TEST(testRunner, TestDocumentClass);
    RUN_TEST(testRunner, TestDocBeginRegex);
    RUN_TEST(testRunner, TestDocEndRegex);
    RUN_TEST(testRunner, TestDocumentReader);
}

}