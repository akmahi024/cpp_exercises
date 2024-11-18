#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
#include <stdexcept>

float compute_median(std::vector<float> data) {
    if (data.empty()) {
        throw std::invalid_argument("Input vector is empty");
    }

    size_t n = data.size();
    size_t mid = n / 2;

    if (n % 2 == 1) {
        std::nth_element(data.begin(), data.begin() + mid, data.end());
        return data[mid];
    } else {
        std::nth_element(data.begin(), data.begin() + mid, data.end());
        float mid1 = data[mid];
        std::nth_element(data.begin(), data.begin() + mid - 1, data.end());
        float mid2 = data[mid - 1];
        return (mid1 + mid2) / 2.0f;
    }
}

std::vector<float> compute_k_closest(std::vector<float> data, int k) {
    if (k <= 0 || k > data.size()) {
        throw std::invalid_argument("Invalid value of k");
    }

    float median = compute_median(data);

    auto comparator = [median](float a, float b) {
        return std::abs(a - median) < std::abs(b - median);
    };

    std::nth_element(data.begin(), data.begin() + k, data.end(), comparator);

    return std::vector<float>(data.begin(), data.begin() + k);
}

void test_compute_k_closest() {
    // Test case 1: General case
    std::vector<float> data1 = {7.5, 1.2, 3.4, 8.9, 5.0, 6.3, 4.4};
    int k1 = 3;
    std::vector<float> result1 = compute_k_closest(data1, k1);
    std::cout << "Test case 1 - Input: {7.5, 1.2, 3.4, 8.9, 5.0, 6.3, 4.4}, k = 3\n";
    std::vector<float> expected1 = {5.0, 4.4, 6.3};
    std::sort(result1.begin(), result1.end());
    std::sort(expected1.begin(), expected1.end());
    std::cout << "Expected Output: {5.0, 4.4, 6.3}\n";
    std::cout << "Output: ";
    for (float num : result1) std::cout << num << " ";
    std::cout << "\nPassed: " << (result1 == expected1 ? "Yes" : "No") << "\n\n";
    
    // Test case 2: Single element vector
    std::vector<float> data2 = {42.0};
    int k2 = 1;
    std::vector<float> result2 = compute_k_closest(data2, k2);
    std::cout << "Test case 2 - Input: {42.0}, k = 1\n";
    std::cout << "Expected Output: {42.0}\n";
    std::cout << "Output: ";
    for (float num : result2) std::cout << num << " ";
    std::cout << "\nPassed: " << (result2 == std::vector<float>{42.0} ? "Yes" : "No") << "\n\n";

    // Test case 3: All elements equal
    std::vector<float> data3 = {3.0, 3.0, 3.0, 3.0};
    int k3 = 2;
    std::vector<float> result3 = compute_k_closest(data3, k3);
    std::cout << "Test case 3 - Input: {3.0, 3.0, 3.0, 3.0}, k = 2\n";
    std::cout << "Expected Output: {3.0, 3.0}\n";
    std::cout << "Output: ";
    for (float num : result3) std::cout << num << " ";
    std::cout << "\nPassed: " << (result3 == std::vector<float>{3.0, 3.0} ? "Yes" : "No") << "\n\n";

    // Test case 4: Vector with negative and positive numbers
    std::vector<float> data4 = {-5.0, -1.0, 0.0, 1.0, 5.0, 10.0};
    int k4 = 4;
    std::vector<float> result4 = compute_k_closest(data4, k4);
    std::cout << "Test case 4 - Input: {-5.0, -1.0, 0.0, 1.0, 5.0, 10.0}, k = 4\n";
    
    // Expected output
    std::vector<float> expected4 = {-1.0, 0.0, 1.0, 5.0};
    std::sort(result4.begin(), result4.end());
    std::sort(expected4.begin(), expected4.end());

    std::cout << "Expected Output: {-1.0, 0.0, 1.0, 5.0}\n";
    std::cout << "Output: ";
    for (float num : result4) std::cout << num << " ";
    std::cout << "\nPassed: " << (result4 == expected4 ? "Yes" : "No") << "\n\n";

    // Test case 5: Invalid k
    try {
        std::vector<float> data5 = {1.0, 2.0, 3.0};
        compute_k_closest(data5, 5);
        std::cout << "Test case 5 - Input: {1.0, 2.0, 3.0}, k = 5\n";
        std::cout << "Expected Output: Exception\n";
        std::cout << "Output: No exception\n";
        std::cout << "Passed: No\n\n";
    } catch (const std::invalid_argument& e) {
        std::cout << "Test case 5 - Input: {1.0, 2.0, 3.0}, k = 5\n";
        std::cout << "Expected Output: Exception\n";
        std::cout << "Output: Exception caught\n";
        std::cout << "Passed: Yes\n\n";
    }
}

int main() {
    test_compute_k_closest();
    return 0;
}
