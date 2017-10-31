#include "dialog.h"
#include "ui_dialog.h"

Dialog::Dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog)
{
    ui->setupUi(this);
}

Dialog::~Dialog()
{
    delete ui;
}

QString Dialog::getNazevPily()
{
    return ui->addNazevPily->text();
}



int Dialog::getDelkaListy()
{
    return ui->addDelkaListy->value();
}

int Dialog::getVykon()
{
    return ui->addVykon->value();
}

QString Dialog::GetNazevVyrobce()
{
    return ui->nazev_Vyrobce->text();
}

QString Dialog::GetNazevProdejny()
{
    return ui->addNazev->text();
}

QString Dialog::GetUlice()
{
    return ui->addUlice->text();
}

QString Dialog::GetPSC()
{
    return ui->addPSC->text();
}

QString Dialog::GetTEL()
{
    return ui->addTEL->text();
}

QString Dialog::GetMesto()
{
    return ui->addMesto->text();
}

void Dialog::OpenTabWidget1()
{
    ui->tabWidget->setCurrentIndex(0);
}

void Dialog::OpenTabWidget2()
{
    ui->tabWidget->setCurrentIndex(1);
}

void Dialog::OpenTabWidget3()
{
    ui->tabWidget->setCurrentIndex(2);
}
