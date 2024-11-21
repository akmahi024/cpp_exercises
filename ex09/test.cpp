
#include <iostream>
#include "MatNxN.h"

// Define a small epsilon value for floating-point comparison
const float EPSILON = 1e-5;

// Function to check if two floating-point numbers are equal within a tolerance
bool isEqual(float a, float b)
{
    return (std::abs(a - b) < EPSILON);
}

// Function to verify if the result matrix matches the expected matrix
template<class T, int N>
void verify(const MatNxN<T, N> result, const T expected[N*N], const std::string& name)
{
    bool passed = true;
    
    // Print the expected result
    std::cout << "Expected Output for " << name << ":\n";
    for (int i = 0; i < N; ++i)
    {
        for (int j = 0; j < N; ++j)
        {
            std::cout << expected[i * N + j] << " ";
        }
        std::cout << std::endl;
    }

    // Compare each element of the result matrix with the expected matrix
    for (int i = 0; i < N; ++i)
    {
        for (int j = 0; j < N; ++j)
        {
            if (!isEqual(result(i, j), expected[i * N + j]))
            {
                passed = false;
            }
        }
    }

    // Print the result of the test
    if (passed)
    {
        std::cout << "Test: " << name << " passed!" << "\n\n";
    }
    else
    {
        std::cout << "Test: " << name << " failed!" << "\n\n";
    }
}

// Function to test the constructors of the MatNxN class
template<class T, int N>
void constructorTest()
{
    std::cout << "\nTesting constructors for N = " << N << ":\n";

    // Test the default constructor
    MatNxN<T, N> identityMatrix;
    
    T expected[N*N] = {0}; // Default expected matrix values (identity for square matrices)
    
    for(int i = 0; i < N; ++i)
    {
        expected[i * N + i] = 1;  // Identity matrix: diagonal elements are 1
    }

    // Verify that the default constructor gives an identity matrix
    verify(identityMatrix, expected, "Default constructor");

    // Test the array constructor with incremental values
    T array[N*N];

    for(int i = 0; i < N*N; ++i)
    {
        array[i] = T(i + 1);  // Populate array with values 1, 2, 3, ...
    }

    MatNxN<T, N> matrix(array);
    
    // Verify that the array constructor initializes the matrix with the array values
    verify(matrix, array, "Array constructor");
}

// Function to test the arithmetic operations of the MatNxN class
template<class T, int N>
void arithmeticTest()
{
    std::cout << "\nTesting arithmetic operations for N = " << N << ":\n";
 
    // Define two matrices for testing with incremental values
    T arr1[N*N];
    T arr2[N*N];

    for(int i = 0; i < N*N; ++i)
    {
        arr1[i] = T(i + 1);  // Populate arr1 with values 1, 2, 3, ...
        arr2[i] = T(i + N*N + 1);  // Populate arr2 with values offset by N*N
    }

    MatNxN<T, N> matrix1(arr1);
    MatNxN<T, N> matrix2(arr2);

    // Test binary addition
    MatNxN<T, N> sum = matrix1 + matrix2;
    T expectedSum[N*N];

    for(int i = 0; i < N*N; ++i)
    {
        expectedSum[i] = arr1[i] + arr2[i];  // Element-wise addition
    }
    
    verify(sum, expectedSum, "Binary addition");

    // Test binary subtraction
    MatNxN<T, N> diff = matrix2 - matrix1;
    T expectedDiff[N*N];

    for(int i = 0; i < N*N; ++i)
    {
        expectedDiff[i] = arr2[i] - arr1[i];  // Element-wise subtraction
    }

    verify(diff, expectedDiff, "Binary subtraction");

    // Test binary multiplication
    MatNxN<T, N> prod = matrix1 * matrix2;
    T expectedProd[N*N] = {0}; 

    for(int i = 0; i < N; ++i)
    {
        for(int j = 0; j < N; ++j)
        {
            expectedProd[i * N + j] = 0; // Reset before accumulating

            for(int k = 0; k < N; ++k)
            {
                expectedProd[i * N + j] += arr1[i * N + k] * arr2[k * N + j];  // Matrix multiplication
            }
        }
    }
    
    verify(prod, expectedProd, "Binary multiplication");

    // Test compound addition
    MatNxN<T, N> temp = matrix1;
    temp += matrix2;
    verify(temp, expectedSum, "Compound addition");

    // Test compound subtraction
    temp = matrix2;
    temp -= matrix1;
    verify(temp, expectedDiff, "Compound subtraction");

    // Test compound multiplication
    temp = matrix1;
    temp *= matrix2;
    verify(temp, expectedProd, "Compound multiplication");
}

// Function to test the unary minus operator of the MatNxN class
template<class T, int N>
void unaryMinusTest()
{
    std::cout << "\nTesting unary minus for N = " << N << ":\n";

    // Define a matrix for testing
    T arr[N*N];

    for(int i = 0; i < N*N; ++i)
    {
        arr[i] = T(i + 1);  // Populate matrix with values 1, 2, 3, ...
    }

    MatNxN<T, N> m(arr);

    // Test the unary minus operator (negates the matrix)
    MatNxN<T, N> neg = -m;

    T expectedMinus[N*N];
    
    for(int i = 0; i < N*N; ++i)
    {
        expectedMinus[i] = -arr[i];  // Negate each element
    }

    verify(neg, expectedMinus, "Unary minus");
}

// Function to test the equality operator of the MatNxN class
template<class T, int N>
void equalityTest()
{
    // Define two matrices for testing (same values for both matrices)
    T arr1[N*N];
    T arr2[N*N];

    for(int i = 0; i < N*N; ++i)
    {
        arr1[i] = T(i + 1);
        arr2[i] = T(i + 1);  // Identical elements
    }

    MatNxN<T, N> m1(arr1);
    MatNxN<T, N> m2(arr2);

    std::cout << "\nTesting equality:\n";

    // Test the equality operator (should pass since the matrices are identical)
    if (m1 == m2)
    {
        std::cout << "Equality test passed!" << "\n\n";
    }
    else
    {
        std::cout << "Equality test failed!" << "\n\n";
    }
}

int main()
{
    // Run all tests
    constructorTest<float, 2>();  // Test for 2x2 matrices with float elements
    arithmeticTest<float, 2>();  // Test arithmetic operations for 2x2 matrices
    unaryMinusTest<float, 2>();  // Test unary minus for 2x2 matrices
    equalityTest<float, 2>();  // Test equality for 2x2 matrices

    constructorTest<int, 3>();  // Test for 3x3 matrices with int elements
    arithmeticTest<int, 3>();  // Test arithmetic operations for 3x3 matrices
    unaryMinusTest<int, 3>();  // Test unary minus for 3x3 matrices
    equalityTest<int, 3>();  // Test equality for 3x3 matrices

    // Test matrix output for 2x2 and 3x3 matrices
    std::cout << "\nTest the matrix output for N=2:\n";
    
    float arr2x2[] = {1.0f, 2.0f, 3.0f, 4.0f};
    MatNxN<float, 2> test2x2(arr2x2);
    
    std::cout << test2x2 << std::endl;

    std::cout << "Test the matrix output for N=3:\n";
    
    int arr3x3[] = {1, 2, 3, 4, 5, 6, 7, 8, 9};
    MatNxN<int, 3> test3x3(arr3x3);
    
    std::cout << test3x3 << std::endl;

    return 0;
}
