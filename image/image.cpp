#include "image.h"

#include <algorithm>
#include <stdexcept>

Image::Image(size_t width, size_t height) {
    if ((width == 0) != (height == 0)) {
        throw std::invalid_argument("both width and height must be zero or non-zero.");
    }
    pixels_.assign(height, std::vector<Pixel>(width));
}

size_t Image::GetWidth() const {
    return pixels_.empty() ? 0 : pixels_[0].size();
}

size_t Image::GetHeight() const {
    return pixels_.size();
}

Pixel& Image::At(const size_t x, const size_t y) {
    if (y < 0 || y >= GetHeight()) {
        throw std::out_of_range("incorrect y.");
    } if (x < 0 || x >= GetWidth()) {
        throw std::out_of_range("incorrect x.");
    }
    return pixels_[y][x];
}

const Pixel& Image::At(const size_t x, const size_t y) const {
    if (y < 0 || y >= GetHeight()) {
        throw std::out_of_range("incorrect y.");
    } if (x < 0 || x >= GetWidth()) {
        throw std::out_of_range("incorrect x.");
    }
    return pixels_[y][x];
}


void Image::SetPixel(const size_t x, const size_t y, const uint8_t r, const uint8_t g, const uint8_t b) {
    pixels_[y][x].SetR(r);
    pixels_[y][x].SetG(g);
    pixels_[y][x].SetB(b);
}

void Image::SetPixel(const size_t x, const size_t y, const Pixel p) {
    pixels_[y][x].SetR(p.GetR());
    pixels_[y][x].SetG(p.GetG());
    pixels_[y][x].SetB(p.GetB());
}

void Image::Crop(const size_t width, const size_t height) {
    const size_t h = std::min(height, GetHeight());
    const size_t w = std::min(width, GetWidth());
    pixels_.resize(h);
    for (int y = 0; y < h; ++y) {
        pixels_[y].resize(w);
    }
}
