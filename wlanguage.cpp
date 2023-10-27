#include "wlanguage.h"
#include "ui_wlanguage.h"
#include "global_forms.h"

WLanguage::WLanguage(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::WLanguage)
{
    ui->setupUi(this);
}

WLanguage::~WLanguage()
{
    delete ui;
}

void WLanguage::on_buttonBox_rejected()
{
    this->close();
}


void WLanguage::on_buttonBox_accepted()
{
    app_settings.load_current_config_file_locale();
    this->close();
}


void WLanguage::on_rb_en_US_toggled(bool checked)
{
    if (checked){
        app_settings.application_locale_set("en_US");
    }
}


void WLanguage::on_rb_ru_RU_toggled(bool checked)
{
    if (checked){
        app_settings.application_locale_set("ru_RU");
    }
}

void WLanguage::showEvent( QShowEvent * ){
    if ( app_settings.application_locale_get()=="en_US" )
        this->ui->rb_en_US->toggle();
    else if ( app_settings.application_locale_get()=="ru_RU" )
        this->ui->rb_ru_RU->toggle();
}

