#pragma once
#include<string>
#include"Unidad_Usuario.h"
#include"Nodo.h"
#include"Quicksort.hpp"
template<class T>
class Listas_Usuarios {
private:
	Nodo<T>* inicio;
public:
	Listas_Usuarios() { inicio = NULL; }
	~Listas_Usuarios() {
		Nodo<T>* temp;
		while (inicio != NULL)
		{
			temp = inicio;
			inicio = inicio->siguiente;
			delete temp;
			temp = NULL;
		}
	}
	void insertar_usuario(T v) {
		Nodo<T>* nodo = new Nodo<T>(v);
		if (inicio == NULL)inicio = nodo;
		else
		{
			nodo->siguiente = inicio;
		}
		inicio = nodo;
		nodo = NULL;
	}
	void eliminar(int cod, string nombre) {
		if (inicio == NULL) {
			// La lista está vacía, no hay nada que eliminar
			return;
		}

		Nodo<T>* nodoActual = inicio;
		Nodo<T>* nodoAnterior = NULL;

		while (nodoActual != NULL) {
			Usuario* usu = (Usuario*)(nodoActual->valor);
			if (usu->codigo == cod && usu->Nombre == nombre) {
				// Se encontró el curso a eliminar
				if (nodoAnterior == NULL) {
					// El nodo a eliminar es el primero de la lista
					inicio = nodoActual->siguiente;
				}
				else {
					// El nodo a eliminar está en el medio o al final de la lista
					nodoAnterior->siguiente = nodoActual->siguiente;
				}

				delete nodoActual;
				nodoActual = NULL;

				cout << "El usuario ha sido eliminado correctamente." << endl;
				return;
			}

			// Avanzar al siguiente nodo
			nodoAnterior = nodoActual;
			nodoActual = nodoActual->siguiente;
		}
	}
	void Mostrar() {
		Nodo<T>* nodo = inicio;
		do
		{
			Usuario* usu = (Usuario*)(nodo->valor);
			usu->mostrar();
			nodo = nodo->siguiente;

		} while (nodo != NULL);
		system("pause");
		system("cls");
	}
	int size() {
		Nodo<T>* nodo = inicio;
		int n = 0;
		do
		{
			n++;
			nodo = nodo->siguiente;

		} while (nodo != NULL);
		return n;
	}


	bool HayUsuario(string u, int code) {
		Nodo<T>* nodo = inicio;
		bool hay_usuario = false;
		while (nodo != NULL)
		{
			Usuario* usu = (Usuario*)(nodo->valor);
			if (usu->Nombre == u && usu->codigo == code) { hay_usuario = true; break; }
			nodo = nodo->siguiente;
		}
		return hay_usuario;
	}
	void Agregar_Curso_Al_Usuario(string u, int code, Curso* c) {
		Nodo<T>* nodo = inicio;
		while (nodo != NULL)
		{
			Usuario* usu = (Usuario*)(nodo->valor);
			if (usu->Nombre == u && usu->codigo == code) { usu->Agregar_Curso(c); }
			nodo = nodo->siguiente;
		}
	}
	void Mostrar_Mis_Cursos(string u, int code) {
		Nodo<T>* nodo = inicio;
		while (nodo != NULL)
		{
			Usuario* usu = (Usuario*)(nodo->valor);
			if (usu->Nombre == u && usu->codigo == code) {
				if (usu->Lista_CursoxUsuario.Lleno()) { usu->Mostrar_mis_Cursos(); }
				else
				{
					cout << "\nNo se encontraron cursos(Todavia no se inscrito a ninguno)\n";
				} break;
			}
			nodo = nodo->siguiente;
		}
	}
	void Cambiar_plan(string u, int cod) {
		Nodo<T>* nodo = inicio;
		while (nodo != NULL)
		{
			Usuario* usu = (Usuario*)(nodo->valor);
			if (usu->Nombre == u && usu->codigo == cod) {
				char P; cout << "-------Planes-----";
				cout << "\nPremiun Personal(P) - 37$ al mes "; cout << "\nPremiun Empresa(E) - 125$ al mes"; cout << "\nA que plan desea suscribirse: "; cin >> P;
				usu->Cambiar_Plan(P); break;
			}
			nodo = nodo->siguiente;
		}
	}
	void MostrarUsuarioxCodigo(int cod) {
		Nodo<T>* nodo = inicio;

		while (nodo != NULL)
		{
			Usuario* usu = (Usuario*)(nodo->valor);
			if (usu->codigo == cod) { usu->mostrar(); }
			nodo = nodo->siguiente;
		}
	}

	//QUICKSORT
	void Quicksort_Codigo() {
		Nodo<T>* nodo = inicio;
		int N = size();
		int* Arreglo_codigo = new int[N];
		int i = 0;
		while (nodo != NULL)
		{
			Usuario* usu = (Usuario*)(nodo->valor);
			Arreglo_codigo[i] = usu->codigo;
			nodo = nodo->siguiente;
			i++;
		}
		quicksort(Arreglo_codigo, 0, i - 1);
		cout << "Arreglo ordenado por quicksort" << endl;
		for (int j = 0; j < N; j++) {
			nodo = inicio;
			Usuario* usu = NULL; // Inicializar a NULL
			while (nodo != NULL) {
				usu = (Usuario*)(nodo->valor);
				if (usu->codigo == Arreglo_codigo[j]) {
					usu->mostrar();
					break; // Salir del bucle while una vez que se encuentra el curso
				}
				nodo = nodo->siguiente;
			}
		}
		delete[] Arreglo_codigo;
	}
};
