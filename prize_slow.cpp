#include "prize_slow.h"
#include "global_widgets.h"

Prize_Slow::Prize_Slow(QWidget *parent)
    : Prize{parent}{
    this->image.load("images/prize_slow.png");
}

bool Prize_Slow::with_expiration_time(){
    return true;
}

QString Prize_Slow::get_class_id(){
    return "Slow";
}

void Prize_Slow::expand_game_mechanics(){
    this->saved_deltha = gameframe->get_ball()->get_default_deltha();
    gameframe->get_ball()->set_deltha( this->saved_deltha / 2 );
}

void Prize_Slow::revert_game_mechanics(){
    gameframe->get_ball()->set_deltha( this->saved_deltha );
}

