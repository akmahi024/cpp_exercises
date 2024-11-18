#include <iostream>
#include <unordered_set>
#include <fstream>
#include <sstream>
#include <string>
#include <cmath>

// Define a struct for 3D Point
struct Point {
    float x, y, z;

    Point() : x(0.f), y(0.f), z(0.f) {}
    Point(float x, float y, float z) : x(x), y(y), z(z) {}

    // Equality operator for unordered_set comparison
    bool operator==(const Point& other) const {
        return x == other.x && y == other.y && z == other.z;
    }
};

// Hash function for Point to work with std::unordered_set
struct PointHash {
    std::size_t operator()(const Point& p) const {
        std::size_t hx = std::hash<float>()(p.x);
        std::size_t hy = std::hash<float>()(p.y);
        std::size_t hz = std::hash<float>()(p.z);
        return hx ^ (hy << 1) ^ (hz << 2); // Combine hashes
    }
};

// Function to find if a point exists in the hash-set
bool find(const std::unordered_set<Point, PointHash>& points_set, const Point& query_point) {
    return points_set.find(query_point) != points_set.end();
}

// Function to read points from a CSV file and populate a hash-set
std::unordered_set<Point, PointHash> read_from_csv(const std::string& filename) {
    std::unordered_set<Point, PointHash> points_set;
    std::ifstream file(filename);

    if (!file.is_open()) {
        throw std::runtime_error("Error: Could not open file " + filename);
    }

    std::string line;
    while (std::getline(file, line)) {
        std::stringstream ss(line);
        std::string token;
        float coords[3];
        int i = 0;

        // Parse each line
        while (std::getline(ss, token, ',')) {
            try {
                coords[i++] = std::stof(token);
            } catch (const std::invalid_argument& e) {
                throw std::runtime_error("Error: Invalid data in CSV file");
            }
            if (i > 3) {
                throw std::runtime_error("Error: Too many values on a line");
            }
        }
        if (i != 3) {
            throw std::runtime_error("Error: Not enough values on a line");
        }

        points_set.emplace(coords[0], coords[1], coords[2]);
    }
    file.close();
    return points_set;
}

// Test the implementation
void test_functions(const std::string& filename) {
    try {
        // Read points from the CSV file
        auto points_set = read_from_csv(filename);

        // Test the find function
        Point query1(1.0, 2.0, 3.0);  // Expected to be in the file
        Point query2(10.0, 11.0, 12.0);  // Not expected to be in the file

        std::cout << "Testing point (1.0, 2.0, 3.0): ";
        if (find(points_set, query1)) {
            std::cout << "Found (PASSED)\n";
        } else {
            std::cout << "Not Found (FAILED)\n";
        }

        std::cout << "Testing point (10.0, 11.0, 12.0): ";
        if (find(points_set, query2)) {
            std::cout << "Found (FAILED)\n";
        } else {
            std::cout << "Not Found (PASSED)\n";
        }
    } catch (const std::exception& e) {
        std::cerr << e.what() << std::endl;
    }
}

int main() {
    // Specify the name of the CSV file
    const std::string test_filename = "test_points.csv";

    // Test functions with the given CSV file
    test_functions(test_filename);

    return 0;
}
