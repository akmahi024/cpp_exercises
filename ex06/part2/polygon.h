#ifndef POLYGON_H
#define POLYGON_H

#include "shape.h"
#include "point.h"  // Ensure this is included
#include <vector>
#include <string>

class Polygon : public Shape {
private:
    std::vector<Point> vertices;

public:
    // Constructor that takes a vector of Points
    Polygon(const std::vector<Point>& vertices);

    // Copy constructor
    Polygon(const Polygon& other);  // Declare it here

    // Overriding Shape interface methods
    std::string get_name() const override;
    float compute_area() const override;
    Polygon* create() const override;
    Polygon* clone() const override;

    // Destructor
    ~Polygon() override {}
};

#endif // POLYGON_H
