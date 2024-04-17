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
#include <cstdlib>
#include <algorithm>

using namespace std;


// Algoritmo greedy para determinar las paradas óptimas
std::vector<int> paradasOptimas(const std::vector<float>& g, const float& capTanque, const float& dist) {
    vector<int> resp;
    float distanciaActual= 0;
    
    if( g[0]> capTanque){
        cerr<<"Distancia entre el inicio y la primera gasolinera más grande que la capacidad del tanque, no hay solución"<<endl;
    }
    for(int i =0; i< g.size(); i++){
        if(g[i+1] - g[i]> capTanque){
            cerr<<"Error, no hay solución, distancia entre dos gasolineras contiguas más grande que la capacidad del tanque"<<endl;
        }
    }
    if( dist - g.back() > capTanque){
        cerr<<"Distancia entre la ultima gasolinera y el final del trayecto más grande que la capacidad del tanque, no hay solución"<<endl;
    }

    for(int i =0; i< g.size() && distanciaActual < dist; i++){
        if( distanciaActual + capTanque < g[i+1] &&  i != g.size() ){
            distanciaActual = g[i];
            resp.push_back(i);
        }else if( i == g.size()-1 ){
            if( distanciaActual + capTanque < dist){
                distanciaActual = g[i];
                resp.push_back(i);
            }
        }
    }
    
    
    return resp;
}

int main() {
    int n; // Número de gasolineras
    float k; // Capacidad del tanque en kilómetros
    float distanciaTotal; // Distancia total de la ruta
    float aux;

    std::cout << "Ingrese el número de gasolineras: \n";
    std::cin >> n;
    while( n < 0){
        std::cout << "Ingrese un número correcto de gasolineras: \n";
        std::cin >> n;
    }

    std::vector<float> gasolineras(n);

    for (int i = 0; i < n; ++i) {
        std::cout << "Ingrese el punto kilométrico de la gasolinera " << i + 1 << ": \n";
        std::cin >> aux;

        while( n < 0){
            std::cout << "Ingrese un número correcto para el punto kilométrico: \n";
            std::cin >> aux;
        }
        
        gasolineras.push_back(aux);
    }

    std::cout << "Ingrese la distancia total de la ruta: \n";
    std::cin >> distanciaTotal;
    while( n < 0){
        std::cout << "Ingrese un número correcto para la distancia final del recorrido: \n";
        std::cin >> distanciaTotal;
    }

    std::cout << "Ingrese la capacidad del tanque: \n";
    std::cin >> k;
    while( n < 0){
        std::cout << "Ingrese un número correcto de capacidad: \n";
        std::cin >> k;
    }
    
    // Ordenamos las gasolineras por distancia
    std::sort(gasolineras.begin(), gasolineras.end());

    // Calculamos las paradas óptimas
    std::vector<int> final = paradasOptimas(gasolineras, k, distanciaTotal);

    std::cout << "Las paradas óptimas para repostar son: " << endl;
    for (int i=0; i<final.size();i++) {
        cout << "  Distancia: " << gasolineras[final[i]] << endl;
    }
    std::cout << std::endl;

    return 0;
}

