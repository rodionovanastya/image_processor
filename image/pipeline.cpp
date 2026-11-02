#include "pipeline.h"

#include <stdexcept>

Pipeline& SelectFilters(Pipeline& p, FilterOddEven even_odd) {
    Pipeline pl = Pipeline();
    int i = 0;
    for (std::unique_ptr<AbstractFilter>& ptr : p.GetFilters()) {
        if (even_odd == FilterOddEven::Even && i % 2 == 1 || even_odd == FilterOddEven::Odd && i % 2 == 0) {
            pl.AddFilter(std::move(ptr));
        }
        i++;
    }
    return p = std::move(pl);
}

AbstractFilter* Pipeline::AddFilter(AbstractFilter* filter) {
    if (!filter) {
        throw std::invalid_argument("cannot add empty filter to pipeline.");
    }
    std::unique_ptr<AbstractFilter> owned(filter);
    filters_.push_back(std::move(owned));
    return filters_.back().get();
}

void Pipeline::SelectFilters(FilterOddEven even_odd) {
    std::vector<std::unique_ptr<AbstractFilter>>::iterator it = filters_.begin();
    for (size_t i = 0; i < filters_.size(); ++i) {
        if (even_odd == FilterOddEven::Even && i % 2 == 0 || even_odd == FilterOddEven::Odd && i % 2 == 1) {
            it = filters_.erase(it);
        } else {
            ++it;
        }
    }
}

void Pipeline::AddFilter(std::unique_ptr<AbstractFilter>&& filter_ptr) {
    filters_.emplace_back(std::move(filter_ptr));
}

void Pipeline::Apply(Image& image) const {
    for (const std::unique_ptr<AbstractFilter>& filter : filters_) {
        filter->Apply(image);
    }
}
