#include "queue.h"

int main() {
    Queue q;

    // Test enqueue
    q.enqueue(Point(1, 2, 3));
    q.enqueue(Point(4, 5, 6));
    q.enqueue(Point(7, 8, 9));

    // Test size
    std::cout << "Queue size after enqueues: " << q.size() << std::endl; // Should print 3

    // Test peek
    Point p = q.peek();
    std::cout << "Peek: (" << p.x << ", " << p.y << ", " << p.z << ")" << std::endl; // Should print (1, 2, 3)

    // Test dequeue
    q.dequeue();
    std::cout << "Queue size after one dequeue: " << q.size() << std::endl; // Should print 2

    p = q.peek();
    std::cout << "Peek after one dequeue: (" << p.x << ", " << p.y << ", " << p.z << ")" << std::endl; // Should print (4, 5, 6)

    // Fill the queue to test overflow
    q.enqueue(Point(10, 11, 12));
    q.enqueue(Point(13, 14, 15));

    // Should print queue size 4
    std::cout << "Queue size after more enqueues: " << q.size() << std::endl; // Should print 4

    // Test dequeuing all elements
    while (!q.empty()) {
        Point current = q.peek();
        std::cout << "Dequeuing: (" << current.x << ", " << current.y << ", " << current.z << ")" << std::endl;
        q.dequeue();
    }

    // Final size should be 0
    std::cout << "Final queue size: " << q.size() << std::endl; // Should print 0

    return 0;
}
