#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
using namespace std;
struct Datos_Admin {
    string codigo = " ";
    string nombre = " ";
};

class LectorDatos_Admin {
private:
    vector<Datos_Admin> datos_;
public:
    void leerArchivo(const  string& nombreArchivo) {
        ifstream archivo(nombreArchivo);
        if (!archivo.is_open()) {
            cout << "No se pudo abrir el archivo." << endl;
            return;
        }

        string linea;
        while (getline(archivo, linea)) {
            Datos_Admin datos;
            stringstream ss(linea);
            string campo;
            getline(ss, campo, '|');
            datos.codigo = campo;
            getline(ss, campo, '|');
            datos.nombre = campo;


            datos_.push_back(datos);
        }

        archivo.close();
    }

    const vector<Datos_Admin>& obtenerDatos() const {
        return datos_;
    }
};
