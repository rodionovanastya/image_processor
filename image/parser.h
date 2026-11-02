#ifndef WORKSHOPX_PARSER_H
#define WORKSHOPX_PARSER_H

#include <vector>

struct FilterDescriptor
{
    const char* name;
    std::vector<const char*> args;
};


class Parser {
public:
    enum class Result {
        Ok,                     // Все хорошо распарсилось, можно пытаться конвертировать
        NoArguments,            // Аргументов не дали, надо вывести справку
        NoOutputFile,           // Только входной файл
        UnknownArgument,        // Лишний аргумент
    };

public:
    Parser()
    : inputFileName_(nullptr)
    , outputFileName_(nullptr)
{
}

    Result Parse(int argc, char* argv[]);

    const char* GetInputFileName() const { return inputFileName_; }
    const char* GetOutputFileName() const { return outputFileName_; }
    const std::vector<FilterDescriptor>& GetFilters() const { return filters_; }
private:
    Result ParseFilters(int argc, char* argv[]);

    const char* inputFileName_;
    const char* outputFileName_;
    std::vector<FilterDescriptor> filters_;
};

#endif // WORKSHOPX_PARSER_H