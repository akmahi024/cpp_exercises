import pandas as pd
import matplotlib.pyplot as plt

# Load the results from the CSV file
df = pd.read_csv('results.csv')

# Plot the results for milliseconds (ms)
plt.figure(figsize=(10, 6))
for num_threads in df['num_threads'].unique():
    subset = df[df['num_threads'] == num_threads]
    plt.plot(subset['vector_size'], subset['time_ms'], label=f'Threads: {num_threads}')

plt.xlabel('Vector Size')
plt.ylabel('Elapsed Time (ms)')
plt.title('Dot Product Computation Time in Milliseconds')
plt.legend()
plt.grid(True)
plt.savefig('results_plot_ms.png')
plt.show()

# Plot the results for microseconds (us)
plt.figure(figsize=(10, 6))
for num_threads in df['num_threads'].unique():
    subset = df[df['num_threads'] == num_threads]
    plt.plot(subset['vector_size'], subset['time_us'], label=f'Threads: {num_threads}')

plt.xlabel('Vector Size')
plt.ylabel('Elapsed Time (us)')
plt.title('Dot Product Computation Time in Microseconds')
plt.legend()
plt.grid(True)
plt.savefig('results_plot_us.png')
plt.show()
