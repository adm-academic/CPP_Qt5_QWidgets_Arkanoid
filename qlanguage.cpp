#include "qlanguage.h"
#include "ui_qlanguage.h"

QLanguage::QLanguage(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::QLanguage)
{
    ui->setupUi(this);
}

QLanguage::~QLanguage()
{
    delete ui;
}
