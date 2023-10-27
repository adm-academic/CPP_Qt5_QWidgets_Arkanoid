#include <QPainter>
#include "block.h"

Block::Block(QWidget *parent)
    : QWidget{parent}
{
    this->image.load(":/rc/images/block_green.png");

    setAttribute(Qt::WA_TransparentForMouseEvents);
}




void Block::paintEvent(QPaintEvent *event){
    Q_UNUSED(event);
    QPainter painter(this);

    painter.drawImage( QRect(0,0,this->width(), this->height() ), \
                       this->image, \
                       QRect(0,0,this->image.width(), this->image.height()) \
                       );
}
