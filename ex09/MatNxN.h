#ifndef MATNXN
#define MATNXN

// MatNxN.h

#include <iostream>

template<class T, int N>
class MatNxN 
{
    private:
        T elems[N*N];
    public:
        // Default constructor
        MatNxN();
        
        // Constructor to take a pointer to an array of size N*N
        MatNxN(T* arr);
        
        // Compound addition operator
        MatNxN& operator += (const MatNxN& rhs);
        
        // Compound subtraction operator
        MatNxN& operator -= (const MatNxN& rhs);
        
        // Compound multiplication operator
        MatNxN& operator *= (const MatNxN& rhs);
        
        // Unary minus
        MatNxN operator - () const;
        
        // Access operator to get matrix elements
        const T& operator () (int i, int j) const;
        
        // Access operator to set matrix elements
        T& operator () (int i, int j);
        
        // Equality operator
        bool operator == (const MatNxN& rhs) const;
        
        // Stream insertion operator to print the matrix
        template<class U, int M>
        friend std::ostream& operator <<(std::ostream& os, const MatNxN<U,M>& m);
};

// Binary operators for the general template
template<class T, int N>
MatNxN<T,N> operator + (const MatNxN<T,N>& lhs, const MatNxN<T,N>& rhs);

template<class T, int N>
MatNxN<T,N> operator - (const MatNxN<T,N>& lhs, const MatNxN<T,N>& rhs);

template<class T, int N>
MatNxN<T,N> operator * (const MatNxN<T,N>& lhs, const MatNxN<T,N>& rhs);

// Specialization for 2x2 matrices
template<class T>
class MatNxN<T,2>
{
    private:
        T a00, a01, a10, a11;  // Individual elements instead of array
    
    public:
        // Default constructor (identity matrix)
        MatNxN() : a00(T(1)), a01(T(0)), a10(T(0)), a11(T(1)) {}
        
        // Constructor from array
        MatNxN(T* arr) : a00(arr[0]), a01(arr[1]), a10(arr[2]), a11(arr[3]) {}
        
        // Optimized compound addition
        MatNxN& operator += (const MatNxN& rhs) 
        {
            a00 += rhs.a00;
            a01 += rhs.a01;
            a10 += rhs.a10;
            a11 += rhs.a11;
            
            return *this;
        }
        
        // Optimized compound subtraction
        MatNxN& operator -= (const MatNxN& rhs) 
        {
            a00 -= rhs.a00;
            a01 -= rhs.a01;
            a10 -= rhs.a10;
            a11 -= rhs.a11;
            
            return *this;
        }
        
        // Optimized compound multiplication
        MatNxN& operator *= (const MatNxN& rhs) 
        {
            T temp00 = a00 * rhs.a00 + a01 * rhs.a10;
            T temp01 = a00 * rhs.a01 + a01 * rhs.a11;
            T temp10 = a10 * rhs.a00 + a11 * rhs.a10;
            T temp11 = a10 * rhs.a01 + a11 * rhs.a11;
            
            a00 = temp00;
            a01 = temp01;
            a10 = temp10;
            a11 = temp11;
            
            return *this;
        }
        
        // Optimized unary minus
        MatNxN operator - () const 
        {
            MatNxN result;
            result.a00 = -a00;
            result.a01 = -a01;
            result.a10 = -a10;
            result.a11 = -a11;
            return result;
        }
        
        // Access operators
        const T& operator () (int i, int j) const 
        {
            if (i == 0) 
            {
                return (j == 0 ? a00 : a01);
            }
            
            return (j == 0 ? a10 : a11);
        }
        
        T& operator () (int i, int j) 
        {
            if (i == 0) 
            {
                return (j == 0 ? a00 : a01);
            }
            
            return (j == 0 ? a10 : a11);
        }
        
        // Equality operator
        bool operator == (const MatNxN& rhs) const 
        {
            const T epsilon = T(1e-5);
            
            return (std::abs(a00 - rhs.a00) <= epsilon && 
                    std::abs(a01 - rhs.a01) <= epsilon && 
                    std::abs(a10 - rhs.a10) <= epsilon && 
                    std::abs(a11 - rhs.a11) <= epsilon);
        }
        
        // Stream insertion operator
        template<class U>
        friend std::ostream& operator << (std::ostream& os, const MatNxN<U,2>& m) 
        {
            os << m.a00 << " " << m.a01 << "\n" << m.a10 << " " << m.a11 << "\n";
            return os;
        }
};

#endif
