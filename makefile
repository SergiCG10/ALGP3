#!usr/bin

all:
	#Compilando Problema 1...
	#@g++ -o problema1.bin problema1.cpp -std=c++11
	#Compilando Problema 2...
	#@g++ -o problema2.bin problema2.cpp -std=c++11
	#Compilando Problema 3...
	#@g++ -o problema3.bin problema3.cpp -std=c++11
	#Compilando Problema 4...
	#@g++ -o problema4.bin problema4.cpp -std=c++11
	#Compilando Problema 5...
	@g++ -o problema5.bin problema5.cpp -std=c++11

#Elimina los ejecutables
clean:
	#@rm problema1.bin
	#@rm problema2.bin
	#@rm problema3.bin
	#@rm problema4.bin
	#@rm problema5.bin
	
.PHONY: clean
