#include "prize_score500.h"
#include "global_widgets.h"

Prize_Score500::Prize_Score500(QWidget *parent)
    : Prize{parent}
{
    this->image.load(":/rc/images/prize_score_500.png");
}


bool Prize_Score500::with_expiration_time(){
    return false;
}

QString Prize_Score500::get_class_id(){
    return "Score500";
}

void Prize_Score500::single_action_of_a_prize(){
    gamestate->add_score( 500 );
}
