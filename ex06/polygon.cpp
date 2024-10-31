// polygon.cpp

#include "polygon.h"

Polygon::Polygon(int num_vertices, const std::vector<Point>& vertices)
    : num_vertices_(num_vertices), vertices_(vertices) {
    if (num_vertices_ < 3) {
        throw std::invalid_argument("A polygon must have at least 3 vertices.");
    }
    if (num_vertices_ != vertices_.size()) {
        throw std::invalid_argument("Number of vertices does not match the size of the vertices list.");
    }
}

std::string Polygon::get_name() const {
    return "Polygon";
}

float Polygon::compute_area() const {
    float area = 0.0f;
    for (int i = 0; i < num_vertices_; ++i) {
        const Point& p1 = vertices_[i];
        const Point& p2 = vertices_[(i + 1) % num_vertices_]; // Wrap around for closing the polygon
        area += (p1.x * p2.y) - (p1.y * p2.x);
    }
    return std::abs(area) / 2.0f; // Area is always positive
}

Polygon* Polygon::create() const {
    // Creates a simple triangle with vertices (0,0), (1,0), and (0,2)
    // This triangle has an area of 1 based on the given formula.
    std::vector<Point> default_vertices = {Point(0, 0), Point(1, 0), Point(0, 2)};
    return new Polygon(3, default_vertices);
}


Polygon* Polygon::clone() const {
    return new Polygon(*this); // Uses the copy constructor to create a new Polygon
}
