#pragma once
#include<iostream>
#include<string>
class Ciudad {
private:
	std::string ciudad;
	int distancia;
public:
	Ciudad(std::string c, int d) {
		ciudad = c;
		distancia = d;
	}
	void mostrar() {
		std::cout << "\t|Ciudad : " << ciudad << "\n\t|Distancia en horas: " << distancia << "\n";
	}
};
