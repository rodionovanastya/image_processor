#include "filters.h"

#include <cmath>

namespace {

using GaussKernel = std::vector<double>;

const GaussKernel MakeGaussKernel(const double sigma, const size_t max_radius) {
    const int64_t r = static_cast<int64_t>(std::min(static_cast<double>(max_radius), std::ceil(3 * sigma)));
    GaussKernel kernel(2 * r + 1);
    double sum = 0;
    for (int64_t d = -r; d <= r; ++d) {
        const double w = std::exp(-(d * d) / (2.0 * sigma * sigma));
        kernel[d + r] = w;
        sum += w;
    }
    for (double& w : kernel) {
        w /= sum;
    }
    return kernel;
}

} //namespace

void BlurFilter::Apply(Image& image) const {
    class DoublePixel {
    public:
        double r;
        double g;
        double b;
    };

    const GaussKernel kernel = MakeGaussKernel(sigma_, std::max(image.GetWidth(), image.GetHeight()));
    const int64_t r = kernel.size() / 2;
    std::vector<DoublePixel> rows(image.GetWidth() * image.GetHeight());
    for (size_t y = 0; y < image.GetHeight(); ++y) {
        for (size_t x = 0; x < image.GetWidth(); ++x) {
            double R = 0;
            double G = 0;
            double B = 0;
            for (int64_t d = -r; d <= r; ++d) {
                const Pixel& p = image.At(NormalizeIndex(static_cast<int64_t>(x) + d, image.GetWidth()), y);
                R += p.GetR() * kernel[d + r];
                G += p.GetG() * kernel[d + r];
                B += p.GetB() * kernel[d + r];
            }
            rows[y * image.GetWidth() + x] = DoublePixel{R, G, B};
        }
    }
    for (size_t y = 0; y < image.GetHeight(); ++y) {
        for (size_t x = 0; x < image.GetWidth(); ++x) {
            double R = 0;
            double G = 0;
            double B = 0;
            for (int64_t d = -r; d <= r; ++d) {
                const size_t Y = NormalizeIndex(static_cast<int64_t>(y) + d, image.GetHeight());
                const DoublePixel& p = rows[Y * image.GetWidth() + x];
                R += p.r * kernel[d + r];
                G += p.g * kernel[d + r];
                B += p.b * kernel[d + r];
            }
            image.SetPixel(x, y, NormalizeColor(std::round(R)), NormalizeColor(std::round(G)), NormalizeColor(std::round(B)));
        }
    }
}
