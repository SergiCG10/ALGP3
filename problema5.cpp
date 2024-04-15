#include <iostream>
#include <algorithm>
#include "quicksort.cpp"

using namespace std;

class unionFind{
    private:
        int* padre;
        int size;
    public:

    unionFind(){
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

    ~unionFind(){
        delete [] padre;
        size = 0;
    }   
};

class grafo{

    private:

    int numVertices;
    int numAristas;

    float** matrizAdyacencia;

    public:

    grafo(){
        numVertices = 0;
        numAristas = 0;
    }
    
    grafo(int v, int a ){

        if( v < 0 || a < 0){
            throw invalid_argument("Numero de vertices o de aristas erroneo");
        }
        numVertices = v;
        numAristas = a;

        matrizAdyacencia = new float* [v];
        for(int i =0; i < v; i++){
            matrizAdyacencia[i] = new float[v];
        }
        
        //CONTINUAR CON EL IMPUT DE LOS ARISTAS
        //for(int i =0; i < v; int )
        for(int i =0; i < v; i++){
            for(int j =0; j< v; j++){
                matrizAdyacencia[i][j] = 0; // 0 representará nuestro infinito
            }
        }
        
    }

    int getNumVertices() const{
        return numVertices;
    }

    int getNumAristas() const{
        return numAristas;
    }

    pair<bool, float> getArista(int n1, int n2) const{
        pair< bool, float> ret(false, 0);

        if( n1 < 0 || n2 < 0 || n1 >= (*this).getNumVertices() || n2 >= (*this).getNumVertices()){
            throw std::out_of_range("Alguno de los nodos no existe");
        }

        if( matrizAdyacencia[n1][n2] != 0){
            ret.first = true;
            ret.second = matrizAdyacencia[n1][n2];
        }
        return ret;
    }

    bool setArista( int n1, int n2, int valor){
        bool cambio = false;
        
        if(getArista(n1,n2).first ==false){
            matrizAdyacencia[n1][n2] = valor;
            cambio = true;
        }else{
            cout<< "¿Desea sobreescribir el arista? s/n";
            char opcion;
            cin>>opcion;

            if(opcion == 's'){
                matrizAdyacencia[n1][n2] = valor;
                cambio = true;
            }
        }

        return cambio;
    }

    void insertarAristas(int nodo){
        
        int n;
        do{
            cout<<"Introduzca el vertice con el que insertar el arista, -1 para terminar"<<endl;
            cin >>n;

            while( n < -1){
                cout<<"Valor erróneo, ID del vertice no puede ser negativo, introduzca de nuevo:"<<endl; 
                cin >>n;
            }
            if( n != -1 ){
                float valor;
                cout<<"Que valor desea introducir?"<<endl;  
                cin >> valor;

                while( n < -1){
                    cout<<"Valor erróneo, -1 para vertices no conexos, valor positivo para los conexos:"<<endl; 
                    cin >>n;
                }

                matrizAdyacencia[nodo][n] = valor;
                matrizAdyacencia[n][nodo] = valor;
            }
            
        }while( n != -1);
    }
    void insertarNodo(float *arista){
        
        //Aumentamos el número de vertices
        numVertices++;

        //Copiamos la matriz
        float ** nuevaMatriz = new float * [getNumVertices()];
        for( int i =0 ; i < getNumVertices() -1; i++){
            for(int j =0; j < getNumVertices() - 1; j++){
                nuevaMatriz[i][j] = getArista(i, j).second;
            }
        } 

        //Inicializamos a -1 los aristas entre los nodos
        for(int i = 0 ; i < getNumVertices(); i++){
            nuevaMatriz[i][getNumVertices()-1] = -1;
        }
        for(int j = 0 ; j < getNumVertices() -1 ; j++){
            nuevaMatriz[getNumVertices()-1][j] = -1;
        }

        //Insertamos los valores de los aristas
        insertarAristas(getNumVertices()-1);

        for(int i =0; i < getNumVertices()-1; i++ ){
            delete [] matrizAdyacencia[i];
        }
        delete matrizAdyacencia;
        matrizAdyacencia = nuevaMatriz;
    }

    void Kruskal(){
        float precioTotal = 0; //Precio de asfaltar el conjunto de 
                           //calles seleccionadas
        unionFind S;
        

    while(0 ){
        ;
    }
}
};


int main(){
    
}