#include "prize_score100.h"
#include "global_widgets.h"

Prize_Score100::Prize_Score100(QWidget *parent)
    : Prize{parent}
{
    this->image.load("images/prize_score_100.png");
    this->arkanoid_state = new State_Prize_Score100();
}


bool Prize_Score100::with_expiration_time(){
    return false;
}


//----------------------------------------------------------------------------------
bool State_Prize_Score100::have_action_single()
{
    return true;
}

void State_Prize_Score100::action_single()
{
    gamestate->add_score( 100 );
}
