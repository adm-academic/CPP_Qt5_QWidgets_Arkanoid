#include "prize_fast.h"
#include "global_widgets.h"

Prize_Fast::Prize_Fast(QWidget *parent)
    : Prize{parent}{
    this->image.load(":/rc/images/prize_fast.png");
}

bool Prize_Fast::with_expiration_time(){
    return true;
}

QString Prize_Fast::get_class_id(){
    return "Fast";
}

void Prize_Fast::expand_game_mechanics(){
    this->saved_deltha = gameframe->get_ball()->get_default_deltha();
    gameframe->get_ball()->set_deltha( this->saved_deltha * 2 );
}

void Prize_Fast::revert_game_mechanics(){
    gameframe->get_ball()->set_deltha( this->saved_deltha );
}

