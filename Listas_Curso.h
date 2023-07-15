#pragma once
#include"Unidad_Curso.h"
#include"Nodo.h"
#include"Quicksort.hpp"
#include"HashTabla.hpp"
template<class T>
class Listas_Cursos {
private:
	Nodo<T>* inicio;

public:
	Listas_Cursos() {
		inicio = NULL;
	}
	~Listas_Cursos() {
		Nodo<T>* temp;
		while (inicio != NULL)
		{
			temp = inicio;
			inicio = inicio->siguiente;
			delete temp;
			temp = NULL;
		}
	}

	//HASH - TABLA
	void imprimirTablaHash(HashTabla* ht, int* keys, int* values) {
		cout << "SIZE TABLA: " << ht->size() << endl;
		cout << "SIZE ACTUAL: " << ht->sizeactual() << endl;
		for (int i = 0; i < ht->size(); ++i) {
			if (ht->buscar(keys[i]) != -1) { cout << ht->buscar(keys[i]) << " : " << values[i] << endl; }
		}
	}
	void ImprimirValor(HashTabla* ht, int* keys, int* values, int indice) {
		Nodo<T>* nodo = inicio;
		int aux;
		aux = ht->buscar_Llave(indice);
		while (nodo != NULL)
		{
			Curso* cur = (Curso*)(nodo->valor);
			if (aux == cur->precio) { cur->mostrar(); }
			nodo = nodo->siguiente;
		}
	}

	void Funcionalidad_Hash_Precio() {
		Nodo<T>* nodo = inicio;
		HashTabla* hashito = new HashTabla(300);
		int values[300]{};
		int keys[300] = {};
		int indice;

		for (int i = 0; i < 300 && nodo != nullptr; i++) {
			Curso* curso = (Curso*)(nodo->valor);
			values[i] = curso->precio; //value[1]= 13
			keys[i] = 1 + rand() % (301);//Keys[1]= 40
			hashito->insertar(keys[i], values[i]);
			nodo = nodo->siguiente;
		}
		cout << "TABLA DE HASH" << endl;
		imprimirTablaHash(hashito, keys, values);
		cout << "\nUsted desea buscar por indice: ";
		cin >> indice;
		ImprimirValor(hashito, keys, values, indice);

	}

	//FUNCIONES CLASICAS 
	void insertar_Curso(T v) {
		Nodo<T>* nodo = new Nodo<T>(v);
		if (inicio == NULL)
		{
			inicio = nodo;
		}
		else
		{
			nodo->siguiente = inicio;
		}
		inicio = nodo;
		nodo = NULL;
	}
	void Eliminar_Curso() {

		if (inicio == NULL) {
			// La lista está vacía, no hay nada que eliminar
			return;
		}

		int cod;
		cout << "Ingrese el código del curso a eliminar: ";
		cin >> cod;

		Nodo<T>* nodoActual = inicio;
		Nodo<T>* nodoAnterior = NULL;

		while (nodoActual != NULL) {
			Curso* curso = (Curso*)(nodoActual->valor);
			if (curso->cod == cod) {
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

				cout << "El curso ha sido eliminado correctamente." << endl;
				return;
			}

			// Avanzar al siguiente nodo
			nodoAnterior = nodoActual;
			nodoActual = nodoActual->siguiente;
		}

		// No se encontró el curso en la lista
		cout << "No se encontró ningún curso con el código ingresado." << endl;

	}
	Curso* Hay_Curso(int cod) {
		Nodo<T>* nodo = inicio;
		Curso* aux = NULL;
		bool hay_curso = false;
		while (nodo != NULL)
		{
			Curso* cur = (Curso*)(nodo->valor);
			if (cur->cod == cod) { hay_curso = true; aux = cur; return aux; break; }
			nodo = nodo->siguiente;
		}
		return aux;
	}
	void mostrar() {
		Nodo<T>* nodo = inicio;
		do
		{
			Curso* cur = (Curso*)(nodo->valor);
			cur->mostrar();
			nodo = nodo->siguiente;
		} while (nodo != NULL);
	}
	bool Lleno() {
		if (inicio != NULL) { return true; }
		else
		{
			return false;
		}
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

	//ORDANMIENTO POR QUICKSORT
	void Quicksort_precio() {
		Nodo<T>* nodo = inicio;
		int N = size();
		int* Arreglo_precio = new int[N];
		int i = 0;
		while (nodo != NULL)
		{
			Curso* cur = (Curso*)(nodo->valor);
			Arreglo_precio[i] = cur->precio;
			nodo = nodo->siguiente;
			i++;
		}

		quicksort(Arreglo_precio, 0, i - 1);
		cout << "Arreglo ordenado por quicksort" << endl;
		for (int j = 0; j < N; j++) {
			nodo = inicio;
			Curso* cur = NULL; // Inicializar a NULL
			while (nodo != NULL) {
				cur = (Curso*)(nodo->valor);
				if (cur->precio == Arreglo_precio[j]) {
					cur->mostrar();
					break; // Salir del bucle while una vez que se encuentra el curso
				}
				nodo = nodo->siguiente;
			}
		}
		delete[] Arreglo_precio;
	}
	void Quicksort_codigo() {
		Nodo<T>* nodo = inicio;
		int N = size();
		int* Arreglo_codigo = new int[N];
		int i = 0;
		while (nodo != NULL)
		{
			Curso* cur = (Curso*)(nodo->valor);
			Arreglo_codigo[i] = cur->cod;
			nodo = nodo->siguiente;
			i++;
		}
		quicksort(Arreglo_codigo, 0, i - 1);
		cout << "Arreglo ordenado por quicksort" << endl;
		for (int j = 0; j < N; j++) {
			nodo = inicio;
			Curso* cur = NULL; // Inicializar a NULL
			while (nodo != NULL) {
				cur = (Curso*)(nodo->valor);
				if (cur->cod == Arreglo_codigo[j]) {
					cur->mostrar();
					break; // Salir del bucle while una vez que se encuentra el curso
				}
				nodo = nodo->siguiente;
			}
		}
		delete[] Arreglo_codigo;
	}

};
