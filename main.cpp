// main.cpp
#include <iostream>

#ifdef _WIN32
#define IMPORT __declspec(dllimport)
#else
#define IMPORT
#endif

extern "C" {
    IMPORT void hello();
    IMPORT int add(int a, int b);
}

int main() {
    hello();
    
    int result = add(5, 3);
    std::cout << "5 + 3 = " << result << std::endl;

    return 0;
}