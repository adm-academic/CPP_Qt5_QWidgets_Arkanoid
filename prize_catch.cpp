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
    this->arkanoid_state = new State_Prize_Catch();
}



bool Prize_Catch::with_expiration_time(){
    return true;
}


//----------------------------------------------------------------------------------

bool State_Prize_Catch::have_action_single()
{
    return false;
}

void State_Prize_Catch::action_enter()
{
    gameframe->get_ball()->set_ball_must_be_caught(true);
}

void State_Prize_Catch::action_update()
{
    
}

void State_Prize_Catch::action_repaint()
{
    
}

void State_Prize_Catch::action_exit()
{
    gameframe->get_ball()->set_ball_must_be_caught(false);
}
