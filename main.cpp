#include "pch.h"
#include <iostream>
#include <string>
#include "Listas_Usuario.h"
#include "Listas_Curso.h"
#include"Listas_Admin.h"
#include"File_Usuario.h"
#include"File_Curso.h"
#include"File_Admin.h"
#include"ArbolB.hpp"
#include <chrono>
#include <thread>
#include <conio.h>
#include <Windows.h>
using namespace std;
using namespace System;

void Imprimir(int e) { cout << e << " "; }
// --- LOGO DEL PROGRAMA ---
void Logo() {
    Console::SetWindowSize(70, 30);

    Console::SetCursorPosition(31, 5);
    cout << "INSOMNIA\n";
    Console::ForegroundColor = ConsoleColor::DarkMagenta;
    Console::SetCursorPosition(12, 8);
    cout << "                    /     \\" << endl;
    Console::SetCursorPosition(12, 9);
    cout << "                   ((     ))" << endl;
    Console::SetCursorPosition(12, 10);
    cout << "               ===  \\_v_//  ===" << endl;
    Console::SetCursorPosition(12, 11);
    cout << "                 ====)_^_(====" << endl;
    Console::SetCursorPosition(12, 12);
    cout << "                 ===/ O O \\===" << endl;
    Console::SetCursorPosition(12, 13);
    cout << "                 = | /_ _\\ | =" << endl;
    Console::SetCursorPosition(12, 14);
    cout << "                =   \\/_ _\\/   =" << endl;
    Console::SetCursorPosition(12, 15);
    cout << "                     \\_ _/" << endl;
    Console::SetCursorPosition(12, 16);
    cout << "                     (o_o)" << endl;
    Console::SetCursorPosition(12, 17);
    cout << "                      VwV" << endl;

    Console::ResetColor(); // -> volverlo blanco
    Console::SetCursorPosition(31, 18);
    cout << "Cargando... ";
    Console::SetCursorPosition(43, 18);
    for (int i = 0; i < 10; i++) {
        // Imprimir un caracter que represente el progreso
        cout << "[" << string(i, '=') << string(10 - i, ' ') << "]";

        // Esperar un momento para simular la carga
        this_thread::sleep_for(chrono::milliseconds(10));

        // Mover el cursor a la izquierda para actualizar el progreso
        cout << "\r";   Console::SetCursorPosition(43, 18);
    }
    // Imprimir un mensaje de finalización

    Console::SetCursorPosition(31, 19);
    cout << "COMPLETADO" << std::endl;

    // Limpiar pantalla
    Console::ForegroundColor = ConsoleColor::Black;
    system("pause");
    Console::ResetColor();
    system("cls");

}

// --- FLECHITA PA ELEGIR --- 
int elegirOpcion(int opciones, int x, int y) {
    int tecla = 0;
    int limSuperior = y;
    int limInferior = y + opciones - 1;
    int opcionSeleccionada = 1;

    // Limpiar el buffer de entrada de teclado
    while (_kbhit()) {
        tecla = _getch();
    }

    do {
        // Dibujar la flecha en la opción seleccionada
        Console::SetCursorPosition(x, y + opcionSeleccionada - 1);
        Console::ForegroundColor = ConsoleColor::DarkRed;
        cout << "<" << char(205) << " ";

        // Leer la tecla presionada
        tecla = _getch();

        // Borrar la flecha de la opción seleccionada
        Console::SetCursorPosition(x, y + opcionSeleccionada - 1);
        cout << "  ";

        switch (tecla) {
        case 72: // Flecha hacia arriba
            opcionSeleccionada = (opcionSeleccionada - 1 <= 0) ? opciones : opcionSeleccionada - 1;
            break;
        case 80: // Flecha hacia abajo
            opcionSeleccionada = (opcionSeleccionada + 1 > opciones) ? 1 : opcionSeleccionada + 1;
            break;
        }
    } while (tecla != 13); // Presionar enter para seleccionar

    Console::ResetColor();
    return opcionSeleccionada;
}

int Menu() {
    Console::SetCursorPosition(8, 2);
    cout << "Bienvenido\t" << endl;
    // AQUI IRA LAS OPCIONES GENERALES (?)
    Console::SetCursorPosition(10, 6);
    cout << "Usar las teclas direccionales para mover la flecha";
    Console::SetCursorPosition(13, 7);
    cout << "Presionar enter para elegir una opcion";
    Console::SetCursorPosition(13, 8);
    cout << "1. Registrarse";
    Console::SetCursorPosition(13, 9);
    cout << "2. Iniciar Sesion";
    Console::SetCursorPosition(13, 10);
    cout << "3. Cuenta Administrador";
    Console::SetCursorPosition(13, 11);
    cout << "4. Salir";

    return elegirOpcion(4, 50, 8);
}

