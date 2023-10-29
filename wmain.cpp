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
    gamestate->load_game();
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


void WMain::on_tb_SceneClear_pressed()
{
   this->ui->fr_game->unload_scene_in_frame();
}


void WMain::on_tb_InitScene_pressed()
{
    this->ui->fr_game->load_scene_in_frame();
    gamestate->set_lifes(3);
}

