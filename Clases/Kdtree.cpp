#include "Kdtree.hpp"
#include <fstream>
#include <sstream>
#include <utility>
#include <set>
#include <stack>
#include <limits>
#include <queue>
#include <chrono>
using namespace std;

Kdtree::~Kdtree(){
    delete root;
    root = nullptr;
}

void Kdtree::insert(Point newP){
    insert(root, newP, 0);
}

void Kdtree::insert(Node *&current, Point newP, int level){
    if (current == nullptr){
        current = new Node(newP, level);
        return;
    }
    int xyz = level % dimension;
    if (xyz == 0){
        insert(current->child[current->p.x < newP.x],newP,++level);
    }
    else if (xyz == 1)    {
        insert(current->child[current->p.y < newP.y],newP,++level);
    }
    else{
        insert(current->child[current->p.z < newP.z],newP,++level);
    }
}

void Kdtree::printNodes(){
    printNodes(root);
}

void Kdtree::printNodes(Node *current){
    if (current == nullptr)
        return;
    printNodes(current->child[0]); // Left Node
    cout<<*current;
    printNodes(current->child[1]); // Right Node
}

bool Kdtree::search(Point auxP){
    return search(root, auxP, 0);
}

bool Kdtree::search(Node *current, Point auxP, int level){
    if (current == nullptr)
        return false;
    if (current->p == auxP)
        return true;
    int xyz = level % dimension;
    if (xyz == 0){
        return search(current->child[current->p.x < auxP.x],auxP,++level);
    }
    else if (xyz == 1){
        return search(current->child[current->p.y < auxP.y],auxP,++level);
    }
    else{
        return search(current->child[current->p.z < auxP.z],auxP,++level);
    }
}

vector<Neighbor> Kdtree::KNN(Point data, int n_points){
    vector<Neighbor> aux;
    KNN(root, data, n_points, aux);
    return aux;
}

void Kdtree::KNN(Node *current, Point target, int n_points, vector<Neighbor> &neighbors) {
    if (current == nullptr) return;

    // Calcula la distancia entre el punto almacenado en el nodo y el punto de consulta
    double dist = current->p.distance(target);

    // Si aún no hemos alcanzado la cantidad deseada de vecinos, o si la distancia es menor que el vecino más lejano actual
    if (neighbors.size() < n_points) {
        // Agrega el nodo actual a la lista de vecinos y reorganiza la lista para mantenerla ordenada por distancia
        neighbors.emplace_back(current->p, dist);
        push_heap(neighbors.begin(), neighbors.end());
    }
    else if (dist < neighbors.front().distance) {
        // Si la distancia es menor que el vecino más lejano, actualiza el vecino más lejano y reorganiza la lista
        pop_heap(neighbors.begin(), neighbors.end());
        neighbors.back() = Neighbor(current->p, dist);
        push_heap(neighbors.begin(), neighbors.end());
    }

    // Determina la dimensión actual (eje) en la que se divide el árbol
    int xyz = current->level % dimension;

    // Determina el orden de visita de los nodos hijos basándose en la posición del punto de consulta en la dimensión actual
    Node *firstNodeToVisit = nullptr;
    Node *secondNodeToVisit = nullptr;

    if (target.getCoordinate(xyz) < current->p.getCoordinate(xyz)) {
        firstNodeToVisit = current->child[0];
        secondNodeToVisit = current->child[1];
    }
    else {
        firstNodeToVisit = current->child[1];
        secondNodeToVisit = current->child[0];
    }
    // Realiza la búsqueda recursiva en el nodo correspondiente (primero el que debe visitarse primero)
    KNN(firstNodeToVisit, target, n_points, neighbors);
    // Verifica si es necesario realizar la búsqueda en el otro nodo, basándose en la distancia al plano de separación
    if (neighbors.size() < n_points || fabs(target.getCoordinate(xyz) - current->p.getCoordinate(xyz)) < neighbors.front().distance){
        KNN(secondNodeToVisit, target, n_points, neighbors);
    }
}

void insertPointsFromFileKdtree(const string& filename, Kdtree *root) {
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
            root->insert({x, y, z});
        } else {
            cerr << "Error al leer la línea: " << line << endl;
        }
    }
    end = chrono::high_resolution_clock::now();
    tiempo = end - start;
    cout << "Tiempo de inserción en el KDTree: " << tiempo.count() << " milisegundos." << endl;
    file.close();
}

