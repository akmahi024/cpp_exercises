// polygon.h

#ifndef POLYGON_H
#define POLYGON_H

#include "shape.h"
#include "point.h"
#include <vector>
#include <string>
#include <stdexcept>

class Polygon : public Shape {
public:
    Polygon(int num_vertices, const std::vector<Point>& vertices);

    std::string get_name() const override;
    float compute_area() const override;
    Polygon* create() const override;
    Polygon* clone() const override;

    ~Polygon() override = default;

private:
    int num_vertices_;
    std::vector<Point> vertices_;
};

#endif // POLYGON_H
