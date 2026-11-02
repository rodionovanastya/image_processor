#include "filters.h"

namespace {

Kernel SHARPENING_KERNEL = {
    { 0, -1,  0},
    {-1,  5, -1},
    { 0, -1,  0},
};

} //namespace

void SharpeningFilter::Apply(Image& image) const {
    ApplyKernel(image, SHARPENING_KERNEL);
}
