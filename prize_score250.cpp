#include "prize_score250.h"
#include "global_widgets.h"

Prize_Score250::Prize_Score250(QWidget *parent)
    : Prize{parent}
{
    this->image.load("images/prize_score_250.png");
    this->arkanoid_state = new State_Prize_Score250;
}


bool Prize_Score250::with_expiration_time(){
    return false;
}

//----------------------------------------------------------------------------------

bool State_Prize_Score250::have_action_single()
{
    return true;
}

void State_Prize_Score250::action_single()
{
    gamestate->add_score( 250 );
}
