#include "application.h"

#include "bmp.h"
#include "filter_producers.h"

#include <fstream>
#include <iostream>
#include <stdexcept>
#include <string>

namespace {

    const char* const HELP_TEXT = R"(Usage:
  image_processor <input.bmp> <output.bmp> [-filter [param ...]] ...

Filters (applied in the order listed):
  -crop width height   keep the top-left width x height part
  -gs                  grayscale
  -neg                 negative
  -sharp               sharpening
  -edge threshold      edge detection
  -blur sigma          gaussian blur
  -kuwahara radius     kuwahara filter

Example:
  image_processor input.bmp output.bmp -crop 800 600 -gs -blur 0.5
)";


const char* DescribeParseResult(Parser::Result result) {
    switch (result) {
        case Parser::Result::NoArguments:
            return "no arguments given.";
        case Parser::Result::NoOutputFile:
            return "output file is not specified.";
        case Parser::Result::UnknownArgument:
            return "unexpected argument before the first filter.";
    }
    return "invalid command line.";
}

Image LoadImage(const char* file_name) {
    std::ifstream file(file_name, std::ios_base::in | std::ios_base::binary);
    if (!file.is_open()) {
        throw std::runtime_error(std::string("cannot open input file: ") + file_name + ".");
    }
    return BmpIO::Read(file);
}

void SaveImage(const Image& image, const char* file_name) {
    std::ofstream file(file_name, std::ios_base::out | std::ios_base::binary);
    if (!file.is_open()) {
        throw std::runtime_error(std::string("cannot open output file: ") + file_name + ".");
    }
    BmpIO::Write(file, image);
    file.close();
    if (!file) {
        throw std::runtime_error(std::string("failed to write output file: ") + file_name + ".");
    }
}

}  // namespace

void Application::Init() {
    filter_factory_.AddFilterProducer("neg", &NegativeProducer);
    filter_factory_.AddFilterProducer("gs", &GrayscaleProducer);
    filter_factory_.AddFilterProducer("crop", &CropProducer);
    filter_factory_.AddFilterProducer("sharp", &SharpeningProducer);
    filter_factory_.AddFilterProducer("edge", &EdgeDetectionProducer);
    filter_factory_.AddFilterProducer("blur", &BlurProducer);
    filter_factory_.AddFilterProducer("kuwahara", &KuwaharaProducer);
}

void Application::Run(int argc, char* argv[]) {
    const Parser::Result result = parser_.Parse(argc, argv);
    if (result == Parser::Result::NoArguments) {
        std::cout << HELP_TEXT;
        return;
    }
    if (result != Parser::Result::Ok) {
        throw std::invalid_argument(DescribeParseResult(result));
    }
    const Pipeline pipeline = filter_factory_.CreatePipeline(parser_.GetFilters());
    Image image = LoadImage(parser_.GetInputFileName());
    pipeline.Apply(image);
    SaveImage(image, parser_.GetOutputFileName());
}