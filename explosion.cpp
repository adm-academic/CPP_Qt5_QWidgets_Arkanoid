#include "explosion.h"
#include <QPainter>
#include "global_widgets.h"
#include "elementar_moving_algebra.h"

Explosion::Explosion(int x_center, int y_center,
                     QWidget *parent)
    : QWidget{parent}
{
    this->current_frame_index = -1;
    this->max_frame_index = 8;
    this->animation_dir_path = "animations/explosion/";

    this->sprite_frames.resize(this->max_frame_index+1);
    for (int i=0;i<=this->max_frame_index;i++){ // заполним массив фреймов для спрайта!
        QImage frame( this->animation_dir_path +
                      "explosion" +
                      QString::number(i) +
                      ".png" );
        this->sprite_frames[i] = frame ;
    };

    this->explosion_x_center = x_center;
    this->explosion_y_center = y_center;
    this->resize(this->explosion_radius*2, this->explosion_radius*2);
    this->move( this->explosion_x_center - (this->width()/2),
                this->explosion_y_center - (this->height()/2)  );
    this->show();
    gamestate->sound_play_rocket_explosion();

    this->timer.setInterval(100);
    connect(&this->timer,SIGNAL(timeout()),
            this,SLOT(slot_animate_explosion()));
    this->timer.start();
}

Explosion::~Explosion()
{

}

void Explosion::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);
    QPainter painter(this);

    painter.drawImage( QRect(0,0,this->width(), this->height() ),
                       this->current_frame,
                       QRect(0,0,this->current_frame.width(),
                                 this->current_frame.height()
                             )
                       );
}

void Explosion::slot_animate_explosion()
{
    // листаем фреймы из вектора и помещаем текущий в объект изображения
    if ( this->current_frame_index >= this->max_frame_index ){ /// конец анимации взрыва, здесь логика взрыва
        this->timer.stop(); // остановим таймер взрыва
        this->hide(); // скроем спрайт взрыва
        delete this; // удалим объект взрыва
        return;
    }
    else if ( this->current_frame_index >= (this->max_frame_index/2)  ){
        // проверим наш взрыв на коллизии со всеми блоками на игровом поле
        // и удалим взорванные блоки
        int y_count = gameframe->get_blocks_vector().count();
        for ( int y=0; y<y_count; y++ ){
            int x_count = gameframe->get_blocks_vector()[y].count();
            for ( int x=0; x<x_count; x++ ){
                if ( gameframe->get_blocks_vector()[y][x] == nullptr ) // пропустим удалённый блок в векторе
                    continue;
                QRect explosion_rect = QRect( this->explosion_x_center - this->explosion_radius,
                                              this->explosion_y_center - this->explosion_radius,
                                              this->explosion_radius*2,
                                              this->explosion_radius*2
                                              );
                QRect block_rect = QRect( gameframe->get_blocks_vector()[y][x]->x(),
                                          gameframe->get_blocks_vector()[y][x]->y(),
                                          gameframe->get_blocks_vector()[y][x]->width(),
                                          gameframe->get_blocks_vector()[y][x]->height()
                                          );
                if ( is_rects_collision(&explosion_rect,&block_rect) ){ // проверим коллизию с текущим блоком
                    gameframe->delete_block(y,x); // удалим блок в который взрыв попал
                    if (gameframe->get_blocks_count()<=0){ // если выбили все блоки
                        this->timer.stop(); // остановим таймер взрыва
                        this->hide(); // скроем спрайт взрыва
                        gameframe->check_blocks_are_over(); // проверим на конец уровня или игры
                        delete this; // удалим объект взрыва
                        return;
                    }
                };
            };
        };
    };
    this->current_frame_index++;

    this->current_frame = this->sprite_frames[this->current_frame_index];
    this->resize(this->current_frame.width(),
                 this->current_frame.height());
    this->move( this->explosion_x_center - (this->width()/2),
                this->explosion_y_center - (this->height()/2)  );
    this->update();
}


