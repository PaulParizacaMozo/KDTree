#ifndef KDTREE_HPP
#define KDTREE_HPP

#include "Point.hpp"
#include "Neighbor.hpp"
#include <iostream>
#include <vector>
#include <string>
#include <cstddef>

class Kdtree{
    struct Node{
        Point p;
        int level;
        Node *child[2];
        Node(Point p, int level) : p(p), level(level), child{nullptr, nullptr} {}
        friend std::ostream& operator<< (std::ostream &out, const Node &aux) {
            return out << aux.p << "\n ->Level: "<<aux.level<<"\n";
        }
    };

    public:
        Node *root;
        int dimension;
        Kdtree(int dimension) : root(nullptr), dimension(dimension) {}
        ~Kdtree();
        void insert(Point newP);
        void insert(Node *&current, Point newP, int level);
        void printNodes();
        void printNodes(Node *root);
        bool search(Point auxP);
        bool search(Node *root, Point auxP, int level);
        std::vector<Neighbor> KNN(Point p, int n_points);
        void KNN(Node *current, Point target, int n_points, std::vector<Neighbor> &neighbors);
};

#endif
