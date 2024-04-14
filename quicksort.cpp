using namespace std;

int ordenarParte(int *v, int inicio, int fin ){
    int pivote = v[inicio];
	int ext_izquierdo = inicio + 1 ;
	int ext_derecho = fin;

	while( ext_izquierdo != ext_derecho){
		if( v[ext_izquierdo] <= pivote){
			ext_izquierdo++;
		}else{
			while( (ext_derecho != ext_izquierdo) && (v[ext_derecho] > pivote) ){
				ext_derecho--;
			}
			int aux = v[ext_derecho];
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
void quickSort( int* v, int inicio, int fin){

	if(inicio < fin){
		int q = ordenarParte(v, inicio, fin);
		quickSort(v, inicio, q - 1 );
		quickSort(v, q + 1, fin);
	}
}
