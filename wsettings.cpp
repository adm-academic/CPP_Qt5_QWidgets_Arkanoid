#include "wsettings.h"
#include "ui_wsettings.h"

WSettings::WSettings(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::WSettings)
{
    ui->setupUi(this);
}

WSettings::~WSettings()
{
    delete ui;
}

void WSettings::changeEvent(QEvent* pe)
{
    if (pe->type() == QEvent::LanguageChange){
        ui->retranslateUi(this);
    };
    QWidget::changeEvent(pe);
}
