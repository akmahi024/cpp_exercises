#include <iostream>
#include <vector>
#include <bitset>

const uint64_t P[8] = {
    0b0111011011010011001011010010011001011001010010001011011010000001,  // P0
    0b0100110000110010010100100110000110110000010000010110100110000100,  // P1
    0b1001001100101100001000000101101000000100100001101001000100100101,  // P2
    0b0010001010001000011000011001010010001011010000010001010001010010,  // P3
    0b0000110000000010010000100100110010000100100110010010110000010000,  // P4
    0b1101001001100000101001000100001000100001000100100101000100101000,  // P5
    0b1010000001000010000011000011011000010000001011010000001011010000,  // P6
    0b0000010100010000100010100100100000010100100100010010000010100110   // P7
};

bool is_prime(int n) {
    if (n < 2) return false;  // 0 and 1 
    if (n == 2) return true;   // 2 
    if (n % 2 == 0) return false; 

    int k = (n - 1) / 2;  // Compute k for odd n
    int word_index = k / 64;  // Determine which 64-bit word to read
    int bit_index = k % 64;    // Determine which bit in the word to read

    // Check if the bit is set (1 for prime) or not (0 for not prime)
    return (P[word_index] >> (63 - bit_index)) & 1;
}

int main() {
    // List of specific numbers to check for primality
    std::vector<int> numbersToCheck = {1, 3, 5, 11, 13, 17, 23, 29, 31, 97, 101, 103,22,24};

    // Check each number in the list
    for (int number : numbersToCheck) {
        bool result = is_prime(number);
        std::cout << number << " is " << (result ? "prime" : "not prime") << std::endl;
    }

    return 0;
}
