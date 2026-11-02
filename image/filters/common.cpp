#include "common.h"


uint8_t NormalizeColor(int64_t c) {
    if (c > MAX_CHANNEL) {
        c = MAX_CHANNEL;
    }
    if (c < MIN_CHANNEL) {
        c = MIN_CHANNEL;
    }
    return static_cast<uint8_t>(c);
}

size_t NormalizeIndex(const int64_t ind, const size_t size) {
    size_t res;
    if (ind < 0) {
        res = 0;
    } else if (ind >= size) {
        res = size - 1;
    } else {
        res = ind;
    }
    return res;
}

Pixel CalcPixel(const Image& source, const size_t x, const size_t y, const Kernel &mtx) {
    int64_t R = 0;
    int64_t G = 0;
    int64_t B = 0;
    int64_t r = mtx.size() / 2;
    for (int64_t dx = -r; dx <= r; ++dx) {
        for (int64_t dy = -r; dy <= r; ++dy) {
            const size_t X = NormalizeIndex(static_cast<int64_t>(x) + dx, source.GetWidth());
            const size_t Y = NormalizeIndex(static_cast<int64_t>(y) + dy, source.GetHeight());
            const Pixel source_p = source.At(X, Y);
            R += source_p.GetR() * mtx[dy + r][dx + r];
            G += source_p.GetG() * mtx[dy + r][dx + r];
            B += source_p.GetB() * mtx[dy + r][dx + r];
        }
    }
    return Pixel(NormalizeColor(R), NormalizeColor(G), NormalizeColor(B));
}

void ApplyKernel(Image& image, const Kernel& mtx) {
    Image source = image;
    for (size_t y = 0; y < image.GetHeight(); ++y) {
        for (size_t x = 0; x < image.GetWidth(); ++x) {
            image.SetPixel(x, y, CalcPixel(source, x, y, mtx));
        }
    }
}

uint8_t Gray(const Pixel& p) {
    return 0.299 * p.GetR() + 0.587 * p.GetG() + 0.114 * p.GetB();
}

double GetSpread(const Image& image, const int64_t x1, const int64_t y1, const size_t radius) {
    double avg_f2 = 0;
    double avg_f = 0;

    for (int64_t x = x1; x < x1 + radius; ++x) {
        for (int64_t y = y1; y < y1 + radius; ++y) {
            uint16_t f = Gray(image.At(NormalizeIndex(x, image.GetWidth()), NormalizeIndex(y, image.GetHeight())));
            avg_f2 += f * f;
            avg_f += f;
        }
    }
    avg_f2 /= (radius * radius);
    avg_f /= (radius * radius);

    return avg_f2 - avg_f * avg_f;
}

Pixel GetAverage(const Image& image, const int64_t x1, const int64_t y1, const size_t radius) {
    uint64_t R = 0;
    uint64_t G = 0;
    uint64_t B = 0;
    for (int64_t x = x1; x < x1 + radius; ++x) {
        for (int64_t y = y1; y < y1 + radius; ++y) {
            const Pixel& p = image.At(NormalizeIndex(x, image.GetWidth()), NormalizeIndex(y, image.GetHeight()));
            R += p.GetR();
            G += p.GetG();
            B += p.GetB();
        }
    }
    size_t S = radius * radius;
    return Pixel(R / S, G / S, B / S);
}
