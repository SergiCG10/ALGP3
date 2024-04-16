#include <iostream>
#include <vector>
#include <algorithm>
#include <cstdlib>
#include <chrono>
#include <iostream>
#include <fstream>
#include <bits/stdc++.h>
#include <algorithm>
#include <random>
#include <vector>

struct Gasolinera {
    int distancia; // Distancia en kilómetros desde el origen
    int capacidad; // Capacidad de la gasolinera en kilómetros
};

// Función para comparar gasolineras por distancia
bool compararPorDistancia(const Gasolinera& a, const Gasolinera& b) {
    return a.distancia < b.distancia;
}

// Algoritmo greedy para determinar las paradas óptimas
std::vector<int> paradasOptimas(const std::vector<Gasolinera>& gasolineras, int capacidadTanque, int distanciaTotal) {
    std::vector<int> paradas;
    int distanciaRecorrida = 0;
    int indiceGasolinera = 0;

    while (distanciaRecorrida < distanciaTotal) {
        // Buscamos la gasolinera más lejana que aún esté dentro del alcance
        int siguienteGasolinera = -1;
        for (int i = indiceGasolinera; i < gasolineras.size(); ++i) {
            if (gasolineras[i].distancia - distanciaRecorrida <= capacidadTanque) {
                siguienteGasolinera = i;
            } else {
                break;
            }
        }

        if (siguienteGasolinera == -1) {
            // No hay gasolineras dentro del alcance, repostamos en la más cercana
            paradas.push_back(gasolineras[indiceGasolinera].distancia);
            distanciaRecorrida = gasolineras[indiceGasolinera].distancia;
        } else {
            // Repostamos en la gasolinera más lejana dentro del alcance
            paradas.push_back(gasolineras[siguienteGasolinera].distancia);
            distanciaRecorrida = gasolineras[siguienteGasolinera].distancia;
            indiceGasolinera = siguienteGasolinera + 1;
        }
    }

    return paradas;
}

int main() {
    int n; // Número de gasolineras
    int k; // Capacidad del tanque en kilómetros
    int distanciaTotal; // Distancia total de la ruta

    std::cout << "Ingrese el número de gasolineras: ";
    std::cin >> n;

    std::vector<Gasolinera> gasolineras(n);
    for (int i = 0; i < n; ++i) {
        std::cout << "Ingrese la distancia de la gasolinera " << i + 1 << ": ";
        std::cin >> gasolineras[i].distancia;
        std::cout << "Ingrese la capacidad de la gasolinera " << i + 1 << ": ";
        std::cin >> gasolineras[i].capacidad;
    }

    std::cout << "Ingrese la capacidad del tanque: ";
    std::cin >> k;

    std::cout << "Ingrese la distancia total de la ruta: ";
    std::cin >> distanciaTotal;

    // Ordenamos las gasolineras por distancia
    

    
    std::sort(gasolineras.begin(), gasolineras.end(), compararPorDistancia);

    // Calculamos las paradas óptimas
    std::vector<int> paradas = paradasOptimas(gasolineras, k, distanciaTotal);

    std::cout << "Las paradas óptimas para repostar son: ";
    for (int parada : paradas) {
        std::cout << parada << " ";
    }
    std::cout << std::endl;

    return 0;
}

