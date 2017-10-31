#include "vyberprodejnu.h"
#include "ui_vyberprodejnu.h"
#include <QSqlQuery>
vyberprodejnu::vyberprodejnu(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::vyberprodejnu)
{
    ui->setupUi(this);
    QSqlQuery dotaz;
    dotaz.prepare("SELECT * FROM seznam_prodejen");
    dotaz.exec();
    while(dotaz.next())
    {
        ui->comboBox->insertItem(0,dotaz.value("nazev").toString(), dotaz.value("id"));
    }
}

vyberprodejnu::~vyberprodejnu()
{
    delete ui;
}

int vyberprodejnu::getIdProdejny()
{
    return ui->comboBox->currentData().toInt();
}
