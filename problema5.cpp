#include <iostream>
#include <algorithm>
#include "quicksort.cpp"
#include <vector>

using namespace std;

/**
 * @brief Estructura arista auxiliar para ordenar en función de su precio
 */
struct arista{
    float cantidad;
    int indice1;
    int indice2;
};

/**
 * @brief operador <. Operador menor que para el struct arista
 *
 * @param A1 arista 1 para comprobar
 * @param A2 arista 2 para comprobar
 * @return true si A1 menor que A2
 */
bool operator<( const arista& A1, const arista&A2 ){
    return A1.cantidad < A2.cantidad;
}

/**
 * @brief operador <. Operador menor que para el struct arista
 *
 * @param A1 arista 1 para comprobar
 * @param A2 arista 2 para comprobar
 * @return true si A1 mayor que A2
 */
bool operator>( const arista& A1, const arista&A2 ){
    return A1.cantidad > A2.cantidad;
}

/**
 * @brief operador <. Operador menor que para el struct arista
 *
 * @param A1 arista 1 para comprobar
 * @param A2 arista 2 para comprobar
 * @return true si A1 igual que A2
 */
bool operator==(const arista& A1, const arista&A2 ){
    return A1.cantidad == A2.cantidad;
}

/**
 * @brief operador <. Operador menor que para el struct arista
 *
 * @param A1 arista 1 para comprobar
 * @param A2 arista 2 para comprobar
 * @return true si A1 menor o igual que A2
 */
bool operator<=(const arista& A1, const arista&A2 ){
    return A1 == A2 || A1 < A2;
}

/**
 * @brief operador <. Operador menor que para el struct arista
 *
 * @param A1 arista 1 para comprobar
 * @param A2 arista 2 para comprobar
 * @return true si A1 mayor o igual que A2
 */
bool operator>=(const arista& A1, const arista&A2 ){
    return A1 == A2 || A1 > A2;
}

/**
 * @brief Clase unionFind para utilizar en la funcion Kruskal
 *
 * @param padre. Vector para almacenar los padres de cada vertice
 * @param size Numero de vertices
 * @param aristas Numero de aristas
 */
class unionFind{
    private:
        int* padre; 
        int size;
        int aristas;
    public:

    /**
     * @brief Constructor por defecto de la clase
     */
    unionFind(){
        padre = 0;
        size = 0;
        aristas =0;
    }
    
    /**
     * @brief Funcion getSize. Devuelve el numero de vertices
     *
     * @return numero de vertices
     */
    int getSize() const{
        return size;
    }

    /**
     * @brief Funcion getAristas. Devuelve el numero de aristas 
     *
     * @return numero de aristas
     */
    int getAristas() const{
        return aristas;
    }

    /**
     * @brief Función getPadre. Devuelve el valor de la posición n. Metodo set
     *
     * @param n. Indice del vertice 
     *
     * @return valor de padre[n]
     */
    int & getPadre(int n){
        if(n < this->getSize() && n >= 0){
            return padre[n];
        }else{
            throw out_of_range("Indice fuera de rango");
        }
    }

    /**
     * @brief Función getPadre. Devuelve el valor de la posición n. Metodo get
     *
     * @param n. Indice del vertice
     *
     * @return valor de padre[n]
     */
    const int & getPadre(int n) const{
        if(n < this->getSize() && n >= 0){
            return padre[n];
        }else{
            throw out_of_range("Indice fuera de rango");
        }
    }

    /**
     * @brief Función makeSet. Construye un vector para n elementos
     *
     * @param n. Numero de vertices del grafo 
     */
    void makeSet(int n){
        size = n;
        padre = new int [n];

        for( int i = 0; i< this->getSize(); i++){
            padre[i] = i;
        }
    }

    /**
     * @brief Función findSet. Devuelve el padre de n.
     *
     * @param n. Indice del vertice 
     *
     * @return padre de n
     */
    int findSet(int n ){
        int ret =  n;
        if( n != padre[n]){
            ret = findSet(padre[n]);
        }
        return ret;
    }

    /**
     * @brief Funcion Union. Une el vertice x con el y, convirtiendose en padre aquel que sea menor
     *
     * @param x Indice del primer vertice
     * @param y Indice del segundo vertice
     */
    void Union( int x, int y){
        if( x > y){
            padre[ findSet(x) ] = y;
        }else{
            padre[ findSet(y) ] = x;
        }
        aristas++;
    }

