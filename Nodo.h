#pragma once
template<class T>
class Nodo {
public:
	T valor;
	Nodo<T>* siguiente;

	Nodo(T value, Nodo<T>* sgt = nullptr) {
		siguiente = sgt;
		valor = value;
	}
	~Nodo() {}
};


