#ifndef WORKSHOPX_IMAGE_H
#define WORKSHOPX_IMAGE_H

#include <cstddef>
#include <vector>
#include <stdint.h>


class Pixel {
public:
    Pixel()
        : r_(0)
        , g_(0)
        , b_(0)
    {
    }

    Pixel(const uint8_t r, const uint8_t g, const uint8_t b)
        : r_(r)
        , g_(g)
        , b_(b)
    {
    }

    uint8_t GetR() const { return r_; }
    uint8_t GetG() const { return g_; }
    uint8_t GetB() const { return b_; }

    void SetR(const uint8_t r) { r_ = r; }
    void SetG(const uint8_t g) { g_ = g; }
    void SetB(const uint8_t b) { b_ = b; }
    void Set(const uint8_t c) { r_ = g_ = b_ = c; }

private:
    uint8_t r_;
    uint8_t g_;
    uint8_t b_;
};


class Image {
public:
    Image() = default;

    Image(const size_t width, const size_t height);

    size_t GetWidth() const;
    size_t GetHeight() const;

    Pixel& At(const size_t x, const size_t y);
    const Pixel& At(const size_t x, const size_t y) const;

    void SetPixel(const size_t x, const size_t y, const uint8_t r, const uint8_t g, const uint8_t b);
    void SetPixel(const size_t x, const size_t y, const Pixel p);
    void Crop(const size_t width, const size_t height);

private:
    // pixels_[y][x]
    std::vector<std::vector<Pixel>> pixels_;
};

#endif // WORKSHOPX_IMAGE_H