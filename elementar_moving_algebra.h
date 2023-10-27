// функции для просчёта движения
#ifndef ELEMENTAR_MOVING_ALGEBRA_H
#define ELEMENTAR_MOVING_ALGEBRA_H

// дробные полярные координаты
struct plane_polar_coorinate_f{
    double r;
    double phi;
};

// дробные декартовы координаты
struct plane_rectanular_coorinate_f{
    double x;
    double y;
};

// переводит из дробных прямоугольных координат в дробные полярные координаты
plane_polar_coorinate_f rectanular_to_polar(plane_rectanular_coorinate_f coord);
// переводит из дробных полярных координат в дробные прямоугольные координаты
plane_rectanular_coorinate_f polar_to_rectanular(plane_polar_coorinate_f coord);

// нормализует угол raw_angle держа его между 0 и 360
int normalized_angle( int raw_angle );

// возвращает квадрант угла, если угол попадает на одну из осей системы координат то возвращает -1
int get_angle_quadrant(int angle);

enum class Barrier_Type{ // тип препятсвия при столкновении вектора
    barrier_top,
    barrier_left,
    barrier_bottom,
    barrier_right,
    // ... ещё нужны типы для 90 градусов и для уголков
};

int get_angle_mirror(int angle, Barrier_Type barrier_type); // возвращает новый угол при столкновении с препятствием

bool between( int value, int low_param, int high_param ); // возвращает истину если значение value
            // лежит в промежутке между low_param и high_param

#endif // ELEMENTAR_MOVING_ALGEBRA_H
