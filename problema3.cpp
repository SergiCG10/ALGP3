///*
// * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
// * Click nbfs://nbhost/SystemFileSystem/Templates/cppFiles/main.cc to edit this template
// */
//
///* 
// * File:   main.cpp
// * Author: emil
// *
// * Created on April 2, 2024, 5:55 PM
// */
//
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

using namespace std;

struct Gasolinera {
    int distancia; // Distancia en kilómetros desde el origen
    int capacidad; // Capacidad de la gasolinera en kilómetros
};

// Función para comparar gasolineras por distancia
bool compararPorDistancia(const Gasolinera& a, const Gasolinera& b) {
    return a.distancia < b.distancia;
}
bool compararPorDistancia_(const Gasolinera& a, const Gasolinera& b) {
    return a.distancia > b.distancia;
}


// Algoritmo greedy para determinar las paradas óptimas
std::vector<Gasolinera> paradasOptimas(const std::vector<Gasolinera>& gasolineras, int capacidadTanque, int distanciaTotal) {

    int distanciaRecorrida = 0;
    int indiceGasolinera = 0;
     std::vector<Gasolinera> final;
     std::vector<Gasolinera> resp;
     
   while (distanciaRecorrida <= distanciaTotal) {
        // Buscamos la gasolinera más lejana que aún esté dentro del alcance
        for(int i=indiceGasolinera; gasolineras[i].distancia  <=   capacidadTanque ; i++){
            final.push_back(gasolineras[i]);
            final.back().distancia=capacidadTanque-final.back().distancia+final.back().capacidad;
            //cout << final.back().distancia << endl;
            final.back().capacidad=indiceGasolinera;
            indiceGasolinera++;
        }
         std::sort(final.begin(), final.end(),compararPorDistancia);
//        for(int i=0; i<indiceGasolinera;i++ ){
//            cout << "N: " <<i << "  C: " << final[i].capacidad << " D: " << final[i].distancia << endl;
//        }
         indiceGasolinera = final.back().capacidad;
        // cout << indiceGasolinera << endl; 
         distanciaRecorrida +=  final.back().distancia;
         capacidadTanque = final.back().distancia;
         resp.push_back(gasolineras[indiceGasolinera]);
          //cout << "  D: " << resp.back().distancia << " C: " << resp.back().capacidad << endl;
         
    }

    return resp;
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
//    for(int i=0; i<n;i++ ){
//        cout << "N: " <<i << "  D: " << gasolineras[i].distancia << " C: " << gasolineras[i].capacidad << endl;
//    }
    // Calculamos las paradas óptimas
    std::vector<Gasolinera> final = paradasOptimas(gasolineras, k, distanciaTotal);

    std::cout << "Las paradas óptimas para repostar son: " << endl;
    for (int i=0; i<final.size();i++) {
        cout << "  Distancia: " << final[i].distancia << " Capacidad: " << final[i].capacidad << endl;
    }
    std::cout << std::endl;

    return 0;
}

