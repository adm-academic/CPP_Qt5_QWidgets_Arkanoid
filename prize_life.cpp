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
    this->arkanoid_state = new State_Prize_Life();
}


bool Prize_Life::with_expiration_time(){
    return false;
}

//----------------------------------------------------------------------------------
bool State_Prize_Life::have_single_action()
{
    return true;
}

void State_Prize_Life::single_action()
{
    gamestate->add_lifes( 1 );
}
