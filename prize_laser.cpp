#include "prize_laser.h"
#include "shoot.h"

Prize_Laser::Prize_Laser(QWidget *parent):Prize(parent)
{
    this->image.load("images/prize_laser.png");
    this->arkanoid_state = new State_Prize_Laser();

    this->antagonists_classnames << "Prize_Rocket";
}

bool Prize_Laser::with_expiration_time()
{
    return true;
}

//-----------------------------------------------------------------------------------
bool State_Prize_Laser::have_action_single()
{
    return false;
}

void State_Prize_Laser::action_enter()
{

}

void State_Prize_Laser::action_update()
{
    // при каждом вызове action_update стеляем объектом Shoot
    new Shoot(  gameframe->get_platform()->get_platform_center_top().x(),
                gameframe->get_platform()->get_platform_center_top().y(),
                gameframe );
}

void State_Prize_Laser::action_repaint()
{

}

void State_Prize_Laser::action_exit()
{

}