    /**
     * @brief operador de asignacion de la clase UnionFind. Copia los valores de otro objeto del mismo tipo
     *
     * @param uf Objeto UnionFind del que copiar los datos
     *
     * @return referencia a este objeto para poder encadenar
     */
    unionFind operator = (const unionFind& uf){
        this->size = uf.size;

        delete [] this->padre;
        this->padre = new int [this->size];
                 
        for(int i = 0; i < this->size; i++){
            this->padre[i] = uf.padre[i];
        }
        return *this;
    }

    /**
     * @brief constructor de copia de la clase UnionFind. Crea un objeto con los valores de otro objeto del mismo tipo
     *
     * @param uf Objeto UnionFind del que copiar los datos
     */
    unionFind(const unionFind& uf){
        this->size = uf.size;
        
        this->padre = new int [this->size];

        for(int i = 0; i < this->size; i++){
            this->padre[i] = uf.padre[i];
        }
    }
    
    /**
     * @brief destructor  de la clase UnionFind. Libera memoria reservada para el objeto
     */
    ~unionFind(){
        delete [] padre;
        size = 0;
    }   
};

/**
 * @brief clase grafo
 *
 * @param numVertices. Numero de vertices del grafo
 * @param numAristas. Numero de aristas del grafo
 * @param matrizAdyacencia. Matriz que almacena los valores de los aristas entre los vertices
 */
class grafo{
    private:

        int numVertices;
        int numAristas;

        float** matrizAdyacencia;
        
        /**
         * @brief Funcion auxiliar para inicializar la matriz
         *
         * @param v Numero de vertices del grafo
         */
        void inicializar(int v){
            this->matrizAdyacencia = new float* [v];
            for(int i =0; i < v; i++){
                this->matrizAdyacencia[i] = new float[v];
                for(int j =0; j < v; j++){
                    this->matrizAdyacencia[i][j] = 0;
                }
            }
        }

        /**
         * @brief Funcion auxiliar para liberar el espacio de la matriz
         */
        void borrar(){
            for(int i =0; i < getNumVertices(); i++ ){
                delete [] this->matrizAdyacencia[i];
            }
            delete [] this->matrizAdyacencia;
        }

        /**
         * @brief Funcion auxiliar borrar el arista del grafo entre n1 y n2 (establecerlo con distancia infinita "0" )
         *
         * @param n1 Vertice 1
         * @param n2 vertice 2
         */
        void borrarArista( int n1, int n2){
            if( getArista(n1, n2).first == true){
                matrizAdyacencia[n1][n2] =0;
                matrizAdyacencia[n2][n1] =0;
                numAristas--;
            }
        }

    public:

        /**
         * @brief Funcion auxiliar para determinar el valor de el arista entre n1 y n2
         *
         * @param n1 Vertice 1
         * @param n2 Vertice 2
         * @param valor Valor nuevo para el arista
         *
         * @return true si ha podido cambiar el arista, false si no
         */
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

        /**
         * @brief Funcion auxiliar para insertar k aristas a nodo con el resto de nodos 
         *
         * @param nodo Nodo al que cambiar los aristas
         */
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

        /**
         * @brief Funcion auxiliar para borrar k aristas de nodo con el resto de nodos 
         *
         * @param nodo Nodo al que cambiar los aristas
         */
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

        /**
         * @brief Constructor por defecto de la clase grafo
         */
        grafo(){
            numVertices = 0;
            numAristas = 0;
        }
        
        /**
         * @brief Constructor por parámetros de la clase grafo
         *
         * @param nVertices Numero de vertices del grafo
         */
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

        /**
         * @brief Constructor de copia de la clase grafo. Construye un objeto a partir de los datos del otro
         *
         * @param g Grafo del que sacar los datos
         */
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

        /**
         * @brief Operador de asignación de la clase grafo. Copia en este objeto los datos del otro
         *
         * @param g Grafo del que sacar los datos
         */
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
        
        /**
         * @brief Funcion getNumVertices
         * 
         * @return numero de vertices del grafo
         */
        int getNumVertices() const{
            return numVertices;
        }

