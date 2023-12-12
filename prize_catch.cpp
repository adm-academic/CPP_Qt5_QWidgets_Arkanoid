#include "prize_catch.h"
#include <QPainter>
#include <QDateTime>
#include <QDebug>
#include <QtMath>
#include "global_widgets.h"
#include "ball.h"

Prize_Catch::Prize_Catch(QWidget *parent)
    : Prize{parent}
{
    this->image.load("images/prize_catch.png");
}



bool Prize_Catch::with_expiration_time(){
    return true;
}


void Prize_Catch::expand_game_mechanics(){
    gameframe->get_ball()->set_ball_must_be_caught(true);
}

void Prize_Catch::revert_game_mechanics(){
    gameframe->get_ball()->set_ball_must_be_caught(false);
}

void Prize_Catch::single_action_of_a_prize(){

}
