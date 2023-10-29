#include <QPainter>
#include <QPen>
#include <QBrush>
#include <QDebug>
#include <math.h>
#include <QtMath>
#include "ball.h"
#include "gameframe.h"
#include "platform.h"
#include "elementar_moving_algebra.h"
#include "global_widgets.h"

Ball::Ball(QWidget *parent)
    : QWidget{parent}
{

    this->resize( this->ball_width, this->ball_height ); // меняем размер виджета как указано в объявлении класса

    this->image.load(":/rc/images/ball.png"); // загружаем картинку шарика в объект изобажения

    setAttribute(Qt::WA_TransparentForMouseEvents); // делаем виджет прозрачным для мышки
}



void Ball::paintEvent(QPaintEvent *event){ // отисовываем картинку на виджете
    Q_UNUSED(event);
    QPainter painter(this);

    painter.drawImage( QRect(0,0,this->width(), this->height() ), \
                       this->image, \
                       QRect(0,0,this->image.width(), this->image.height()) \
                       );

}


void Ball::ball_flying_start(){ // запускаем шарик в полёт
    gamestate->sound_play_ball_with_platform();
    this->move( this->x(), this->y() - 1); // приподнимем шарик слегка вверх
    // над платформой, чтобы он к ней не прилиал на старте
    this->ball_is_flying = true;
}

bool Ball::is_flying(){
    return this->ball_is_flying;
}

void Ball::ball_landing(){ // приземляем шарик на центр платформы
    if ( gameframe->get_platform() == nullptr ) return; // если объект платформы не создан - выходим из метода
    this->ball_is_flying = false; // останаливаем шарик
    int ball_left = gameframe->get_platform()->x() + \
                    ( gameframe->get_platform()->width() / 2 ) - \
                    ( this->width() / 2 ); // устаналиваем левую позицию шарика
    int ball_top  = gameframe->get_platform()->y() - this->height(); // устаналиаем верхнюю позицию шарика
    this->ball_angle = this->default_angle;
    this->move( ball_left, ball_top ); // перемещаем виджет шарика
}


void Ball::fly_to_next_position(){ // просчитываем следующее положение шарика и
                                   // "перелетаем" туда.
                                   // Следующее положение шарика зависит от текущего положения,
                                   // deltha,угла и препятствий
    if (!this->ball_is_flying) return; // если шарик сейчас не летит, то выходим из метода

    // шарик перемещается вдоль по линии заданной его углом ball_angle и на расстояние deltha
    // чтобы переместить шарик нам нужно вычислить его новую позицию исходя из ball_angle и deltha
    // для начала пересчитаем ball_angle и deltha в прямоугольные координаты
    plane_polar_coorinate_f relative_dest_polar_coords;
    relative_dest_polar_coords.r = deltha; // зададим deltha
    relative_dest_polar_coords.phi = qDegreesToRadians(ball_angle); // зададим ball_angle
    plane_rectanular_coorinate_f relative_dest_rect_coords = \
            polar_to_rectanular( relative_dest_polar_coords ); // преобразуем наши относительные полярные координаты в относительные прямоугольные
    // мы теперь фактически получили dx,dy для сложения с текущими прямоугольными координатами
    // прибавим их к текущим прямоугольным координатам виджета и тем самым переместим
    // шарик на очередную позицию
    this->move( this->x() + relative_dest_rect_coords.x, \
                this->y() + relative_dest_rect_coords.y ); // переместим виджет по новым координатам

    this->process_collisions(); // вызываем метод обработки коллизий

}

