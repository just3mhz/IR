#include "bsbi/bsbi.h"
#include "bsbi/inv_index_provider.h"
#include "logging.h"

#include "boost/program_options.hpp"
#include "boost/log/trivial.hpp"

namespace options = boost::program_options;

void buildIndex(
    const std::filesystem::path& documentsPath,
    const std::filesystem::path& outputPath)
{
    BOOST_LOG_TRIVIAL(info) << "Build index for " << documentsPath;
    bsbi::BlockedSortBasedIndexer indexer(10000);
    indexer.makeIndex(documentsPath, outputPath);
}

options::variables_map parseArgs(int argc, char** argv)
{
    options::variables_map variablesMap;
    options::options_description description("Making inverted index");
    auto addOptions = description.add_options();
    addOptions("help,h", "Help screen");
    addOptions("documents,d",
        options::value<std::filesystem::path>()->required(),
        "Path to file with documents");
    addOptions("output,o",
        options::value<std::filesystem::path>()->required(),
        "Path to output index");
    try {
        options::store(options::parse_command_line(argc, argv, description),
            variablesMap);
        options::notify(variablesMap);
    } catch (const options::error& ex) {
        std::cout << ex.what() << std::endl;
        std::cout << description << std::endl;
        std::exit(0);
    }
    return variablesMap;
}

int main(int argc, char** argv)
{
    auto variablesMap = parseArgs(argc, argv);
    initLogging("index_builder.log");
    buildIndex(variablesMap["documents"].as<std::filesystem::path>(),
        variablesMap["output"].as<std::filesystem::path>());
    return 0;
}
