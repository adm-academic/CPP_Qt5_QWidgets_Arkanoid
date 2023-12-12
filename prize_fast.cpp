#include "prize_fast.h"
#include "global_widgets.h"

Prize_Fast::Prize_Fast(QWidget *parent)
    : Prize{parent}{
    this->image.load("images/prize_fast.png");
}

bool Prize_Fast::with_expiration_time(){
    return true;
}

void Prize_Fast::expand_game_mechanics(){
    this->saved_deltha = gameframe->get_ball()->get_default_deltha();
    gameframe->get_ball()->set_deltha( this->saved_deltha * 2 );
}

void Prize_Fast::revert_game_mechanics(){
    gameframe->get_ball()->set_deltha( this->saved_deltha );
}

