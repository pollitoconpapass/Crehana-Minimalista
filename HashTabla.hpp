#pragma once
#ifndef __HASHTABLA_HPP__
#define __HASHTABLA_HPP__
#include <iostream>
#include"HashEntidad.hpp"
class HashTabla {
private:

    HashEntidad** tabla;
    int numElementos;
    int TABLE_SIZE;

public:
    HashTabla(int TABLE_SIZE = 128) {
        this->TABLE_SIZE = TABLE_SIZE;
        tabla = new HashEntidad * [TABLE_SIZE];
        for (int i = 0; i < TABLE_SIZE; ++i) {
            tabla[i] = nullptr; //-> todo esta en NULL
        }
        numElementos = 0;
    }
    ~HashTabla() { // -> destructor
        for (int i = 0; i < TABLE_SIZE; ++i) {
            if (tabla[i] != nullptr) {
                delete tabla[i];
            }
        }
        delete[] tabla;
    }

    // --- INSERTAR ---
    void insertar(int key, int value) {
        int base, step, hash; //-> para calcular la posicion

        if (numElementos == TABLE_SIZE)return; //-> si esta lleno

        base = key % TABLE_SIZE;
        hash = base;
        step = 0;

        while (tabla[hash] != nullptr) {
            hash = (base + step) % TABLE_SIZE;
            step++;
        }

        tabla[hash] = new HashEntidad(key, value);
        numElementos++;
    }

    // --- BUSCAR ---
    int buscar(int key) {
        int step = 0;
        int i, base;
        i = base = key % TABLE_SIZE; //hash1 es = a hash2 cuando step=0;
        while (true)
        {
            if (tabla[i] == nullptr)return -1;
            // si esta vacio retorna -1
            else if (tabla[i]->getKey() == key) {
                return i;
                //-> devuelve la posicion en la que se encuentra
            }
            else step++;

            i = (base + step) % TABLE_SIZE;
        }
    }
    int buscar_Llave(int key) {
        int step = 0;
        int i, base;
        i = base = key % TABLE_SIZE; //hash1 es = a hash2 cuando step=0;
        while (true)
        {
            if (tabla[i] == nullptr)return -1;
            // si esta vacio retorna -1
            else if (tabla[i]->getKey() == key) {
                return tabla[i]->getValue();
                //-> devuelve la posicion en la que se encuentra
            }
            else step++;

            i = (base + step) % TABLE_SIZE;
        }
    }

    // --- DEVOLVER EL TAMAÑO ---
    int size() {
        return TABLE_SIZE;
    }

    int sizeactual() {
        return numElementos;
    }
};


#endif // !__HASHTABLA_HPP__
