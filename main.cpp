#include <iostream>
#include <chrono>
#include <string>
#include "Ciphers.h"

std::string gen_random(const int len) {
    static const char alphanum[] =
        "0123456789"
        "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
        "abcdefghijklmnopqrstuvwxyz";
    std::string tmp_s;
    tmp_s.reserve(len);

    for (int i = 0; i < len; ++i) {
        tmp_s += alphanum[rand() % (sizeof(alphanum) - 1)];
    }

    return tmp_s;
}

int main()
{
    /*
    std::string in = gen_random(10000000);
    std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();
    ciphers::classic::caesar(in, 1, true);

    std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();
    std::cout << "Time difference = " << std::chrono::duration_cast<std::chrono::nanoseconds> (end - begin).count() << "[ns]" << std::endl;
    return 0;
    */

    std::string in = "This is a test.";
    std::string key;
    while (true) {
        
        //std::cout << "Enter key: ";
        //std::getline(std::cin, key);
        key = "Test";
        ciphers::modern::solitaire(in, key, true);
    }
    return 0;
}
