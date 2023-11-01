#include "prize_score250.h"
#include "global_widgets.h"

Prize_Score250::Prize_Score250(QWidget *parent)
    : Prize{parent}
{
    this->image.load("images/prize_score_250.png");
}


bool Prize_Score250::with_expiration_time(){
    return false;
}

QString Prize_Score250::get_class_id(){
    return "Score250";
}

void Prize_Score250::single_action_of_a_prize(){
    gamestate->add_score( 250 );
}
