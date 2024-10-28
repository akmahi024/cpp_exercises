#include "disk.h"
#include "polygon.h"
#include <iostream>
#include <vector>

int main() {
    // Test Disk with positive coordinates
    Disk d1(Point(2.0f, 3.0f), 5.0f);
    std::cout << "Shape: " << d1.get_name() << std::endl;
    std::cout << "Coordinates: (" << d1.get_center().x << ", " << d1.get_center().y << ")" << std::endl; // Print coordinates
    std::cout << "Area: " << d1.compute_area() << std::endl;

    Shape* d2 = d1.create();
    std::cout << "Created Shape: " << d2->get_name() << ", Area: " << d2->compute_area() << std::endl;

    Shape* d3 = d1.clone();
    std::cout << "Cloned Shape: " << d3->get_name() << ", Area: " << d3->compute_area() << std::endl;
    delete d2;
    delete d3;

    // Test Disk with negative coordinates
    Disk d4(Point(-2.0f, -3.0f), 5.0f);
    std::cout << "\nDisk with Negative Coordinates:" << std::endl;
    std::cout << "Shape: " << d4.get_name() << std::endl;
    std::cout << "Coordinates: (" << d4.get_center().x << ", " << d4.get_center().y << ")" << std::endl; // Print coordinates
    std::cout << "Area: " << d4.compute_area() << std::endl;

    Shape* d5 = d4.create();
    std::cout << "Created Shape: " << d5->get_name() << ", Area: " << d5->compute_area() << std::endl;

    Shape* d6 = d4.clone();
    std::cout << "Cloned Shape: " << d6->get_name() << ", Area: " << d6->compute_area() << std::endl;
    delete d5;
    delete d6;

    // Test Polygon with positive coordinates
    std::vector<Point> points = {Point(0.0f, 0.0f), Point(4.0f, 0.0f), Point(4.0f, 3.0f), Point(0.0f, 3.0f)};
    Polygon p1(points);
    std::cout << "\nShape: " << p1.get_name() << std::endl;
    std::cout << "Coordinates: ";
    for (const auto& point : points) {
        std::cout << "(" << point.x << ", " << point.y << ") ";
    }
    std::cout << std::endl; // Print coordinates
    std::cout << "Area: " << p1.compute_area() << std::endl;

    Shape* p2 = p1.create();
    std::cout << "Created Shape: " << p2->get_name() << ", Area: " << p2->compute_area() << std::endl;

    Shape* p3 = p1.clone();
    std::cout << "Cloned Shape: " << p3->get_name() << ", Area: " << p3->compute_area() << std::endl;
    delete p2;
    delete p3;

    // Test Polygon with negative coordinates
    std::vector<Point> negativePoints = {
        Point(-4.0f, -2.0f),
        Point(0.0f, -2.0f),
        Point(0.0f, 2.0f),
        Point(-4.0f, 2.0f)
    };
    Polygon p4(negativePoints);
    std::cout << "\nPolygon with Negative Coordinates:" << std::endl;
    std::cout << "Shape: " << p4.get_name() << std::endl;
    std::cout << "Coordinates: ";
    for (const auto& point : negativePoints) {
        std::cout << "(" << point.x << ", " << point.y << ") ";
    }
    std::cout << std::endl; // Print coordinates
    std::cout << "Area: " << p4.compute_area() << std::endl;

    return 0;
}
