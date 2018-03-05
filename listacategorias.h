#ifndef LISTACATEGORIAS_H
#define LISTACATEGORIAS_H
#include <string>
#include <fstream>
#include <iostream>

using namespace std;

class listaCategorias{

public:
    string categoria;
    listaCategorias* siguiente;
    void insertarCategoria(string nombreCategoria);
    void mostarCategoria();
    void buscarCategoria(string nombreCategoria);
    void eliminarCategoria(string nodoBuscado);
    void graficarCategoria();
    void modificarCategoria(string dato, string datoNuevo);
    int contador;
    ofstream salida;
    listaCategorias* primero;
    listaCategorias* ultimo;

};
#endif // LISTACATEGORIAS_H
