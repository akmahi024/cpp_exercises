#include <iostream>
#include <algorithm>  // For std::swap

namespace PL04 {

    // Helper function to increment an iterator (like std::next)
    template <class FwdIt>
    FwdIt next(FwdIt it) {
        FwdIt temp = it;
        ++temp;
        return temp;
    }

    // Sorting function using Bubble Sort
    template <class FwdIt>
    void sort(FwdIt begin, FwdIt end) {
        bool swapped;
        do {
            swapped = false;
            for (FwdIt it = begin; next(it) != end; ++it) {
                FwdIt next_it = next(it);
                if (*it > *next_it) {
                    std::swap(*it, *next_it);  // Swap elements if they are in wrong order
                    swapped = true;
                }
            }
        } while (swapped);  // Continue until no more swaps are needed
    }

}  // namespace PL04

// Testing the sort function
int main() {
    // Example test case
    int arr[] = {5, 3, 8, 4, 2};
    int* begin = arr;
    int* end = arr + 5;
    std::cout << "unSorted array: ";
    for (int i = 0; i < 5; ++i) {
        std::cout << arr[i] << " ";
    }
    std::cout << std::endl;

    PL04::sort(begin, end);

    // Expected sorted array
    int expected[] = {2, 3, 4, 5, 8};
    std::cout << "expected array: ";
    for (int i = 0; i < 5; ++i) {
        std::cout << expected[i] << " ";
    }
    std::cout << std::endl;

    // Check if the array is sorted correctly
    bool passed = true;
    for (int i = 0; i < 5; ++i) {
        if (arr[i] != expected[i]) {
            passed = false;
            break;
        }
    }

    // Output the result
    std::cout << "Sorted array: ";
    for (int i = 0; i < 5; ++i) {
        std::cout << arr[i] << " ";
    }
    std::cout << std::endl;

    // Check if test passed
    if (passed) {
        std::cout << "Test passed!" << std::endl;
    } else {
        std::cout << "Test failed." << std::endl;
    }

    return 0;
}
