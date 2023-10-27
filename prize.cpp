#include "prize.h"
#include <QPainter>
#include <QDateTime>
#include <QDebug>
#include <QtMath>

Prize::Prize(QWidget *parent)
    : QWidget{parent}
{
    this->setFixedSize(this->prize_width, this->prize_height);
    this->set_timeout_seconds(15);
    this->show();
}



void Prize::set_timeout_seconds(uint timeout_value){
    this->timeout_seconds = timeout_value;
    this->timeout_start_timestamp = QDateTime::currentDateTime().toTime_t();
}

void Prize::reset_timeout(){
    this->timeout_seconds = this->default_timeout;
    this->timeout_start_timestamp = QDateTime::currentDateTime().toTime_t();
}

uint  Prize::get_timer_value(){
    // текущая разница между последним выставлением таймаута и текущим временем
    uint time_deltha = ( QDateTime::currentDateTime().toTime_t() - this->timeout_start_timestamp  );
    uint remaining = this->timeout_seconds - time_deltha; // ЗНАЧЕНИЕ ТАЙМЕРА
    if ( remaining < 3600 )
        return remaining;
    else
        return 0;
}

uint  Prize::get_remaining_time(){
    return this->get_timer_value();
}

uint  Prize::get_timestamp(){
    return this->timeout_start_timestamp;
}

bool Prize::actual(){
    if ( this->get_timer_value() > 0 )
        return true;
    else
        return false;
}

void  Prize::increment_gravity(){
    this->move( this->x(), this->y()+this->increent_gravity_value );
}

void Prize::set_drawing_progress(bool draw_progess){
    this->drawing_progress = draw_progess;
}

bool Prize::get_drawing_progress(){
    return this->drawing_progress;
}

void Prize::paintEvent(QPaintEvent *event){
    Q_UNUSED(event);
    QPainter painter(this);

    //настраиваем кисть
    QBrush brush(Qt::green);
    brush.setStyle(Qt::SolidPattern);
    painter.setBrush(brush);

    // отрисовываем фон
    painter.drawRect( 0,0, this->width(), this->height()  );

    // отрисуем прогрессбар
    this->draw_progress(painter);
}

void Prize::draw_progress(QPainter &painter){
    if ( drawing_progress ){ // если в объекте выставлено отрисовывать прогрессбар
        // зададим кисть
        QPen pen(Qt::blue);
        pen.setWidth(3);
        painter.setPen(pen);
        // высчитаем полукуг (арку) в соответстии с таймаутом
        double one_pie_degrees = 360 / this->timeout_seconds; // минимальный кусочек дуги прогрессбара
        double current_degrees = one_pie_degrees * \
                (this->timeout_seconds - this->get_timer_value() ); // текущая длинна дуги  градусах
        // теперь нарисуем полукруг, который соотетсвует таймауту текущего объекта приза
        painter.drawArc(0+3,0+3,this->width()-6,this->height()-6,0, \
                        current_degrees * 16 );
    };
}

bool Prize::with_expiration_time(){
    return true;
}

QString Prize::get_class_id(){
    return "Abstract";
}

void Prize::expand_game_mechanics(){//по умолчанию приз не оказывает никакого дейстия на игру

}

void Prize::revert_game_mechanics(){//по умолчанию приз не оказывает никакого дейстия на игру

}

void Prize::single_action_of_a_prize(){//по умолчанию приз не оказывает никакого дейстия на игру

}
