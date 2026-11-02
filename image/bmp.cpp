#include "bmp.h"

#include <limits>
#include <stdexcept>
#include <vector>

namespace {

const size_t BYTES_PER_PIXEL = 3;
const size_t ROW_ALIGNMENT = 4;
const uint16_t BITS_PER_PIXEL = 24;
const uint32_t HEADERS_SIZE = sizeof(BmpHeader) + sizeof(DibHeader);

static_assert(sizeof(BmpHeader) == 14, "BmpHeader must be packed to 14 bytes");
static_assert(sizeof(DibHeader) == DIB_HEADER_SIZE, "DibHeader must be packed to 40 bytes");

size_t CalcRowSize(size_t width) {
    return (width * BYTES_PER_PIXEL + ROW_ALIGNMENT - 1) / ROW_ALIGNMENT * ROW_ALIGNMENT;
}

void CheckFitsBmp(const Image& image) {
    const uint64_t max_side = std::numeric_limits<int32_t>::max();
    const uint64_t max_pixel_bytes = std::numeric_limits<uint32_t>::max() - HEADERS_SIZE;
    if (image.GetWidth() > max_side || image.GetHeight() > max_side ||
        uint64_t(CalcRowSize(image.GetWidth())) * image.GetHeight() > max_pixel_bytes) {
        throw std::invalid_argument("image is too large for BMP format.");
    }
}

BmpHeader MakeBmpHeader(uint32_t pixel_bytes) {
    BmpHeader header{};
    header.bfType = BMPHDR_SIGN;
    header.bfSize = HEADERS_SIZE + pixel_bytes;
    header.bfOffBits = HEADERS_SIZE;
    return header;
}

DibHeader MakeDibHeader(const Image& image, uint32_t pixel_bytes) {
    DibHeader header{};
    header.biSize = DIB_HEADER_SIZE;
    header.biWidth = static_cast<int32_t>(image.GetWidth());
    header.biHeight = static_cast<int32_t>(image.GetHeight());
    header.biPlanes = 1;
    header.biBitCount = BITS_PER_PIXEL;
    header.biSizeImage = pixel_bytes;
    return header;
}

void WritePixels(std::ostream& ostr, const Image& image, size_t row_size) {
    std::vector<unsigned char> row(row_size, 0);
    for (size_t file_y = 0; file_y < image.GetHeight(); ++file_y) {
        const size_t y = image.GetHeight() - 1 - file_y;
        for (size_t x = 0; x < image.GetWidth(); ++x) {
            const Pixel& pixel = image.At(x, y);
            row[x * BYTES_PER_PIXEL] = pixel.GetB(); // в файле порядок BGR
            row[x * BYTES_PER_PIXEL + 1] = pixel.GetG();
            row[x * BYTES_PER_PIXEL + 2] = pixel.GetR();
        }
        ostr.write(reinterpret_cast<const char*>(row.data()),
                   static_cast<std::streamsize>(row_size));
    }
}

}  // namespace

void BmpIO::ReadBmpHeader(std::istream& istr, BmpHeader& header) {
    istr.read((char*)&header, sizeof(header));

    if (!istr) {
        throw std::invalid_argument("cannot read BMP header.");
    }
}
void BmpIO::ReadDibHeader(std::istream& istr, DibHeader& header) {
    istr.read((char*)&header, sizeof(header));

    if (!istr) {
        throw std::invalid_argument("failed to read DIB header.");
    }
    if (header.biSize != DIB_HEADER_SIZE) {
        throw std::invalid_argument("invalid DIB header size.");
    }
    if (header.biPlanes != 1 ||
        header.biBitCount != 24) {
        throw std::invalid_argument("only 24-bit BMP is supported.");
    }
}

Image BmpIO::Read(std::istream& istr) {
    BmpHeader bmp_header;
    DibHeader dib_header;

    ReadBmpHeader(istr, bmp_header);
    ReadDibHeader(istr, dib_header);
    
    int64_t width = dib_header.biWidth;
    int64_t height = dib_header.biHeight;
    if (height < 0) {
        height = -height;
    }

    const size_t row_size = CalcRowSize(width);
    Image image(width, height);
    std::vector<unsigned char> row(row_size);
    for (int file_y = 0; file_y < height; ++file_y) {
        istr.read((char*)row.data(), static_cast<std::streamsize>(row_size));
        if (!istr) {
            throw std::runtime_error("Failed to read BMP pixel data.");
        }
        const size_t y = dib_header.biHeight > 0
                          ? height - 1 - file_y
                          : file_y;

        for (size_t x = 0; x < width; ++x) {
            const size_t pos = x * 3;
            const uint8_t b = row[pos]; // в файле порядок BGR
            const uint8_t g = row[pos + 1];
            const uint8_t r = row[pos + 2];
            image.SetPixel(x, y, r, g, b);
        }
    }

    return image;
}

void BmpIO::WriteBmpHeader(std::ostream& ostr, const BmpHeader& header) {
    ostr.write((const char*)(&header), sizeof(header));
}

void BmpIO::WriteDibHeader(std::ostream& ostr, const DibHeader& header) {
    ostr.write((const char*)(&header), sizeof(header));
}

void BmpIO::Write(std::ostream& ostr, const Image& image) {
    CheckFitsBmp(image);
    const size_t row_size = CalcRowSize(image.GetWidth());
    const uint32_t pixel_bytes = row_size * image.GetHeight();

    WriteBmpHeader(ostr, MakeBmpHeader(pixel_bytes));
    WriteDibHeader(ostr, MakeDibHeader(image, pixel_bytes));
    WritePixels(ostr, image, row_size);
    if (!ostr) {
        throw std::runtime_error("failed to write BMP data.");
    }
}