#include "disk.h"
#include <iostream>

int main() {
    // Create a disk with center (2.0, 3.0) and radius 5.0
    Disk d1(Point(2.0f, 3.0f), 5.0f);

    // Test get_name()
    std::cout << "Shape: " << d1.get_name() << std::endl;

    // Test compute_area()
    std::cout << "Area: " << d1.compute_area() << std::endl;

    // Test create()
    Shape* d2 = d1.create();
    std::cout << "Created Shape: " << d2->get_name() << ", Area: " << d2->compute_area() << std::endl;

    // Test clone()
    Shape* d3 = d1.clone();
    std::cout << "Cloned Shape: " << d3->get_name() << ", Area: " << d3->compute_area() << std::endl;

    // Clean up
    delete d2;
    delete d3;

    return 0;
}
