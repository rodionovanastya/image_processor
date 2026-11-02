#include "filters.h"

void CropFilter::Apply(Image& image) const {
    image.Crop(width_, height_);
}
