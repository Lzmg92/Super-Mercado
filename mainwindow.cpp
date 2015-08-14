#include <iostream>
#include <stdlib.h>

#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "ecajas.h"
#include "ecarretas.h"
#include "eclientes.h"
#include "time.h"

using namespace std;


PilaCarreta* ArregloPilas[5];
ColaClientes* ColaParaCarreta = new ColaClientes();
ListaCircularClientes* DeCompras = new ListaCircularClientes();
ColaClientes* ColaParaCaja = new ColaClientes();
ColaClientes* ColaOroCaja = new ColaClientes();
ListaCajas* Cajas = new ListaCajas();
bool on = 1;
QString cons = "";
int contit = 1;

///////////////////////////////////////////////////////////////////////////////////////////////////////////// MAIN

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}



//---------------------------------------------------------------------------- insertar carretas
void InsertarNCarretas(int n){

    for(int i = 0; i < 5 ; i++){
    ArregloPilas[i] = new PilaCarreta(); }

    srand (time(NULL));

    int cont = 1;
    while(cont<=n){
      int j = rand() % 5;
      ArregloPilas[j]->Insertar(new NodoCarreta(cont));
      cons = cons + "\nCarreta "+ QString::number(cont) + " en " +  QString::number(j);

      cont++;
  }
}

//---------------------------------------------------------------------------- crear cajas

void CrearListaCajas(int n){
    for(int i = 0; i<n; i++){
        Cajas->Insertar(new NodoCaja());
        cons = cons + "\ncaja creada "+QString::number(i);
    }
}

//------------------------------------------------------------------------------Llegan N cantidad de clientes

void LleganNClientes(int n){
    srand (time(NULL));
   for(int i = 0; i<n;i++){
       int la= rand() % 73 + 18;
       int le= rand() % 2;
       int li= rand() % 2;
       ColaParaCarreta->Insertar(new NodoCliente(  la, le , li));
     //  cons = cons + "\Cliente Creado- edad "+ QString::number(la)+" hombre? "+QString::number(le)+" embarazada? "+QString::number(li);
   }
}

//------------------------------------------------------------------------------ toman carreta y acceden a lista circular

void TomarCarretaYCompar(){

    NodoCliente* temp1 = ColaParaCarreta->inicio;
    int i = 0;

            while(temp1 && (!ArregloPilas[0]->vacia() || !ArregloPilas[1]->vacia() || !ArregloPilas[2]->vacia() ||
                            !ArregloPilas[3]->vacia() || !ArregloPilas[4]->vacia())){
           if(!ArregloPilas[i]->vacia()){
            NodoCliente* temp = new NodoCliente(ColaParaCarreta->Get().edad,
                                                ColaParaCarreta->Get().masculino,
                                                ColaParaCarreta->Get().embarazada);

            int idtemp = ColaParaCarreta->Get().id;

            temp->SetId(idtemp);

            NodoCarreta* tempca = new NodoCarreta(ArregloPilas[i]->Extraer().num);
            temp->SetCarreta(tempca);
            cons = cons +"Cliente con carreta a compras "+QString::number(idtemp);

            DeCompras->Insertar(temp);
            ColaParaCarreta->Extraer();

            temp1 = temp1->siguiente;
           } else if(i<5){i++;}

        }
}

//----------------------------------------------------------------- despues de comprar pasan a cola Para caja

void PasarAColaCaja(){
     srand (time(NULL));
     int ClientesASalir = 0;

     if(!DeCompras->vacia()){
     ClientesASalir = rand() % DeCompras->size+1;}

     int cont = 0;
     cout << "---------------------- Clientes que salen"<< ClientesASalir << endl;
     while (cont < ClientesASalir && !DeCompras->vacia()){
         int IndiceASacar = rand () % DeCompras->size;

         NodoCliente* temp = new NodoCliente(DeCompras->Get(IndiceASacar).edad,
                                             DeCompras->Get(IndiceASacar).masculino,
                                             DeCompras->Get(IndiceASacar).embarazada);

         int idtemp = DeCompras->Get(IndiceASacar).id;
         temp->SetId(idtemp);

         NodoCarreta* tempca = new NodoCarreta(DeCompras->Get(IndiceASacar).GetCarreta()->num);
         temp->SetCarreta(tempca);

         int monto = rand() % 200 + 301;
         temp->SetGasto(monto);

         if(DeCompras->EntraAoro(temp)){
             ColaOroCaja->InsertarEspecial(temp);
             DeCompras->Extraer(IndiceASacar);
         }else{
             ColaParaCaja->InsertarEspecial(temp);
             DeCompras->Extraer(IndiceASacar);
         }
     cont++;
     }
}