void Despedida() { // -> Para cuando presionen 4. Salir
    Console::SetCursorPosition(30, 15);
    cout << "GRACIAS POR PREFERIRNOS :)" << endl;
    Console::SetCursorPosition(50, 19);
    cout << "Presione cualquier tecla para continuar";
    system("pause>nul");
    system("cls");
}

// --- REGISTRO E INICIAR SESION (USUARIO-ADMIN) ---
void Registrar_Usuario(Listas_Usuarios<Usuario*>& Listas_usuario, ArbolBB<int>*& objArbol) {
    int code;
    string Nombre;
    string Apellido;
    char sexo;
    char plan;
    int dis;
    string c;
    cout << "Registro: \n";
    do {
        cout << "Codigo/Contrasena: "; cin >> code;
    } while (objArbol->Buscar(code) == true);
    cin.ignore(); // Ignorar el carácter de nueva línea después de la lectura de 'code'

    cout << "Nombre: ";    getline(cin, Nombre);
    cout << "Apellido: "; getline(cin, Apellido);
    cout << "Sexo: "; cin >> sexo;
    cout << "Plan: "; cin >> plan;
    cin.ignore(); // Ignorar el carácter de nueva línea después de la lectura de 'plan'

    cout << "Ingrese su ciudad: "; getline(cin, c);
    cout << "A cuantos metros se encuentra: "; cin >> dis;

    Ciudad* ciudad = new Ciudad(c, dis);
    Listas_usuario.insertar_usuario(new Usuario(ciudad, code, Nombre, Apellido, sexo, plan));
    objArbol->Insertar(code);
    fstream archivo("Archivo_Usuarios.txt", ios::in | ios::out | ios::app);
    if (!archivo) {
        cout << "No se pudo abrir el archivo." << endl;
    }
    archivo.seekp(0, ios::end);
    archivo << c << "|" << dis << "|" << code << "|" << Nombre << "|" << Apellido << "|" << sexo << "|" << "F" << endl;
    cout << "Datos agregados correctamente." << endl;
    archivo.close();
    system("cls");
    Menu();
}
void Registrar_Admin(Listas_Admin<Admin*>& Listas_admin) {
    int code;
    string nombre;
    cout << "Registro de Admin: ";
    cout << "Nombre: "; getline(cin, nombre);
    cin.ignore();
    cout << "Code: "; cin >> code;
    Listas_admin.insertar_Admin(new Admin(nombre, code));

    fstream archivo("Archivo_Admin.txt", ios::in | ios::out | ios::app);
    if (!archivo) { cout << "No se puede abrir el archivo. " << endl; }
    archivo.seekp(0, ios::end);
    archivo << code << "|" << nombre << endl;
    cout << "Datos agregados correctamente." << endl;
    archivo.close();
}
void Registrar_Curso(Listas_Cursos<Curso*>& Listas_curso) {
    int codigo;
    string curso;
    string Profesor;
    string Descripcion;
    string area;
    string modalidad;
    int cantidad;
    int precio;
    int duracion;
    cout << "Registro de Curso: \n";
    cout << "Codigo: "; cin >> codigo;
    cin.ignore();
    cout << "Curso: "; getline(cin, curso);
    cout << "Profesor: "; getline(cin, Profesor);
    cout << "Descripcion: "; getline(cin, Descripcion);
    cout << "Area: "; getline(cin, area);
    cout << "Modalidad: "; getline(cin, modalidad);
    cout << "Cantidad: "; cin >> cantidad;
    cout << "Precio: "; cin >> precio;
    cout << "Duracion: "; cin >> duracion;

    Listas_curso.insertar_Curso(new Curso(Descripcion, curso, Profesor, area, modalidad, codigo, cantidad, precio, duracion));

    fstream archivo("Archivo_Admin.txt", ios::in | ios::out | ios::app);
    if (!archivo) { cout << "No se puede abrir el archivo. " << endl; }
    archivo.seekp(0, ios::end);
    //codigo|curso|descripcion|area|modalidad|profesor|cantidad|precio|duracion
    archivo << codigo << "|" << curso << "|" << Descripcion << "|" << area << "|" << modalidad << "|" << Profesor << "|" << cantidad << "|" << precio << "|" << duracion << endl;
    cout << "Datos agregados correctamente." << endl;
    archivo.close();
}
void Agregar_Curso_Usuario(Listas_Usuarios<Usuario*>& Lista_Usuarios, Listas_Cursos<Curso*>& Lista_Cursos, string usu, int code) {
    cout << "Ingrese el codigo del curso al que desea registrarse:";
    int cod; cin >> cod;
    Lista_Usuarios.Agregar_Curso_Al_Usuario(usu, code, Lista_Cursos.Hay_Curso(cod));
}
int MenuADMIN() {
    system("cls");
    int op;
    cout << "1.- Mostrar todos los cursos\n";
    cout << "2.- Mostrar todos los usuarios\n";
    cout << "3.- Eliminar un Administrador\n";
    cout << "4.- Agregar un Adminitrador\n";
    cout << "5.- Salir\n";
    cout << "Elije opcion: "; cin >> op;
    return op;
}
int MenuAlIniciarSesion() {
    system("cls");
    int op;
    system("cls");
    cout << "1.- Mostrar los cursos\n";
    cout << "2.- Mostrar mis Cursos\n";
    cout << "3.- Cambiar de Plan\n";
    cout << "4.- Buscar Curso por precio\n";
    cout << "5.- Salir\n";
    cout << "Elije opcion: "; cin >> op;
    return op;
}
void IniciarSesion_A(Listas_Admin<Admin*>& Lista_admin, Listas_Cursos<Curso*>& Lista_curso, Listas_Usuarios<Usuario*>& Lista_usuario, ArbolBB<int>*& objArbol) {
    system("cls");
    string usu;
    int code;
    cout << "Ingrese su Nombre: ";
    cin.ignore();
    getline(cin, usu);
    cout << "Ingrese su codigo/contrasena: "; cin >> code;
    cin.ignore();
    if (Lista_admin.HayUsuario(usu, code)) {
        _sleep(5);
        int op = NULL;

        while (op != 5) {
            op = MenuADMIN();
            switch (op)
            {
            case 1: system("cls"); int opcion1; Lista_curso.mostrar();
                cout << "\n1.-Ordenar Por Codigo. " << "\n2.-Ordenar Por Precio."; cin >> opcion1; switch (opcion1)
                {
                case 1: Lista_curso.Quicksort_codigo();
                    break;
                case 2: Lista_curso.Quicksort_precio();
                    break;
                case 3: break;
                default:
                    break;
                }
                system("pause");//Agregar el quicksort
                break;
            case 2:  int opcion2;  system("cls"); Lista_usuario.Mostrar(); cout << "\n1.-Ordenar Por Codigo" << "\n2.-Buscar usuario por codigo\n"; cin >> opcion2;
                switch (opcion2)
                {
                case 1: Lista_usuario.Quicksort_Codigo();
                    break;
                case 2: int Codigo_buscar_usuario; cout << "INGRESE EL CODIGO DEL USUARIO A BUSCAR: "; cin >> Codigo_buscar_usuario; if (objArbol->Buscar(Codigo_buscar_usuario)) { Lista_usuario.MostrarUsuarioxCodigo(Codigo_buscar_usuario); }
                      else
                {
                    cout << "\n---------NO HAY NINGUN USUARIO CON ESE CODIGO------- ";
                }
                      break;
                case 3: break;
                default:
                    break;
                } system("pause");//Agregar el qiucksort
                break;
            case 3: system("cls"); Lista_admin.eliminar(); system("pause");
                break;
            case 4: system("cls"); Registrar_Admin(Lista_admin); system("pause");
                break;
            case 5: false;
                break;

            default:
                break;
            }

        }
    }
    else {
        char o;
        cout << "La contraseña o el nombre es incorrecto\n";
        cout << "Desea volver a intentar la contraseña S/N: "; cin >> o;
        if (o == 's' || o == 'S') IniciarSesion_A(Lista_admin, Lista_curso, Lista_usuario, objArbol);
        cin.ignore();
    }

}
void IniciarSesion_U(Listas_Usuarios<Usuario*>& Lista_usuarios, Listas_Cursos<Curso*>& Lista_Curso) {
    system("cls");
    string usu;
    int code;
    cout << "Ingrese su Nombre: ";
    cin.ignore();
    getline(cin, usu);
    cout << "Ingrese su codigo/contrasena: ";  cin >> code;
    cin.ignore();
    if (Lista_usuarios.HayUsuario(usu, code)) {
        _sleep(5);
        int op = NULL;
        while (op != 5) {

            op = MenuAlIniciarSesion();
            switch (op)
            {
            case 1: system("cls"); int opcion; Lista_Curso.mostrar(); cout << "\n1. - Ordenar Por Codigo. " << "\n2. - Ordenar Por Precio." << "\n3. - Entrar a un curso \n"; cin >> opcion; switch (opcion)
            {
            case 1: system("cls"); Lista_Curso.Quicksort_codigo(); system("pause");
                break;
            case 2: system("cls"); Lista_Curso.Quicksort_precio(); system("pause");
                break;
            case 3: system("cls"); Agregar_Curso_Usuario(Lista_usuarios, Lista_Curso, usu, code);
                break;
            case 4: system("cls");
                break;
            default:
                break;
            } system("pause");
            break;
            case 2: system("cls"); Lista_usuarios.Mostrar_Mis_Cursos(usu, code); system("pause");
                break;
            case 3: system("cls"); Lista_usuarios.Cambiar_plan(usu, code); system("pause");
                break;
            case 4: system("cls"); Lista_Curso.Funcionalidad_Hash_Precio(); system("pause"); system("cls");
                break;
            case 5: false;
                break;

            default:
                break;
            }
        }
    }
    else {
        char o;
        cout << "La contraseña o el nombre es incorrecto\n";
        cout << "Desea volver a intentar la contraseña S/N: ";
        cin >> o;
        if (o == 's' || o == 'S') IniciarSesion_U(Lista_usuarios, Lista_Curso);

    }

}


