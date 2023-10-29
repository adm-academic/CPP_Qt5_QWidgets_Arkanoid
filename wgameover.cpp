#include "wgameover.h"
#include "ui_wgameover.h"

WGameOver::WGameOver(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::WGameOver)
{
    ui->setupUi(this);
}

WGameOver::~WGameOver()
{
    delete ui;
}

void WGameOver::changeEvent(QEvent* pe)
{
    if (pe->type() == QEvent::LanguageChange){
        ui->retranslateUi(this);
    };
    QWidget::changeEvent(pe);
}
