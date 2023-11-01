// Класс исчезающих блоков
#ifndef BLOCK_H
#define BLOCK_H

#include <QWidget>
#include <QImage>


class Block : public QWidget
{
    Q_OBJECT
public:
    explicit Block(QWidget *parent = nullptr);

    // размеры блока зависят от внешних параметров, этот метод меняет размер блока в
    // зависимости от параметров внешней к блоку среды
    void initialize_block(int gameframe_width, // размер игрового фрейма
                          int col_count, // количество столбцов в игровом фрейме
                          int begin_x, // x-координата начала вывода массива блоков в игровом фрейме
                          int begin_y  // y-координата начала вывода массива блоков в игровом фрейме
                          );
    int get_width(); // возвращает ширину блока
    int get_height(); // возвращает высоту блока
    int get_spacing(); // возвращает величину пробела между блоками

protected:
    void paintEvent(QPaintEvent *event);
    QImage image; // картинка блока

    int block_height = 30; // высота блока
    int block_spacing = 5 ; // величина промежутка между блоками
    int block_width; // ширина блока, зависит от внешних параметров
    int begin_x; // х-координата начала вывода блоков на игровом фрейме
    int begin_y; // y-координата начала вывода блоков на игровом фрейме

signals:

};

#endif // BLOCK_H
