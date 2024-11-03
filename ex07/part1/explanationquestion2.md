Exceptions can slow down a program, even if they're not actually thrown.
because:
When exceptions are possible, the compiler adds extra instructions to prepare for them which impacts the performance.
exceptions cause unpredictable jumps in the program flow, which makes it harder for the CPU to optimize, leading to slower code.
Handling exceptions can increase memory usage because more data structures are needed to manage errors.
code bloat:
Exception handling adds extra tables and data to the compiled program, making it larger.
so it should be mostly avoided where performance and memory are tightly limited.

ILLUSTRATION:
--------------
Using Exceptions:
---------------
#include <iostream>
#include <exception>

double divide(double a, double b) {
    if (b == 0) {
        throw std::runtime_error("Division by zero");
    }
    return a / b;
}

int main() {
    try {
        double result = divide(10, 0);
        std::cout << "Result: " << result << std::endl;
    } catch (const std::exception& e) {
        std::cerr << "Caught exception: " << e.what() << std::endl;
    }
    return 0;
}

ASSEMBLY CODE:
--------------
.LC1:
        .string "Division by zero"----------------------------------------->3
divide(double, double):
        push    rbp
        mov     rbp, rsp
        push    r12
        push    rbx
        sub     rsp, 16
        movsd   QWORD PTR [rbp-24], xmm0
        movsd   QWORD PTR [rbp-32], xmm1
        pxor    xmm0, xmm0
        ucomisd xmm0, QWORD PTR [rbp-32]
        jp      .L2
        pxor    xmm0, xmm0
        ucomisd xmm0, QWORD PTR [rbp-32]
        jne     .L2
        mov     edi, 16
        call    __cxa_allocate_exception------------------------------------>1
        mov     rbx, rax
        mov     esi, OFFSET FLAT:.LC1
        mov     rdi, rbx
        call    std::runtime_error::runtime_error(char const*) [complete object constructor]
        mov     edx, OFFSET FLAT:std::runtime_error::~runtime_error() [complete object destructor]
        mov     esi, OFFSET FLAT:typeinfo for std::runtime_error
        mov     rdi, rbx
        call    __cxa_throw-------------------------------------------------->2

ANALYSIS:
---------
1)The call to __cxa_allocate_exception allocates memory for the exception object, adding extra memory usage.
2) __cxa_throw is invoked to throw the exception, disrupting the normal control flow.
3)The line .string "Division by zero" sets up a string for the error message. Each message and function used to handle exceptions contributes to an increase in binary size.

USING RETURN CODE INSTEAD:
-------------------------
#include <iostream>

double divide(double a, double b, bool& error) {
    if (b == 0) {
        error = true;
        return 0;
    }
    error = false;
    return a / b;
}

int main() {
    bool error;
    double result = divide(10, 0, error);
    if (error) {
        std::cerr << "Error: Division by zero" << std::endl;
    } else {
        std::cout << "Result: " << result << std::endl;
    }
    return 0;
}

ASSEMBLY CODE:
-------------
divide(double, double, bool&):
        push    rbp
        mov     rbp, rsp
        movsd   QWORD PTR [rbp-8], xmm0
        movsd   QWORD PTR [rbp-16], xmm1
        mov     QWORD PTR [rbp-24], rdi
        pxor    xmm0, xmm0
        ucomisd xmm0, QWORD PTR [rbp-16]
        jp      .L2
        pxor    xmm0, xmm0
        ucomisd xmm0, QWORD PTR [rbp-16]
        jne     .L2
        mov     rax, QWORD PTR [rbp-24]
        mov     BYTE PTR [rax], 1
        pxor    xmm0, xmm0
        jmp     .L4

ANALYSIS:
---------
1)Instead of allocating memory and throwing an exception, the code only sets a Boolean flag (bool&) to indicate whether an error occurred.
2)Since there’s no __cxa_allocate_exception or __cxa_throw, binary size is significantly smaller, reducing executable bloat.
3) function flow is linear with minimum jumps.

Quantatitive Analysis:
----------------------
1)Binary Size: Compiling with exceptions increase the binary size.
2)Execution Time: Without exceptions, running divide with a non-zero divisor could take less time than with exceptions.
 
