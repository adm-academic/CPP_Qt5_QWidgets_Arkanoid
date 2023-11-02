#include "wgameover.h"
#include "ui_wgameover.h"
#include <QPainter>

WGameOver::WGameOver(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::WGameOver)
{
    ui->setupUi(this);

    this->image.load("images/game_over.jpeg");

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

void WGameOver::paintEvent(QPaintEvent *event){
    Q_UNUSED(event);
    QPainter painter(this);

    painter.drawImage( QRect(0,0,this->width(), this->height() ), \
                       this->image, \
                       QRect(0,0,this->image.width(), this->image.height()) \
                       );
}
