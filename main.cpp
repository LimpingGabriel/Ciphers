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
    
    std::string in;
    std::string key;
    std::string encodeString;
    
    while (true) {
        std::cout << "Enter message: ";
        std::getline(std::cin, in);
        std::cout << "Enter key: ";
        std::getline(std::cin, key);
        std::cout << "Encode? (y/n) ";
        std::getline(std::cin, encodeString);
        
        bool encode = (encodeString == "Y" || encodeString == "y");
        std::cout << "Ciphertext: " << std::endl;
        std::cout << ciphers::modern::solitaire(in, key, encode) << std::endl;
    }
    return 0;
    
    

    /*
    //Benchmark: 22513403000[ns] Release x64, 1000 char instring, 52 char key, 100000 iterations
    //Fast mod, preincrement: 21423867200[ns] Release x64, 1000 character instring, 52 char key, 100000 iterations
    //Fast countcut, 16829706200[ns] Release x64 1000 character instring, 52 char key, 100000 iterations
    //Reorganized tripleCut, 5896591500[ns] Release x64 1000 character instring, 52 char key, 100000 iterations
    std::string in = gen_random(1000);
    std::string key = gen_random(52);
    std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();

    for (int i = 0; i < 100000; ++i) {
        ciphers::modern::solitaire(in, key, true);
    }

    std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();
    std::cout << "Time difference = " << std::chrono::duration_cast<std::chrono::nanoseconds> (end - begin).count() << "[ns]" << std::endl;

    return 0;
    */
}
