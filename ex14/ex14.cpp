#include <chrono>
#include <iostream>
#include <vector>
#include <stdexcept> 
#include <thread>
#include <mutex>
#include <cmath>

// Complete: Additional necessary headers ...


// Complete: write the function split that computes the lower/higher indices 
// for which each thread will be responsible. 
void split(std::size_t nele, std::size_t nthreads, std::vector<std::size_t>& lower, std::vector<std::size_t>& upper) 
{
    std::size_t base = nele / nthreads;
    std::size_t rem  = nele % nthreads;

    std::size_t start = 0;

    lower.resize(nthreads);
    upper.resize(nthreads);

    for(std::size_t i=0; i<nthreads; ++i)
    {
        std::size_t size = base + (i < rem ? 1 : 0); 
        lower[i] = start;
        upper[i] = start + size;

        start += size;
    }
}

std::mutex m;

// Complete: add dot_product and modify it such that there is no race condition. 
void dot_product(const std::vector<float>& v1, const std::vector<float>& v2, std::size_t lower, std::size_t higher, float* result) 
{
    float sum = 0;
    for (std::size_t i = lower; i < higher; ++i) 
    {
        sum += v1[i]*v2[i];
    }

    std::lock_guard<std::mutex> lck{m};
    *result += sum;
}


// Complete: the parallel_dot_product function that computes on nthreads the dot product 
// of v1 and v2 
float parallel_dot_product(const std::vector<float>& v1, const std::vector<float>& v2, std::size_t nthreads) 
{

  if (v1.size() != v2.size()) throw std::runtime_error("Sizes of v1 and v2 don't match");

  std::size_t nele = v1.size(); 
  float result = 0;

 
  // Split 'nele' elements into 'nthreads' part
  std::vector<std::size_t> lower;
  std::vector<std::size_t> higher;
  // lower[i] and higher[i] contains the lower and higher indices
  // for which a given thread will compute the dot product
  split(nele, nthreads, lower, higher);  


  // Complete: start 'nthreads' threads
  // don't forget to pass explicitly a reference to the arrays v1 and v2

  std::vector<std::thread> threads;
  for (std::size_t i=0; i<nthreads; ++i) 
  {
    threads.emplace_back(dot_product, std::cref(v1), std::cref(v2), lower[i], higher[i], &result);
    // start a thread that will compute the dot product between v1 and v2 
    // for indices between lower[i] and higher[i]
  }

  // Complete: join the threads with the main thread
    for(std::thread &t : threads)
    {
        t.join();
    }

  return result;
}

void usage(const char* pname) 
{
  std::cout << "Incorrect number of arguments" << std::endl;
  std::cout << "Usage: " << pname << " nele nthreads" << std::endl;
  std::cout << "where nele is the number of elements in the random vectors" << std::endl;
  std::cout << "and nthreads is the number of threads to be used" << std::endl;
  exit(1); 
}


int main(int argc, char** argv)
{
  if (argc != 3) usage(argv[0]); 

  std::size_t nele = std::stoi(argv[1]); 
  std::size_t nthreads = std::stoi(argv[2]); 

  // fill the input vectors with random numbers
  std::vector<float> v1(nele);
  for (size_t i = 0; i < nele; ++i) 
  {
    v1[i] = float(rand())/float(RAND_MAX);
  }

  std::vector<float> v2(nele);
  for (size_t i = 0; i < nele; ++i) 
  {
    v2[i] = float(rand())/float(RAND_MAX);
  }

  std::chrono::steady_clock::time_point start = std::chrono::steady_clock::now();
  float result = parallel_dot_product(v1, v2, nthreads); 
  std::chrono::steady_clock::time_point stop = std::chrono::steady_clock::now();

  std::cout << "Result: " << result << " / Elapsed time (ms): " 
            << std::chrono::duration_cast<std::chrono::milliseconds>(stop - start).count()
            << " / (microsecs): " 
            << std::chrono::duration_cast<std::chrono::microseconds>(stop - start).count()
            << std::endl;
}
