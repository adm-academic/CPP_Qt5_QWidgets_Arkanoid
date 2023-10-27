#include "elementar_moving_algebra.h"
#include <math.h>


plane_polar_coorinate_f rectanular_to_polar(plane_rectanular_coorinate_f coord){
    plane_polar_coorinate_f pcf;
    pcf.r = std::sqrt( coord.x * coord.x + coord.y * coord.y );
    pcf.phi = std::atan( coord.y / coord.x );
    return pcf;
}



plane_rectanular_coorinate_f polar_to_rectanular(plane_polar_coorinate_f coord){
    plane_rectanular_coorinate_f rcf;
    rcf.x= coord.r * std::cos(coord.phi);
    rcf.y= coord.r * std::sin(coord.phi);
    return rcf;
}

int normalized_angle(int raw_angle ){
    int result_angle;
    if ( raw_angle > 360 ){ // если градус превышает 360, то приводим его в диапазон 0..360
       result_angle = raw_angle % 360;
    }
    else if ( raw_angle < 0 ){// если градус отрицательный, то приводим его в положителный диапазон 0..360
        result_angle = 360 - std::abs( ( raw_angle ) % 360 );
    }else{
        result_angle = raw_angle;
    };
    return result_angle;
}



int get_angle_mirror(int angle, Barrier_Type barrier_type){ // возвращает новый угол при столкновении с препятствием
    if (angle>360 or angle<0) // если необходимо - нормализуем угол
        angle = normalized_angle(angle);

    int first_quadrant_angle = angle % 90; // значение угла, приведенное к первому квадранту

    // вычислим квадрант угла
    int angle_quadrant = get_angle_quadrant( angle );

    // В первую очередь обработаем случаи касательного отражения вектора соответвующего нашему углу
    // всего таких случаев будет 8
    if ( angle_quadrant == 4 \
         and barrier_type==Barrier_Type::barrier_right ){
        angle = normalized_angle( angle - ( 2 * first_quadrant_angle ) );
    }
    else if ( angle_quadrant == 3 \
              and barrier_type==Barrier_Type::barrier_top ){
        angle = normalized_angle( angle - ( 2 * first_quadrant_angle ) );
    }
    else if ( angle_quadrant == 2 \
              and barrier_type==Barrier_Type::barrier_left ){
        angle = normalized_angle( angle - ( 2 * first_quadrant_angle ) );
    }
    else if ( angle_quadrant == 1 \
              and barrier_type==Barrier_Type::barrier_bottom ){
        angle = normalized_angle( angle - ( 2 * first_quadrant_angle ) );
    }
    //
    else if ( angle_quadrant == 2 \
              and barrier_type==Barrier_Type::barrier_bottom ){
        angle = normalized_angle( angle + ( 2 * first_quadrant_angle ) );
    }
    else if ( angle_quadrant == 3 \
              and barrier_type==Barrier_Type::barrier_left){
        angle = normalized_angle( angle + ( 2 * first_quadrant_angle ) );
    }
    else if ( angle_quadrant == 4 \
              and barrier_type==Barrier_Type::barrier_top ){
        angle = normalized_angle( angle + ( 2 * first_quadrant_angle ) );
    }
    else if ( angle_quadrant == 1 \
              and barrier_type==Barrier_Type::barrier_right){
        angle = normalized_angle( angle + ( 2 * first_quadrant_angle ) );
    };

    if (angle_quadrant == -1){
        if      ( angle == 90 )
            angle = 270;
        else if ( angle == 360 or angle==0 )
            angle = 180;
        else if ( angle == 270 )
            angle = 90;
        else if ( angle == 180 )
            angle = 0;
    }

    return angle;
}

int get_angle_quadrant(int angle){
    if ( angle>0  and angle<90 ) {
        return 1;
    }
    else if (angle>90 and angle<180){
        return 2;
    }
    else if (angle>180 and angle<270){
        return 3;
    }
    else if (angle>270 and angle<360){
        return 4;
    }
    else {
        return -1;
    }
}

bool between( int value, int low_param, int high_param ){
    if ( value>low_param and value<high_param ){
        return true;
    }
    else{
        return false;
    };
}
