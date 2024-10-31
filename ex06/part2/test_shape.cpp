// test_shape.cpp

#include "polygon.h"
#include <iostream>
#include <vector>

void print_shape_info(Shape* shape) {
    std::cout << "Shape name: " << shape->get_name() << std::endl;
    std::cout << "Area: " << shape->compute_area() << std::endl;
}

int main() {
    // Test Polygon with a simple triangle
    std::vector<Point> triangle_vertices = {{0, 0}, {4, 0}, {2, 3}};
    Shape* triangle = new Polygon(triangle_vertices.size(), triangle_vertices);
    print_shape_info(triangle);
    delete triangle;

    // Test Polygon with a quadrilateral
    std::vector<Point> quadrilateral_vertices = {{0, 0}, {4, 0}, {4, 3}, {0, 3}};
    Shape* quadrilateral = new Polygon(quadrilateral_vertices.size(), quadrilateral_vertices);
    print_shape_info(quadrilateral);
    delete quadrilateral;

    // Test Polygon with a pentagon
    std::vector<Point> pentagon_vertices = {{0, 0}, {3, 0}, {4, 2}, {1, 4}, {-1, 2}};
    Shape* pentagon = new Polygon(pentagon_vertices.size(), pentagon_vertices);
    print_shape_info(pentagon);
    delete pentagon;

    // Test create() method
    Shape* new_polygon = triangle->create(); // Create a new empty Polygon
    std::cout << "Created Shape: " << new_polygon->get_name() << std::endl; // Print name of the created shape
    print_shape_info(new_polygon); // Show created shape info

    // Test clone() method
    Shape* cloned_triangle = triangle->clone(); // Clone the original triangle
    std::cout << "Cloned Shape: " << cloned_triangle->get_name() << std::endl; // Print name of the cloned shape
    print_shape_info(cloned_triangle); // Show cloned shape info

    return 0;
}
