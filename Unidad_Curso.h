#pragma once
#include<iostream>
using namespace std;
class Curso {
public:
	string descripcion;
	string curso;
	string profesor;
	string area;
	string modalidad;
	int cod;
	int cantidad;
	int precio;
	int duracion;

	Curso(string _descripcion, string _curso, string _profesor, string _area, string _modalidad, int _codigo, int _cant, int _precio, int _duracion) {
		descripcion = _descripcion;
		curso = _curso;
		profesor = _profesor;
		area = _area;
		cod = _codigo;
		cantidad = _cant;
		precio = _precio;
		duracion = _duracion;
	}
	~Curso() {}
	void disminuir_cant(bool entrar) {
		if (entrar) { cantidad--; }
		else { cantidad++; }
	}

	void mostrar() {
		cout << cod << "\t|CURSO: " << curso << "\n" << "\t|ACERCA DE: " << descripcion << "\n" << "\t|AREA: " << area << "\n" << "\t|PROF: " << profesor << "\n" << "\t|N ALUM: " << cantidad << "\n" << "\t|$: " << precio << "\n" << "\t|CLASES: " << duracion << "\n";
		cout << "============================================" << endl;
	}
	int get_code() {
		return cod;
	}
};
