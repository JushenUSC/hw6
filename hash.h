#ifndef HASH_H
#define HASH_H

#include <iostream>
#include <cmath>
#include <random>
#include <chrono>

typedef std::size_t HASH_INDEX_T;

struct MyStringHash {
    HASH_INDEX_T rValues[5] { 983132572, 1468777056, 552714139, 984953261, 261934300 };
    MyStringHash(bool debug = true)
    {
        if(false == debug){
            generateRValues();
        }
    }
    // hash function entry point (i.e. this is h(k))
    HASH_INDEX_T operator()(const std::string& k) const
    {
        unsigned long long w[5] = {0};
        int len = k.length();
        int chunk_index = 4;

        while (len > 0 && chunk_index >= 0) {
            int chunk_size = std::min(6, len);
            unsigned long long value = 0;
            unsigned long long base = 1;
            for (int i = len - 1; i >= len - chunk_size; --i) {
                char c = k[i];
                HASH_INDEX_T digit = letterDigitToNumber(c);
                value += static_cast<unsigned long long>(digit) * base;
                base *= 36;
            }
            w[chunk_index] = value;
            len -= chunk_size;
            chunk_index--;
        }

        unsigned long long hash = 0;

        for (int i = 0; i < 5; ++i) {
            hash += static_cast<unsigned long long>(rValues[i]) * w[i];
        }

        return static_cast<HASH_INDEX_T>(hash);
    }

    // A likely helper function is to convert a-z,0-9 to an integral value 0-35
    HASH_INDEX_T letterDigitToNumber(char letter) const
    {
        // Add code here or delete this helper function if you do not want it
		char lower = std::tolower(static_cast<unsigned char>(letter));
        if (lower >= 'a' && lower <= 'z') {
            return lower - 'a';
        } else if (lower >= '0' && lower <= '9') {
            return 26 + (lower - '0');
        } else {
            return 0; // Only letters and digits expected
        }
    }

    // Code to generate the random R values
    void generateRValues()
    {
        // obtain a seed from the system clock:
        unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
        std::mt19937 generator (seed);  // mt19937 is a standard random number generator

        // Simply call generator() [it has an operator()] to get another random number
        for(int i{ 0 }; i < 5; ++i)
        {
            rValues[i] = generator();
        }
    }
};

#endif
