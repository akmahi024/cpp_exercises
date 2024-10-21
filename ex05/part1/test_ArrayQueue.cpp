// test_ArrayQueue.cpp
#include "ArrayQueue.h"
#include <iostream>

// Helper function to print test result
void run_test(const std::string& test_name, bool result) {
    std::cout << test_name << ": " << (result ? "SUCCESS" : "FAIL") << std::endl;
}

int main() {
        // Test 1: Default Constructor
        ArrayQueue q1;
        bool t1 = q1.empty() && q1.size() == 0;
        run_test("Test 1 - Default Constructor", t1);

        // Test 2: Enqueue elements
        q1.enqueue("apple");
        q1.enqueue("banana");
        q1.enqueue("cherry");
        bool t2 = (q1.size() == 3) && (q1.peek() == "apple");
        run_test("Test 2 - Enqueue Elements", t2);

        // Test 3: Dequeue elements
        q1.dequeue(); // Removes "apple"
        bool t3 = (q1.size() == 2) && (q1.peek() == "banana");
        run_test("Test 3 - Dequeue Element", t3);

        // Test 4: Enqueue more elements (wrap-around test)
        q1.enqueue("date");
        q1.enqueue("bananastick");
        bool t4 = (q1.size() == 4);
        run_test("Test 4 - Enqueue with Wrap-Around", t4);

        // Test 5: Dequeue all elements to empty the queue
        q1.dequeue(); // "banana"
        q1.dequeue(); // "cherry"
        q1.dequeue(); // "date"
        q1.dequeue(); // "bananastick"
        bool t5 = q1.empty();
        run_test("Test 5 - Empty the Queue", t5);

        // Test 6: Resize by adding more elements
        ArrayQueue q2(2);  // Small initial capacity to force resizing
        for (int i = 0; i < 20; ++i) {
            q2.enqueue("item" + std::to_string(i));
        }
        bool t6 = (q2.size() == 20);
        run_test("Test 6 - Enqueue with Resize", t6);

        // Test 7: Dequeue multiple elements and check front
        for (int i = 0; i < 10; ++i) {
            q2.dequeue();
        }
        bool t7 = (q2.size() == 10) && (q2.peek() == "item10");
        run_test("Test 7 - Dequeue and Check Front", t7);

        std::cout << "All tests completed!" << std::endl;

    return 0;
}
