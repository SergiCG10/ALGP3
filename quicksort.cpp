#include <vector>
using namespace std;

template <typename T>
T ordenarParte(vector<T>v, int inicio, int fin ){
    T pivote = v[inicio];
	T ext_izquierdo = inicio + 1 ;
	T ext_derecho = fin;

	while( ext_izquierdo != ext_derecho){
		if( v[ext_izquierdo] <= pivote){
			ext_izquierdo++;
		}else{
			while( (ext_derecho != ext_izquierdo) && (v[ext_derecho] > pivote) ){
				ext_derecho--;
			}
			T aux = v[ext_derecho];
			v[ext_derecho] = v[ext_izquierdo];
			v[ext_izquierdo] = aux;
		}
	}

	if( v[ext_izquierdo] > pivote ){
		ext_izquierdo--;
	}

	v[inicio] = v[ext_izquierdo];
	v[ext_izquierdo] = pivote;

	return (ext_izquierdo);

}

template <typename T>
void quickSort( vector<T> v, int inicio, int fin){

	if(inicio < fin){
		T q = ordenarParte(v, inicio, fin);
		quickSort(v, inicio, q - 1 );
		quickSort(v, q + 1, fin);
	}
}
