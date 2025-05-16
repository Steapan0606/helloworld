
#include <iostream>

#ifdef _WIN32
#define IMPORT __declspec(dllimport)
#else
#define IMPORT
#endif

extern "C" {
    IMPORT void greet();
    IMPORT int multiply(int, int);
}

int main() {
    greet();
    int product = multiply(7, 8);
    std::cout << "7 * 8 = " << product << std::endl;
    return 0;
}
