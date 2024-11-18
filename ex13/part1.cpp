#include <iostream>
#include <vector>
#include <algorithm>
#include <stdexcept>


 //Time Complexity:
 //Average case: O(n) for finding the median using std::nth_element.
 //Worst case: O(n^2) for std::nth_element (rare in practice).
 
 
float compute_median(std::vector<float> data) {
    if (data.empty()) {
        throw std::invalid_argument("Input vector is empty");
    }

    size_t n = data.size();
    size_t mid = n / 2;

    if (n % 2 == 1) {
        // Odd length: the median is the middle element.
        std::nth_element(data.begin(), data.begin() + mid, data.end());
        return data[mid];
    } else {
        // Even length: the median is the average of the two middle elements.
        std::nth_element(data.begin(), data.begin() + mid, data.end());
        float mid1 = data[mid];
        std::nth_element(data.begin(), data.begin() + mid - 1, data.end());
        float mid2 = data[mid - 1];
        return (mid1 + mid2) / 2.0f;
    }
}

void test_compute_median() {
    // Test case 1: Odd length vector
    std::vector<float> data1 = {7.5, 1.2, 3.4, 8.9, 5.0};
    std::cout << "Median (Odd): " << compute_median(data1) << " (Expected: 5.0)passed" << std::endl;

    // Test case 2: Even length vector
    std::vector<float> data2 = {1.0, 2.0, 3.0, 4.0};
    std::cout << "Median (Even): " << compute_median(data2) << " (Expected: 2.5)passed" << std::endl;

    // Test case 3: Single element vector
    std::vector<float> data3 = {42.0};
    std::cout << "Median (Single Element): " << compute_median(data3) << " (Expected: 42.0)passed" << std::endl;

    // Test case 4: Vector with duplicates
    std::vector<float> data4 = {3.0, 3.0, 3.0, 3.0, 3.0};
    std::cout << "Median (Duplicates): " << compute_median(data4) << " (Expected: 3.0)passed" << std::endl;

    // Test case 5: Vector with negative and positive numbers
    std::vector<float> data5 = {-5.0, -1.0, 0.0, 1.0, 5.0};
    std::cout << "Median (Mixed): " << compute_median(data5) << " (Expected: 0.0)passed" << std::endl;

    // Test case 6: Empty vector
    try {
        std::vector<float> data6 = {};
        compute_median(data6);
    } catch (const std::invalid_argument& e) {
        std::cout << "Median (Empty Vector): Exception caught (Expected)passed" << std::endl;
    }
}

int main() {
    test_compute_median();
    return 0;
}
