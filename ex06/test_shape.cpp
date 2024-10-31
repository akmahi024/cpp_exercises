// test_shape.cpp

#include "disk.h"
#include "polygon.h"
#include <iostream>
#include <vector>

void print_shape_info(Shape* shape) {
    std::cout << "Shape name: " << shape->get_name() << std::endl;
    std::cout << "Area: " << shape->compute_area() << std::endl;
}

int main() {
    // Test Disk
    Point center(1.0f, 2.0f);
    float radius = 5.0f;
    Shape* disk = new Disk(center, radius);
    std::cout << "Original Disk:" << std::endl;
    print_shape_info(disk);

    // Test create() function for Disk
    Shape* created_disk = disk->create();
    std::cout << "\nCreated Disk (using create()):" << std::endl;
    print_shape_info(created_disk);

    // Test clone() function for Disk
    Shape* cloned_disk = disk->clone();
    std::cout << "\nCloned Disk (using clone()):" << std::endl;
    print_shape_info(cloned_disk);

    // Clean up Disk objects
    delete disk;
    delete created_disk;
    delete cloned_disk;

    // Test Polygon
    std::vector<Point> vertices = {{0, 0}, {4, 0}, {4, 3}, {0, 3}};
    int num_vertices = vertices.size();
    Shape* polygon = new Polygon(num_vertices, vertices);
    std::cout << "\nOriginal Polygon:" << std::endl;
    print_shape_info(polygon);

    // Test create() function for Polygon
    Shape* created_polygon = polygon->create();
    std::cout << "\nCreated Polygon (using create()):" << std::endl;
    print_shape_info(created_polygon);

    // Test clone() function for Polygon
    Shape* cloned_polygon = polygon->clone();
    std::cout << "\nCloned Polygon (using clone()):" << std::endl;
    print_shape_info(cloned_polygon);
    
    //test for polygon with vertices<3(terminates)
    
    std::vector<Point> vertices1 = {{0, 0}, {4, 0}};
    int num_vertices1 = vertices1.size();
    Shape* polygon1 = new Polygon(num_vertices1, vertices1);
    std::cout << "\nOriginal Polygon:" << std::endl;
    print_shape_info(polygon1);

    // Clean up Polygon objects
    delete polygon;
    delete created_polygon;
    delete cloned_polygon;

    return 0;
}
