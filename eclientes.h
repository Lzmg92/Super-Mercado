#ifndef ECLIENTES
#define ECLIENTES
#include <iostream>
#include <stdlib.h>
#include <time.h>
#include "ecarretas.h"

using namespace std;

struct NodoCliente{
    NodoCliente* siguiente;
    NodoCliente* anterior;

    int id;
    int edad;
    bool masculino;
    bool embarazada;
    NodoCarreta* Carreta;
    int Gasto;


    NodoCliente(int edad, bool masculino, bool embarazada){
     this->edad = edad;
     this->masculino = masculino;
        if(masculino || edad > 30){
     this->embarazada = 0;}
        else {
     this->embarazada = embarazada;
        }
     siguiente = NULL;
    }

    void SetId(int ID){
        id = ID;
    }


    void SetGasto(int gasto){
        Gasto = gasto;
    }

    void SetCarreta(NodoCarreta* carreta){
        Carreta=carreta;
    }


    int GetGasto(){
       return Gasto;
    }

    int GetId(){
        return id;
    }

    NodoCarreta* GetCarreta(){
        return Carreta;
    }

};

// -----------------------------------------------------------------------------------------   struct para metodos cola

struct ColaClientes{
    NodoCliente* inicio;
    NodoCliente* fin;
    int size, Tsize;

    ColaClientes(){
        inicio = fin = NULL;
        size = 0;
        Tsize =0;

    }

// ------------------------------------------------------  funcion vacia?

    bool vacia(){
        if(inicio==NULL){return 1;}else {return 0;}
    }


//------------------------------------------------------- insertar


    void Insertar(NodoCliente* nod){

        if(vacia()){
            nod->SetId(size);
            fin = inicio = nod;
            size++;
            Tsize++;
        }else if(nod->edad >= 60 ||(nod->embarazada)){
            InsertarEspecial(nod);
        }else{
            nod->SetId(size);
            fin->siguiente =nod;
            fin = fin->siguiente;
            size++;
            Tsize++;
        }
    }

//------------------------------------------------------- bool caja de oro
    bool EntraAoro(NodoCliente* nod){
        if(nod->edad >= 60 ||(nod->embarazada)){
          return true;
         } else {return false;}
    }

//------------------------------------------------------ insertado especial

    void InsertarEspecial(NodoCliente* nod){
            if(vacia()){
                nod->SetId(size);
                inicio = fin = nod;
                size++;
                Tsize++;
            }  else {
                nod->SetId(size);
                nod->siguiente = inicio;
                inicio = nod;
                size++;
                Tsize++;
            }
    }

//------------------------------------------------------ sacar de la cola

    void Extraer(){
        if(!vacia()){
            inicio = inicio->siguiente;
            Tsize--;
        }  else {
            cout << "La cola de clientes esta vacia" << endl;
        }
    }

//---------------------------------------------------- sacar ultimo

    NodoCliente GetP(){
        NodoCliente* temp = new NodoCliente(-1,0,0);

        if(!vacia()){
           temp = inicio->siguiente;
           return *temp;
        }  else {
            cout << "La cola de clientes esta vacia" << endl;
            return *temp;
        }
    }

// ---------------------------------------------------- get

    NodoCliente Get(){
        if(!vacia()){
            NodoCliente* temp;
            temp = inicio;
            return *temp;
        }  else {
            cout << "La cola de clientes esta vacia" << endl;
            NodoCliente* err = new NodoCliente(-1,0,0);
            return *err;
        }
    }

//----------------------------------------------------- recorrer la cola

    void Recorrer(){
        NodoCliente* temp;
        temp = inicio;

        while(temp){
            cout << "el valor en cola, id es: " << temp->id << endl;
            cout << "el valor en cola, edad es: " << temp->edad << endl;
            cout << "el valor en cola, es hombre?: " << temp->masculino << endl;
            cout << "el valor en cola, esta embarazada?: " << temp->embarazada << "\n"<< endl;
            temp = temp->siguiente;
        }
    }

};

//---------------------------------------------------------------------------------------------struct para metodos circular
struct ListaCircularClientes{

    NodoCliente* inicio;
    NodoCliente* fin;
    int size;

    ListaCircularClientes(){
        inicio = fin = NULL;
        size = 0;}

    //-------------------------------------------------------funcion vacia?

    bool vacia(){
        if (inicio==NULL){return true;}else{return false;}
    }

    //------------------------------------------------------- insertar nuevo

    void Insertar(NodoCliente* nod){
        if(vacia()){
            inicio = fin = nod;
            size++;
        }else{
        fin->siguiente = nod;
        inicio->anterior = nod;
        nod->siguiente = inicio;
        nod->anterior = fin;
        fin = fin->siguiente;
        size++;
        }
    }

    //------------------------------------------------------ extraer segun indice

    NodoCliente Extraer(int pos){
        NodoCliente* temp = new NodoCliente(-1,0,0);
        NodoCliente* prevtemp;
        prevtemp = inicio;
        temp = inicio->siguiente;
        int cont = 0;
        if(vacia()){
        cout << "Lista circular vacia" << endl;
        return *temp;}
        else {
            while(cont < size){
                if(pos == 0 && size == 1){
                    inicio = fin = NULL;
                    size--;
                    return *temp;
                    }
                else if(pos==0){
                    prevtemp->siguiente = temp->siguiente;
                    temp->siguiente->anterior = prevtemp;
                    inicio=temp;
                    size--;
                    return *temp;
                } else if(cont == pos-1){
                    prevtemp->siguiente = temp->siguiente;
                    temp->siguiente->anterior = prevtemp;
                    size--;
                    return *temp;
                }else{
                    temp = temp->siguiente;
                    prevtemp = prevtemp->siguiente;
                    cont++;}
            }
        }
    }

    //---------------------------------------------------------------- get segun pos


    NodoCliente Get(int pos){
        NodoCliente* temp;
        temp = inicio;
        int cont = 0;
        if(!vacia()){
            while(temp){
                if(cont == pos){
                return *temp;
                break;
                }else{
                temp = temp->siguiente;
                cont++;}

        }} else {cout << "La lista circular esta vacia" << endl;
        NodoCliente* err = new NodoCliente(-1, 0 ,0);
        return *err;}

        }



    //---------------------------------------------------------------- recorrer

    void Recorrer(){
        NodoCliente* temp;
        temp = inicio;
        int cont = 0;
        if(vacia()){
            cout << "La lista circular esta vacia" << endl;
        }

        cout << "tamaño " << size << endl;
        while(cont<size){
            cout << "comprando, id: " << temp->id << endl;
            cout << "carreta: " << temp->Carreta->num << "\n" << endl;
            temp = temp->siguiente;
            cont++;
        }

    }

    //------------------------------------------------------- bool caja de oro
        bool EntraAoro(NodoCliente* nod){
            if(nod->edad >= 60 ||(nod->embarazada)){
              return true;
             } else {return false;}
        }

};

#endif // ECLIENTES

