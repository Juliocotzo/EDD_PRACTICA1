#ifndef LISTACONTACTOS_H
#define LISTACONTACTOS_H
#include <string>
#include <fstream>
#include <iostream>

using namespace std;

class listaContactos{
public:
    string nombre;
    string direccion;
    string telefono;
    string categoria;
    string path;
    listaContactos* siguiente;
    listaContactos* atras;
    int contador=0;
    void insertarContacto(string nombre, string direccion, string telefono, string categoria, string path);
    void mostrarContacto();
    void eliminarContacto(string nombre);
    void graficarListaContacto();
    void buscarContacto(string nombre, string telefono, string categoria);
    void modificarContacto(string nombre, string nuevoNombre, string nuevaDireccion, string nuevoTelefono, string nuevaCategoria, string nuevoPath);
    listaContactos* Primero;
    listaContactos* Ultimo;
};


#endif // LISTACONTACTOS_H
