
#include <iostream>

#ifdef _WIN32
#define EXPORT __declspec(dllexport)
#else
#define EXPORT
#endif

extern "C" {
    EXPORT void greet() {
        std::cout << "Welcome from the DLL!" << std::endl;
    }

    EXPORT int multiply(int a, int b) {
        return a * b;
    }
}
