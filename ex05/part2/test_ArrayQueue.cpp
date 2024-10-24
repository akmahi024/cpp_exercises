// test_ArrayQueue.cpp
#include "ArrayQueue.h"
#include <iostream>
#include <cassert>  // For assertions

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
    ArrayQueue q1;  // Test default constructor

    std::cout << "Starting tests...\n\n";

    // Enqueue elements
    q1.enqueue("apple");
    q1.enqueue("banana");
    q1.enqueue("cherry");

    // Test size after enqueue
    print_test_int("Queue size after 3 enqueues", 3, q1.size());

    // Test peek
    print_test("Peek front item", "apple", q1.peek());

    // Test copy constructor
    ArrayQueue q2 = q1;  // Copy q1 into q2
    print_test_int("Queue size of copy (q2)", 3, q2.size());
    print_test("Peek front item of copy (q2)", "apple", q2.peek());

    // Modify q2 and check that q1 is unaffected
    q2.dequeue();
    print_test("Peek front item of q2 after dequeue", "banana", q2.peek());
    print_test("Peek front item of original queue (q1)", "apple", q1.peek());

    // Test assignment operator
    ArrayQueue q3;
    q3.enqueue("date");
    q3.enqueue("elderberry");

    q3 = q1;  // Assign q1 to q3
    print_test_int("Queue size of assigned queue (q3)", 3, q3.size());
    print_test("Peek front item of assigned queue (q3)", "apple", q3.peek());

    // Modify q3 and ensure q1 remains unchanged
    q3.dequeue();
    print_test("Peek front item of q3 after dequeue", "banana", q3.peek());
    print_test("Peek front item of original queue (q1) remains unchanged", "apple", q1.peek());

    // Test dequeue on q1 until empty
    q1.dequeue();
    q1.dequeue();
    q1.dequeue();
    print_test_int("Queue size of q1 after all dequeues", 0, q1.size());

    // Try dequeue on empty queue (should not crash)
    std::cout << "[TEST] Dequeue on empty queue\n";
    std::cout << "  Expected: Error message about underflow\n";
    std::cout << "  Actual:   ";
    q1.dequeue();  // This should print an error message

    std::cout << "\nAll tests completed!\n";
    return 0;
}
