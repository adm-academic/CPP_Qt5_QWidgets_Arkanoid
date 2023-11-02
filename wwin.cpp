#include "wwin.h"
#include "ui_wwin.h"
#include <QPainter>

WWin::WWin(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::WWin)
{
    ui->setupUi(this);

    this->image.load("images/game_win.jpg");
}

WWin::~WWin()
{
    delete ui;
}

void WWin::paintEvent(QPaintEvent *event){
    Q_UNUSED(event);
    QPainter painter(this);

    painter.drawImage( QRect(0,0,this->width(), this->height() ), \
                       this->image, \
                       QRect(0,0,this->image.width(), this->image.height()) \
                       );
}

void WWin::changeEvent(QEvent* pe)
{
    if (pe->type() == QEvent::LanguageChange){
        ui->retranslateUi(this);
    };
    QWidget::changeEvent(pe);
}

