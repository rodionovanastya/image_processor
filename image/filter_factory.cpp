#include "filter_factory.h"
#include <stdexcept>
#include <string>

Pipeline FilterFactory::CreatePipeline(const std::vector<FilterDescriptor>& fds) {
    Pipeline pl = Pipeline();
    for (const FilterDescriptor& fd : fds) {
        FilterProducerPtr ptr = GetProducer(fd.name);
        if (!ptr) {
            throw std::invalid_argument(std::string("unknown filter: -") + fd.name + ".");
        }
        AbstractFilter* filter = ptr(fd);
        if (!filter) {
            throw std::invalid_argument(std::string("cannot create filter: -") + fd.name + ".");
        }
        pl.AddFilter(filter);
    }
    return pl;
}

FilterFactory::FilterProducerPtr FilterFactory::AddFilterProducer(const char* filter_name, FilterProducerPtr producer) {
    if (!filter_name || !producer) {
        throw std::invalid_argument("filter producer needs a name and a function.");
    }
    if (!producers_.emplace(filter_name, producer).second) { //вставка не произошла
        throw std::invalid_argument(std::string("filter producer already registered: ") + filter_name + ".");
    }
    return producer;
}

FilterFactory::FilterProducerPtr FilterFactory::GetProducer(const char* filter_name) {
    if (!filter_name) {
        return nullptr;
    }
    ProducerDictionary::const_iterator it = producers_.find(filter_name);
    if (it == producers_.end()) {
        return nullptr;
    }
    return (*it).second;
}