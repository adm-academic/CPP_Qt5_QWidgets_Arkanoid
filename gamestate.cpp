#include <QGridLayout>
#include "device_background.h"
#include "gamestate.h"
#include <global_widgets.h>

GameState::GameState(QWidget *parent): QFrame{parent}
{

}

void GameState::set_devices(QLabel* lb_score,   QLabel* lb_high_score,
                 QLabel* lb_level,   QLabel* lb_lifes,
                 Device_Prizes_List* device_prizes_list){

    this->lb_score= lb_score;
    this->lb_high_score= lb_high_score;
    this->lb_level= lb_level;
    this->lb_lifes= lb_lifes;
    this->device_prizes_list= device_prizes_list;

}

void GameState::set_score(int value){
    this->lb_score->setText(QString::number(value));
}

void GameState::add_score(int value){
    this->set_score( this->get_score() + value );
}


int  GameState::get_score(){
    return this->lb_score->text().toInt();
}


void GameState::set_high_score(int value){
    this->lb_high_score->setText(QString::number(value));
}


void GameState::add_high_score(int value){
    this->set_high_score( this->get_high_score() + value  );
}


int  GameState::get_high_score(){
    return this->lb_high_score->text().toInt();
}

int  GameState::get_level(){
    return this->lb_level->text().toInt();
}

void GameState::set_level(int value){
    this->lb_level->setText(QString::number(value));
}

void GameState::add_level(int value){
    this->set_level( this->get_level() + value );
}

void GameState::increment_level(){
    this->set_level( this->get_level() + 1 );
}

void GameState::set_lifes(int value){
    this->lb_lifes->setText(QString::number(value));
}


void GameState::add_lifes(int value){
    this->set_lifes( this->get_lifes() + value );
}


int  GameState::get_lifes(){
    return this->lb_lifes->text().toInt();
}

void GameState::add_prize(Prize *prize){
    device_prizes_list->add_prize(prize); // добавим приз в прибор отобажения призов
}










void GameState::load_scene_state(){
    // !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
    // !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
}

void GameState::unload_scene_state(){
    // !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
    // !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
}

