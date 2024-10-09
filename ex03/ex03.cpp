// test_pointers.cpp
#include <iostream>
#include <iomanip>
// COMPLETE include necessary headers
int main(void)
{
  //
  // 1. Declare a variable f as a pointer to a float
  float* f = new float();
  
  // 2. Create a float variable named e, and store the value 2.71828f
  float e = 2.71828;
  // 3. Make f points to e
  f = &e;
  // 4. Print out the content of the memory location pointed to by f
  std::cout << *f << std::endl; 
  //
  unsigned a[] = {10, 9, 8, 7, 6, 5, 4, 3, 2, 1};
  // 5. Declare a variable up as a pointer to an unsigned integer
  unsigned int* up;
  
  // 6. Make up points to the beginning of the array a
  up = a;
  // 7. Print out what up points to and the content of a[0] (verify they are the same)
  std::cout << "value pointed to by up :" << *up << "(a[0] =" << a[0] << ")" << std::endl;
  // 8. Increase up by 3 and check that what it points to corresponds to a[3]
  up += 3;
  std::cout << "value after incrementing by 3 :" << *up << "(a[3] =" << a[3] << ")" << std::endl;
  
  // 9. Make up points to the last element of the array
  up = &a[9];
  std::cout << "last element pointed to by up :" << *up << "(a[9] =" << a[9] << ")" << std::endl;

  // 
  int n = 20;
  // 10. Declare a variable fa as a pointer to float and 
  // make it point to an array of "n" elements of type "float" created on the heap
  float* fa = new float[n];
  // 11. Store the values i / 11.0f for i ranging through the different elements in the array 
  for (int i = 0 ;i < n ; ++i){
      fa[i]= i/11.0f;
  }
  // 12. Print out each element of fa
  std::cout <<"Elements of fa:" << std::endl;
  for( int i = 0 ; i<n;++i){
      std::cout <<"fa["<< i+1<<"] = " << fa[i] <<std::endl;
  }


  // 13. Delete the previously allocated memory and set it to nullptr
  delete[] fa;
  fa = nullptr;
  

  //
  int m = 5;
  n = 5;
  double** dd;
  // 14. Allocate memory for a 2d array of size m * n on the heap (i.e. m arrays of size n).
  // Make dd points to this 2d array.
  dd = new double*[m];
  for( int i = 0 ; i<m;++i){
      dd[i] = new double[n];
      
  }
  // 15. Set the element dd[i][j] to be equal to i/(j+1.0) for i and j ranging through the array elements
  for(int i = 0;i<m;++i){
      for(int j = 0; j<n;++j){
          dd[i][j] = i / (j + 1.0);
          
      }
  }
  // 16. Print each element of the double array dd 
  std::cout << "Elements of dd:" << std::endl;
  for(int i = 0;i<m; ++i){
      for(int j = 0;j<n;++j){
          std::cout << "element[" << i+1 <<"][" << j+1<<"]="<<dd[i][j]<<std::endl; 
  }
  }
  
  
  
  // 17. Delete the memory allocated for the 2d array and set it to nullptr
  for(int i = 0;i<m;++i){
      delete[] dd[i];
  }
  delete[] dd;
  dd = nullptr;
  

  return 0;
}
