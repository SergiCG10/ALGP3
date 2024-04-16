#include <iostream>
#include <algorithm>
#include "quicksort.cpp"
#include <vector>

using namespace std;

struct arista{
    float cantidad;
    int indice1;
    int indice2;
};
bool operator<( const arista& A1, const arista&A2 ){
    return A1.cantidad < A2.cantidad;
}
bool operator>( const arista& A1, const arista&A2 ){
    return A1.cantidad > A2.cantidad;
}
bool operator==(const arista& A1, const arista&A2 ){
    return A1.cantidad == A2.cantidad;
}
bool operator<=(const arista& A1, const arista&A2 ){
    return A1 == A2 || A1 < A2;
}
bool operator>=(const arista& A1, const arista&A2 ){
    return A1 == A2 || A1 > A2;
}

class unionFind{
    private:
        int* padre;
        int size;
        int aristas;
    public:

    unionFind(){
        padre = 0;
        size = 0;
        aristas =0;
    }
    
    int getSize() const{
        return size;
    }

    int getAristas() const{
        return aristas;
    }

    int & getPadre(int n){
        if(n < this->getSize() && n >= 0){
            return padre[n];
        }else{
            throw out_of_range("Indice fuera de rango");
        }
    }

    const int & getPadre(int n) const{
        if(n < this->getSize() && n >= 0){
            return padre[n];
        }else{
            throw out_of_range("Indice fuera de rango");
        }
    }

    void makeSet(int n){
        size = n;
        padre = new int [n];

        for( int i = 0; i< this->getSize(); i++){
            padre[i] = i;
        }
    }

    int findSet(int n ){
        int ret =  n;
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
        aristas++;
    }

    unionFind operator = (const unionFind& uf){
        this->size = uf.size;

        delete [] this->padre;
        this->padre = new int [this->size];
                 
        for(int i = 0; i < this->size; i++){
            this->padre[i] = uf.padre[i];
        }
        return *this;
    }
    unionFind(const unionFind& uf){
        this->size = uf.size;
        
        this->padre = new int [this->size];

        for(int i = 0; i < this->size; i++){
            this->padre[i] = uf.padre[i];
        }
    }
    void print(){
        cout<<endl;
        cout<<"Estructura de relaciones del conjunto: "<<endl;
        for(int i =0; i <this->getSize(); i++){
            cout<< "Vértice:"<< i<<" Padre: "<<this->getPadre(i)<<endl;
        }
        cout<<endl;
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
            this->matrizAdyacencia = new float* [v];
            for(int i =0; i < v; i++){
                this->matrizAdyacencia[i] = new float[v];
                for(int j =0; j < v; j++){
                    this->matrizAdyacencia[i][j] = 0;
                }
            }
        }

        void borrar(){
            for(int i =0; i < getNumVertices(); i++ ){
                delete [] this->matrizAdyacencia[i];
            }
            delete [] this->matrizAdyacencia;
        }

        void borrarArista( int n1, int n2){
            if( getArista(n1, n2).first == true){
                matrizAdyacencia[n1][n2] =0;
                matrizAdyacencia[n2][n1] =0;
                numAristas--;
            }
        }

    public:

