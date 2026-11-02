
#ifndef WORKSHOPX_FILTERFACTORY_H
#define WORKSHOPX_FILTERFACTORY_H

#include <map>
#include <string>
#include <vector>

#include "parser.h"
#include "filter.h"
#include "pipeline.h"

class FilterFactory {
public:
    using FilterProducerPtr = AbstractFilter*(*)(const FilterDescriptor&);
    using ProducerDictionary = std::map<std::string, FilterProducerPtr>;

public:
    Pipeline CreatePipeline(const std::vector<FilterDescriptor>& fd);
    FilterProducerPtr AddFilterProducer(const char* filter_name, FilterProducerPtr producer);
    FilterProducerPtr GetProducer(const char* filter_name);
private:
    ProducerDictionary producers_;
};

#endif //WORKSHOPX_FILTERFACTORY_H