#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "dialog.h"
#include <QSqlQuery>
#include <QItemSelectionModel>
#include <QMessageBox>
#include <QDebug>
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("../DbaProjec/motorovepily.db");
    db.open();
    modelVyrobci = new QSqlTableModel(this);
    modelVyrobci -> setTable("vyrobci");
    modelVyrobci->select();
    modelPily = new QSqlTableModel(this);
    modelPily ->setTable("pily");
    modelPily ->select();
    modelProdejny = new QSqlTableModel(this);
    modelProdejny ->setTable("seznam_prodejen");
    modelProdejny->select();

    ui->vyrobci->setModel(modelVyrobci);
    ui->vyrobci->hideColumn(0);
    ui->pily->setModel(modelPily);
    ui->pily->hideColumn(0);
    ui->seznam_prodejen->setModel(modelProdejny);
    ui->seznam_prodejen->hideColumn(0);

    ui->seznam_prodejen->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->pily->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->vyrobci->setSelectionBehavior(QAbstractItemView::SelectRows);
    aktualni_vyrobce=-1;

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_3_clicked()
{
    Dialog d;
    d.OpenTabWidget2();
    if(d.exec() == QDialog::Accepted)
    {
        QSqlQuery dotaz;
        dotaz.prepare("INSERT INTO pily VALUES(NULL, :nazev, :idvyrobce, :vykon, :delkalisty)");
        dotaz.bindValue(":nazev", d.getNazevPily());
        dotaz.bindValue(":idvyrobce", aktualni_vyrobce);
        dotaz.bindValue(":vykon", d.getVykon());
        dotaz.bindValue(":delkalisty", d.getDelkaListy());
        dotaz.exec();
        modelPily->select();
    }
}

void MainWindow::on_pushButton_2_clicked()
{
    Dialog d;
    d.OpenTabWidget1();
    if(d.exec() == QDialog::Accepted)
    {

        QSqlQuery dotaz;
        dotaz.prepare("INSERT INTO vyrobci VALUES(NULL, :nazev)");
        dotaz.bindValue(":nazev", d.GetNazevVyrobce());
        dotaz.exec();
        modelVyrobci->select();
     }
}

void MainWindow::on_pushButton_5_clicked()
{
    Dialog d;
    d.OpenTabWidget3();
    if(d.exec() == QDialog::Accepted)
    {
        QSqlQuery dotaz;
        dotaz.prepare("INSERT INTO seznam_prodejen VALUES(NULL, :nazev, :mesto, :ulice, :PSC, :TEL)");
        dotaz.bindValue(":nazev", d.GetNazevProdejny());
        dotaz.bindValue(":mesto", d.GetMesto());
        dotaz.bindValue(":ulice", d.GetUlice());
        dotaz.bindValue(":PSC", d.GetPSC());
        dotaz.bindValue(":TEL", d.GetTEL());
        dotaz.exec();

        modelProdejny->select();

    }
}

void MainWindow::on_pushButton_6_clicked()
{
    QItemSelectionModel *selection = ui->seznam_prodejen->selectionModel();
    QString sql = "DELETE FROM seznam_prodejen WHERE id IN (";
    for(int i = 0; i<selection->selectedRows().count(); ++i)
    {
        QModelIndex index = selection->selectedRows().at(i);
        sql+= QString::number(modelProdejny->data(index).toInt());
        if(i+1 != selection->selectedRows().count())
        {
            sql+=", ";
        }
    }
    sql+=")";
    QSqlQuery dotaz;
    dotaz.prepare(sql);
    dotaz.exec();
    modelProdejny->select();

}

void MainWindow::on_pushButton_4_clicked()
{
    QItemSelectionModel *selection = ui->pily->selectionModel();
    QString sql = "DELETE FROM pily WHERE id IN (";
    for(int i = 0; i<selection->selectedRows().count(); ++i)
    {
        QModelIndex index = selection->selectedRows().at(i);
        sql+= QString::number(modelPily->data(index).toInt());
        if(i+1 != selection->selectedRows().count())
        {
            sql+=", ";
        }
    }
    sql+=")";
    QSqlQuery dotaz;
    dotaz.prepare(sql);
    dotaz.exec();

    modelPily->select();

}

void MainWindow::on_pushButton_clicked()
{
    QItemSelectionModel *selection = ui->vyrobci->selectionModel();
    QString sql = "DELETE FROM vyrobci WHERE id IN (";
    for(int i = 0; i<selection->selectedRows().count(); ++i)
    {
        QModelIndex index = selection->selectedRows().at(i);
        sql+= QString::number(modelVyrobci->data(index).toInt());
        if(i+1 != selection->selectedRows().count())
        {
            sql+=", ";
        }
    }
    sql+=")";
    QSqlQuery dotaz;
    dotaz.prepare(sql);
    dotaz.exec();
    modelVyrobci->select();
}

