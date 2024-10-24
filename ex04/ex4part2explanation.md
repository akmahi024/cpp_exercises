cube() is a constexpr function, meaning it performs the calculation at compile-time if given constant inputs.
It takes an integer n and returns n cubed (n * n * n).
test_cube():
        push    rbp
        mov     rbp, rsp
        mov     DWORD PTR [rbp-4], 8
        mov     DWORD PTR [rbp-8], 27
        nop
        pop     rbp
        ret
main:
        push    rbp
        mov     rbp, rsp
        call    test_cube()
        mov     eax, 0
        pop     rbp
        ret
