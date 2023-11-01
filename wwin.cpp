#include "wwin.h"
#include "ui_wwin.h"

WWin::WWin(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::WWin)
{
    ui->setupUi(this);
}

WWin::~WWin()
{
    delete ui;
}
