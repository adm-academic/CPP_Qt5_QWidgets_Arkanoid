#include "rocket.h"
#include <QPainter>
#include "explosion.h"


Rocket::Rocket(int x_lefttop, int y_lefttop,  QWidget *parent):
    QWidget(parent)
{
    gamestate->sound_play_rocket_launch();

    this->speed_dy = 10;
    this->setFixedSize( 15, 49 );
    this->sprite.load( "images/rocket.png" );

    this->move(x_lefttop,y_lefttop);

    this->timer.setInterval(33);
    connect(&this->timer,SIGNAL(timeout()),
            this,SLOT(slot_rocket_move()));
    this->timer.start();

    this->show();
}

Rocket::~Rocket()
{

}

void Rocket::slot_rocket_move()
{
    this->move(this->x(),this->y() - this->speed_dy); // переместим ракету на заданную дистанцию
    int y_bottom = this->y() + this->height(); // найдём координату низа спрайта ракеты
    if ( y_bottom <= 0 ){ // если вышли за пределы игрового виджета
        this->timer.stop(); // остановим таймер ракеты
        delete this; // удалим объект ракеты
        return; // выход из слота
    };
    // проверим нашу ракету на коллизии со всеми блоками на игровом поле
    int y_count = gameframe->get_blocks_vector().count();
    for ( int y=0; y<y_count; y++ ){
        int x_count = gameframe->get_blocks_vector()[y].count();
        for ( int x=0; x<x_count; x++ ){
            if ( gameframe->get_blocks_vector()[y][x] == nullptr ) // пропустим удалённый блок в векторе
                continue;
            if (is_rects_collision(this,gameframe->get_blocks_vector()[y][x])){ // если есть коллизия
                this->timer.stop(); // остановим таймер ракеты
                gamestate->sound_play_rocket_explosion(); // проиграем звук
                ///! ракета взрывает несколько блоков,
                /// создадим объект взрыва. Игровую логику он обработает сам.
                new Explosion( this->x()+(this->width()/2),
                               this->y(),
                               gameframe );
                this->hide(); // скроем объект ракеты
                delete this; // удалим объект ракеты
                return; // выход из слота
            }
        }
    };
}

void Rocket::paintEvent(QPaintEvent *event)
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


