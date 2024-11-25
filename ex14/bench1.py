# benchmark.py
import subprocess
import pandas as pd
import numpy as np
import re

def compile_program():
    """Compile the C++ program with optimization"""
    try:
        subprocess.run(['g++', '-o', 'dot_product', 'ex14.cpp', '-pthread'], check=True)
        return True
    except subprocess.CalledProcessError:
        print("Failed to compile the program")
        return False

def run_benchmark(vector_size, num_threads):
    """Run a single benchmark and return timing results"""
    try:
        result = subprocess.run(['./dot_product', str(vector_size), str(num_threads)],
                                capture_output=True, text=True, check=True)

        # Extract milliseconds and microseconds using regex
        ms_match = re.search(r'Elapsed time \(ms\): (\d+)', result.stdout)
        us_match = re.search(r'\(microsecs\): (\d+)', result.stdout)

        if ms_match and us_match:
            return float(ms_match.group(1)), float(us_match.group(1))
        else:
            print(f"Failed to parse timing output: {result.stdout}")
            return None, None
    except subprocess.CalledProcessError as e:
        print(f"Error running benchmark: {e}")
        return None, None

def main():
    # Configuration
    vector_sizes = [1_000_000, 5_000_000, 10_000_000, 50_000_000, 100_000_000]
    thread_counts = [1, 2, 4, 8, 16]
    runs_per_config = 3
    output_file = 'benchmark_results.csv'

    # Compile the program
    if not compile_program():
        return

    # Initialize results list
    results = []

    # Run benchmarks
    total_runs = len(vector_sizes) * len(thread_counts) * runs_per_config
    current_run = 0

    for size in vector_sizes:
        for threads in thread_counts:
            times_ms, times_us = [], []

            for run in range(runs_per_config):
                current_run += 1
                print(f"Progress: {current_run}/{total_runs} "
                      f"(Size: {size}, Threads: {threads}, Run: {run + 1})")

                ms, us = run_benchmark(size, threads)
                if ms is not None and us is not None:
                    times_ms.append(ms)
                    times_us.append(us)

            # Calculate average times
            if times_ms and times_us:
                results.append({
                    'vector_size': size,
                    'num_threads': threads,
                    'time_ms': np.mean(times_ms),
                    'time_us': np.mean(times_us)
                })

    # Convert results to DataFrame
    df = pd.DataFrame(results)

    # Save results to CSV
    df.to_csv(output_file, index=False)
    print(f"\nResults saved to {output_file}")

if __name__ == "__main__":
    main()
