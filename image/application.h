#ifndef WORKSHOPX_APPLICATION_H
#define WORKSHOPX_APPLICATION_H

#include "filter_factory.h"
#include "parser.h"


class Application {
public:
    void Init();
    void Run(int argc, char* argv[]);

private:
    Parser parser_;
    FilterFactory filter_factory_;
};

#endif //WORKSHOPX_APPLICATION_H