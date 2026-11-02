cmake_minimum_required(VERSION 3.5)

project(WorkshopX CXX)

if (NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Debug)
endif(NOT CMAKE_BUILD_TYPE)

set(CMAKE_CXX_STANDARD 17)

# the following options prevent compiler-optimization issues that are unwanted in an edu process
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -O0 -Werror=return-type")
set(CMAKE_C_FLAGS_DEBUG "${CMAKE_C_FLAGS_DEBUG} -O0")

add_executable(image_processor
            image/main.cpp
            image/application.cpp
            image/application.h
            image/parser.cpp
            image/parser.h
            image/filter_factory.cpp
            image/filter_factory.h
            image/filter_producers.cpp
            image/filter_producers.h
            image/pipeline.h
            image/pipeline.cpp
            image/image.cpp
            image/image.h
            image/bmp.cpp
            image/bmp.h
            image/filter.h

            image/filters/abstract_filter.h
            image/filters/filters.h
            image/filters/common.h
            image/filters/common.cpp
            
            image/filters/blur_filter.cpp
            image/filters/crop_filter.cpp
            image/filters/edgedetection_filter.cpp
            image/filters/grayscale_filter.cpp
            image/filters/kuwahara_filter.cpp
            image/filters/negative_filter.cpp
            image/filters/sharpening_filter.cpp
)
