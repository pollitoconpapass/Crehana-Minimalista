#pragma once
#include"Unidad_Admin.h"
#include"Nodo.h"
using namespace std;
template<class T>
class Listas_Admin
{
private:
	Nodo<T>* inicio;
public:
	Listas_Admin() {
		inicio = NULL;
	}
	~Listas_Admin() {
		Nodo<T>* temp;
		while (inicio != NULL)
		{
			temp = inicio;
			inicio = inicio->siguiente;
			delete temp;
			temp = NULL;
		}
	}
	void insertar_Admin(T v) {
		Nodo<T>* nodo = new Nodo<T>(v);
		if (inicio == NULL)inicio = nodo;
		else
		{
			nodo->siguiente = inicio;
		}
		inicio = nodo;
		nodo = NULL;
	}
	void eliminar() {

		if (inicio == NULL) {
			// La lista está vacía, no hay nada que eliminar
			return;
		}
		int cod; string nombre;
		cout << "Codigo: "; cin >> cod; cout << "Nombre: "; getline(cin, nombre);
		Nodo<T>* nodoActual = inicio;
		Nodo<T>* nodoAnterior = NULL;

		while (nodoActual != NULL) {
			Admin* admin = (Admin*)(nodoActual->valor);
			if (admin->code == cod && admin->Nombre == nombre) {
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
			Admin* admin = (Admin*)(nodo->valor);
			admin->Mostrar();
			nodo = nodo->siguiente;

		} while (nodo != NULL);
		system("pause");
		system("cls");
	}

	bool HayUsuario(string u, int code) {
		Nodo<T>* nodo = inicio;
		bool hay_usuario = false;
		while (nodo != NULL)
		{
			Admin* admin = (Admin*)(nodo->valor);
			if (admin->Nombre == u && admin->code == code) { hay_usuario = true; break; }
			nodo = nodo->siguiente;
		}
		return hay_usuario;
	}

};

