#include "prize_expand.h"
#include <QPainter>
#include <QDateTime>
#include <QDebug>
#include <QtMath>
#include "global_widgets.h"
#include "platform.h"
#include "ball.h"

Prize_Expand::Prize_Expand(QWidget *parent)
    : Prize{parent}{
    this->image.load(":/rc/images/prize_expand.png");
}


bool Prize_Expand::with_expiration_time(){
    return true;
}

QString Prize_Expand::get_class_id(){
    return "Expand";
}

void Prize_Expand::expand_game_mechanics(){
    this->stored_width = gameframe->get_platform()->get_width();
    gameframe->get_platform()->set_width( gameframe->get_platform()->get_width() * 2 );

    this->stored_original_image = gameframe->get_platform()->get_image();
    this->stored_prize_image = new QImage(":/rc/images/platform_expanding.png");

    gameframe->get_platform()->set_image( this->stored_prize_image );
}

void Prize_Expand::revert_game_mechanics(){
    gameframe->get_platform()->set_width( this->stored_width );
    gameframe->get_platform()->set_image( this->stored_original_image );
    if ( this->stored_prize_image != nullptr ){
        delete this->stored_prize_image;
        this->stored_prize_image = nullptr;
    };
}

void Prize_Expand::single_action_of_a_prize(){

}
