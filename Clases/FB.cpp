#include "FB.hpp"
#include <fstream>
#include <sstream>
#include <set>
#include <vector>
#include <chrono>

using namespace std;

void FB::print(){
    for (const auto &p : points)
        cout << "(" << p.x << ", " << p.y << ", " << p.z << ")" << endl;
}

bool FB::search(Point data){
    for (const auto &p : points)
        if (p == data)
            return true;
    return false;
}

set<Neighbor> FB::searchNeighbors(Point auxP, int cantPoints) {
    set<Neighbor> neighbors;
    for (auto &p : this->points) {
        double dist = p.distance(auxP);
        Neighbor neighbor(p,dist);
        if ((int)neighbors.size() < cantPoints)
            neighbors.emplace(neighbor);
        else {
            if (dist < neighbors.rbegin()->distance) {
                neighbors.erase(prev(neighbors.end()));
                neighbors.emplace(neighbor);
            }
        }
    }
    return neighbors;
}

void insertPointsFromFileFB(const string& filename, FB &fb) {
    ifstream file(filename);
    if (!file.is_open()) {
        cerr << "Error al abrir el archivo " << filename << endl;
        return;
    }

    auto start = chrono::high_resolution_clock::now();
    auto end = chrono::high_resolution_clock::now();
    chrono::duration<double, milli> tiempo;
    string line;
    start = chrono::high_resolution_clock::now();
    while (getline(file, line)) {
        stringstream ss(line);
        double x, y, z;

        // Lee los valores x, y, z del formato x,y,z
        char discard;
        if (ss >> x >> discard >> y >> discard >> z) {
           fb.insert({x, y, z});
        } else {
            cerr << "Error al leer la línea: " << line << endl;
        }
    }
    end = chrono::high_resolution_clock::now();
    tiempo = end - start;
    cout << "Tiempo de inserción en Vector(Fuerza Bruta): " << tiempo.count() << " milisegundos." << endl;
    file.close();
}
