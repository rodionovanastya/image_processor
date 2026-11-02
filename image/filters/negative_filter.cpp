#include "filters.h"

void NegativeFilter::Apply(Image& image) const {
    for (size_t y = 0; y < image.GetHeight(); ++y) {
        for (size_t x = 0; x < image.GetWidth(); ++x) {
            Pixel& pixel = image.At(x, y);
            pixel.SetR(MAX_CHANNEL - pixel.GetR());
            pixel.SetG(MAX_CHANNEL - pixel.GetG());
            pixel.SetB(MAX_CHANNEL - pixel.GetB());
        }
    }
}