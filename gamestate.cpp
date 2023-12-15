#include <QGridLayout>
#include "device_background.h"
#include "gamestate.h"
#include "global_widgets.h"
#include "global_forms.h"


GameState::GameState(QWidget *parent): QFrame{parent}
{
    this->music_play_gaming();

    this->level_loader.initialize_loader(); // инициализируем объект-загрузчик уровней
}


Level_Loader* GameState::get_level_loader(){
    return &(this->level_loader);
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
    if ( this->get_score() > this->get_high_score() )
        this->set_high_score( this->get_score() );
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

void GameState::decrement_level(){
    this->set_level( this->get_level() - 1 );
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

void GameState::decrement_lifes(){
    this->set_lifes( this->get_lifes() -1 );
}

void GameState::add_prize(Prize *prize){
    device_prizes_list->check_and_add_prize(prize); // добавим приз в прибор отобажения призов
}

void GameState::prize_states_action_update()
{
    this->device_prizes_list->prize_states_action_update();
}

void GameState::prize_states_action_repaint()
{
    this->device_prizes_list->prize_states_action_repaint();
}




void GameState::reset_devices(){
    this->device_prizes_list->clear_prizes(); // очистим прибор активных призов
    this->set_score(0);
    this->set_high_score(0);
    this->set_level(0);
    this->set_lifes(0);
}


void GameState::start_new_game(){ // начинает новую игру
    gameframe->unload_game_scene();
    this->device_prizes_list->clear_prizes(); // очистим прибор активных призов
    this->set_score(0); // счёт уровня нулевой
    this->set_high_score(0); // максималный счёт нулевой
    this->set_level(0); // уровень - нулевой
    this->set_lifes(3); // жизней - три (3)
    this->start_level_number(0); //загрузим нулевой уровень в игру
    gameframe->load_game_scene();
}

void GameState::start_level_number(int level_number){// начинает игру указанного уровня
    gameframe->unload_game_scene(); // выгрузим текущую сцену из игрового фрейма
    gameframe->load_game_scene(); // загрузим новую сцену в игровой фрейм
    this->get_level_loader()->load_level_in_gameframe(  level_number ); // загрузим указанный уровень из ФС
    gameframe->load_game_scene(); // загрузим игровую сцену
    this->set_level(level_number);
    this->set_score(0);
}

void GameState::game_over(){
    this->device_prizes_list->clear_prizes(); // очистим прибор активных призов
    this->sound_play_game_over(); // проиграем звук завершения игры
    gameframe->unload_game_scene(); // выгрузим сцену из игрового фрейма
    wgameover->exec(); // покажем форму Game Over
}

void GameState::start_next_level(){
    this->device_prizes_list->clear_prizes();
    if ( this->get_level() == this->get_level_loader()->get_last_level_index() ){
        this->game_win();
    }
    else{

        this->start_level_number( this->get_level() + 1 );
    }
}

void GameState::game_win(){
    this->sound_play_game_win();

    wwin->exec();
    wscorestatistic->append_new_result(this->get_high_score(),this->get_score());
    wscorestatistic->exec();


    gameframe->unload_game_scene();
}


void GameState::music_play_gaming(){
    playlist.addMedia(QUrl("qrc:/rc/sounds/gaming.mp3"));
    playlist.setPlaybackMode(QMediaPlaylist::Loop);
    music.setPlaylist(&this->playlist);
    music.play();
}

void GameState::sound_play_from_qmap(QString qmap_key,QString wav_filename){
    if ( ! this->sound_effects.contains(qmap_key) ){
        this->sound_effects.insert(qmap_key,new QSoundEffect);
    }
    this->sound_effects[qmap_key]->setSource( QUrl::fromLocalFile( wav_filename ));
    this->sound_effects[qmap_key]->setVolume(1.0f);
    this->sound_effects[qmap_key]->play();
}


void GameState::sound_play_ball_lost(){
    sound_play_from_qmap("ball_lost","sounds/ball_lost.wav");
}

void GameState::sound_play_ball_with_block(){
    sound_play_from_qmap("ball_with_block","sounds/ball_with_block.wav");
}

void GameState::sound_play_ball_with_border(){
    sound_play_from_qmap("ball_with_border","sounds/ball_with_border.wav");
}

void GameState::sound_play_ball_with_platform(){
    sound_play_from_qmap("ball_with_platform","sounds/ball_with_platform.wav");

}

void GameState::sound_play_prize_caught(){
    sound_play_from_qmap("prize_caught","sounds/prize_caught.wav");
}

void GameState::sound_play_game_over(){
    sound_play_from_qmap("game_over","sounds/game_over.wav");
}

void GameState::sound_play_game_win(){
    sound_play_from_qmap("game_win","sounds/game_is_won.wav");
}

void GameState::sound_play_level_win(){
    sound_play_from_qmap("level_win","sounds/level_win.wav");
}

void GameState::sound_play_shoot_hit()
{
    sound_play_from_qmap("shoot_hit","sounds/shoot_hit.wav");
}

void GameState::sound_play_shoot_laser()
{
    sound_play_from_qmap("shoot_laser","sounds/shoot_laser.wav");
}

void GameState::sound_play_rocket_launch()
{
    sound_play_from_qmap("shoot_laser","sounds/rocket_launch.wav");
}

void GameState::sound_play_rocket_explosion()
{
    sound_play_from_qmap("shoot_laser","sounds/rocket_explosion.wav");
}
