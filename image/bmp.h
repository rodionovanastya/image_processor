#ifndef WORKSHOPX_BMP_H
#define WORKSHOPX_BMP_H

#include "image.h"

#include <cstdint>
#include <iostream>

const uint16_t BMPHDR_SIGN = 0x4D42;
const uint32_t DIB_HEADER_SIZE = 40;

struct __attribute__((packed)) BmpHeader {
    uint16_t bfType;
    uint32_t bfSize;
    int16_t bfReserved1;
    int16_t bfReserved2;
    uint32_t bfOffBits;
};

struct __attribute__((packed)) DibHeader {
    uint32_t biSize;
    uint32_t biWidth;
    int32_t biHeight;
    uint16_t biPlanes;
    uint16_t biBitCount;
    uint32_t biCompression;
    uint32_t biSizeImage;
    int32_t biXPelsPerMeter;
    int32_t biYPelsPerMeter;
    uint32_t biClrUsed;
    uint32_t biClrImportant;
};

class BmpIO {
public:
    static void ReadBmpHeader(std::istream &istr, BmpHeader &header);
    static void ReadDibHeader(std::istream &istr, DibHeader &header);
    static void WriteBmpHeader(std::ostream &ostr, const BmpHeader &header);
    static void WriteDibHeader(std::ostream &ostr, const DibHeader &header);
    static Image Read(std::istream& istr);
    static void Write(std::ostream& ostr, const Image& image);
};

#endif //WORKSHOPX_BMP_H