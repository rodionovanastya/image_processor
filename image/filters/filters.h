#ifndef WORKSPACEX_FILTERS_H
#define WORKSPACEX_FILTERS_H

#include "abstract_filter.h"
#include "common.h"

class BlurFilter : public AbstractFilter {
public:
    BlurFilter(const double sigma)
        : sigma_(sigma)
    {
    };

    void Apply(Image& image) const override;
private:
    const double sigma_;
};

class CropFilter : public AbstractFilter {
public:
    CropFilter(const size_t width, const size_t height) 
        : width_(width)
        , height_(height)
    {
    }
    void Apply(Image& image) const override;

private:
    size_t width_;
    size_t height_;
};

class EdgeDetectionFilter : public AbstractFilter {
public:
    EdgeDetectionFilter(const double threshold)
        : threshold_(threshold)
    {
    };

    void Apply(Image& image) const override;
private:
    const double threshold_;
};

class GrayscaleFilter : public AbstractFilter {
public:
    void Apply(Image& image) const override;
};

class KuwaharaFilter : public AbstractFilter {
public:
    KuwaharaFilter(const size_t radius)
        : radius_(radius)
    {
    };

    void Apply(Image& image) const override;
    static const size_t max_radius = 15;
private:
    const size_t radius_;
};

class NegativeFilter : public AbstractFilter {
public:
    void Apply(Image& image) const override;
};

class SharpeningFilter : public AbstractFilter {
public:
    void Apply(Image& image) const override;
};

#endif //WORKSPACEX_FILTERS_H
