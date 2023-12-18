#include "prize_fast.h"
#include "global_widgets.h"

Prize_Fast::Prize_Fast(QWidget *parent)
    : Prize{parent}{
    this->image.load("images/prize_fast.png");
    this->arkanoid_state = new State_Prize_Fast();

    this->antagonists_classnames << "Prize_Slow";
}

bool Prize_Fast::with_expiration_time(){
    return true;
}

//----------------------------------------------------------------------------------

bool State_Prize_Fast::have_action_single()
{
    return false;
}

void State_Prize_Fast::action_enter()
{
    this->saved_deltha = gameframe->get_ball()->get_default_deltha();
    gameframe->get_ball()->set_deltha( this->saved_deltha * 2 );
}

void State_Prize_Fast::action_update()
{
    
}

void State_Prize_Fast::action_repaint()
{
    
}

void State_Prize_Fast::action_exit()
{
    gameframe->get_ball()->set_deltha( this->saved_deltha );
}
