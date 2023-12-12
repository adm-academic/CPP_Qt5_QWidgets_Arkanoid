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


void Prize_Score50::single_action_of_a_prize(){
    gamestate->add_score( 50 );
}

bool State_Prize_Score50::have_single_action()
{
    return true;
}

void State_Prize_Score50::single_action()
{
    gamestate->add_score( 50 );
}
