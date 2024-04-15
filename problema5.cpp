#include <iostream>
#include <algorithm>
#include "quicksort.cpp"
#include <vector>

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
    void print(){

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
        
        void inicializar(int v){
            matrizAdyacencia = new float* [v];
            for(int i =0; i < v; i++){
                matrizAdyacencia[i] = new float[v];
            }
        }

        void borrar(){
            for(int i =0; i < getNumVertices(); i++ ){
                delete [] matrizAdyacencia[i];
            }
            delete matrizAdyacencia;
        }

        bool setArista( int n1, int n2, int valor){
            bool cambio = false;
            
            if(getArista(n1,n2).first ==false){
                matrizAdyacencia[n1][n2] =valor;
                matrizAdyacencia[n2][n1] =valor;
                cambio = true;
                numAristas++;
            }else{
                cout<< "¿Desea sobreescribir el arista? s/n";
                char opcion;
                cin>>opcion;

                if(opcion == 's'){
                    matrizAdyacencia[n1][n2] =valor;
                    matrizAdyacencia[n2][n1] =valor;
                    cambio = true;
                    numAristas++;
                }
            }

            return cambio;
        }

        void borrarArista( int n1, int n2){
            
            matrizAdyacencia[n1][n2] =0;
            matrizAdyacencia[n2][n1] =0;
            numAristas--;
            
        }

    public:

        void insertarAristas(int nodo){
            
            int n;
            do{
                cout<<"Introduzca el vertice con el que insertar el arista con "<<nodo<<", -1 para terminar"<<endl;
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

                    setArista(nodo, n, valor);

                    numAristas++;
                }
                
            }while( n != -1);
        }

        void borrarAristas(int nodo){
            
            int n;
            do{
                cout<<"Introduzca el vertice con el que borrar el arista con "<<nodo<<", -1 para terminar"<<endl;
                cin >>n;

                while( n < -1){
                    cout<<"Valor erróneo, ID del vertice no puede ser negativo, introduzca de nuevo:"<<endl; 
                    cin >>n;
                }
                if( n != -1 ){
                    borrarArista(nodo, n, 0);
                }
                
            }while( n != -1);
        }

        grafo(){
            numVertices = 0;
            numAristas = 0;
        }
        
        grafo(int nVertices){

            if( nVertices < 0){
                throw invalid_argument("Numero de vertices o de aristas erroneo");
            }
            numVertices = nVertices;
            numAristas = 0;

            inicializar(nVertices);
            
            for(int i =0; i < nVertices; i++){
                insertarAristas(i);
            }
            
        }

        grafo( const grafo& g){
            this->numVertices = g.getNumVertices();
            this->numAristas = g.getNumAristas();

            inicializar(g.getNumVertices());
            for(int i =0 ; i < this->getNumVertices(); i++){
                for(int j =0; j < this->getNumVertices(); j++){
                    this->matrizAdyacencia[i][j] = g.getArista(i,j);
                }
            }
        }

        grafo operator=( const grafo& g){
            this->numVertices = g.getNumVertices();
            this->numAristas = g.getNumAristas();

            borrar();
            inicializar(g.getNumVertices());
            for(int i =0 ; i < this->getNumVertices(); i++){
                for(int j =0; j < this->getNumVertices(); j++){
                    this->matrizAdyacencia[i][j] = g.getArista(i,j);
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

        vector<float> getTodosAristas(){
            vector<float> conjuntoArista;
            int filasComprobadas = 0; 
            int aristasAdded = 0;

            for( int i = 0; i < getNumVertices()&& this->getNumAristas() != aristasAdded; i++ ){
                for(int j =filasComprobadas; j < getNumVertices() && this->getNumAristas() != aristasAdded; j++){
                    if( getArista(i,j).first == true ){
                        conjuntoArista.push_back( getArista(i,j).second );
                        aristasAdded++;
                    }
                }
            }

            return conjuntoArista;
        }

        void insertarNodo(){
            
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

            //Liberamos memoria
            borrar();

            //Aumentamos el número de vertices
            numVertices++;

            //Sustituimos por nuestra nueva matriz
            matrizAdyacencia = nuevaMatriz;
        }

        ~grafo(){
            for(int i =0; i < getNumVertices()-1; i++ ){
                delete [] matrizAdyacencia[i];
            }
            delete matrizAdyacencia;
            numVertices = 0;
            numAristas =0;
        }   
};

pair<bool, unionFind> Kruskal(grafo g){
    float precioTotal = 0; //Precio de asfaltar el conjunto de 
                            //calles seleccionadas
    unionFind S;
    pair<bool, unionFind> ret;

    ret.first = false;

    vector<float> todosAristas = g.getTodosAristas();
    quickSort(todosAristas, 0, g.getNumAristas());

    S.makeSet( g.getNumVertices());

    while( !todosAristas.empty() && S.getSize() != g.getNumVertices() ){
        int n1, n2;
        
        if( S.findSet(n1) != S.findSet(n2) ){
            S.Union(n1, n2);
        }
    }
    if( S.getSize() == g.getNumVertices()) {
        ret.first = true;
    }

    return ret;
}

int main(){
    int opcion;
    Grafo g;
    cout<<"Comenzando ejecución...."<<endl;

    do{
        cout<<"¿Que desea hacer?"<<endl;
        
        cout<<"\t 1: Crear grafo"<<endl;
        cout<<"\t 2: Insertar vertice"<<endl;
        cout<<"\t 3: Insertar aristas"<<endl;
        cout<<"\t 4: Eliminar aristas"<<endl;
        cout<<"\t 5: Calcular el recorrido óptimo"<<endl;
        cout<<"\t Otro numero: Terminar el programa"<<endl;
        cin>>opcion;

        switch(opcion){
            case 1:
                cout<<"¿Cuantos vertices tendrá el grafo?"<<endl;
                int vert;
                cin>> vert;
                g = Grafo(vert);
                break;
            case 2:
                g.insertarNodo();
                break;
            case 3:
                g.insertarAristas();
                break;
            case 4:
                cout<<"De que vertice desea eliminar aristas?"<<endl;
                int vert;
                cin>> vert;
                g.borrarAristas();
                break;
            case 5:
                unionFind uf;
                uf = g.Kruskal();
                uf.print();
                break;
            default: 
            
                break;
        }
    }while(opcion > 0 && opcion < 5);

    cout<<"Terminando ejecución..." 
    return 0;
}