        /**
         * @brief Funcion getNumAristas
         * 
         * @return numero de aristas del grafo
         */
        int getNumAristas() const{
            return numAristas;
        }

        /**
         * @brief Funcion getArista. Devuelve si existe el valor del vertice entre n1 y n2
         *
         * @param n1 Vertice 1
         * @param n2 Vertice 2
         *
         * @return pair formado por un bool que determina si existe el arista y valor del arista
         */
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

        /**
         * @brief getTodosAristas
         *
         * @return Devuelve un vector con todos los aristas del grafo (No los da ordenados)
         */
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

        /**
         * @brief Funcion insertarNodo. Inserta un nuevo nodo e inicializa a 0 los aristas entre el resto de nodos
         */
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
                nuevaMatriz[i][ this->getNumVertices()-1] = 0;
            }
            for(int j = 0 ; j < this->getNumVertices() -1 ; j++){
                nuevaMatriz[ this->getNumVertices()-1][j] = 0;
            }

            //Sustituimos por nuestra nueva matriz
            matrizAdyacencia = nuevaMatriz;
        }

        /**
         * @brief Funcion auxiliar para imprimir la matriz de adyacencia de los vertices. Valor 0 para aquellos donde no tengan vertice
         */
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

        /**
         * @brief Destructor de la clase grafo. Libera memoria
         */
        ~grafo(){
            borrar();
            numVertices = 0;
            numAristas =0;
        }   
};

/**
 * @brief estruct solucion. Estructura auxiliar para devolver los parámetros
 * 
 * @param Solucion. Objeto union find que contiene el grafo resultante
 * @param sumatoria. Suma total de los aristas
 * @param esSolucion Variable booleana que determina si es solucion o no
 * @param aristas. vector que contiene los aristas seleccionados
 */
struct solucion {
    unionFind Solucion;
    float sumatoria;
    bool esSolucion;
    vector<arista> aristas;
};

/**
 * @brief Funcion Kruskal. Para un grafo g, calcula si hay un recorrido minimo para recorrerlo.
 *
 * @param g Grafo del que calcular el arbol minimal
 * @return Devuelve un struct con un grafo unionFind, la suma total del recorrido, si es solucion y un vector con los aristas escogidos para la solucion
 */
solucion Kruskal(grafo g){
    solucion ret;
    ret.esSolucion = false;

    if(g.getNumVertices() > 1 ){
        float precioTotal = 0; //Precio de asfaltar el conjunto de calles seleccionadas
        unionFind S; //Objeto que representa al grafo resultante
        vector<arista> aristasSeleccionados; //Vector con los aristas escogidos finalmente
        arista eleccion; //Arista seleccionada
        int n1, n2; //Nodos aux
        S.makeSet( g.getNumVertices()); //Iniciamos los valores del grafo

        //Creamos vector con todos los aristas del grafo
        vector<arista> todosAristas = g.getTodosAristas();
        
        //Ordenamos los aristas
        quickSort(todosAristas, 0, todosAristas.size()-1);
        
        //Recorremos el vector de los aristas ya ordenados
        for(int i = 0; i < todosAristas.size() && S.getAristas() != g.getNumVertices()-1; i++ ){
            
            eleccion = todosAristas[i]; //Arista seleccionada
            
            n1 = eleccion.indice1; //Vertice 1 del arista
            n2 = eleccion.indice2; //Vertice 2 del arista
            
            //Nos aseguramos de que no se creen ciclos
            if( S.findSet(n1) != S.findSet(n2) ){ 
                S.Union(n1, n2); //Unimos los dos vertices
                precioTotal += eleccion.cantidad; //Sumamos la cantidad a la total
                aristasSeleccionados.push_back(eleccion); //Guardamos el arista
            }
            
        }
        //Para n vertices, necesitamos n-1 aristas para unirlos sin crear ciclos
        if( S.getAristas() == S.getSize() -1 ) { 
            ret.esSolucion = true;
            ret.sumatoria = precioTotal;
            ret.Solucion = S;
            ret.aristas = aristasSeleccionados;
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
                    cout<<endl<< "Se ha encontrado una solución mínima, para la que el coste total minimo asciende a: "<<resultado.sumatoria<<" euros"<<endl;

                    
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
