#include "polygon.h"

// Constructor that takes a vector of Points
Polygon::Polygon(const std::vector<Point>& vertices) : vertices(vertices) {}

// Copy constructor
Polygon::Polygon(const Polygon& other) : vertices(other.vertices) {}

// Overriding Shape interface methods
std::string Polygon::get_name() const {
    return "Polygon";
}

// Compute the signed area of the polygon
float Polygon::compute_area() const {
    float area = 0.0f;
    int N = vertices.size();

    for (int i = 0; i < N; i++) {
        area += (vertices[i].x * vertices[(i + 1) % N].y) - (vertices[i].y * vertices[(i + 1) % N].x);
    }

    return 0.5f * area;  // Return the absolute value of area
}

// Create a new Polygon object
Polygon* Polygon::create() const {
    return new Polygon(std::vector<Point>());  // Default to an empty polygon
}

// Clone the current Polygon object
Polygon* Polygon::clone() const {
    return new Polygon(*this);
}
