#include "prize_expand.h"
#include <QPainter>
#include <QDateTime>
#include <QDebug>
#include <QtMath>
#include "global_widgets.h"
#include "platform.h"
#include "ball.h"

Prize_Expand::Prize_Expand(QWidget *parent)
    : Prize{parent}{
    this->image.load("images/prize_expand.png");
    this->arkanoid_state = new State_Prize_Expand();
}


bool Prize_Expand::with_expiration_time(){
    return true;
}

//----------------------------------------------------------------------------------

bool State_Prize_Expand::have_single_action()
{
    return false;
}

void State_Prize_Expand::action_enter()
{
    this->stored_width = gameframe->get_platform()->get_width();
    gameframe->get_platform()->set_width( gameframe->get_platform()->get_width() * 2 );

    this->stored_original_image = gameframe->get_platform()->get_image();
    this->stored_prize_image = new QImage("images/platform_expanding.png");

    gameframe->get_platform()->set_image( this->stored_prize_image );
}

void State_Prize_Expand::action_update()
{
    
}

void State_Prize_Expand::action_repaint()
{
    
}

void State_Prize_Expand::action_exit()
{
    gameframe->get_platform()->set_width( this->stored_width );
    gameframe->get_platform()->set_image( this->stored_original_image );
    if ( this->stored_prize_image != nullptr ){
        delete this->stored_prize_image;
        this->stored_prize_image = nullptr;
    };
}
