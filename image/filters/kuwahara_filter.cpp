#include "filters.h"

void KuwaharaFilter::Apply(Image& image) const {
    const Image source = image;
    for (int64_t x = 0; x < image.GetWidth(); ++x) {
        for (int64_t y = 0; y < image.GetHeight(); ++y) {
            int64_t curr_x = x - radius_;
            int64_t curr_y = y - radius_;
            double curr_res = GetSpread(source, x - radius_, y - radius_, radius_ + 1);
            for (int64_t dx = -1; dx <= 0; ++dx) {
                for (int64_t dy = -1; dy <= 0; ++dy) {
                    double res = GetSpread(source, x + dx * radius_, y + dy * radius_, radius_ + 1);
                    if (res < curr_res) {
                        curr_res = res;
                        curr_x = x + dx * radius_;
                        curr_y = y + dy * radius_;
                    } 
                }
            }
            image.SetPixel(x, y, GetAverage(source, curr_x, curr_y, radius_ + 1));
        }
    }
}
