#include "listacategorias.h"
#include <iostream>
#include <fstream>

using namespace std;

///////////////////////////////////////////
/// Funciones De Lista Categoria///////////
///////////////////////////////////////////

void listaCategorias::insertarCategoria(string nombreCategoria){
    listaCategorias* nuevo = new listaCategorias();
    nuevo->categoria=nombreCategoria;
    if(primero == NULL){
        primero = nuevo;
        primero->siguiente = NULL;
        ultimo = nuevo;
    }else{
        ultimo->siguiente=nuevo;
        nuevo->siguiente=NULL;
        ultimo = nuevo;
    }
    cout<<"Categoria Ingresada"<<endl;
}


void listaCategorias::mostarCategoria(){
    listaCategorias* aux = new listaCategorias();
    aux = primero;
    if(primero!=NULL){
        while (aux!=NULL) {
            cout<<aux->categoria<<endl;
            aux=aux->siguiente;
        }
    }else{
        cout<<"Lista Vacia"<<endl;
    }


}

void listaCategorias::buscarCategoria(string nombreCategoria){
    listaCategorias* aux = new listaCategorias();
    aux = primero;
    bool encontrado = false;
    if(primero!=NULL){
        while (aux!=NULL && encontrado!=true) {
            if(aux->categoria==nombreCategoria){
                cout<<"Nodo con el dato "<<nombreCategoria<<" Encontrado"<<endl;
                encontrado=true;
            }
            aux=aux->siguiente;
        }
        if(!encontrado){
            cout<<"Categoria No encontrada"<<endl;
        }
    }else{
        cout<<"Lista Vacia"<<endl;
    }
}


void listaCategorias::eliminarCategoria(string nodoBuscado){
    listaCategorias* aux = new listaCategorias();
    listaCategorias* anterior = new listaCategorias();
    aux = primero;
    anterior = NULL;
    bool encontrado = false;
    if(primero!=NULL){
        while (aux!=NULL && encontrado!=true) {
            if(aux->categoria==nodoBuscado){
                cout<<"Nodo con el dato "<<nodoBuscado<<"Encontrado";

                if(aux==primero){
                    primero=primero->siguiente;
                }else if(aux==ultimo){
                    anterior->siguiente=NULL;
                    ultimo = anterior;
                }else{
                    anterior->siguiente=aux->siguiente;
                }
                cout<<"\n Nodo Eliminado";
                encontrado=true;
            }
            anterior=aux;
            aux=aux->siguiente;

        }
        if(!encontrado){
            cout<<"Categoria No encontrada"<<endl;
        }
    }else{
        cout<<"Lista Vacia"<<endl;
    }
}

void listaCategorias::graficarCategoria(){
    salida.open("ListaCategorias.txt");
    salida<<"digraph G {\n";
    salida<<"\trankdir=LR;\n";
    salida<<"\tnode [shape=record]\n";

    listaCategorias* aux = new listaCategorias();
    aux = primero;

    if(primero!=NULL){
        while (aux!=NULL) {
            //cout<<aux->categoria<<endl;
            salida<<contador<<"[label=\""<<aux->categoria<<"\"]; \n";
            aux=aux->siguiente;
            if(aux!=NULL){
                salida<<contador<<"->"<<contador+1<<"\n";
                contador++;
            }
        }
    }else{
        cout<<"Lista Vacia"<<endl;
    }
    salida<<"\n";
    salida<<"}";
    salida.close();
    system("dot -Tpng ListaCategorias.txt -o ListaCategorias.png" );
    cout<<"Lista Categoria Graficada"<<endl;
    contador=0;

}

void listaCategorias::modificarCategoria(string dato, string datoNuevo){
    listaCategorias* aux = new listaCategorias();
    aux = primero;
    bool encontrado = false;
    if(primero!=NULL){
        while (aux!=NULL&&encontrado!=true) {
            if(aux->categoria==dato){
                cout<<"Nodo con el dato "<<dato<<"Encontrado";
                //cout<< "ingrese el nuevo dato para este nodo";
                aux->categoria = datoNuevo;
                encontrado=true;
            }

            aux=aux->siguiente;

        }
        if(!encontrado){
            cout<<"Categoria No encontrada"<<endl;
        }
    }else{
        cout<<"Lista Vacia"<<endl;
    }
}
