#include "shoot.h"
#include <QPainter>

Shoot::Shoot(int x_lefttop, int y_lefttop,
             QWidget *parent):
    QWidget(parent)
{
    gamestate->sound_play_shoot_laser();

    this->speed_dy = 30;
    this->setFixedSize( 10, 23 );
    this->sprite.load( "images/laser_shoot.png" );

    this->move(x_lefttop,y_lefttop);

    this->timer.setInterval(33);
    connect(&this->timer,SIGNAL(timeout()),
            this,SLOT(slot_shoot_move()));
    this->timer.start();

    this->show();
}

Shoot::~Shoot()
{

}


void Shoot::slot_shoot_move()
{
    this->move(this->x(),this->y() - this->speed_dy); // переместим выстрел на заданную дистанцию
    int y_bottom = this->y() + this->height(); // найдём координату низа спрайта выстрела
    if ( y_bottom <= 0 ){ // если вышли за пределы игрового виджета
        this->timer.stop(); // остановим таймер выстрела
        delete this; // удалим объект выстрела
        return; // выход из слота
    };
    // проверим наш выстрел на коллизии со всеми блоками на игровом поле
    int y_count = gameframe->get_blocks_vector().count();
    for ( int y=0; y<y_count; y++ ){
        int x_count = gameframe->get_blocks_vector()[y].count();
        for ( int x=0; x<x_count; x++ ){
            if ( gameframe->get_blocks_vector()[y][x] == nullptr ) // пропустим удалённый блок в векторе
                continue;
            if (is_rects_collision(this,gameframe->get_blocks_vector()[y][x])){ // если есть коллизия
                this->timer.stop(); // остановим таймер выстрела
                gamestate->sound_play_shoot_hit(); // проиграем звук
                gameframe->delete_block(y,x); // удалим блок в который выстрел попал
                this->hide(); // скроем спрайт выстрела
                delete this; // удалим объект выстрела
                gameframe->check_blocks_are_over(); // если блоки закончились - конец уровня или игры
                return; // выход из слота
            }
        }
    };
}


void Shoot::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);
    QPainter painter(this);

    painter.drawImage( QRect(0,0,this->width(), this->height() ),
                       this->sprite,
                       QRect(0,0,this->sprite.width(),
                                 this->sprite.height()
                             )
                       );
}
