#include "parser.h"

#include <cctype>
#include <cstring>
#include <stdexcept>
#include <string>

namespace {

const int INPUT_FILE_INDEX = 1;
const int OUTPUT_FILE_INDEX = 2;
const int FIRST_FILTER_INDEX = 3;
const char FILTER_PREFIX = '-';
const char* const FILENAME_SUFFIX = ".bmp";

bool IsFilterName(const char* arg) {
    if (arg[0] != FILTER_PREFIX || arg[1] == '\0') {
        return false;
    }
    return !std::isdigit(static_cast<unsigned char>(arg[1])) && arg[1] != '.';
}

void CheckFileExtension(const char* file_name) {
    if (std::strcmp(file_name + std::strlen(file_name) - std::strlen(FILENAME_SUFFIX), FILENAME_SUFFIX)) {
        throw std::invalid_argument("take only .bmp files.");
    }
}

}  // namespace

Parser::Result Parser::Parse(int argc, char* argv[]) {
    if (argc <= INPUT_FILE_INDEX) {
        return Result::NoArguments;
    }
    if (argc <= OUTPUT_FILE_INDEX) {
        return Result::NoOutputFile;
    }
    inputFileName_ = argv[INPUT_FILE_INDEX];
    CheckFileExtension(inputFileName_);
    outputFileName_ = argv[OUTPUT_FILE_INDEX];
    CheckFileExtension(outputFileName_);
    return ParseFilters(argc, argv);
}

Parser::Result Parser::ParseFilters(int argc, char* argv[]) {
    for (int i = FIRST_FILTER_INDEX; i < argc; ++i) {
        if (IsFilterName(argv[i])) {
            filters_.push_back(FilterDescriptor{argv[i] + 1, {}});
        } else if (filters_.empty()) {
            return Result::UnknownArgument;
        } else {
            filters_.back().args.push_back(argv[i]);
        }
    }
    return Result::Ok;
}