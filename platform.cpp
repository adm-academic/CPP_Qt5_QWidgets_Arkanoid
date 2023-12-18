#include <QPainter>
#include <QPen>
#include <QBrush>
#include <QDebug>
#include "platform.h"
#include "global_forms.h"
#include "gameframe.h"
#include "global_widgets.h"

Platform::Platform(QWidget *parent)
    : QWidget{parent}
{
    this->resize( this->platform_width, this->platform_height ); // зададим размер платформы
    this->set_platform_pos( (gameframe->width() / 2) - (this->width() / 2) ); // установим началную позицию платформы

    this->image = new QImage("images/platform.png");
}

int Platform::get_platform_top(){
    return gameframe->height() - ( this->platform_height + this->hover );
}

QPoint Platform::get_platform_center_top()
{
    QPoint result;
    result.setX( this->x() + ( this->width() / 2 ) );
    result.setY( this->y() );
    return result;
}

void Platform::set_platform_pos(int position){
    if ( position<0 )
    {
        this->platform_left=0;
    }
    else if ( position >( gameframe->width()-this->width() ) ){
        this->platform_left=gameframe->width()-this->width();
    }
    else{
        this->platform_left = position;
    }
    int current_platform_top = gameframe->height() - this->height() - this->hover;
    this->move( this->platform_left, current_platform_top );
    if ( gameframe->get_ball()!=nullptr ) { // если шарик инициализирован
        if ( !gameframe->get_ball()->is_flying() ){// и не летит в данный момент
            gameframe->get_ball()->ball_landing();
        };
    }
    this->repaint();
}

void Platform::platform_go_left(){
    this->set_platform_pos( this->platform_left - this->platform_move_increment );
}

void Platform::platform_go_right(){
    this->set_platform_pos( this->platform_left + this->platform_move_increment );
}


void Platform::paintEvent(QPaintEvent *event){
    Q_UNUSED(event);
    QPainter painter(this);

    painter.drawImage( QRect(0,0,this->width(), this->height() ), \
                       (*this->image), \
                       QRect(0,0,this->image->width(), this->image->height()) \
                       );
}

int  Platform::get_width(){
    return this->platform_width;
}
void Platform::set_width(int value){
    this->platform_width = value;
    this->resize( this->platform_width, this->platform_height ); // зададим размер платформы
}

QImage* Platform::get_image(){
    return this->image;
}

void    Platform::set_image(QImage* img){
    this->image = img;
}

QRect Platform::get_platform_full_rect()
{
    return QRect( this->x(), this->y(),
                  this->width(), this->height()
                );
}

QRect Platform::get_platform_left_zone_rect()
{
    return QRect( this->x(), this->y(),
                  this->width() / 4,
                  this->height()
                );
}

QRect Platform::get_platform_right_zone_rect()
{
    return QRect( this->x()+this->width() - (this->width() / 4),
                  this->y(),
                  this->width() / 4,
                  this->height()
                );
}
