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


// Algoritmo greedy para determinar las paradas óptimas
std::vector<int> paradasOptimas(const std::vector<int>& gasolineras, const int capacidadTanque, int distanciaTotal) {

    int indiceGasolinera = 0;
     std::vector<int> film;
     std::vector<int> resp;
     int parada=capacidadTanque;
   while (parada < distanciaTotal) {
        // Buscamos la gasolinera más lejana que aún esté dentro del alcance
      // cout <<"M "<< parada << endl;
        while( gasolineras[indiceGasolinera]  <=  parada && indiceGasolinera<gasolineras.size()){
           //cout << indiceGasolinera << endl; 
            film.push_back(gasolineras[indiceGasolinera]);
            indiceGasolinera++;
            
        }
//        for(int i=0; i<indiceGasolinera;i++ ){
//            cout << "N: " <<i << "  C: " << final[i].capacidad << " D: " << final[i].distancia << endl;
//        }
         std::sort(film.begin(), film.end());
         parada=film.back()+capacidadTanque;
         resp.push_back(film.back());
         cout <<"Parada " <<parada << endl;
        film.clear();
          //cout << "  D: " << resp.back().distancia << " C: " << resp.back().capacidad << endl;
         
    }

    return resp;
}
int main(int argc, char** argv) {

   int n; // Número de gasolineras
    int k; // Capacidad del tanque en kilómetros
    int distanciaTotal; // Distancia total de la ruta

    std::cout << "Ingrese el número de gasolineras: ";
    std::cin >> n;
   
    std::vector<int> gasolineras(n);
    for (int i = 0; i < n; ++i) {
        std::cout << "Ingrese la distancia de la gasolinera " << i + 1 << ": ";
        std::cin >> gasolineras[i];
    }

    std::cout << "Ingrese la capacidad del tanque: ";
    std::cin >> k;

    std::cout << "Ingrese la distancia total de la ruta: ";
    std::cin >> distanciaTotal;

    // Ordenamos las gasolineras por distancia
    

    
    std::sort(gasolineras.begin(), gasolineras.end());
        for(int i=0; i<n;i++ ){
       cout << "N: " <<i << "  D: " << gasolineras[i] << endl;
   }
    std::vector<int> film = paradasOptimas(gasolineras, k, distanciaTotal);

    std::cout << "Las paradas óptimas para repostar son: " << endl;
    for (int i=0; i<film.size();i++) {
        cout  << film[i] << " " ;
    }
    std::cout << std::endl;

    return 0;
}


