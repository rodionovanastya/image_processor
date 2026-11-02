#include "filter_producers.h"
#include "filter.h"

#include <cctype>
#include <cmath>
#include <stdexcept>
#include <string>

namespace {

size_t ParseInt(const char* text, const char* name) {
    size_t val = 0;
    for (const char* c = text; *c != '\0'; ++c) {
        if (!std::isdigit(*c)) {
            throw std::invalid_argument(name + (std::string)" is a pisitive integer");
        }
        val = 10 * val + (*c - '0');
    }
    return val;
}

double ParseDouble(const char* text, const char* name) {
    double val = 0.0;
    bool was_dot = false;
    double curr_pow = 1;
    for (const char* c = text; *c != '\0'; ++c) {
        if (*c == '.') {
            if (was_dot) {
                throw std::invalid_argument(name + (std::string)" is a positive double");
            }
            was_dot = true;
        } else if (!std::isdigit(*c)) {
            throw std::invalid_argument(name + (std::string)" is a positive double");
        } else {
            if (was_dot) {
                curr_pow *= 10;
                val += (*c - '0') / curr_pow;
            } else {
                val = 10 * val + (*c - '0');
            }
        }
    }
    return val;
}

std::string ToString(const size_t x) {
    std::string s;
    size_t n = x;
    while (n > 0) {
        s += '0' + n % 10;
        n /= 10;
    }
    if (s.empty()) {
        s = "0";
    }
    std::string res;
    for (int64_t i = s.size() - 1; i >= 0; --i) {
        res += s[i];
    }
    return res;
}

} //namespace

AbstractFilter* NegativeProducer(const FilterDescriptor& fd) {
    if (!fd.args.empty()) {
        throw std::invalid_argument("negative filter takes no parameters.");
    }
    return new NegativeFilter();
}

AbstractFilter* GrayscaleProducer(const FilterDescriptor& fd) {
    if (!fd.args.empty()) {
        throw std::invalid_argument("grayscale filter takes no parameters.");
    }
    return new GrayscaleFilter();
}

AbstractFilter* CropProducer(const FilterDescriptor& fd) {
    if (fd.args.size() != 2) {
        throw std::invalid_argument("crop filter takes 2 parameters.");
    }
    size_t width = ParseInt(fd.args[0], "crop width");
    size_t height = ParseInt(fd.args[1], "crop height");
    if (width == 0 || height == 0) {
        throw std::invalid_argument("crop filter takes positive parameters.");
    }
    return new CropFilter(width, height);
}

AbstractFilter* SharpeningProducer(const FilterDescriptor& fd) {
    if (!fd.args.empty()) {
        throw std::invalid_argument("sharp filter takes no parameters.");
    }
    return new SharpeningFilter();
}

AbstractFilter* EdgeDetectionProducer(const FilterDescriptor& fd) {
    if (fd.args.size() != 1) {
        throw std::invalid_argument("edge-detection filter takes 1 parameter.");
    }
    double threshold = ParseDouble(fd.args[0], "edge-detection threshold");
    if (threshold > 1) {
        throw std::invalid_argument("edge-detection threshold is a double from [0, 1]");
    }
    return new EdgeDetectionFilter(threshold);
}

AbstractFilter* BlurProducer(const FilterDescriptor& fd) {
    if (fd.args.size() != 1) {
        throw std::invalid_argument("blur filter takes 1 parameter.");
    }
    double sigma = ParseDouble(fd.args[0], "blur sigma");
    if (!(sigma > 0.0) || !std::isfinite(sigma)) {
        throw std::invalid_argument("blur sigma is a positive number.");
    }
    return new BlurFilter(sigma);
}

AbstractFilter* KuwaharaProducer(const FilterDescriptor& fd) {
    if (fd.args.size() != 1) {
        throw std::invalid_argument("kuwahara filter takes 1 parameter.");
    }
    size_t radius = ParseInt(fd.args[0], "kuwahara radius");
    if (radius == 0 || radius > KuwaharaFilter::max_radius) {
        throw std::invalid_argument("kuwahara radius is a positive integer from [1, " + ToString(KuwaharaFilter::max_radius) + "].");
    }
    return new KuwaharaFilter(radius);
}