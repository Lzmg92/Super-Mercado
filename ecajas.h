#ifndef ECAJAS
#define ECAJAS

#include <iostream>
#include <stdlib.h>

#include "eclientes.h"

using namespace std;

struct NodoCaja{
    NodoCaja* siguiente;
    NodoCaja* anterior;

    int numero;
    bool libre;
    NodoCliente* cliente;
    ColaClientes* log;
    int dinero;


    NodoCaja (){

        this->libre = 1;
        this->log = new ColaClientes();
        this->dinero = 0;
        siguiente = NULL;
    }

    void SetNumero(int num){
        numero = num;
    }

    void SetLibre(bool Libre){
        libre = Libre;
    }

    void SetCliente(NodoCliente* Cliente){
        cliente=Cliente;
    }

    void SetDinero(int Dinero){
        dinero= Dinero;
    }

    int GetDinero(){
        return dinero;
    }

    bool GetLibre(){
        return libre;
    }

};

// ----------------------------------------------------------------------- struct para metodos


struct ListaCajas{
 NodoCaja* inicio;
 NodoCaja* fin;
 int contnum;
 int size;

 ListaCajas(){
     inicio = fin = NULL;
     contnum = 0;
 }

 //----------------------------------------------------- vacia?
 bool vacia(){
     if (inicio==NULL){return 1;}else{return 0;}
 }

 //--------------------------------------------------- hay cajas libres?

 bool HayLibre(){
     NodoCaja* temp;
     temp = inicio;

     while(temp){
         if(temp->libre){
             return true;
             break;
         } else{
         temp = temp->siguiente;
         }
         return false;
     }
 }

 //-------------------------------------------------- insertar nuevo nodo caja

 void Insertar(NodoCaja* nod){
         if(vacia()){
             inicio = nod;
             size++;
             contnum++;
             nod->SetNumero(0);
         }  else {
             nod->siguiente = inicio;
             inicio = nod;
             nod->SetNumero(contnum);
             size++;
             contnum++;
        }
 }

 //-------------------------------------------------- obtener proxima caja libre

 NodoCaja GetNodoCajaLibre(){

     NodoCaja* temp = new NodoCaja() ;
     temp = inicio;

     while(temp){
         if (temp->libre){
             return *temp;
         } else {
         temp = temp->siguiente;
         return *temp;
     }}
 }





//--------------------------------------------------- recorrer

 void Recorrer(){
     NodoCaja* temp;
     temp = inicio;

     while(temp){
         cout << "Caja numero: " << temp->numero << endl;
         cout << "Libre? " << temp->GetLibre() << endl;
         cout << "Dinero cobrado: "<< temp->GetDinero()<< endl;
         cout << "Clientes Atendidos "<< temp->log->size << endl;
         temp = temp->siguiente;
     }
 }

 //------------------------------------------------- get n

 NodoCaja Get(int n){

     NodoCaja* temp = new NodoCaja();
     temp = inicio;
     int cont = 0;

     while(temp){
         if (cont == n){
          return *temp;
          break;
         } else {
         cont++;
         temp = temp->siguiente;
     }}
     cout << "No se encontró: "<< n << endl;
     return *temp;
 }



};

#endif // ECAJAS

