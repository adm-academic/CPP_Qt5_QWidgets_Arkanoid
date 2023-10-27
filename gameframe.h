// Класс основного игрового поля
#ifndef GAMEFRAME_H
#define GAMEFRAME_H

#include <QWidget>
#include <QFrame>
#include <QObject>
#include <QVector>
#include <QPoint>
#include <QEvent>
#include <QTimer>
#include <QImage>
#include <QtMultimedia/QMediaPlayer>
#include <QtMultimedia/QMediaPlaylist>
#include "device_prizes_list.h"


#include "block.h"
#include "ball.h"
#include "prize.h"
#include "platform.h"
#include "gamestate.h"


class GameFrame : public QFrame
{
    Q_OBJECT
public:
    GameFrame( QWidget* parent = nullptr );

    void regenerate_stars(); // заново генерирует вектор со звёздами, которые отображаются на фоне
    Platform* get_platform(); // возвращает указатель на платформу
    Ball*     get_ball(); // возвращает указатель на шарик
    void in_frame_load_scene(); // загружает сцену арканоида во фрейм
    void in_frame_unload_scene(); //выгружает сцену арканоида во фрейм
    QVector <QVector <Block*> > get_blocks_vector(); // возвращает вектор блоков
    void delete_block(int y_row, int x_col); // удаляет объект-блок из вектора и записывает nullptr; 

private:

    QVector < QPoint > stars; // вектор на координат звёзд, отобажающихся на фоне игрового фрейма
    QVector <QVector <Block*> > blocks_pointers; // двумерный вектор указателей на блоки
    QList< Prize* > game_frame_prizes;  // список летящих призов. если приз улетел вниз, то он
                             // просто удаляется из этого списка, если пойман - то
                             // переписывается в объект класса Device_Prizes_List
    QImage background_image; // фоновая картинка игрового поля
    QMediaPlaylist playlist; // плейлист проигрываемой музыки
    QMediaPlayer music; // медиа-плейер
    Platform* platform = nullptr; // указатель на объект платформы
    Ball*     ball = nullptr; // указатель на объект шарика
    bool scene_loaded=false; // истина если во фрейм загружена сцена
    QTimer game_timer; // объект игрового таймера
    void create_random_prize_at(int x, int y); // добавляет на игровое поле случайный приз
    void initialize_statically_background(); // загружает фоновую картинку для текущей сцены
    void deinitialize_statically_backround(); // очищает фоновую картинку
    void initialize_statically_blocks();// инициализирует блоки статически
    void initialize_platform();// инициализирует платформу
    void initialize_ball();// инициализирует шарик
    void deinitialize_statically_blocks();// выгружает статические блоки
    void deinitialize_platform();// выгружает платформу
    void deinitialize_ball();// выгружает шарик
    void paint_frame(); // рисует рамку вокруг игрового поля
    void play_sound_game_over(); // проигрывает звук при проигрыше
    void play_sound_game_win(); // ............. проигрывает звук при выигрыше

protected slots:
    void process_prizes_on_timer();

protected:
    void paintEvent( QPaintEvent *event );
    void resizeEvent( QResizeEvent *event );
    void keyPressEvent( QKeyEvent *event );
    void mouseMoveEvent(QMouseEvent *event);
    void mousePressEvent(QMouseEvent *event);
};

#endif // GAMEFRAME_H
