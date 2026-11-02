#ifndef WORKSHOPX_PIPELINE_H
#define WORKSHOPX_PIPELINE_H

#include <memory>
#include <vector>

#include "filter.h"
#include "image.h"



enum class FilterOddEven {
    Even,
    Odd,
};


class Pipeline {
public:
    Pipeline() = default;

    Pipeline(const Pipeline&) = delete; // копирование
    Pipeline& operator=(const Pipeline&) = delete; // копирующее присваивание

    Pipeline(Pipeline&&) = default; //перемещ конструктор
    Pipeline& operator=(Pipeline&&) = default; // перемещ присваивание

    AbstractFilter* AddFilter(AbstractFilter* filter);
    void AddFilter(std::unique_ptr<AbstractFilter>&& filter_ptr);

    void SelectFilters(FilterOddEven even_odd);
    std::vector<std::unique_ptr<AbstractFilter>>& GetFilters() { return filters_; }

    void Apply(Image& image) const;

private:
    std::vector<std::unique_ptr<AbstractFilter>> filters_;
};

#endif //WORKSHOPX_PIPELINE_H