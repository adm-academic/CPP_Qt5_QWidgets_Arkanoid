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


void Block::initialize_block(
                      int gameframe_width, // размер игрового фрейма
                      int col_count, // количество столбцов в игровом фрейме
                      int begin_x, // X-точка начала вывода массива блоков в игровом фрейме
                      int begin_y // Y-точка начала вывода массива блоков в игровом фрейме
                             ){
    // ширина блока подстраивается под размер окна
    // и другие переменные и константы
    this->block_width =  ( ( gameframe_width - this->block_spacing ) / col_count) - \
                             this->block_spacing - (begin_x / col_count);
    // также запомним  объекте блока стартовые позиции вывода массива блоков на экран
    this->begin_x = begin_x;
    this->begin_y = begin_y;

    // меняем размер блока, применяя высчитанные величины
    this->resize( this->block_width, this->block_height );
}

int Block::get_width(){
    return this->block_width;
}

int Block::get_height(){
    return this->block_height;
}

int Block::get_spacing(){
    return this->block_spacing;
}