//-------------------------------------------------------------------------------------indice de sig caja libre

int cajalibre(){
   for(int i = 0; i < Cajas->size; i++){
       if(Cajas->Get(i).libre){
           return Cajas->Get(i).numero;
           break;
       } else {return -1; break;}
       return -1;
   }
}

//------------------------------------------------------------------------------------- pasan a la caja

void PasarACaja(){
   cout << "hay libre? "<< Cajas->HayLibre()<< endl;

     NodoCliente* temp1 = ColaOroCaja->inicio;
     NodoCliente* temp2 = ColaParaCaja->inicio;

  while((Cajas->HayLibre()) && (!ColaOroCaja->vacia() || ! ColaParaCaja->vacia()) && (temp1 || temp2)){
  {     if(! ColaOroCaja->vacia()){
            NodoCliente* temp = new NodoCliente(ColaOroCaja->Get().edad,
                                            ColaOroCaja->Get().masculino,
                                            ColaOroCaja->Get().embarazada);

           int numcaja = cajalibre();

            int idtemp = ColaOroCaja->Get().id;
           temp->SetId(idtemp);

           NodoCarreta* tempca = new NodoCarreta(ColaOroCaja->Get().Carreta->num);
           temp->SetCarreta(tempca);

           int monto = ColaOroCaja->Get().Gasto;
           temp->SetGasto(monto);

           cout << "datos a insertar: edad "<< ColaOroCaja->Get().edad << " id " << ColaOroCaja->Get().id<< endl;

           Cajas->Get(numcaja).log->Insertar(temp);

           cout << "numero de nodos de caja libre "<< Cajas->Get(numcaja).numero << endl;

           Cajas->Get(numcaja).SetLibre(0);

           cout << "caja libre segun get" << Cajas->Get(numcaja).libre << endl;

           ColaOroCaja->Extraer();

        temp1 = temp1->siguiente;
        }else if (! ColaParaCaja->vacia()){
                       NodoCliente* temp = new NodoCliente(ColaParaCaja->Get().edad,
                                                           ColaParaCaja->Get().masculino,
                                                           ColaParaCaja->Get().embarazada);

                       int idtemp = ColaParaCaja->Get().id;
                       temp->SetId(idtemp);

                       NodoCarreta* tempca = new NodoCarreta(ColaParaCaja->Get().Carreta->num);
                       temp->SetCarreta(tempca);

                       int monto = ColaOroCaja->Get().Gasto;
                       temp->SetGasto(monto);

                       Cajas->GetNodoCajaLibre().log->Insertar(temp);
                       Cajas->GetNodoCajaLibre().SetLibre(false);
                       ColaParaCaja->Extraer();

                       temp2 = temp2->siguiente;
       }
 }
}
}

//------------------------------------------------------------------------------------------ se limpian los valores de la caja

