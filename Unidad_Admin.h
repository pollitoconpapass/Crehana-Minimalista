#pragma once
#include<iostream>
class Admin {
public:
	std::string Nombre;
	int code;
	Admin(std::string _Nombre, int _code) {
		Nombre = _Nombre;
		code = _code;
	}
	~Admin() {}
	void Mostrar() {
		std::cout << Nombre << "\t" << "|" << code << std::endl;
	}
};