void MainWindow::on_pushButton_7_clicked()
{
    QItemSelectionModel *selection = ui->vyrobci->selectionModel();
    if(selection->selectedRows().count() == 0)
    {
        QMessageBox::warning(this, "Chyba", "Nevybral jsi žádný řádek");
        return;
    }
    aktualni_vyrobce = modelVyrobci->data(selection->selectedRows()[0]).toInt();
    ui->tabWidget->setCurrentIndex(1);
}

void MainWindow::on_tabWidget_currentChanged(int index)
{

    if(index == 1)
    {
        if(aktualni_vyrobce == -1)
        {
            QMessageBox::warning(this, "Chyba", "Nevybral jsi žádný řádek");
            ui->tabWidget->setCurrentIndex(0);
            return;
        }
        QSqlQuery dotaz;
        dotaz.prepare("SELECT * FROM vyrobci WHERE ID=:vyrobce");
        dotaz.bindValue(":vyrobce", aktualni_vyrobce);
        dotaz.exec();
        if(!dotaz.next()) {
            QMessageBox::warning(this, "Chyba", "Nevybral jsi žádný řádek");
            ui->tabWidget->setCurrentIndex(0);
            return;
        }
        ui->label_2->setText(dotaz.value("nazev").toString());
        ui->pily->hideColumn(0);
        ui->pily->hideColumn(2);
        modelPily->setFilter("ID_vyrobce="+QString::number(aktualni_vyrobce));
        modelPily->select();

    }
}

void MainWindow::on_pushButton_8_clicked()
{
    vyberprodejnu v;
    if(v.exec() == QDialog::Accepted)
    {
        int id_prodejny = v.getIdProdejny();
        QSqlQuery dotaz;
        dotaz.prepare("INSERT INTO pily_to_prodejny VALUES (NULL, :pila, :prodejna)");
        dotaz.bindValue(":pila", aktualni_vyrobce);
        dotaz.bindValue(":prodejna", id_prodejny);
        dotaz.exec();
    }
    nacti_prodejny();
}

void MainWindow::nacti_prodejny()
{
    QSqlQuery dotaz;
    dotaz.prepare("SELECT seznam_prodejen.Nazev, seznam_prodejen.Mesto, seznam_prodejen.Ulice, seznam_prodejen.PSC, seznam_prodejen.TEL, pily_to_prodejny.id AS "
                  "id_vazby FROM pily_to_prodejny LEFT JOIN seznam_prodejen"
                  " ON id_prodjeny = seznam_prodejen.id WHERE id_pily = :vyrobce");
    dotaz.bindValue(":vyrobce", aktualni_vyrobce);
    dotaz.exec();
    ui->tableWidget->clear();
    ui->tableWidget->setRowCount(0);
    int rows = 0;
    int columns = 5;
    ui->tableWidget->setColumnCount(columns);
    QStringList hlavicky;
    hlavicky << "Id_vazby" << "Nazev" << "Mesto" << "Ulice" << "PSC" << "TEL";
    ui->tableWidget->setHorizontalHeaderLabels(hlavicky);
    ui->tableWidget->hideColumn(0);
    ui->tableWidget->setSelectionBehavior(QAbstractItemView::SelectRows);
    qDebug() << "Nacten radek";
    while(dotaz.next())
    {
        qDebug() << "Nacten radek";
        rows+=1;
        ui->tableWidget->setRowCount(rows);
        QTableWidgetItem *id;
        id = new QTableWidgetItem(dotaz.value("id_vazby").toString());
        ui->tableWidget->setItem(rows-1, 0, id);
        QTableWidgetItem *nazev;
        nazev = new QTableWidgetItem(dotaz.value("Nazev").toString());
        ui->tableWidget->setItem(rows-1, 1, nazev);
        QTableWidgetItem *mesto;
        mesto = new QTableWidgetItem(dotaz.value("Mesto").toString());
        ui->tableWidget->setItem(rows-1, 2, mesto);
        QTableWidgetItem *ulice;
        ulice = new QTableWidgetItem(dotaz.value("Ulice").toString());
        ui->tableWidget->setItem(rows-1, 3, ulice);
        QTableWidgetItem *psc;
        psc = new QTableWidgetItem(dotaz.value("PSC").toString());
        ui->tableWidget->setItem(rows-1, 4, psc);
        QTableWidgetItem *tel;
        tel = new QTableWidgetItem(dotaz.value("TEL").toString());
        ui->tableWidget->setItem(rows-1, 5, tel);
   }
}