void LimpiarCajas(){



    if(on){

       srand (time(NULL));
       for(int i = 1; i <= Cajas->size; i++){
           if(! Cajas->Get(i).libre){

            Cajas->Get(i).SetLibre(true);

            int din = Cajas->Get(i).GetDinero() + Cajas->Get(i).log->GetP().Gasto;
            cout << "--------------------- dinero " << din << endl;
            Cajas->Get(i).SetDinero(din);

            int carr = Cajas->Get(i).log->GetP().Carreta->num;
            int j = rand() % 5;
            ArregloPilas[j]->Insertar(new NodoCarreta(carr));
           }
       }

        on = false;}else{on = true;}
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////// GRAPH






/////////////////////////////////////////////////////////////////////// boton iniciar

void MainWindow::on_pushButton_2_clicked()
{   cons = "\n++++++++++  Paso 0 ++++++++++ ";
    QString text = ui->txtcarretas->text();
    int  i = text.toInt();
    QString text2 = ui->txtcajas->text();
    int o = text2.toInt();
    InsertarNCarretas(i);
    cons = cons + "\nIngresan -"+cons + text + "- carretas -" ;
    CrearListaCajas(o);
    "\nEl numero de cajas será: "+text2;


    ui->txtcarretas->setText("");
    ui->txtcajas->setText("");

    ui->consola->setText(cons);
}

/////////////////////////////////////////////////////////////// btn continuar

void MainWindow::on_pushButton_clicked()
{
    if(contit ==1){
    QString txt = ui->txtclientes->text();
    int a = txt.toInt();
    LleganNClientes(a);


    QString s = QString::number(contit);

    cons = cons + "\n++++++++++  Paso "+ s +"   ++++++++++";
    cons = cons + "\nLlegan -"+ txt +"- clientes y se colocan en la cola de espera";
    contit++;
    } else if(contit ==2){

        QString txt = ui->txtclientes->text();
        QString s = QString::number(contit);
        int a = txt.toInt();
        cons = cons + "\n++++++++++  Paso "+ s +"   ++++++++++";


        TomarCarretaYCompar();
        cons = cons + "\nEstan comprando "+QString::number(DeCompras->size);

        LleganNClientes(a);
        cons = cons + "\nLlegan -"+ txt +"- clientes y se colocan en la cola de espera, "+
                                         "Nueva cola de espera: "+ QString::number(ColaParaCarreta->Tsize);


        contit++;

    } else if(contit == 3){

        QString txt = ui->txtclientes->text();
        int a = txt.toInt();
        QString s = QString::number(contit);

        cons = cons + "\n++++++++++  Paso "+ s +"   ++++++++++";

        PasarAColaCaja();
        cons = cons + "\nDespues de comprar y en cola de oro: "+ QString::number(ColaOroCaja->Tsize);
        cons = cons + "\nDespues de comprar y en cola regular: "+ QString::number(ColaParaCaja->Tsize);

        TomarCarretaYCompar();
        cons = cons + "\nEstan comprando "+QString::number(DeCompras->size);

        LleganNClientes(a);
        cons = cons + "\nLlegan -"+ txt +"- clientes y se colocan en la cola de espera, "+
                                         "Nueva cola de espera: "+ QString::number(ColaParaCarreta->Tsize);



        contit++;

    } else if(contit > 3){
        QString txt = ui->txtclientes->text();
        int a = txt.toInt();
        QString s = QString::number(contit);

        cons = cons + "\n++++++++++  Paso "+ s +"   ++++++++++";
        //  LimpiarCajas();


        PasarAColaCaja();
        cons = cons + "\nDespues de comprar y en cola de oro: "+ QString::number(ColaOroCaja->Tsize);
        cons = cons + "\nDespues de comprar y en cola regular: "+ QString::number(ColaParaCaja->Tsize);

        TomarCarretaYCompar();
        cons = cons + "\nEstan comprando "+QString::number(DeCompras->size);

        LleganNClientes(a);
        cons = cons + "\nLlegan -"+ txt +"- clientes y se colocan en la cola de espera, "+
                                         "Nueva cola de espera: "+ QString::number(ColaParaCarreta->Tsize);

        contit++;

    }


    ui->txtclientes->setText("");
    ui->consola->setText(cons);
}

QString MainWindow::RecorrerP(NodoCarreta *Carr){

    QString a="";
    if(Carr && Carr->siguiente)
    {
        a.append("Carreta");
        a.append(QString::number(Carr->num));
        a.append("->");
        a.append("\n");
        return a.append(RecorrerP(Carr->siguiente));
    }
    else if(Carr)
    {

        a.append("Carreta");
        a.append(QString::number(Carr->num));
        a.append("\n");
        return a.append(RecorrerP(Carr->siguiente));

    } else{   return "";}
}


QString MainWindow::GraficarCab(PilaCarreta* pila, int num)
{
    if(pila->vacia())
    {
        QString a="";
        a.append("subgraph cluster"+QString::number(num)+"{");
        a.append("");
        a.append("\n}");

     return a;
    }
    else{
    QString a="";
    a.append("subgraph cluster"+QString::number(num)+"{");
    a.append(RecorrerP(pila->inicio));
    a.append("\n}");
    return a;
    };
}


QString MainWindow::RecorrerC(NodoCliente *Cli){

    QString a="";
    if(Cli && Cli->siguiente)
    {
        a.append("Cliente");
        a.append(QString::number(Cli->id));
        a.append("\nEdad ");
        a.append(QString::number(Cli->edad));
        a.append("\nHombre?");
        a.append(QString::number(Cli->masculino));
        a.append("->");
        a.append("\n");
        a.append(RecorrerC(Cli->siguiente));
        return a;
    }
    else if(Cli)
    {

        a.append("Cliente");
        a.append(QString::number(Cli->id));
        a.append("\nEdad ");
        a.append(QString::number(Cli->edad));
        a.append("\nHombre?");
        a.append(QString::number(Cli->masculino));
        a.append("\n");
        a.append(RecorrerC(Cli->siguiente));
        return a;
    } else{   return "";}
}




void MainWindow::on_pushButton_3_clicked()
{
    ofstream fs;
    fs.open("filedt.dot");
    cout<<"se creo el archivo"<<endl;


    fs << "digraph G {\n";
         fs << "subgraph clusterC {";
         fs <<"\nrankdir=LR";
         fs << "\nPCarretas5 [fontcolor=red fontsize=20 width=0.4 shape=box style=filled]";
         fs << "\nPCarretas4 [fontcolor=red fontsize=20 width=0.4 shape=box style=filled]";
         fs << "\nPCarretas3 [fontcolor=red fontsize=20 width=0.5 shape=box style=filled]";
         fs << "\nPCarretas2 [fontcolor=red fontsize=20 width=0.5 shape=box style=filled]";
         fs << "\nPCarretas1 [fontcolor=red fontsize=20 width=0.5 shape=box style=filled]";
         fs << "\n}";


         fs<<GraficarCab(ArregloPilas[0],1).toStdString().c_str() ;
         QString ah= "";
         ah.append("\nPCarretas1->Carreta"+QString::number(ArregloPilas[0]->inicio->num));
         fs << ah.toStdString().c_str();
         fs << "\n";

         fs<<GraficarCab(ArregloPilas[1],2).toStdString().c_str() ;
         QString ah2= "";
         ah2.append("\nPCarretas2->Carreta"+QString::number(ArregloPilas[1]->inicio->num));
         fs << ah2.toStdString().c_str();
         fs << "\n";

         fs<<GraficarCab(ArregloPilas[2],3).toStdString().c_str() ;
         QString ah3= "";
         ah3.append("\nPCarretas3->Carreta"+QString::number(ArregloPilas[2]->inicio->num));
         fs << ah3.toStdString().c_str();
         fs << "\n";

         fs<<GraficarCab(ArregloPilas[3],4).toStdString().c_str() ;
         QString ah4= "";
         ah4.append("\nPCarretas4->Carreta"+QString::number(ArregloPilas[3]->inicio->num));
         fs << ah4.toStdString().c_str();
         fs << "\n";

         fs<<GraficarCab(ArregloPilas[4],5).toStdString().c_str() ;
         QString ah5= "";
         ah5.append("\nPCarretas5->Carreta"+QString::number(ArregloPilas[4]->inicio->num));
         fs << ah5.toStdString().c_str();
         fs << "\n";



         fs << "subgraph clusterA {";
         fs << "\nColaClientes [fontcolor=red fontsize=20 width=0.4 shape=box style=filled]";
        // fs << RecorrerC(ColaParaCaja->inicio->siguiente).toStdString().c_str();
         fs << "\n}";

    fs.close();
    system("dot filedt.dot -o img.png -Tpng");
    cout<<"se compilo el archivo"<<endl;
    QPixmap img("img.png");
    ui->grafica->setPixmap(img);

}

QString MainWindow::GraphPila(PilaCarreta *pila, int numero){



    if(pila->vacia())
       {
           QString a="";
           a.append("subgraph cluster"+QString::number(numero)+"{");
           a.append("");
           a.append("\n}");

        return a;
       }
       else{
       QString a="";
       a.append("subgraph cluster"+QString::number(numero)+"{");
       a.append(RecorrerP(pila->inicio ));
       //a.append(ConectarNodos(p->cima));
       a.append("\n}");
       return a;
       }
}
