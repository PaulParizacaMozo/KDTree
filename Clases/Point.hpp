#include <iostream>
#include <math.h>

#ifndef POINT_H
#define POINT_H

class Point{
    public:
        double  x = 0;
        double  y = 0;
        double  z = 0;
        Point(double x,double y ,double z) : x(x), y(y), z(z){}
        bool operator== (const Point &p) const{
            return (x == p.x) && (y == p.y) && (z == p.z);
        }
        friend std::ostream& operator<< (std::ostream &out, const Point &p){
            return out <<"("<<p.x<<","<<p.y<<","<<p.z<<")";
        }
        double getCoordinate(int coordinate) const {
            switch (coordinate)            {
            case 0:
                return x;
            case 1:
                return y;
            case 2:
                return z;
            default:
                return 0.0;
            }
        }
        double distance(Point aux){
            return std::sqrt(std::pow(x - aux.x, 2) + std::pow(y - aux.y, 2) + std::pow(z - aux.z, 2));
        }

};

#endif /* POINT_H */