void Ball::process_collisions(){ // обрабатываем столкновения
    if (!this->ball_is_flying) return; // если шарик сейчас не летит, то выходим из метода

    // обрабатываем столкновения со стенками игрового поля
    if ( this->x()<=0 ){// столкновение с левой стенкой
        gamestate->sound_play_ball_with_border();
        this->ball_angle = get_angle_mirror( this->ball_angle, Barrier_Type::barrier_left );
        this->move( 0,this->y() ); // поставим виджет перед стенкой, с которой он столкнулся
        return;
    }
    else if ( this->y()<=0 ) {// столкновение с верхней стенкой
        gamestate->sound_play_ball_with_border();
        this->ball_angle = get_angle_mirror( this->ball_angle, Barrier_Type::barrier_top );
        this->move( this->x(), 0 ); // поставим виджет перед стенкой, с которой он столкнулся
        return;
    }
    else if ( this->x()>=(gameframe->width()-this->width()) ){ // столкновение с правой стенкой
        gamestate->sound_play_ball_with_border();
        this->ball_angle = get_angle_mirror( this->ball_angle, Barrier_Type::barrier_right );
        this->move( gameframe->width()-this->width(), \
                    this->y() ); // поставим виджет перед стенкой, с которой он столкнулся
        return;
    }
    else if ( this->y()>gameframe->height() ){ // выход на пределы нижней стенки
        gamestate->sound_play_ball_lost();
        gamestate->decrement_lifes();
        if ( gamestate->get_lifes()<=0 ){ // завершаем игру - игрок проиграл
            gamestate->game_over();
        }
        this->ball_landing();
        return;
    }


    // обрабатываем столкновения с платформой на игровом поле
    int bottom_coordinate_value = this->y() + this->height(); // нижняя координата шарика
    int platform_left_x = gameframe->get_platform()->x(); // левая координата платформы
    int platform_right_x = gameframe->get_platform()->x() + \
                           gameframe->get_platform()->width(); // правая координата платформы
    int ball_left_x = this->x();
    int ball_right_x = this->x() + this->width();
    if ( bottom_coordinate_value >=  \
         gameframe->get_platform()->get_platform_top() )
       {// если шарик по координатам достиг верхнего края платфомы
        if ( ( ball_left_x>platform_left_x and ball_left_x<platform_right_x  ) or \
             ( ball_right_x>platform_left_x and ball_right_x<platform_right_x ) ){
            // если шарик достиг платформы левым или правым краем
            if ( this->ball_must_be_caught ){ // если мяч должен быть пойман
                this->ball_landing();
                gamestate->sound_play_ball_with_platform();
            }else{ // если мячик не нужно ловить, значит нужно отбивать
                this->ball_angle = get_angle_mirror( this->ball_angle, Barrier_Type::barrier_bottom );
                this->move( this->x() , \
                            bottom_coordinate_value - this->height()  ); // поставим виджет наверх платформы

                gamestate->sound_play_ball_with_platform();
                return;
            }
        }
    };

    // обрабатываем столкновения с блоками на игровом поле
    // для этого организуем цикл по всем блокам и с каждым блоком индивидуально
    // проверяем столкновения
    for ( int y=0; y<gameframe->get_blocks_vector().count(); y++ ){
        for ( int x=0; x<gameframe->get_blocks_vector()[0].count(); x++ ){

            if (gameframe->get_blocks_vector()[y][x]!=nullptr ){
                // подготовим позиции очередного блока и шарика
                int block_left = gameframe->get_blocks_vector()[y][x]->x();
                int block_top  = gameframe->get_blocks_vector()[y][x]->y();
                int block_right = block_left + \
                             gameframe->get_blocks_vector()[y][x]->width();
                int block_bottom = block_top + \
                             gameframe->get_blocks_vector()[y][x]->height();
                int ball_left = this->x();
                int ball_top =  this->y();
                int ball_right = ball_left + this->width();
                int ball_bottom = ball_top + this->height();
                // теперь можно проверить на пересечение шарик и текущий блок
                // > пересечение снизу блока
                if ( between(ball_top,block_top,block_bottom) ){
                    if ( between(ball_left,block_left,block_right) or \
                         between(ball_right,block_left,block_right) ){ // пересеклись снизу блока
                        this->ball_angle = get_angle_mirror( this->ball_angle, \
                                                             Barrier_Type::barrier_top ); // помеха сверху, отразим шарик от блока

                        gamestate->add_score(25);
                        gamestate->sound_play_ball_with_block();
                        gameframe->delete_block(y,x);

                    }
                }
                // > пересечение справа блока
                else if ( between(ball_left,block_left,block_right) ){
                    if ( between(ball_top,block_top,block_bottom) or \
                         between(ball_bottom,block_top,block_bottom) ){
                        this->ball_angle = get_angle_mirror( this->ball_angle, \
                                                             Barrier_Type::barrier_left ); // помеха слева, отразим шарик от блока

                        gamestate->add_score(25);
                        gamestate->sound_play_ball_with_block();
                        gameframe->delete_block(y,x);
                    }
                }
                // > пересечение сверху блока
                else if ( between(ball_bottom,block_top,block_bottom) ){
                    if ( between(ball_left,block_left,block_right) or \
                         between(ball_right,block_left,block_right) ){
                        this->ball_angle = get_angle_mirror( this->ball_angle, \
                                                             Barrier_Type::barrier_bottom ); // помеха снизу, отразим шарик от блока

                        gamestate->add_score(25);
                        gamestate->sound_play_ball_with_block();
                        gameframe->delete_block(y,x);
                    }
                }
                // > пересечение слева блока
                else if ( between(ball_right,block_left,block_right) ){
                    if ( between(ball_top,block_top,block_bottom) or \
                         between(ball_bottom,block_top,block_bottom) ){
                        this->ball_angle = get_angle_mirror( this->ball_angle, \
                                                             Barrier_Type::barrier_right ); // помеха справа, отразим шарик от блока

                        gamestate->add_score(25);
                        gamestate->sound_play_ball_with_block();
                        gameframe->delete_block(y,x);
                    }
                };
            }// закончен код коллизий с шарика с блоками
            /// ! нужно улучшить обработку коллизий, так как шарик не !
            /// ! всегда коректно отражается !
        } // end for x
    } // end for y
}



bool Ball::get_ball_must_be_caught(){
    return this->ball_must_be_caught;
}

void Ball::set_ball_must_be_caught(bool be_caught){
    this->ball_must_be_caught = be_caught;
}

int Ball::get_default_deltha(){
    return this->default_deltha;
}

void Ball::set_deltha(int deltha){
    this->deltha = deltha;
}
