#include <iostream>
#include <algorithm>
#include "quicksort.cpp"

using namespace std;

class unionFind{
    private:
        int* padre;
        int size;
    public:

    UnionFind(){
        padre = 0;
        size = 0;
    }
    
    int getSize() const{
        return size;
    }

    int & getPadre(int n){
        if(n < this->getSize() && n >= 0){
            return padre[n];
        }
    }

    const int & getPadre(int n) const{
        if(n < this->getSize() && n >= 0){
            return padre[n];
        }
    }

    void makeSet(int n){
        size = n;
        padre = new int [n];

        for( int i = 0; i< this->getSize(); i++){
            padre[n] = n;
        }
    }

    int findSet(int n ){
        int ret = n;
        if( n != padre[n]){
            ret = findSet(padre[n]);
        }
        return ret;
    }

    void Union( int x, int y){
        if( x > y){
            padre[ findSet(x) ] = y;
        }else{
            padre[ findSet(y) ] = x;
        }
    }

    ~UnionFind(){
        delete [] padre;
        size = 0;
    }   
};

void Kruskal( int* V, int* A ){
    float precioTotal = 0; //Precio de asfaltar el conjunto de 
                           //calles seleccionadas
}

int main(){
    
}