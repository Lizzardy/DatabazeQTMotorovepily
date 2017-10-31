#ifndef VYBERPRODEJNU_H
#define VYBERPRODEJNU_H

#include <QDialog>

namespace Ui {
class vyberprodejnu;
}

class vyberprodejnu : public QDialog
{
    Q_OBJECT

public:
    explicit vyberprodejnu(QWidget *parent = 0);
    ~vyberprodejnu();
    int getIdProdejny();

private:
    Ui::vyberprodejnu *ui;
};



#endif // VYBERPRODEJNU_H
