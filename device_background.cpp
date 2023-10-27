#include "device_background.h"
#include <QPainter>
#include <QRandomGenerator>

Device_Background::Device_Background(QWidget *parent)
    : QWidget{parent}
{
    this->points_count  = this->width() / 2;

    this->device_timer.setInterval(100);
    connect(&this->device_timer,SIGNAL( timeout() ), \
             this, SLOT(slot_on_timer()) );
    this->device_timer.start();

}



void Device_Background::slot_on_timer(){
    this->repaint();
}

void Device_Background::paintEvent(QPaintEvent *event){
    Q_UNUSED(event);
    //setAttribute(Qt::WA_OpaquePaintEvent);
    QPainter painter(this);

    // настраиваем карандаш
    QPen pen(Qt::darkGreen);
    pen.setCapStyle(Qt::RoundCap);
    pen.setWidth(1);
    //painter.setRenderHint(QPainter::Antialiasing,true);
    painter.setPen(pen);

    //настраиваем кисть
    QBrush brush(Qt::black);
    brush.setStyle(Qt::SolidPattern);
    painter.setBrush(brush);

    // отрисовываем чёрный фон
    painter.drawRect( 0,0, this->width()-1, this->height()-1  );

    // отрисовываем пиксельный шум
    for (int i=0;i<points_count;i++){
        painter.drawPoint(QRandomGenerator::global()->bounded(0, this->width()), \
                          QRandomGenerator::global()->bounded(0, this->height())  \
                          );
    }
}
