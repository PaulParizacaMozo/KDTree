#include <bits/types/struct_timeval.h>
#include <iostream>
#include "Clases/Kdtree.cpp"
#include "Clases/FB.cpp"
#include "Clases/Neighbor.hpp"
#include <chrono>
using namespace std;

int menuPoints(){
    int opt;
    cout << "***Seleccione un archivo para leer***" << endl;
    cout << "1.- 1000.csv" << endl;
    cout << "2.- 10000.csv" << endl;
    cout << "3.- 20000.csv" << endl;
    cout << "Seleccione una opcion\n -> ";
    cin >> opt;
    return opt; 
}

int menuSearch(){
    int opt;
    cout << "\n***MENU PRINCIPAL***" << endl;
    cout << "1.- Mostrar KDTree" << endl;
    cout << "2.- Buscar un punto en el KDTree" << endl;
    cout << "3.- Buscar un punto mediante Fuerza Bruta(vector)" << endl;
    cout << "4.- Buscar los N puntos vecinos en el KDTree" << endl;
    cout << "5.- Buscar los N puntos vecinos mediante Fuerza Bruta(vector)" << endl;
    cout << "0.- Salir" << endl;
    cout << "Seleccione una opcion\n -> ";
    cin >> opt;
    return opt;
}

int main(){
    Kdtree kd(3);
    FB fb;
    int opt;
    vector<Neighbor>vecinos;
    set<Neighbor>vec;
    opt = menuPoints();
    switch (opt) {
        case 1:
            insertPointsFromFileKdtree("1000.csv",&kd);
            insertPointsFromFileFB("1000.csv",fb);
            break;
        case 2:
            insertPointsFromFileKdtree("10000.csv",&kd);
            insertPointsFromFileFB("10000.csv",fb);
            break;
        case 3:
            insertPointsFromFileKdtree("20000.csv",&kd);
            insertPointsFromFileFB("20000.csv",fb);
            break;
        default:
            return 1;
            break;
    }
    bool salir = false;
    while (!salir){
        opt = menuSearch();
        auto start = chrono::high_resolution_clock::now();
        auto end = chrono::high_resolution_clock::now();
        chrono::duration<double, milli> tiempo;
        int x, y, z, n;
        switch (opt){
            case 1:
                kd.printNodes();
                break;
            case 2:
                cout << "Ingrese los valores del punto a buscar(x y z):\n ";
                cin >> x >> y >> z;
                start = chrono::high_resolution_clock::now();
                kd.search(Point(x,y,z)) ? cout << "Si se encontro el punto\n" : cout << " No se encontro el punto.\n";
                end = chrono::high_resolution_clock::now();
                tiempo = end - start;
                cout << "Tiempo de ejecucion: " << tiempo.count() << " milisegundos." << endl;
                break;
            case 3:
                cout << "Ingrese los valores del punto a buscar(x y z):\n ";
                cin >> x >> y >> z;
                start = chrono::high_resolution_clock::now();
                fb.search(Point(x,y,z)) ? cout << "Si se encontro el punto\n" : cout << " No se encontro el punto.\n";
                end = chrono::high_resolution_clock::now();
                tiempo = end - start;
                cout << "Tiempo de ejecucion: " << tiempo.count() << " milisegundos" << endl;
                break;
            case 4:
                cout << "Ingrese la cantidad de puntos mas cercanos a buscar: ";
                cin >> n;
                cout << "Ingrese los valores del punto base(x y z):\n ";
                cin >> x >> y >> z;
                start = chrono::high_resolution_clock::now();
                vecinos = kd.KNN(Point(x, y, z), n);
                end = chrono::high_resolution_clock::now();
                cout << "Los " << n << " puntos mas cercanos son:" << endl;
                for (auto &v : vecinos) {
                    cout << v.p << "  - Distancia al punto: " << v.distance << endl;
                }
                tiempo = end - start;
                cout << "Tiempo de ejecucion: " << tiempo.count() << " milisegundos" << endl;
                break;
            case 5:
                cout << "Ingrese la cantidad de puntos mas cercanos a buscar: ";
                cin >> n;
                cout << "Ingrese los valores del punto base(x y z):\n ";
                cin >> x >> y >> z;
                start = chrono::high_resolution_clock::now();
                vec = fb.searchNeighbors(Point(x, y, z), n);
                end = chrono::high_resolution_clock::now();
                cout << "Los " << n << " puntos mas cercanos son:" << endl;
                for (auto &v : vec) {
                    cout << v.p << " - Distancia al punto: " << v.distance << endl;
                }
                tiempo = end - start;
                cout << "Tiempo de ejecucion: " << tiempo.count() << " milisegundos" << endl;
                break;
            
            case 0:
                salir = true;
                break;
        }
    }

    return 0;
}

