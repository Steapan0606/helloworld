// example.cpp
#include <iostream>

#ifdef _WIN32
#define EXPORT __declspec(dllexport)
#else
#define EXPORT
#endif

extern "C" {
    EXPORT void hello() {
        std::cout << "Hello from the DLL!" << std::endl;
    }

    EXPORT int add(int a, int b) {
        return a + b;
    }
}