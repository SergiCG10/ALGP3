#include <chrono>
#include <iostream>
#include <cstdlib>
#include <fstream>
#include <vector>

using namespace std;

vector<int> SolucionProblema2(const vector<vector<int>>& vProblema, const int& n);
void PrintVector(const vector<int>& v);
void PrintMatriz(const vector<vector<int>>& matriz);

int main(int argc, char* argv []){
  vector<vector<int>> vProblema;
  vector<int> mesa;
  int n, i, argumento, simetria=1;
  chrono::time_point<std::chrono::high_resolution_clock> t0, tf; // Para medir el tiempo de ejecución
  unsigned long int semilla;
  ofstream fsalida;
	
	if (argc <= 3) {
		cerr<<"\nError: El programa se debe ejecutar de la siguiente forma.\n\n";
		cerr<<argv[0]<<" NombreFicheroSalida Semilla tamCaso1 tamCaso2 ... tamCasoN\n\n";
		return 0;
	}
	
	// Abrimos fichero de salida
	fsalida.open(argv[1]);
	if (!fsalida.is_open()) {
		cerr<<"Error: No se pudo abrir fichero para escritura "<<argv[1]<<"\n\n";
		return 0;
	}
  // Generamos numeros aleatorios
  semilla = atoi(argv[2]); 
  srand(semilla);
	// Pasamos por cada tamaño de caso
	for (argumento= 3; argumento<argc; argumento++) {
		
		// Cogemos el tamanio del caso
		n= atoi(argv[argumento]);
		
		// Reservamos memoria para la matriz
    vProblema.resize(n);
    for(i = 0; i < n; i++)
      vProblema[i].resize(n);
		
    //Matriz simétrica, establecemos la diagonal principal
    for(i = 0; i < n; i++)
      vProblema[i][i]= 100; //A cada comensal le conviene estar consigo mismo
    
    //Establecemos la conveniencia para los comensales
    for(i = 0; i < n; i++, simetria++){
      for(int j = simetria; j < n; j++){
        vProblema[i][j] = rand()%101;
        vProblema[j][i] = vProblema[i][j];
      }
    }
		
		cerr << "Ejecutando Problema2 para tam. caso: " << n << endl;
        
		t0= std::chrono::high_resolution_clock::now(); // Cogemos el tiempo en que comienza la ejecuciÛn del algoritmo
    mesa=SolucionProblema2(vProblema, n);
		tf= std::chrono::high_resolution_clock::now(); // Cogemos el tiempo en que finaliza la ejecuciÛn del algoritmo

    cerr << endl;
		unsigned long tejecucion= std::chrono::duration_cast<std::chrono::microseconds>(tf - t0).count();
		cerr << "\tTiempo de ejec. (micros): " << tejecucion << " para tam. caso "<< n<<endl;
		// Guardamos tam. de caso y t_ejecucion a fichero de salida
		fsalida<<n<<" "<<tejecucion<<"\n";
		
		
		// Liberamos memoria del vector
    vProblema.clear();
    mesa.clear();
	}
	
	// Cerramos fichero de salida
	fsalida.close();
	
	return 0;
}


vector<int> SolucionProblema2(const vector<vector<int>>& vProblema, const int& n){
  vector<int> mesa(n); //O(n)
  vector<bool> estansentados(n, false); //O(n)
  int nasiento = 1, inv1=0, inv2, maxconv, invelegido=0; //O(1)

  while(nasiento < n){ //O(n-1)*O(n-1) => O(n²)
    estansentados[invelegido] = true; //O(1) Hemos sentado el 0
    inv1=invelegido; //O(1)
    maxconv = -1; //O(1)
    for(inv2 = 1; inv2 < n; inv2++){ //O(n-1)
      if(vProblema[inv1][inv2] > maxconv
          && !estansentados[inv2]){ //O(1)

        maxconv = vProblema[inv1][inv2]; //O(1)
        invelegido = inv2; //O(1)
      }
    }
    mesa[nasiento++]=invelegido; //O(1)
  }

  return mesa;
}

void PrintVector(const vector<int>& v){
  if(v.empty())
    return;
  for(int elem: v)
    cout << elem << " ";
  cout << endl;
}
void PrintMatriz(const vector<vector<int>>& matriz){
  if(matriz.empty())
    return;
  for(vector<int> fila: matriz)
    PrintVector(fila);
}

