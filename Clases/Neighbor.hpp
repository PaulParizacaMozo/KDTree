#ifndef NEIGHBOR_HPP
#define NEIGHBOR_HPP

#include "Point.hpp"

class Neighbor{
    public:
        Point p;
        double distance;
        Neighbor(Point p, double distance) : p(p), distance(distance) {}
        bool operator<(const Neighbor &aux) const {
            return distance < aux.distance;
        }
};

#endif // NEIGHBOR_HPP
