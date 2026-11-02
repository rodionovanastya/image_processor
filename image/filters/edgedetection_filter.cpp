#include "filters.h"

namespace {

Kernel EDGE_DETECTION_KERNEL = {
    { 0, -1,  0},
    {-1,  4, -1},
    { 0, -1,  0},
};

} //namespace

void EdgeDetectionFilter::Apply(Image& image) const {
    GrayscaleFilter().Apply(image);
    ApplyKernel(image, EDGE_DETECTION_KERNEL);
    for (size_t y = 0; y < image.GetHeight(); ++y) {
        for (size_t x = 0; x < image.GetWidth(); ++x) {
            Pixel& p = image.At(x, y);
            if (p.GetR() > threshold_ * MAX_CHANNEL) {
                p.Set(MAX_CHANNEL);
            } else {
                p.Set(MIN_CHANNEL);
            }
        }
    }
}