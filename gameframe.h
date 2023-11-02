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
    void load_game_scene(); // загружает сцену арканоида во фрейм
    void unload_game_scene(); // выгружает сцену арканоида из фрейма
    QVector <QVector <Block*> > get_blocks_vector(); // возвращает вектор блоков
    int  get_blocks_count(); // возвращает количество блоков на экране
    void process_level_finished(); // проверяет закончен уровень и переходит к следующему
                                             // все летящие призы на уровне исчезают
    void reinitialize_blocks_vector_size(int cols_x, int rows_y); // пересоздаём вектор, хранящий блоки
    int  get_blocks_vector_max_width(); // возвращает максимальную ширину вектора блоков
    void delete_block(int y_row, int x_col); // удаляет объект-блок из вектора и записывает nullptr;
    void append_block(int y_row, int x_col); // добавляет объект-блок в вектор, для начала одного
                                             // и того-же цвета, в дальнейшем нужно сделать
                                             // загрузку блока указанного цвета
    void set_backround_image_file(QString image_filename); // устанавливает новую
                                             // фоновую картинку из указанного файла
    void set_neutral_background(); // устанавливает нейтральный фон
    void clear_blocks(); // очищает блоки и удаляет их с экрана


private:

    QVector < QPoint > stars; // вектор на координат звёзд, отобажающихся на фоне игрового фрейма
    QVector <QVector <Block*> > blocks_pointers; // двумерный вектор указателей на блоки
    const int blocks_begin_x = 15; // начало вывода блоков по гоизонтали
    const int blocks_begin_y = 15; // начало вывода блоков по вертикали
    QList< Prize* > game_frame_prizes;  // список летящих призов. если приз улетел вниз, то он
                             // просто удаляется из этого списка, если пойман - то
                             // переписывается в объект класса Device_Prizes_List
    QImage background_image; // фоновая картинка игрового поля
    Platform* platform = nullptr; // указатель на объект платформы
    Ball*     ball = nullptr; // указатель на объект шарика
    bool scene_loaded=false; // истина если во фрейм загружена сцена
    QTimer game_timer; // объект игрового таймера
    void create_random_prize_at(int x, int y); // добавляет на игровое поле случайный приз
    void initialize_platform();// инициализирует платформу
    void initialize_ball();// инициализирует шарик
    void deinitialize_platform();// выгружает платформу
    void deinitialize_ball();// выгружает шарик
    void paint_frame(); // рисует рамку вокруг игрового поля
    void delete_all_flying_prizes(); // удаляет все падающие в данный момент призы


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
