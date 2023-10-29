#include "prize_score50.h"
#include "global_widgets.h"

Prize_Score50::Prize_Score50(QWidget *parent)
    : Prize{parent}
{
    this->image.load(":/rc/images/prize_score_50.png");
}


bool Prize_Score50::with_expiration_time(){
    return false;
}

QString Prize_Score50::get_class_id(){
    return "Score50";
}

void Prize_Score50::single_action_of_a_prize(){
    gamestate->add_score( 50 );
}
