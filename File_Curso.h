#pragma once
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
using namespace std;
struct Datos_Curso {
    string descripcion = " ";
    string curso = " ";
    string profesor = " ";
    string area = " ";
    string cod = " ";
    string cantidad = " ";
    string duracion = " ";
    string modalidad = " ";
    string precio = " ";
};

class LectorDatos_Curso {
private:
    vector<Datos_Curso> datos_;
public:
    void leerArchivo(const  string& nombreArchivo) {
        ifstream archivo(nombreArchivo);
        if (!archivo.is_open()) {
            cout << "No se pudo abrir el archivo." << endl;
            return;
        }

        string linea;
        while (getline(archivo, linea)) {
            Datos_Curso datos;
            stringstream ss(linea);
            string campo;
            //codigo|curso|descripcion|area|modalidad|profesor|cantidad|precio|duracion
            getline(ss, campo, '|');
            datos.cod = campo;
            getline(ss, campo, '|');
            datos.curso = campo;
            getline(ss, campo, '|');
            datos.descripcion = campo;
            getline(ss, campo, '|');
            datos.area = campo;
            getline(ss, campo, '|');
            datos.modalidad = campo;
            getline(ss, campo, '|');
            datos.profesor = campo;
            getline(ss, campo, '|');
            datos.cantidad = campo;
            getline(ss, campo, '|');
            datos.precio = campo;
            getline(ss, campo, '|');
            datos.duracion = campo;
            datos_.push_back(datos);
        }

        archivo.close();
    }

    const vector<Datos_Curso>& obtenerDatos() const {
        return datos_;
    }
};
