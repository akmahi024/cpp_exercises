#include "queue.h"

bool Queue::empty() const {
    return _num_items == 0;
}

bool Queue::full() const {
    return _num_items == _max_size;
}

int Queue::size() const {
    return _num_items;
}

void Queue::enqueue(const Point p) {
    if (full()) {
        std::cerr << "Queue overflow error!" << std::endl;
        exit(EXIT_FAILURE);
    }
    _items[_last] = p;
    _last = (_last + 1) % _max_size;
    _num_items++;
}

void Queue::dequeue() {
    if (empty()) {
        std::cerr << "Queue underflow error!" << std::endl;
        exit(EXIT_FAILURE);
    }
    _first = (_first + 1) % _max_size;
    _num_items--;
}

Point Queue::peek() const {
    if (empty()) {
        std::cerr << "Queue is empty!" << std::endl;
        exit(EXIT_FAILURE);
    }
    return _items[_first];
}
