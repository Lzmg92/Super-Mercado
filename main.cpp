#include "mainwindow.h"
#include <QApplication>
#include "ecajas.h"
#include "ecarretas.h"
#include "eclientes.h"
#include "time.h"

#include <QtCore/QString>
#include <QtCore/QFile>
#include <QtCore/QDebug>
#include <QtCore/QTextStream>


/**/




int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();


    /*

    //-------------------------------------------- nuevos clientes
    LleganNClientes(12);
    Cajas->Recorrer();
    cout << "recorrer cola para carreta:" << endl;
    ColaParaCarreta->Recorrer();
    TomarCarretaYCompar();
    //-------------------------------------------- pasan a la circular
    cout << "Pasan a comprar" << endl;
    DeCompras->Recorrer();
    cout << "Aun esperan carreta:" << endl;
    ColaParaCarreta->Recorrer();
    //-------------------------------------------- pasan a la cola de caja
    PasarAColaCaja();
    cout << "Cola Caja: " << endl;
    ColaParaCaja->Recorrer();
    cout << "Cola Oro: " << endl;
    ColaOroCaja->Recorrer();
    cout << "Aun de compras: " << endl;
    DeCompras->Recorrer();
    cout << "\n Atendidos "<< endl;
    PasarACaja();
    Cajas->Recorrer();
    //-------------------------------------------- cajas
    cout << "\n Despues de liberada "<< endl;
    LimpiarCajas();
    Cajas->Recorrer();


*/









    return a.exec();
}
