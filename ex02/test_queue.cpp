#include "queue.h"
#include <iostream>
#include <stdexcept> // For std::runtime_error

int main() {
    // Create a queue with max size 3 to  test overflow
    Queue q(3);
    int x, y, z;

    // User input for points
    for (int i = 0; i < 3; ++i) {
        std::cout << "Enter coordinates for Point " << (i + 1) << " (x y z): ";
        std::cin >> x >> y >> z;

        try {
            q.enqueue(Point(x, y, z));
            std::cout << "Enqueued: (" << x << ", " << y << ", " << z << ")\n";

            // Verify if the queue is full after each enqueue
            if (q.full()) {
                std::cout << "Queue is full now!\n";
                break; // Exit if the queue is full
            }
        } catch (const std::runtime_error& e) {
            std::cout << "Caught exception: " << e.what() << std::endl;
            break; // Exit if an error occurs
        }
    }

    // Check the queue size after user input
    std::cout << "Queue size after attempted enqueues: " << q.size() << std::endl; // Should print 3 or less

    // Peek at the first element
    if (!q.empty()) {
        Point p = q.peek();
        std::cout << "Peek: (" << p.x << ", " << p.y << ", " << p.z << ")\n"; // Should print the first element
    }

    // Dequeue all elements
    std::cout << "Dequeuing all elements...\n";
    while (!q.empty()) {
        Point current = q.peek();
        std::cout << "Dequeuing: (" << current.x << ", " << current.y << ", " << current.z << ")\n";
        q.dequeue();
    }

    // Check the final size
    std::cout << "Final queue size: " << q.size() << std::endl; // Should print 0

    // Attempt to peek on an empty queue (should throw an exception)
    try {
        std::cout << "Attempting to peek on an empty queue...\n";
        q.peek();  // This should throw an exception
    } catch (const std::runtime_error& e) {
        std::cout << "Caught exception: " << e.what() << std::endl;
    }

    return 0;
}
