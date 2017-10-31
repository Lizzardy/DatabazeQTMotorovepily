#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <QSqlTableModel>
#include <QMainWindow>
#include "dialog.h"
#include "vyberprodejnu.h"
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
    void on_pushButton_3_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_5_clicked();

    void on_pushButton_6_clicked();

    void on_pushButton_4_clicked();

    void on_pushButton_clicked();

    void on_pushButton_7_clicked();

    void on_tabWidget_currentChanged(int index);

    void on_pushButton_8_clicked();
    void nacti_prodejny();

private:
    Ui::MainWindow *ui;
    QSqlTableModel *modelVyrobci;
    QSqlTableModel *modelPily;
    QSqlTableModel *modelProdejny;
    QSqlTableModel *modelP_to_P;
    QSqlDatabase db;
    int aktualni_vyrobce;
    int aktualni_pila;
};

#endif // MAINWINDOW_H
