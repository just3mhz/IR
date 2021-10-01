#include "bsbi/bsbi.h"

#include "boost/program_options.hpp"

namespace options = boost::program_options;

void buildIndex(
    const std::filesystem::path& documentsPath,
    const std::filesystem::path& outputPath)
{
    std::cout << "Build index for " << documentsPath << std::endl;
    bsbi::BlockedSortBasedIndexer indexer(2);
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
    buildIndex(variablesMap["documents"].as<std::filesystem::path>(),
        variablesMap["output"].as<std::filesystem::path>());
    return 0;
}
