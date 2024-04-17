#include <iostream>
#include <stdlib.h>
#include <vector>
using namespace std;


int semilla=12345;
void EncontrarParejas (vector<vector<int>> matriz, int n, vector<pair<int,int>> & parejas)
{
    vector<vector<int>> preferencias;
    preferencias.resize(n);
    
    for(int i=0;i<n;i++)    //creamos la que será la matriz de productos (i,j)*(j,i)
        preferencias[i].resize(n);
    for(int i=0;i<n;i++){
        for(int j=0;j<n;j++)
            preferencias[i][j]=matriz[i][j]*matriz[j][i];
    }
    cout<<"Matriz de resultados"<<endl;
    for(int i=0;i<n;i++){
        for(int j=0;j<n;j++)
            cout<<preferencias[i][j]<<" ";
        cout<<endl;
    }

    vector<bool> emparejados(n, false);
    int cont_parejas=0;
    int maximo=-1;
    int candidato=-1;
    int satisfaccionTotal=0;
    for(int i=0;i<n && cont_parejas<n/2;i++){
        if(!emparejados[i]){
            for(int j=0;j<n;j++){
                if(preferencias[i][j]>maximo && i!=j){ //omitimos los valores que conforman la diagonal ya que correspondería a un mismo alumno
                    if(!emparejados[j]){    //suponiendo que el mejor candidato ya ha sido seleccionado, escogeríamos el siguiente con la preferencia más alta
                        maximo=preferencias[i][j];//buscar la mejor satisfacción  en la fila
                        candidato=j;
                    }
                }
            }
            maximo=-1;
            if(!emparejados[candidato])
            {
                pair<int,int> aux(i,candidato);
                parejas.push_back(aux);
                emparejados[i]=true;        //hacemos que los candidatos ya no sean seleccionables para posteriores selecciones
                emparejados[candidato]=true;
                cont_parejas++; //aumentamos el contador de parejas, cuando llegue a n/2 ya no quedarán candidatos seleccionables
                satisfaccionTotal+=preferencias[i][candidato];
            }
        }
    }
    cout<<"Numero de parejas: "<<parejas.size()<<endl;
    for(int i=0;i<n/2;i++)
       cout<<"Pareja "<<i<<": "<<parejas[i].first<<" con "<<parejas[i].second<<endl;
    
    cout<<"Satisfaccion total del grupo="<<satisfaccionTotal<<endl;

}

const int MAX_PREF=10;
int main(int argc, char * argv[])
{
    //filtro de argumentos
    if(argc!=2){
        cout<<"Debe de haber dos argumentos: % prompt <num_estudiantes>"<<endl;
        return 0;
    }
    int num_estudiantes=atoi(argv[1]);
    if(num_estudiantes%2!=0 || num_estudiantes<0)
    {
        cout<<"argv[1] debe ser un numero par"<<endl;
        return 0;
    }
    //crear la matriz nxn
    vector<vector<int>> matriz;
    matriz.resize(num_estudiantes);
    for(int i=0;i<num_estudiantes;i++)
        matriz[i].resize(num_estudiantes);

    srand(semilla);                                                                                            
    for(int i=0;i<num_estudiantes;i++){//inicializar la matriz con valores random
        for(int j=0;j<num_estudiantes;j++){
            if(i==j)
                matriz[i][j]=MAX_PREF;    //asumimos que la preferencia de estar cada uno consigo mismo es máxima
            else{
                matriz[i][j]=rand()%10 +1;  //numeros entre 1 y 10
            }     
        }
    }                                                                                                           
    
    vector<pair<int,int>> parejas;
    EncontrarParejas(matriz,num_estudiantes,parejas);

    
    return 0;
}