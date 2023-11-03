#include <QtDebug>
#include <QMessageBox>
#include <QPushButton>
#include <QFrame>
#include <QMessageBox>
#include <QFontDatabase>
#include "block.h"
#include "wmain.h"
#include "ui_wmain.h"
#include "global_forms.h"
#include "global_widgets.h"
#include "elementar_moving_algebra.h"
#include "gamestate.h"

WMain::WMain(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::WMain)
{
    ui->setupUi(this);
    this->setMouseTracking(true); // команда отслеживать мышь

    // проинициализируем указатели на самые важные элементы интерфейса
    gameframe=this->ui->fr_game; // на игровой фрейм
    gamestate=this->ui->fr_state; // на фрейм состояния
    // на "устройства" - то есть фреймы игровых параметров
    gamestate->set_devices( this->ui->lb_Score, this->ui->lb_HighScore, \
                            this->ui->lb_Level, this->ui->lb_Lifes, \
                            this->ui->dpl_ActivePrizes \
                           );

}

// метод для вывода информации о текущем уровне
void WMain::show_level_info(LevelInfo level_info){
    if ( app_settings.application_locale_get()=="en_US" ){
        this->level_locality = level_info.LevelNameEn;
    }
    else if ( app_settings.application_locale_get()=="ru_RU" ) {
        this->level_locality = level_info.LevelNameRu;
    };
    this->ui->statusbar->showMessage( this->level_locality );
}


void WMain::paintEvent(QPaintEvent *event){
    this->ui->statusbar->showMessage( this->level_locality );
}

WMain::~WMain()
{
    delete ui;
}

GameFrame* WMain::get_gameframe(){
    return this->ui->fr_game;
}

void WMain::resizeEvent( QResizeEvent *event ){
    Q_UNUSED(event);

}

void WMain::changeEvent(QEvent* pe)
{
    if (pe->type() == QEvent::LanguageChange){
        ui->retranslateUi(this);
    };
    QWidget::changeEvent(pe);
}


void WMain::on_actionLocale_triggered()
{
     wlanguage->exec();
}


void WMain::on_actionExit_triggered()
{
    QMessageBox::StandardButton reply;
    reply = QMessageBox::question(this, tr("Exit"), tr("Quit?"),
                                QMessageBox::Yes|QMessageBox::No);
    if (reply == QMessageBox::Yes) {
        QApplication::quit();
    };
}

void WMain::on_actionAbout_triggered()
{
    wabout->exec();
}


void WMain::on_actionSettings_Window_triggered()
{
    wsettings->exec();
}


void WMain::on_actionNew_Game_triggered()
{   // начнём игру с нулевого уровня
    QMessageBox::StandardButton reply;
    reply = QMessageBox::question(this, tr("Start the game from level zero."),
                                  tr("Reset the current game and start playing again from level zero?"),
                                QMessageBox::Yes|QMessageBox::No);
    if (reply == QMessageBox::Yes) {
        this->ui->fr_state->start_new_game();
    };
}


void WMain::on_pushButton_pressed()
{
    //gamestate->start_level_number(
    //            this->ui->comboBox->currentText().toInt()
    //           );
}



void WMain::on_actionWins_Statistic_triggered()
{
    wscorestatistic->exec();
}

