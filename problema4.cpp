/*
EJEMPLO DE INPUT
5 9
1 2 7
1 4 2
2 3 1
2 4 2
3 5 4
4 2 3
4 3 8
4 5 5
5 3 5

1

Los dos primeros números son el número de vértices y de aristas
La primera y segunda columna son los sensores que se unen, la tercera columna es la distancia entre ellos
El número final es el sensor del cual quieres conocer los datos, y luego pedirá cual de todos los vértices es el servidor final.
EJEMPLO DE INPUT DE LAS DIAPOSITIVAS:
6 11
1 2 3
1 3 5
1 4 9
2 4 4
2 3 3
2 5 7
3 4 2
3 5 6
3 6 8
4 6 2
5 6 5

1

6

*/
#include <stdio.h>
#include <vector>
#include <queue>
#include <iostream>
using namespace std;
#define MAX 10005 //maximo numero de vértices
#define Node pair< int , int > //definimos el nodo como un par( first , second ) donde first es el vertice adyacente y second el peso de la arista
#define INF 1<<30 //definimos un valor grande que represente la distancia infinita inicial, basta conque sea superior al maximo valor del peso en alguna de las aristas

//La cola de prioridad de C++ por default es un max-Heap (elemento de mayor valor en el tope)
//por ello es necesario realizar nuestro comparador para que sea un min-Heap
struct cmp {
    bool operator() ( const Node &a , const Node &b ) {
        return a.second > b.second;
    }
};
vector< Node > ady[ MAX ]; //lista de adyacencia
int distancia[ MAX ];      //distancia[ u ] distancia de vértice inicial a vértice con ID = u
bool visitado[ MAX ];      //para vértices visitados
priority_queue< Node , vector<Node> , cmp > Q; //priority queue propia del c++, usamos el comparador definido para que el de menor valor este en el tope
int V;                     //numero de vertices
int previo[ MAX ];         //para la impresion de caminos

//función de inicialización
void init(){
    for( int i = 0 ; i <= V ; ++i ){
        distancia[ i ] = INF;  //inicializamos todas las distancias con valor infinito
        visitado[ i ] = false; //inicializamos todos los vértices como no visitados
        previo[ i ] = -1;      //inicializamos el previo del vertice i con -1
    }
}

//Paso de relajacion (actualizar las distancias mínimas conocidas hacia los vértices adyacentes si se encuentra un camino más corto a través del vértice actual)
void relajacion( int actual , int adyacente , int peso ){
    //Si la distancia del origen al vertice actual + peso de su arista es menor a la distancia del origen al vertice adyacente
    if( distancia[ actual ] + peso < distancia[ adyacente ] ){
        distancia[ adyacente ] = distancia[ actual ] + peso;  //relajamos el vertice actualizando la distancia
        previo[ adyacente ] = actual;                         //a su vez actualizamos el vertice previo
        Q.push( Node( adyacente , distancia[ adyacente ] ) ); //agregamos adyacente a la cola de prioridad
    }
}

//Impresion del camino mas corto desde el vertice inicial y final ingresados
void print( int destino ){
    if( previo[ destino ] != -1 )    //si aun poseo un vertice previo
        print( previo[ destino ] );  //recursivamente sigo explorando
    std::cout << " " << destino<< " ";        //terminada la recursion imprimo los vertices recorridos
}

void dijkstra( int inicial, int nVertices ){
    init(); //inicializamos nuestros arrays
    Q.push( Node( inicial , 0 ) ); //Insertamos el vértice inicial en la Cola de Prioridad
    distancia[ inicial ] = 0;      //Inicializamos la distancia del inicial como 0
    int actual , adyacente , peso;
    while( !Q.empty() ){                   //Mientras cola no este vacia
        actual = Q.top().first;            //Obtengo de la cola el nodo con menor peso, en un comienzo será el inicial
        Q.pop();                           //Sacamos el elemento de la cola
        if( visitado[ actual ] ) continue; //Si el vértice actual ya fue visitado entonces sigo sacando elementos de la cola
        visitado[ actual ] = true;         //Marco como visitado el vértice actual

        for( int i = 0 ; i < ady[ actual ].size() ; ++i ){ //reviso sus adyacentes del vertice actual
            adyacente = ady[ actual ][ i ].first;   //id del vertice adyacente
            peso = ady[ actual ][ i ].second;        //peso de la arista que une actual con adyacente ( actual , adyacente )
            if( !visitado[ adyacente ] ){        //si el vertice adyacente no fue visitado
                relajacion( actual , adyacente , peso ); //realizamos el paso de relajacion
            }
        }
    }


    std::cout << "Distancias mas cortas iniciando en vertice" << inicial << "\n" ;
    for( int i = 1 ; i <= V ; ++i ){
        std::cout << "Vertice " << i << ", distancia mas corta = " << distancia[ i ] << "\n";
    }

    puts("\n**************Impresion de camino mas corto**************");
    std:: cout << "Ingrese vertice destino: ";
    int destino;
    std::cin >> destino;
    while( destino < 0 || destino > V ){
        std::cout<<"Numero de vertice no valido, vuelva a introducir uno del intervalo: [0,"<<nVertices-1<<"]\t";
        std::cin>> destino;
    }
    print(destino);
    std::cout << "\n";
}


int main(){
    int E , origen, destino , peso , inicial;
    
    std::cout<<"Introduzca el numero de vertices"<<std::endl;
    std::cin >> V;
    while( V < 1){
        std::cout<<"Numero de vertices incorrecto, introduzca un numero positivo mayor a 1\t";
        std::cin>> V;
    }

    std::cout<<"Introduzca el numero de aristas"<<std::endl;
    std::cin >> E;
    while( E < 0){
        std::cout<<"Numero de aristas incorrecto, introduzca un numero positivo\t";
        std::cin>> E;
    }

    while( E-- ){
        cout<<"Introduzca el vertice de origen y el vertice de destino y el peso del arista"<<std::endl;
        
        //Garantizamos datos válidos
        std::cin >> origen;
        while( origen < 0 || origen > V ){
            std::cout<<"Numero de vertice no valido para origen, vuelva a introducir uno del intervalo: [0,"<<V-1<<"]\t";
            std::cin>> origen;
        }

        std::cin >> destino;
        //Garantizamos datos válidos
        while( destino < 0 || destino > V ){
            std::cout<<"Numero de vertice no valido para destino, vuelva a introducir uno del intervalo: [0,"<<V-1<<"]\t";
            std::cin>> destino;
        }

        //Garantizamos datos válidos
        std::cin >> peso;
        while( peso <= 0 ){
            std::cout<<"Numero de peso no valido, vuelva a introducir uno positivo\t";
            std::cin>> peso;
        }
        ady[ origen ].push_back( Node( destino , peso ) ); //consideremos grafo dirigido
        ady[ destino ].push_back( Node( origen , peso ) ); //grafo no dirigido
    }
    std::cout << "Introduce el vertice inicial: ";

    std::cin >> inicial;
    //Garantizamos datos válidos
    while( inicial < 0 || inicial > V ){
        std::cout<<"Numero de vertice no valido, vuelva a introducir uno del intervalo: [0,"<<V-1<<"]\t";
        std::cin>> inicial;
    }

    dijkstra( inicial, V );
    return 0;
} 