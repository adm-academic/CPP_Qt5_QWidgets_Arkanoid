// Класс платформы, которая управляет шариком
#ifndef PLATFORM_H
#define PLATFORM_H

#include <QWidget>
#include <QImage>
#include <QPoint>
#include <QRect>



class Platform : public QWidget
{
    Q_OBJECT
public:
    explicit Platform(QWidget *parent = nullptr);

    void set_platform_pos(int position); // указываем позицию платформы в числах.
                                         // позиция автоматически корректируется
    void platform_go_left(); // переместить платформу влево
    void platform_go_right();// переместить платформу вправо
    int  get_platform_top();// получить верх платформы
    QPoint get_platform_center_top();

    int  get_width(); // получить ширину платфомы
    void set_width(int value); // установить ширину платформы

    QImage* get_image(); // получить текущую картинку платфомы
    void    set_image(QImage* img); // установить новую картинку платфомы

    QRect get_platform_full_rect(); // получить объект QRect для текущего положения платформы
    QRect get_platform_left_zone_rect(); // получить объект QRect для левого края платформы
    QRect get_platform_right_zone_rect(); // получить объект QRect для правого края платформы

protected:

    int hover = 40; // высота платформы над нижним краем игрового виджета
    int platform_width = 90; // ширина платформы
    int platform_height = 20; // высота платформы
    int platform_left = 0; // позиция платформы указывается её левым краем
    int platform_move_increment = 20; // приращение координат при движении платформы вправо-влево



    QImage* image = nullptr; // картинка платформы

    void paintEvent(QPaintEvent *event);// отрисовываем платформу
signals:

};

#endif // PLATFORM_H
