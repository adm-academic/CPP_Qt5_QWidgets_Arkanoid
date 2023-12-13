#include "prize_slow.h"
#include "global_widgets.h"

Prize_Slow::Prize_Slow(QWidget *parent)
    : Prize{parent}{
    this->image.load("images/prize_slow.png");
    this->arkanoid_state = new State_Prize_Slow();

    this->antagonists_classnames << "Prize_Fast";
}

bool Prize_Slow::with_expiration_time(){
    return true;
}


//----------------------------------------------------------------------------------

bool State_Prize_Slow::have_action_single()
{
    return false;
}

void State_Prize_Slow::action_enter()
{
    this->saved_deltha = gameframe->get_ball()->get_default_deltha();
    gameframe->get_ball()->set_deltha( this->saved_deltha / 2 );
}

void State_Prize_Slow::action_update()
{
    
}

void State_Prize_Slow::action_repaint()
{
    
}

void State_Prize_Slow::action_exit()
{
    gameframe->get_ball()->set_deltha( this->saved_deltha );
}
