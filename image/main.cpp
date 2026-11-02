#include <exception>
#include <iostream>

#include "application.h"

const int NOT_HANDLED_STANDART_EXCEPTION = -1;
const int NOT_HANDLED_UNKNOWN_EXCEPTION = -2;


int main2(int argc, char* argv[]) {
    Application app;
    app.Init();
    app.Run(argc, argv);
    
    return 0;
}

int main(int argc, char* argv[]) {
    try
    {
        main2(argc, argv);
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
        return NOT_HANDLED_STANDART_EXCEPTION;
    }
    catch(...)
    {
        std::cerr << "unknown exception code.\n";
        return NOT_HANDLED_UNKNOWN_EXCEPTION;
    }
    return 0;
}