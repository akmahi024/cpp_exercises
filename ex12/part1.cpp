#include <iostream>
#include <vector>
#include <queue>
#include <cmath>
#include <algorithm>

struct Point {
    Point() : x(0.f), y(0.f), z(0.f) {}
    Point(float x, float y, float z) : x(x), y(y), z(z) {}
    float x, y, z;

    // A utility function to print the point
    void print() const {
        std::cout << "(" << x << ", " << y << ", " << z << ")";
    }

    bool operator==(const Point& other) const {
        return x == other.x && y == other.y && z == other.z;
    }
};

// Function object for comparing two points
struct Compare {
    bool operator()(const Point& p1, const Point& p2) const {
        float dist1 = std::sqrt(p1.x * p1.x + p1.y * p1.y + p1.z * p1.z);
        float dist2 = std::sqrt(p2.x * p2.x + p2.y * p2.y + p2.z * p2.z);
        return dist1 < dist2; // Min-heap behavior
    }
};

// Function to find k closest points to the origin
std::vector<Point> find_k_closest(int k, const std::vector<Point>& points) {
    if (k <= 0 || points.empty()) {
        return {};
    }

    // Use a max-heap to maintain the k closest points
    auto compare = [](const Point& p1, const Point& p2) {
        float dist1 = std::sqrt(p1.x * p1.x + p1.y * p1.y + p1.z * p1.z);
        float dist2 = std::sqrt(p2.x * p2.x + p2.y * p2.y + p2.z * p2.z);
        return dist1 < dist2;
    };
    std::priority_queue<Point, std::vector<Point>, decltype(compare)> max_heap(compare);

    for (const auto& point : points) {
        max_heap.push(point);
        if (max_heap.size() > k) {
            max_heap.pop(); // Keep only k elements
        }
    }

    // Extract points from the max-heap
    std::vector<Point> result;
    while (!max_heap.empty()) {
        result.push_back(max_heap.top());
        max_heap.pop();
    }

    // Reverse to maintain closest-first order
    std::reverse(result.begin(), result.end());
    return result;
}

// Function to test find_k_closest
void test_find_k_closest() {
    struct TestCase {
        int k;
        std::vector<Point> points;
        std::vector<Point> expected;
    };

    std::vector<TestCase> test_cases = {
        {
            3,
            {Point(1, 2, 3), Point(2, 2, 2), Point(1, 1, 1), Point(3, 3, 3), Point(0, 1, 1)},
            
            {Point(0, 1, 1), Point(1, 1, 1), Point(2, 2, 2)}
        },
        {
            2,
            {Point(3, 3, 3), Point(1, 1, 1), Point(2, 2, 2)},
            {Point(1, 1, 1), Point(2, 2, 2)}
        },
        {
            0,
            {Point(1, 1, 1), Point(2, 2, 2)},
            {}
        },
        {
            1,
            {Point(3, 3, 3), Point(0, 0, 1), Point(0, 0, 0)},
            {Point(0, 0, 0)}
        }
    };

    for (size_t i = 0; i < test_cases.size(); ++i) {
        const auto& test = test_cases[i];
        auto result = find_k_closest(test.k, test.points);

        std::cout << "Test Case " << i + 1 << ": k = " << test.k << ", Points = [";
        for (const auto& point : test.points) {
            point.print();
            std::cout << ", ";
        }
        std::cout << "]\nExpected Closest Points: [";
        for (const auto& point : test.expected) {
            point.print();
            std::cout << ", ";
        }
        std::cout << "]\nActual Closest Points: [";
        for (const auto& point : result) {
            point.print();
            std::cout << ", ";
        }
        std::cout << "]\n";

        if (result == test.expected) {
            std::cout << "Result: PASSED\n\n";
        } else {
            std::cout << "Result: FAILED\n\n";
        }
    }
}

// Main function
int main() {
    test_find_k_closest();
    return 0;
}
