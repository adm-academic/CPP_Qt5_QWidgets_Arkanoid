// хранит и отображает состояние игры
#ifndef GAMESTATE_H
#define GAMESTATE_H

#include <QFrame>
#include <QLabel>
#include <QSoundEffect>
#include <QtMultimedia/QMediaPlayer>
#include <QtMultimedia/QMediaPlaylist>
#include <QMap>
#include "prize.h"
#include "device_prizes_list.h"



class GameState : public QFrame
{
    Q_OBJECT
public:
    GameState(QWidget *parent = nullptr );

    // сохраняет в прямом доступе приборы для отображения состояния игры
    void set_devices(QLabel* lb_score,   QLabel* lb_high_score,
                     QLabel* lb_level,   QLabel* lb_lifes,
                     Device_Prizes_List* device_prizes_list);

    void set_score(int value); // устанавливает значение счёта
    void add_score(int value);   // добавляет значение к счёту
    int  get_score();  // возвращает текущее значение счёта

    void set_high_score(int value);  // устанавливает значение наибольшего счёта
    void add_high_score(int value);  // добавляет значение к наибольшему счёту
    int  get_high_score();  // возвращает значение наибольшего счёта

    void set_level(int value);  // устанавливает значение уровня
    void add_level(int value); // добавляет значение к уровню
    void increment_level();  // приращивает значение уровня на единицу
    void decrement_level();  // уменьшает значение уровня на единицу
    int  get_level();  // возвращает значение уровня

    void set_lifes(int value);  // устанавливает количество жизней
    void add_lifes(int value);  // добаляет значение к количеству жизней
    int  get_lifes();  // возвращает количество жизней
    void decrement_lifes(); // уменьшает количество жизней

    void add_prize(Prize* prize);  // добавляет приз на экран прибора призов

    void game_over(); // нужно вызывать при завершении игры!

    void load_game(); /// !!!!!!!!!!!!!!!!!! загружает состояние сцены арканоида
    void unload_game(); /// !!!!!!!!!!!!!!!!! выгружает состояние сцены арканоида

    //------------------------------------------------------------------
    // все методы для проигрывания звуков вынесены в одно место
    void music_play_gaming();
    void music_play_idle();
    void sound_play_ball_lost();
    void sound_play_ball_with_block();
    void sound_play_ball_with_border();
    void sound_play_ball_with_platform();
    void sound_play_prize_caught();
    void sound_play_game_over();
    void sound_play_level_over();
    void sound_play_level_begin();
    //-------------------------------------------------------------------

protected:
    QLabel* lb_score = nullptr; // баллы, набранные  текущей сцене
    QLabel* lb_high_score = nullptr; // самый большой счёт баллов за игровую сессию
    QLabel* lb_level = nullptr; // текущий уровень игры
    QLabel* lb_lifes = nullptr; // количество жизней игрока
    Device_Prizes_List* device_prizes_list = nullptr; // прибор отображения активных призов

    QMediaPlaylist playlist; // плейлист проигрываемой музыки
    QMediaPlayer music; // медиа-плейер
    QMap<QString,QSoundEffect*> sound_effects; // словарь саундэффектов для воспроизедения звуков

    void sound_play_from_qmap(QString qmap_key,QString wav_filename);
};

#endif // GAMESTATE_H
