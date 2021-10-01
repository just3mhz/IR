#include "bsbi/bsbi.h"

#include "boost/program_options.hpp"

void buildIndex(const std::filesystem::path& documentsPath) {
    std::cout << "Build index for " << documentsPath << std::endl;
}

int main(int argc, char** argv) {
    namespace options = boost::program_options;
    try {
        options::options_description description("Making inverted index");
        description.add_options()
            ("help,h", "Help screen")
            ("documents", options::value<std::filesystem::path>(), "Path to file with documents");
        options::variables_map variablesMap;
        options::store(
            options::parse_command_line(argc, argv, description),
            variablesMap);

        if (variablesMap.count("help"))
            std::cout << description << '\n';
        if (variablesMap.count("documents"))
            buildIndex(variablesMap.at("documents").as<std::filesystem::path>());
    } catch (const options::error& ex) {
        std::cerr << ex.what() << std::endl;
    }
    return 0;
}
