#include "filters.h"

void GrayscaleFilter::Apply(Image& image) const {
    for (size_t y = 0; y < image.GetHeight(); ++y) {
        for (size_t x = 0; x < image.GetWidth(); ++x) {
            Pixel& pixel = image.At(x, y);
            pixel.Set(Gray(pixel));
        }
    }
}
