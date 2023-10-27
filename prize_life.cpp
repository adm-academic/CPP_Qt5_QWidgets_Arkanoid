#include "prize_life.h"
#include <QPainter>
#include <QDateTime>
#include <QDebug>
#include <QtMath>
#include "global_widgets.h"

Prize_Life::Prize_Life(QWidget *parent)
    : Prize{parent}
{
    this->image.load(":/rc/images/prize_life.png");
}

void Prize_Life::paintEvent(QPaintEvent *event){
    Q_UNUSED(event);
    QPainter painter(this);

    painter.drawImage( QRect(0,0,this->width(), this->height() ), \
                       this->image, \
                       QRect(0,0,this->image.width(), this->image.height()) \
                       );
    this->draw_progress(painter);
}

bool Prize_Life::with_expiration_time(){
    return false;
}

QString Prize_Life::get_class_id(){
    return "Life";
}

void Prize_Life::expand_game_mechanics(){
    // этот приз не изменяет игровую механику
}

void Prize_Life::revert_game_mechanics(){
    // этот приз не изменяет игровую механику
}

void Prize_Life::single_action_of_a_prize(){
    gamestate->add_lifes( 1 );
}
