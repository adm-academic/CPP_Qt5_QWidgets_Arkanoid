#include "prize_score500.h"
#include "global_widgets.h"

Prize_Score500::Prize_Score500(QWidget *parent)
    : Prize{parent}
{
    this->image.load("images/prize_score_500.png");
    this->arkanoid_state = new State_Prize_Score500();
}


bool Prize_Score500::with_expiration_time(){
    return false;
}



bool State_Prize_Score500::have_single_action()
{
    return true;
}

void State_Prize_Score500::single_action()
{
    gamestate->add_score( 500 );
}
