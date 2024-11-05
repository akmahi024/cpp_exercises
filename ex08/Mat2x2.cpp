#include "Mat2x2.h"

const float EPSILON = 1e-6;

// Default constructor: Identity matrix
Mat2x2::Mat2x2() {
    m[0][0] = 1.0f; m[0][1] = 0.0f;
    m[1][0] = 0.0f; m[1][1] = 1.0f;
}

// Constructor with array (column-major order)
Mat2x2::Mat2x2(const float elements[4]) {
    m[0][0] = elements[0]; m[1][0] = elements[1];
    m[0][1] = elements[2]; m[1][1] = elements[3];
}

// Matrix addition
Mat2x2 Mat2x2::operator+(const Mat2x2& other) const {
    Mat2x2 result;
    result.m[0][0] = m[0][0] + other.m[0][0];
    result.m[1][0] = m[1][0] + other.m[1][0];
    result.m[0][1] = m[0][1] + other.m[0][1];
    result.m[1][1] = m[1][1] + other.m[1][1];
    return result;
}

// Matrix subtraction
Mat2x2 Mat2x2::operator-(const Mat2x2& other) const {
    Mat2x2 result;
    result.m[0][0] = m[0][0] - other.m[0][0];
    result.m[1][0] = m[1][0] - other.m[1][0];
    result.m[0][1] = m[0][1] - other.m[0][1];
    result.m[1][1] = m[1][1] - other.m[1][1];
    return result;
}

// Matrix multiplication
Mat2x2 Mat2x2::operator*(const Mat2x2& other) const {
    Mat2x2 result;
    result.m[0][0] = m[0][0] * other.m[0][0] + m[0][1] * other.m[1][0];
    result.m[1][0] = m[1][0] * other.m[0][0] + m[1][1] * other.m[1][0];
    result.m[0][1] = m[0][0] * other.m[0][1] + m[0][1] * other.m[1][1];
    result.m[1][1] = m[1][0] * other.m[0][1] + m[1][1] * other.m[1][1];
    return result;
}

// Compound operators
Mat2x2& Mat2x2::operator+=(const Mat2x2& other) {
    *this = *this + other;
    return *this;
}

Mat2x2& Mat2x2::operator-=(const Mat2x2& other) {
    *this = *this - other;
    return *this;
}

Mat2x2& Mat2x2::operator*=(const Mat2x2& other) {
    *this = *this * other;
    return *this;
}

// Unary minus
Mat2x2 Mat2x2::operator-() const {
    Mat2x2 result;
    result.m[0][0] = -m[0][0];
    result.m[1][0] = -m[1][0];
    result.m[0][1] = -m[0][1];
    result.m[1][1] = -m[1][1];
    return result;
}

// Access operator
float Mat2x2::operator()(int i, int j) const {
    return m[i][j];
}

float& Mat2x2::operator()(int i, int j) {
    return m[i][j];
}

// Equality operator with a threshold for floating-point comparison
bool Mat2x2::operator==(const Mat2x2& other) const {
    return (std::fabs(m[0][0] - other.m[0][0]) < EPSILON &&
            std::fabs(m[1][0] - other.m[1][0]) < EPSILON &&
            std::fabs(m[0][1] - other.m[0][1]) < EPSILON &&
            std::fabs(m[1][1] - other.m[1][1]) < EPSILON);
}

// Stream insertion operator
std::ostream& operator<<(std::ostream& os, const Mat2x2& matrix) {
    os << "[" << matrix.m[0][0] << ", " << matrix.m[0][1] << "]\n"
       << "[" << matrix.m[1][0] << ", " << matrix.m[1][1] << "]";
    return os;
}
