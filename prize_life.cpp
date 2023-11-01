#include "prize_life.h"
#include <QPainter>
#include <QDateTime>
#include <QDebug>
#include <QtMath>
#include "global_widgets.h"

Prize_Life::Prize_Life(QWidget *parent)
    : Prize{parent}
{
    this->image.load("images/prize_life.png");
}


bool Prize_Life::with_expiration_time(){
    return false;
}

QString Prize_Life::get_class_id(){
    return "Life";
}

void Prize_Life::single_action_of_a_prize(){
    gamestate->add_lifes( 1 );
}
