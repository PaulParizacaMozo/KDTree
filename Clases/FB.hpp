#ifndef FB_HPP
#define FB_HPP

#include <iostream>
#include <vector>
#include <algorithm>
#include <set>
#include "Point.hpp"
#include "Neighbor.hpp"

class FB {
    private:
        std::vector<Point> points;
    public:
        FB() {}
        FB(std::vector<Point> &points) : points(points) {}
        ~FB() = default;
        void insert(Point p) { points.push_back(p); }
        void print();
        bool search(Point p);
        std::set<Neighbor> searchNeighbors(Point auxP, int cantPoints);
};

#endif
