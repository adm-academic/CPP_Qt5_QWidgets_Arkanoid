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
bool State_Prize_Life::have_action_single()
{
    return true;
}

void State_Prize_Life::action_single()
{
    gamestate->add_lifes( 1 );
}
