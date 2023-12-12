#include "prize_score100.h"
#include "global_widgets.h"

Prize_Score100::Prize_Score100(QWidget *parent)
    : Prize{parent}
{
    this->image.load("images/prize_score_100.png");
}


bool Prize_Score100::with_expiration_time(){
    return false;
}


void Prize_Score100::single_action_of_a_prize(){
    gamestate->add_score( 100 );
}
