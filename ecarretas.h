#ifndef ECARRETAS
#define ECARRETAS

#include <fstream>
#include <iostream>
#include <stdlib.h>

using namespace std;

struct NodoCarreta{
    NodoCarreta* siguiente;
    int num;

    NodoCarreta(int num){
        this->num = num;
        siguiente  = NULL;
    }
};

typedef struct PilaCarreta{
    NodoCarreta* inicio;
    int size;

    PilaCarreta(){
        inicio = NULL;
        size = 0;
    }

    //----------------------------------------------------------- pila vacia?

    bool vacia(){
        if (inicio==NULL){return true;}
        else{return false;}
    }

  // ------------------------------------------------------------- insertar

    void Insertar(NodoCarreta* nod){
            if(vacia()){
                inicio = nod;
                size++;
            }  else {
                nod->siguiente = inicio;
                inicio = nod;
                size++;
            }
    }

//--------------------------------------------------------------- extraer
    NodoCarreta Extraer(){
        if(!vacia()){
            NodoCarreta* temp;
            temp = inicio;
            inicio = inicio->siguiente;
            size--;
            return *temp;
        }  else {
            cout << "La pila de carretas esta vacia" << endl;
            return -1;
        }
    }

//---------------------------------------------------------------- recorrer
    void Recorrer(){
        NodoCarreta* temp;
        temp = inicio;

        while(temp){
            cout << "el valor es: " << temp->num << endl;
            temp = temp->siguiente;
        }
    }

}PilaCarreta;


#endif // ECARRETAS

