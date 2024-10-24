// test_ArrayQueue.cpp
#include "ArrayQueue.h"
#include <iostream>
#include <cassert>

void print_test(const std::string& test_name, const std::string& expected, const std::string& actual) {
    std::cout << "[TEST] " << test_name << "\n";
    std::cout << "  Expected: " << expected << "\n";
    std::cout << "  Actual:   " << actual << "\n";
    std::cout << (expected == actual ? "  -> PASS\n\n" : "  -> FAIL\n\n");
}

void print_test_int(const std::string& test_name, int expected, int actual) {
    std::cout << "[TEST] " << test_name << "\n";
    std::cout << "  Expected: " << expected << "\n";
    std::cout << "  Actual:   " << actual << "\n";
    std::cout << (expected == actual ? "  -> PASS\n\n" : "  -> FAIL\n\n");
}

int main() {
    ArrayQueue q1;
    q1.enqueue("apple");
    q1.enqueue("banana");

    // Move constructor
    ArrayQueue q2 = std::move(q1);
    print_test_int("Queue size after move construction (q2)", 2, q2.size());
    print_test("Peek front item of q2", "apple", q2.peek());
    print_test_int("Queue size of moved-from queue (q1)", 0, q1.size());

    // Move assignment operator
    ArrayQueue q3;
    q3.enqueue("date");
    q3 = std::move(q2);
    print_test_int("Queue size after move assignment (q3)", 2, q3.size());
    print_test("Peek front item of q3", "apple", q3.peek());
    print_test_int("Queue size of moved-from queue (q2)", 0, q2.size());

    std::cout << "All tests completed!\n";
    return 0;
}