void Cargar_usuarios(Listas_Usuarios<Usuario*>& a, LectorDatos_Usuario& LectorDatos_usuario, ArbolBB<int>*& objArbol) {
    LectorDatos_usuario.leerArchivo("Archivo_Usuarios.txt");
    const std::vector<Datos_Usuario>& datos = LectorDatos_usuario.obtenerDatos();
    int code;
    int distancia_hora;
    string Nombre;
    string Apellido;
    string ciudad;
    char sexo;
    char plan;

    for (const Datos_Usuario& dato : datos) {
        ciudad = dato.ciudad;
        distancia_hora = stoi(dato.distancia_hora);
        code = stoi(dato.codigo);
        Nombre = dato.nombre;
        Apellido = dato.apellido;
        sexo = dato.sexo;
        plan = dato.plan;
        a.insertar_usuario(new Usuario(new Ciudad(ciudad, distancia_hora), code, Nombre, Apellido, sexo, plan));
        objArbol->Insertar(code);
    }
}
void Cargar_Curso(Listas_Cursos<Curso*>& b, LectorDatos_Curso lector_C) {
    lector_C.leerArchivo("Archivo_Cursos.txt");
    const std::vector<Datos_Curso>& datos = lector_C.obtenerDatos();
    int code;
    string Profesor;
    string Descripcion;
    string _Curso;
    string area;
    string modalidad;
    int cantidad;
    int precio;
    int duracion;
    for (const Datos_Curso& dato : datos) {
        // cout << dato.cod<<endl<<dato.area<<endl<<dato.cantidad<<endl<<dato.descripcion<<endl<<dato.profesor<<endl<<dato.curso<<endl;
        code = stoi(dato.cod);
        Descripcion = dato.descripcion;
        _Curso = dato.curso;
        area = dato.area;
        Profesor = dato.profesor;
        cantidad = stoi(dato.cantidad);
        precio = stoi(dato.precio);
        duracion = stoi(dato.duracion);
        modalidad = dato.modalidad;
        b.insertar_Curso(new Curso(Descripcion, _Curso, Profesor, area, modalidad, code, cantidad, precio, duracion));
    }
}
void Cargar_Admin(Listas_Admin<Admin*>& c, LectorDatos_Admin lector_A) {
    lector_A.leerArchivo("Archivo_Admin.txt");
    const std::vector<Datos_Admin>& datos = lector_A.obtenerDatos();
    int code;
    string nombre;
    for (const Datos_Admin& dato : datos) {
        code = stoi(dato.codigo);
        nombre = dato.nombre;
        c.insertar_Admin(new Admin(nombre, code));
    }
}

