#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>

namespace Ui {
class Dialog;
}

class Dialog : public QDialog
{
    Q_OBJECT

public:
    explicit Dialog(QWidget *parent = 0);
    QString getNazevPily();

    int getDelkaListy();
    int getVykon();
    QString GetNazevVyrobce();
    QString GetNazevProdejny();
    QString GetUlice();
    QString GetPSC();
    QString GetTEL();
    QString GetMesto();
    void OpenTabWidget1();
    void OpenTabWidget2();
    void OpenTabWidget3();
    ~Dialog();

private:
    Ui::Dialog *ui;
};

#endif // DIALOG_H
