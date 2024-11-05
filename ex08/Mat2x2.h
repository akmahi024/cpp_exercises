#ifndef MAT2X2_H
#define MAT2X2_H

#include <iostream>
#include <cmath>

class Mat2x2 {
private:
    float m[2][2];

public:
    // Default constructor - Identity matrix
    Mat2x2();

    // Constructor that takes an array of 4 elements in column-major order
    Mat2x2(const float elements[4]);

    // Operator overloading
    Mat2x2 operator+(const Mat2x2& other) const;
    Mat2x2 operator-(const Mat2x2& other) const;
    Mat2x2 operator*(const Mat2x2& other) const;

    Mat2x2& operator+=(const Mat2x2& other);
    Mat2x2& operator-=(const Mat2x2& other);
    Mat2x2& operator*=(const Mat2x2& other);

    Mat2x2 operator-() const;

    float operator()(int i, int j) const;
    float& operator()(int i, int j);

    bool operator==(const Mat2x2& other) const;

    friend std::ostream& operator<<(std::ostream& os, const Mat2x2& matrix);
};

#endif // MAT2X2_H
