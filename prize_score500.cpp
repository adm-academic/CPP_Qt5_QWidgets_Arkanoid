#include "prize_score500.h"
#include "global_widgets.h"

Prize_Score500::Prize_Score500(QWidget *parent)
    : Prize{parent}
{
    this->image.load("images/prize_score_500.png");
}


bool Prize_Score500::with_expiration_time(){
    return false;
}



void Prize_Score500::single_action_of_a_prize(){
    gamestate->add_score( 500 );
}
