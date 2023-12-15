#include "prize_rocket.h"
#include "rocket.h"
#include <QDateTime>
#include <time.h>
#include <QTime>


Prize_Rocket::Prize_Rocket(QWidget *parent):Prize(parent)
{
    this->image.load("images/prize_rocket.png");
    this->arkanoid_state = new State_Prize_Rocket();

    this->antagonists_classnames << "Prize_Laser";
}

bool Prize_Rocket::with_expiration_time()
{
    return true;
}

//-----------------------------------------------------------------------------------

bool State_Prize_Rocket::have_action_single()
{
    return false;
}

void State_Prize_Rocket::action_enter()
{
    this->rocket_launched_last_timestamp = 0;
}

void State_Prize_Rocket::action_update()
{   // при вызове action_update запускаем ракету, но не чаще одного раза в секунду...
    uint time_deltha = ( (time(NULL) * 1000) - this->rocket_launched_last_timestamp );
    qDebug() << "###" << time_deltha;
    if ( time_deltha >= this->rockets_delay_milliseconds ){
        new Rocket( gameframe->get_platform()->get_platform_center_top().x(),
                    gameframe->get_platform()->get_platform_center_top().y(),
                    gameframe );
        this->rocket_launched_last_timestamp = (time(NULL) * 1000);
    };
}

void State_Prize_Rocket::action_repaint()
{

}

void State_Prize_Rocket::action_exit()
{

}
