// MatNxN.cpp

#include "MatNxN.h"
#include <cmath>

// For general matrices

// Default constructor 
template<class T, int N>
MatNxN<T,N>::MatNxN() 
{
    for(int i = 0; i < N; i++) 
    {
        for(int j = 0; j < N; j++) 
        {
            if(i == j)
            {
                elems[i*N + j] = T(1);
            }
            
            else
            {
                elems[i*N + j] = T(0);
            }
        }
    }
}

// Constructor taking array
template<class T, int N>
MatNxN<T,N>::MatNxN(T* arr) 
{
    for(int i = 0; i < N*N; i++) 
    {
        elems[i] = arr[i];
    }
}

// Compound addition
template<class T, int N>
MatNxN<T,N>& MatNxN<T,N>::operator += (const MatNxN<T,N>& rhs) 
{
    for(int i = 0; i < N*N; i++) 
    {
        elems[i] += rhs.elems[i];
    }
    
    return *this;
}

// Compound subtraction
template<class T, int N>
MatNxN<T,N>& MatNxN<T,N>::operator -= (const MatNxN<T,N>& rhs) 
{
    for(int i = 0; i < N*N; i++) 
    {
        elems[i] -= rhs.elems[i];
    }
    
    return *this;
}

// Compound multiplication
template<class T, int N>
MatNxN<T, N>& MatNxN<T, N>::operator *= (const MatNxN<T, N>& rhs) 
{
    MatNxN<T, N> temp;
    
    // Initialize temp to zero
    for(int i = 0; i < N; i++) 
    {
        for(int j = 0; j < N; j++) 
        {
            temp(i, j) = 0;
        }
    }
    
    // Perform multiplication 
    for(int i = 0; i < N; i++) 
    {
        for(int j = 0; j < N; j++) 
        {
            for(int k = 0; k < N; k++) 
            {
                temp(i, j) += (*this)(i, k) * rhs(k, j);
            }
        }
    }
    
    // Copy back 
    for(int i = 0; i < N; i++) 
    {
        for(int j = 0; j < N; j++) 
        {
            (*this)(i, j) = temp(i, j);
        }
    }
    
    return *this;
}

// Unary minus
template<class T, int N>
MatNxN<T,N> MatNxN<T,N>::operator - () const 
{
    MatNxN<T,N> result(*this);
    
    for(int i = 0; i < N*N; i++) 
    {
        result.elems[i] = -result.elems[i];
    }
    
    return result;
}

// Access operator (const)
template<class T, int N>
const T& MatNxN<T,N>::operator () (int i, int j) const 
{
    return elems[i*N + j];
}

// Access operator
template<class T, int N>
T& MatNxN<T,N>::operator () (int i, int j) 
{
    return elems[i*N + j];
}

// Equality operator
template<class T, int N>
bool MatNxN<T,N>::operator == (const MatNxN<T,N>& rhs) const 
{
    const T epsilon = T(1e-5);
    
    for(int i = 0; i < N*N; i++) 
    {
        if(std::abs(elems[i] - rhs.elems[i]) > epsilon) 
        {
            return false;
        }
    }
    
    return true;
}

// Stream insertion operator
template<class T, int N>
std::ostream& operator << (std::ostream& os, const MatNxN<T,N>& m) 
{
    for(int i = 0; i < N; i++) 
    {
        for(int j = 0; j < N; j++) 
        {
            os << m(i,j) << " ";
        }
        
        os << "\n";
    }
    
    return os;
}

// Binary addition
template<class T, int N>
MatNxN<T,N> operator + (const MatNxN<T,N>& lhs, const MatNxN<T,N>& rhs) 
{
    MatNxN<T,N> result(lhs);
    
    result += rhs;
    return result;
}

// Binary subtraction
template<class T, int N>
MatNxN<T,N> operator - (const MatNxN<T,N>& lhs, const MatNxN<T,N>& rhs) 
{
    MatNxN<T,N> result(lhs);
    
    result -= rhs;
    return result;
}

// Binary multiplication
template<class T, int N>
MatNxN<T,N> operator * (const MatNxN<T,N>& lhs, const MatNxN<T,N>& rhs) 
{
    MatNxN<T,N> result(lhs);
    
    result *= rhs;
    return result;
}

// For 2x2 matrices

// Binary addition specialization 
template<class T>
MatNxN<T,2> operator + (const MatNxN<T,2>& lhs, const MatNxN<T,2>& rhs) 
{
    MatNxN<T,2> result(lhs);
    
    result += rhs;
    return result;
}

// Binary subtraction specialization
template<class T>
MatNxN<T,2> operator - (const MatNxN<T,2>& lhs, const MatNxN<T,2>& rhs) 
{
    MatNxN<T,2> result(lhs);
    
    result -= rhs;
    return result;
}

// Binary multiplication specialization
template<class T>
MatNxN<T,2> operator * (const MatNxN<T,2>& lhs, const MatNxN<T,2>& rhs) 
{
    MatNxN<T,2> result(lhs);
   
    result *= rhs;
    return result;
}
