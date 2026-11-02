#ifndef WORKSHOPX_FILTER_PRODUCERS_H
#define WORKSHOPX_FILTER_PRODUCERS_H

#include "filter.h"
#include "parser.h"

AbstractFilter* CropProducer(const FilterDescriptor& fd);
AbstractFilter* GrayscaleProducer(const FilterDescriptor& fd);
AbstractFilter* NegativeProducer(const FilterDescriptor& fd);
AbstractFilter* SharpeningProducer(const FilterDescriptor& fd);
AbstractFilter* EdgeDetectionProducer(const FilterDescriptor& fd);
AbstractFilter* BlurProducer(const FilterDescriptor& fd);
AbstractFilter* KuwaharaProducer(const FilterDescriptor& fd);
 
#endif // WORKSHOPX_FILTER_PRODUCERS_H