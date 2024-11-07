#include "Mat2x2.h"
#include <iostream>
#include <cmath>
#include <sstream>

const float EPSILON = 1e-6;

bool assertEqual(float actual, float expected, const char* testName) {
    if (std::fabs(actual - expected) < EPSILON) {
        std::cout << "[PASSED] " << testName << std::endl;
        return true;
    } else {
        std::cout << "[FAILED] " << testName << " | Expected: " << expected << ", but got: " << actual << std::endl;
        return false;
    }
}

bool assertEqual(const Mat2x2& actual, const Mat2x2& expected, const char* testName) {
    if (actual == expected) {
        std::cout << "[PASSED] " << testName << std::endl;
        return true;
    } else {
        std::cout << "[FAILED] " << testName << " | Matrices are not equal." << std::endl;
        return false;
    }
}
bool assertunEqual(const Mat2x2& actual, const Mat2x2& expected, const char* testName) {
    if (!(actual == expected)) {
        std::cout << "[PASSED] " << testName << std::endl;
        return true;
    } else {
        std::cout << "[FAILED] " << testName << " | Matrices are equal." << std::endl;
        return false;
    }
}

// Test default constructor (Identity Matrix)
void testDefaultConstructor() {
    Mat2x2 I;
    assertEqual(I(0, 0), 1.0f, "Default Constructor: I(0,0)");
    assertEqual(I(1, 1), 1.0f, "Default Constructor: I(1,1)");
    assertEqual(I(0, 1), 0.0f, "Default Constructor: I(0,1)");
    assertEqual(I(1, 0), 0.0f, "Default Constructor: I(1,0)");
}

// Test addition operator
void testAddition() {
    float elemsA[] = {1.0, 2.0, 3.0, 4.0};
    float elemsB[] = {5.0, 6.0, 7.0, 8.0};
    Mat2x2 A(elemsA);
    Mat2x2 B(elemsB);
    Mat2x2 C = A + B;

    assertEqual(C(0, 0), 6.0f, "expected:6.0,Addition: C(0,0)");
    assertEqual(C(1, 0), 8.0f, "expected:8.0,Addition: C(1,0)");
    assertEqual(C(0, 1), 10.0f, "expected:10.0,Addition: C(0,1)");
    assertEqual(C(1, 1), 12.0f, "expected:12.0,Addition: C(1,1)");
}

// Test subtraction operator
void testSubtraction() {
    float elemsA[] = {1.0, 2.0, 3.0, 4.0};
    float elemsB[] = {5.0, 6.0, 7.0, 8.0};
    Mat2x2 A(elemsA);
    Mat2x2 B(elemsB);
    Mat2x2 D = A - B;

    assertEqual(D(0, 0), -4.0f, "expected:-4.0,Subtraction: D(0,0)");
    assertEqual(D(1, 0), -4.0f, "expected:-4.0,Subtraction: D(1,0)");
    assertEqual(D(0, 1), -4.0f, "expected:-4.0,Subtraction: D(0,1)");
    assertEqual(D(1, 1), -4.0f, "expected:-4.0,Subtraction: D(1,1)");
}

// Test multiplication operator
void testMultiplication() {
    float elemsA[] = {1.0, 2.0, 3.0, 4.0};
    float elemsB[] = {5.0, 6.0, 7.0, 8.0};
    Mat2x2 A(elemsA);
    Mat2x2 B(elemsB);
    Mat2x2 E = A * B;

    assertEqual(E(0, 0), 23.0f, "expected:23.0,Multiplication: E(0,0)");
    assertEqual(E(1, 0), 34.0f, "expected:34.0,Multiplication: E(1,0)");
    assertEqual(E(0, 1), 31.0f, "expected:31.0,Multiplication: E(0,1)");
    assertEqual(E(1, 1), 46.0f, "expected:46.0,Multiplication: E(1,1)");
}

// Test compound addition operator
void testCompoundAddition() {
    float elemsA[] = {1.0, 2.0, 3.0, 4.0};
    Mat2x2 A(elemsA);
    Mat2x2 G;
    G = A;
    assertEqual(G, A, "Addition: G == A,expected:they are equal");
    G += A;

    assertunEqual(G, A, "Compound Addition: G == A after G += A(test if G!=A after compound addition),expected:they are not equal,");
}

// Test compound subtraction operator
void testCompoundSubtraction() {
    float elemsA[] = {1.0, 2.0, 3.0, 4.0};
    Mat2x2 A(elemsA);
    Mat2x2 H(A);
    H -= A;
    Mat2x2 zero; // Default should be identity matrix
    zero(0, 0) = 0; zero(1, 1) = 0; // Set to zero matrix

    assertEqual(H, zero, "Compound Subtraction: H == Zero after H -= A(expected=H was equal to A,so after compound substraction H = zero)");
}

// Test compound multiplication operator
void testCompoundMultiplication() {
    float elemsA[] = {1.0, 2.0, 3.0, 4.0};
    float elemsB[] = {5.0, 6.0, 7.0, 8.0};
    Mat2x2 A(elemsA);
    Mat2x2 B(elemsB);
    Mat2x2 H(A);
    H *= B;

    Mat2x2 expected = A * B;
    assertEqual(H, expected, "Compound Multiplication: H == A * B after H *= B,expected:H=23,34,31,46");
}

// Test unary minus operator
void testUnaryMinus() {
    float elemsA[] = {1.0, 2.0, 3.0, 4.0};
    Mat2x2 A(elemsA);
    Mat2x2 F = -A;

    assertEqual(F(0, 0), -1.0f, "expected:-1.0,Unary Minus: F(0,0)");
    assertEqual(F(1, 0), -2.0f, "expected:-2.0,Unary Minus: F(1,0)");
    assertEqual(F(0, 1), -3.0f, "expected:-3.0,Unary Minus: F(0,1)");
    assertEqual(F(1, 1), -4.0f, "expected:-4.0,Unary Minus: F(1,1)");
}

// Test equality operator
void testEquality() {
    float elemsA[] = {1.0, 2.0, 3.0, 4.0};
    Mat2x2 A(elemsA);
    Mat2x2 B(elemsA);

    assertEqual(A == B, true, "expected:A is equal to B,Equality: A == B");
}

// Test stream insertion operator
void testStreamInsertion() {
    float elemsA[] = {1.0, 2.0, 3.0, 4.0};
    Mat2x2 A(elemsA);
    std::ostringstream oss;
    oss << A;
    std::string expectedOutput = "[1, 3]\n[2, 4]";
    if (oss.str() == expectedOutput) {
        std::cout << "[PASSED] expected:[1, 3]\n[2, 4],Stream Insertion: Expected output matched" << std::endl;
    } else {
        std::cout << "[FAILED] Stream Insertion: Expected \"" << expectedOutput
                  << "\", but got \"" << oss.str() << "\"" << std::endl;
    }
}

int main() {
    std::cout << "Running tests for Mat2x2 operations..." << std::endl;

    testDefaultConstructor();
    testAddition();
    testSubtraction();
    testMultiplication();
    testCompoundAddition();
    testCompoundSubtraction();
    testCompoundMultiplication();
    testUnaryMinus();
    testEquality();
    testStreamInsertion();

    std::cout << "Testing complete." << std::endl;
    return 0;
}
