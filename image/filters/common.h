#ifndef WORKSHOPX_COMMON_H
#define WORKSHOPX_COMMON_H

#include "../image.h"

#include <limits>

const uint8_t MAX_CHANNEL = std::numeric_limits<uint8_t>::max();
const uint8_t MIN_CHANNEL = std::numeric_limits<uint8_t>::min();
using Kernel = const std::vector<std::vector<double>>;

uint8_t NormalizeColor(int64_t c);

size_t NormalizeIndex(const int64_t ind, const size_t size);

Pixel CalcPixel(const Image& source, const size_t x, const size_t y, const Kernel &mtx);

void ApplyKernel(Image& image, const Kernel& mtx);

uint8_t Gray(const Pixel& p);

double GetSpread(const Image& image, const int64_t x1, const int64_t y1, const size_t radius);

Pixel GetAverage(const Image& image, const int64_t x1, const int64_t y1, const size_t radius);

#endif //WORKSHOPX_COMMON_H