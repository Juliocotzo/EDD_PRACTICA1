#include "listacontactos.h"
#include <iostream>
#include <fstream>

using namespace std;


void listaContactos::insertarContacto(string nombre, string direccion, string telefono, string categoria, string path){
    listaContactos* nuevo = new listaContactos();
    nuevo->nombre=nombre;
    nuevo->direccion=direccion;
    nuevo->telefono=telefono;
    nuevo->categoria=categoria;
    nuevo->path=path;
    if(Primero==NULL){
        Primero = nuevo;
        Ultimo = nuevo;
        Primero->siguiente = Primero;
        Primero->atras = Ultimo;
    }else{
        Ultimo->siguiente = nuevo;
        nuevo->atras = Ultimo;
        nuevo->siguiente = Primero;
        Ultimo = nuevo;
        Primero->atras = Ultimo;
    }
}

void listaContactos::mostrarContacto(){
    listaContactos* actual = new listaContactos();
    actual = Primero;
    if(Primero!=NULL){
        do{
           cout<<"\n"<<actual->nombre<<","<<actual->direccion<<","<<actual->telefono<<","<<actual->categoria<<","<<actual->path<<"\n";
           actual = actual->siguiente;

        }while (actual!=Primero);

    }else{
        cout<<"\n La lista es vacia\n";
    }
    //cout<<endl;
}

void listaContactos::graficarListaContacto(){
    ofstream salida;
    salida.open("listaContactos.txt");
    salida<<"digraph G {\n";
    salida<<"\trankdir=LR;\n";
    salida<<"\tnode [shape=record]\n";

    listaContactos* actual = new listaContactos();
    actual = Primero;
    if(Primero!=NULL){
        do{
           salida<<contador<<"[label=\"";
           salida<<"Nombre: "<<actual->nombre<<"\\nDireccion: "<<actual->direccion<<"\\nTelefono: "<<actual->telefono<<"\\nCategoria: "<<actual->categoria<<"\\nImagen: "<<actual->path;
           salida << "\"]; \n";
           actual = actual->siguiente;
           if (actual!=Primero){
               salida<<contador<<"->"<<contador+1<<endl;
               salida<<contador+1<<"->"<<contador<<endl;
               contador++;
           }

        }while (actual!=Primero);

    }else{
        cout<<"\n La lista es vacia\n";
    }
    cout<<endl;
    //contador++;
    salida<<0<<"->"<<contador<<endl;
    salida<<contador<<"->"<<0<<endl;
    salida<<"}";
    salida.close();
    system("dot -Tpng listaContactos.txt -o listaContactos.png" );
    contador=0;
}

void listaContactos::eliminarContacto(string nombre){
    listaContactos* actual = new listaContactos();
    actual = Primero;
    listaContactos* anterior = new listaContactos();
    anterior = NULL;
    bool encontrado = false;
    //string nodoBuscado;
    //cout<< "Ingrese el dato del nodo a Eliminar: ";
    //cin >> nodoBuscado;
    if(Primero!=NULL){
        do{
            if(actual->nombre==nombre){
                cout<<"\nNodo con el dato ( "<<nombre<<" )encontrado";
                if(actual == Primero){
                    Primero = Primero->siguiente;
                    Primero->atras = Ultimo;
                    Ultimo->siguiente = Primero;
                }else if(actual==Ultimo){
                    Ultimo = anterior;
                    Ultimo->siguiente = Primero;
                    Primero->atras =Ultimo;
                }else{
                    anterior ->siguiente = actual->siguiente;
                    actual->siguiente->atras = anterior;
                }
                cout<<"\nNodo eliminado";
                encontrado = true;
            }
            anterior = actual;
            actual = actual->siguiente;
        }while (actual!=Primero && encontrado !=true);

        if(!encontrado){
            cout<<"Palabra no encotrada";
        }
    }else{
        cout<<"Lista se encuentra vacia";
    }
}

void listaContactos::buscarContacto(string nombre, string telefono, string categoria){
    listaContactos* actual = new listaContactos();
    actual = Primero;

    bool encontrado = false;
    //string nodoBuscado;
    //cout<< "Ingrese el dato del nodo a Eliminar: ";
    //cin >> nodoBuscado;
    if(Primero!=NULL){
        do{
            if(actual->nombre==nombre||actual->telefono==telefono||actual->categoria==categoria){
                //cout<<"\nNodo con el dato ( "<<nodoBuscado<<" )encontrado";
                cout<<"Nombre: "<<actual->nombre<<"\\nDireccion: "<<actual->direccion<<"\\nTelefono: "<<actual->telefono<<"\\nCategoria: "<<actual->categoria<<"\\nImagen: "<<actual->path<<endl;
                encontrado = true;
            }

            actual = actual->siguiente;
        }while (actual!=Primero && encontrado !=true);

        if(!encontrado){
            cout<<"Palabra no encotrada";
        }
    }else{
        cout<<"Lista se encuentra vacia";
    }
}

void listaContactos::modificarContacto(string nombre, string nuevoNombre, string nuevaDireccion, string nuevoTelefono, string nuevaCategoria, string nuevoPath){
    listaContactos* actual = new listaContactos();
    actual = Primero;

    bool encontrado = false;

    if(Primero!=NULL){
        do{
            if(actual->nombre==nombre){
                cout<<"\nNodo con el dato ( "<<nombre<<" )encontrado";
                cout<<"ingrese el nuevo dato";
                actual->nombre = nuevoNombre;
                actual->direccion = nuevaDireccion;
                actual->telefono = nuevoTelefono;
                actual->categoria = nuevaCategoria;
                actual->path = nuevoPath;
                cout<<"Nodo modificado";

                encontrado = true;
            }

            actual = actual->siguiente;
        }while (actual!=Primero && encontrado !=true);

        if(!encontrado){
            cout<<"Palabra no encotrada";
        }
    }else{
        cout<<"Lista se encuentra vacia";
    }
}
