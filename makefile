#!usr/bin

all:
	#Compilando Problema 1...
	@g++ -o problema1.bin problema1.cpp -std=c++17 
	
	#Ejecute de la siguiente manera (ejemplo de solución óptima):    ./problema1.bin 4 8
	#Ejecute de la siguiente manera (ejemplo de solución no óptima): ./problema1.bin 4651 6

	#Compilando Problema 2...
	@g++ -o problema2.bin problema2.cpp -std=c++17 
	
	#Ejecute de la siguiente manera: ./problema2.bin salida.txt 12345 10 100  

	#Compilando Problema 3...
	@g++ -o problema3.bin problema3.cpp -std=c++17 

	#Ejecute de la siguiente manea: ./problema3
	#Introduzca los siguientes parámetros: 
	#5 2 4 7 9 12 15 4

	#Compilando Problema 4...
	@g++ -o problema4.bin problema4.cpp -std=c++17 
	


	#Compilando Problema 5...
	@g++ -o problema5.bin problema5.cpp -std=c++17 

	#Ejecute de la siguiente manea: ./problema5
	#Introduzca los siguientes parámetros (ejemplo del pdf del enunciado de la práctica): 
	#1 5 1 1100000 2 130000 3 450004 4 748456 -1 2 1300000 3 555125 4 1700000 -1 4 554521 -1 4 143552 -1 -1 5

#Elimina los ejecutables
clean:
	@rm problema1.bin
	@rm problema2.bin
	@rm problema3.bin
	@rm problema4.bin
	@rm problema5.bin
	
.PHONY: clean
