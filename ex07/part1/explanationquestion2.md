Exceptions can slow down a program, even if they're not actually thrown.
because:
When exceptions are possible, the compiler adds extra instructions to prepare for them which impacts the performance.
exceptions cause unpredictable jumps in the program flow, which makes it harder for the CPU to optimize, leading to slower code.
Handling exceptions can increase memory usage because more data structures are needed to manage errors.
code bloat:
Exception handling adds extra tables and data to the compiled program, making it larger.
so it should be mostly avoided where performance and memory are tightly limited.