int main() {
    Listas_Usuarios<Usuario*> Lista_Usuarios;
    Listas_Cursos<Curso*> Lista_Cursos;
    Listas_Admin<Admin*> Lista_Admin;
    LectorDatos_Usuario LectorDatos_usuario;
    LectorDatos_Curso LectorDatos_curso;
    LectorDatos_Admin LectorDatos_admin;
    ArbolBB<int>* objArbol = new ArbolBB<int>(Imprimir);
    //Cargar datos
    Cargar_usuarios(Lista_Usuarios, LectorDatos_usuario, objArbol);
    Cargar_Admin(Lista_Admin, LectorDatos_admin);
    Cargar_Curso(Lista_Cursos, LectorDatos_curso);
    // Registrar_Curso(Lista_Cursos);
    int opc = 0;
    bool salir = false;


    // --- FUNCIONAMIENTO PRINCIPAL ---
    Logo();
    Menu();

    while (!false) {
        opc = Menu();
        switch (opc) {
        case 1: system("cls"); Registrar_Usuario(Lista_Usuarios, objArbol);  system("cls"); system("pause");
            break;
        case 2:  system("cls"); IniciarSesion_U(Lista_Usuarios, Lista_Cursos);   system("pause"); system("cls");
            break;
        case 3:      system("pause"); IniciarSesion_A(Lista_Admin, Lista_Cursos, Lista_Usuarios, objArbol); system("cls");
            break;
        case 4:
            Despedida();
            return 0; // -> retorna falso y cierra el bucle...
            break;

        }

    }

    return 0;
}
