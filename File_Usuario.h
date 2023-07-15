#pragma once
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
using namespace std;
struct Datos_Usuario {
    string ciudad = " ";
    string distancia_hora = " ";
    string codigo = " ";
    string nombre = " ";
    string apellido = " ";
    char sexo = ' ';
    char plan = ' ';
};

class LectorDatos_Usuario {
private:
    vector<Datos_Usuario> datos_;
public:
    void leerArchivo(const  string& nombreArchivo) {
        ifstream archivo(nombreArchivo);
        if (!archivo.is_open()) {
            cout << "No se pudo abrir el archivo." << endl;
            return;
        }

        string linea;
        while (getline(archivo, linea)) {
            //ciudad|distancia|codigo|nombre|apellido|sexo|plan
            Datos_Usuario datos;
            stringstream ss(linea);
            string campo;
            getline(ss, campo, '|');
            datos.ciudad = campo;
            getline(ss, campo, '|');
            datos.distancia_hora = campo;
            getline(ss, campo, '|');
            datos.codigo = campo;
            getline(ss, campo, '|');
            datos.nombre = campo;
            getline(ss, campo, '|');
            datos.apellido = campo;
            getline(ss, campo, '|');
            datos.sexo = campo[0];
            getline(ss, campo, '|');
            datos.plan = campo[0];

            datos_.push_back(datos);
        }

        archivo.close();
    }

    const vector<Datos_Usuario>& obtenerDatos() const {
        return datos_;
    }
};
