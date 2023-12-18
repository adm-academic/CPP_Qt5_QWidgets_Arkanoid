#include "prize_score50.h"
#include "global_widgets.h"

Prize_Score50::Prize_Score50(QWidget *parent)
    : Prize{parent}
{
    this->image.load("images/prize_score_50.png");
    this->arkanoid_state = new State_Prize_Score50();
}


bool Prize_Score50::with_expiration_time(){
    return false;
}

//----------------------------------------------------------------------------------

bool State_Prize_Score50::have_action_single()
{
    return true;
}

void State_Prize_Score50::action_single()
{
    gamestate->add_score( 50 );
}