        bool setArista( int n1, int n2, int valor){
            bool cambio = false;
            
            if(getArista(n1,n2).first ==false){
                matrizAdyacencia[n1][n2] =valor;
                matrizAdyacencia[n2][n1] =valor;
                cambio = true;
                numAristas++;
            }else{
                cout<< "\t¿Desea sobreescribir el arista? s/n\t";
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

        void insertarAristas(int nodo){
            
            int n;
            do{
                cout<<"\tIntroduzca el vertice con el que insertar el arista con "<<nodo<<", [ 0,"<< this->getNumVertices()-1<<" ], -1 para terminar\n\t";
                cin >>n;
                cout<<endl;
                while( n < -1 || n == nodo || n>= this->getNumVertices()){
                    cout<<"\tValor erróneo, ID del vertice tiene que estár en el rango [ 0,"<< this->getNumVertices()-1<<" ], introduzca de nuevo:\n\t"; 
                    cin >>n;
                }
                
                if( n != -1 ){
                    float valor;
                    cout<<"\t\tQue valor desea introducir?\n\t\t";  
                    cin >> valor;

                    while( n < -1){
                        cout<<"\tValor erróneo, -1 para vertices no conexos, valor positivo para los conexos:\n\t"; 
                        cin >>n;
                    }
                    setArista(nodo, n, valor);
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
                    borrarArista(nodo, n);
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

            for(int i =0; i < this->getNumVertices(); i++){
                insertarAristas(i);
            }
            
        }

        grafo( const grafo& g){
            this->numVertices = g.getNumVertices();
            this->numAristas = g.getNumAristas();

            inicializar(this->getNumVertices());
            for(int i =0 ; i < this->getNumVertices(); i++){
                for(int j =0; j < this->getNumVertices(); j++){
                    this->matrizAdyacencia[i][j] = g.getArista(i,j).second;
                }
            }
        }

        grafo operator=( const grafo& g){
            
            this->borrar();
            
            this->inicializar(g.getNumVertices());

            this->numVertices = g.getNumVertices();
            this->numAristas = g.getNumAristas();
            
            //Actualizamos los valores
            for(int i =0 ; i < this->getNumVertices(); i++){
                for(int j =0; j < this->getNumVertices(); j++){
                    this->matrizAdyacencia[i][j] = g.getArista(i,j).second;
                    
                }
            }
            return *this;
        }

        int getNumVertices() const{
            return numVertices;
        }

        int getNumAristas() const{
            return numAristas;
        }

        pair<bool, float> getArista(int n1, int n2) const{
            pair< bool, float> ret(false, 0);

            if( n1 < 0 || n2 < 0 ){
                throw std::out_of_range("Algundo de los nodos es menor a 0");
            }

            if( n1 >= this->getNumVertices()){
               
                //throw std::out_of_range("El primer nodo no existe");
            }

            if( n2 >= this->getNumVertices()){
               
                throw std::out_of_range("El segundo nodo existe");
            }

            if( matrizAdyacencia[n1][n2] != 0){
                ret.first = true;
                ret.second = matrizAdyacencia[n1][n2];
            }
            return ret;
        }

        vector<arista> getTodosAristas(){
            vector< arista > conjuntoArista;
            int filasComprobadas = 1; 
            int aristasAdded =0;
            
            for( int i = 0; (i < this->getNumVertices() ) && (this->getNumAristas() != aristasAdded ) ; i++ ){
                for(int j = filasComprobadas; (j < this->getNumVertices() ) && ( this->getNumAristas() != aristasAdded ) ; j++){
                    
                    if( getArista(i,j).first == true ){
                        
                        arista insertar;

                        insertar.cantidad = getArista(i,j).second;
                        insertar.indice1 = i;
                        insertar.indice2 = j;

                        conjuntoArista.push_back( insertar );
                        aristasAdded++;
                    }
                }
                filasComprobadas++;
            }
            return conjuntoArista;
        }

        void insertarNodo(){
            
            //Copiamos la matriz
            float ** nuevaMatriz = new float * [ this->getNumVertices()+1];
            for(int i =0; i < this->getNumVertices()+1; i++){
                nuevaMatriz[i] = new float [ this->getNumVertices()+1];
            }

            for( int i =0 ; i < this->getNumVertices() -1; i++){
                for(int j =0; j < this->getNumVertices() - 1; j++){
                    nuevaMatriz[i][j] = this->getArista(i, j).second;
                }
            } 

            //Liberamos memoria
            borrar();

            //Aumentamos el número de vertices
            numVertices++;

            //Inicializamos a -1 los aristas entre los nodos
            for(int i = 0 ; i < this->getNumVertices(); i++){
                nuevaMatriz[i][ this->getNumVertices()-1] = -1;
            }
            for(int j = 0 ; j < this->getNumVertices() -1 ; j++){
                nuevaMatriz[ this->getNumVertices()-1][j] = -1;
            }

            //Insertamos los valores de los aristas
            this->insertarAristas( this->getNumVertices()-1);

            //Sustituimos por nuestra nueva matriz
            matrizAdyacencia = nuevaMatriz;
        }

        void printMatrizAdy(){

            for(int i =0; i < this->getNumVertices(); i++){
                cout<<"\t";
                for(int j =0; j < this->getNumVertices()-1; j++){
                    cout<< this->getArista(i,j).second<<"-";
                }
                cout<< this->getArista(i,getNumVertices()-1).second;
                
                cout<<endl;
            }
        }

        ~grafo(){
            borrar();
            numVertices = 0;
            numAristas =0;
        }   
};


struct solucion {
    unionFind Solucion;
    float sumatoria;
    bool esSolucion;
};
solucion Kruskal(grafo g){
    solucion ret;
    ret.esSolucion = false;

    if(g.getNumVertices() > 1 ){
        float precioTotal = 0; //Precio de asfaltar el conjunto de calles seleccionadas
        unionFind S;
        arista eleccion;
        int n1, n2;
        S.makeSet( g.getNumVertices());

        vector<arista> todosAristas = g.getTodosAristas();
        
        //Ordenamos los aristas
        quickSort(todosAristas, 0, todosAristas.size()-1);
        
        for(int i = 0; i < todosAristas.size() && S.getAristas() != g.getNumVertices()-1; i++ ){
            
            eleccion = todosAristas[i];
            
            n1 = eleccion.indice1;
            n2 = eleccion.indice2;
            
            if( S.findSet(n1) != S.findSet(n2) ){
                S.Union(n1, n2);
                precioTotal += eleccion.cantidad;
            }
            
        }
        if( S.getAristas() == S.getSize() -1 ) {
            ret.esSolucion = true;
            ret.sumatoria = precioTotal;
            ret.Solucion = S;
        }
    }
    return ret;
}

int main(){
    int opcion;
    grafo g;
    int vert;
    solucion resultado;
    cout<<"Comenzando ejecución...."<<endl;
    
    do{
        cout<<"¿Que desea hacer?"<<endl;
        
        cout<<"\t 1: Crear grafo"<<endl;
        cout<<"\t 2: Insertar vertice"<<endl;
        cout<<"\t 3: Insertar aristas"<<endl;
        cout<<"\t 4: Eliminar aristas"<<endl;
        cout<<"\t 5: Calcular el recorrido óptimo"<<endl;
        cout<<"\t 6: Imprimir la matriz de adyacencias"<<endl;
        cout<<"\t Otro numero: Terminar el programa"<<endl;
        cin>>opcion;

        switch(opcion){
            case 1:
            
                cout<<"¿Cuantos vertices tendrá el grafo?"<<endl;
                
                cin>> vert;

                while( vert < 0){
                    cout<<"Valor erróneo, numero de vertices no puede ser negativo, introduzca de nuevo:"<<endl; 
                    cin >>vert;
                }
                g = grafo(vert);
                        
                break;
            case 2:
                cout<<"Insertando nodo..."<<endl<<endl;
                
                g.insertarNodo();
                
                break;
            case 3:
                cout<<"A que vertice desea añadir aristas? [ 0, "<<g.getNumVertices()-1<<" ]"<<endl;
                cin>> vert;

                while( (vert < 0 || vert >= g.getNumVertices()) && (g.getNumVertices() > 0) ){
                    cout<<"Valor erróneo, introduzca de nuevo:"<<endl; 
                    cin >>vert;
                }

                g.insertarAristas(vert);
                break;
            case 4:
                cout<<"De que vertice desea eliminar aristas? [ 0, "<<g.getNumVertices()-1<<" ]"<<endl;
                cin>> vert;

                while( (vert < 0 || vert >= g.getNumVertices()) && (g.getNumVertices() > 0)){
                    cout<<"Valor erróneo, introduzca de nuevo:"<<endl; 
                    cin >>vert;
                }

                g.borrarAristas(vert);
                break;
            case 5:
                
                resultado = Kruskal(g);
                if( resultado.esSolucion ){
                    cout<< "Se ha encontrado una solución mínima, para la que el coste total minimo asciende a: "<<resultado.sumatoria<<" euros"<<endl;

                    resultado.Solucion.print();
                }else{
                    cout<<"No hay solución para unir todos los vértices del grafo"<<endl<<endl;
                }
                break;
            case 6:
                cout<<"La matriz de adyacencia: "<<endl<<endl;
                g.printMatrizAdy();
                cout<<endl<<endl;
            default: 
                break;
        }
    }while(opcion > 0 && opcion < 7);

    cout<<"Terminando ejecución..." <<endl<<endl;
    return 0;
}