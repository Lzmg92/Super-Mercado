#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include "ecarretas.h"
#include "eclientes.h"
#include <QMainWindow>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_pushButton_2_clicked();

    void on_pushButton_clicked();

    QString GraphPila(PilaCarreta* pila, int numero);

    QString RecorrerP(NodoCarreta* Carr);

    QString RecorrerC(NodoCliente* Cli);

    QString GraficarCab(PilaCarreta* pila, int num);



    void on_pushButton_3_clicked();

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
