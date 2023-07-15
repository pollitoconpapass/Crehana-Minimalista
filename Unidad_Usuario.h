#pragma once
#include"Ciudad.h"
#include"Listas_Curso.h"
using namespace std;

class Usuario
{
public:
	Listas_Cursos<Curso*> Lista_CursoxUsuario;
	Ciudad* ciudad;
	int codigo;
	string Nombre;
	string Apellido;
	char sexo;
	char plan;

	Usuario(Ciudad* c, int _codigo, string _nombre, string _apellido, char _sexo, char _plan) {
		ciudad = c;
		codigo = _codigo;
		Nombre = _nombre;
		Apellido = _apellido;
		sexo = _sexo;
		plan = _plan;
	}
	~Usuario() {}
	void Agregar_Curso(Curso* curso) {
		Lista_CursoxUsuario.insertar_Curso(curso);
	}
	void Eliminar_Curso_del_Usuario() {
		Lista_CursoxUsuario.Eliminar_Curso();
	}
	void mostrar() {
		cout << codigo << "\t| NOMBRE: " << Nombre << "\n\t|APELLIDO: " << Apellido << "\n\t|SEXO: " << sexo << "\n\t|PLAN: " << plan << "\n";
		ciudad->mostrar(); cout << "--> CURSOS AL QUE PERTENECE <-- "; if (Lista_CursoxUsuario.Lleno()) { Lista_CursoxUsuario.mostrar(); }
		else
		{
			cout << "\n\t--- NO PERTENECE A NINGUN CURSO ---\n";
		}
		cout << "========================================================\n";
	}
	void Mostrar_mis_Cursos() { cout << "================MIS CURSOS===============\n "; Lista_CursoxUsuario.mostrar(); }
	void Cambiar_Plan(char P) {
		plan = P;
	}

};
