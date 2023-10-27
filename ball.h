// Класс мячика, который отскакивает от платформы и выбивает блоки
#ifndef BALL_H
#define BALL_H

#include <QWidget>
#include <QImage>
#include <QtMultimedia/QMediaPlayer>
#include <QtMultimedia/QSoundEffect>


class Ball : public QWidget
{
    Q_OBJECT
public:
    explicit Ball(QWidget *parent = nullptr);
    void ball_landing(); // "приземляет" шарик на центр платформы
    void ball_flying_start(); // отправить шарик в полёт
    bool is_flying(); // шарик сейчас летит
    bool get_ball_must_be_caught(); // возращает истину если шарик нужно ловить платфомой
    void set_ball_must_be_caught(bool be_caught); // устаналивает флаг для поимки платформой

public slots:
    void fly_to_next_position(); // заставляет шарик "перелететь" на следующую позицию
                                 // на игровом виджете
private:
    QMediaPlayer media_player;// объект мультимедиа-плейера для проигрывания звуков
    QSoundEffect sound_effect;
    void play_sound_collision_with_platform();
    void play_sound_collision_with_border();
    void play_sound_ball_lost();
    void play_sound_collision_with_block();
    void process_collisions(); // обрабатывает столкновения шарика со всеми объектами
                              // на игровом фрейме и со стенками игрового фрейма
    bool ball_must_be_caught=false; // мячик должен быть пойман
    bool ball_is_flying=false; // истина если мячь сейчас должен лететь
    int ball_width  = 20;
    int ball_height  = 20;
    const double default_angle = 225; // по умолчанию угол полёта шарика 300 градусов
                                      // с таким углом шарик стартует с платформы
                                      // так как координаты пикселей на экране перевёрнуты
                                      // относительно декартовой системы координат, то шарик
                                      // полетит влево вверх
    double ball_angle = 225; // текущий угол полёта шарика
    int deltha = 25; // текущее приращение шарика по оси движения.
                     // фактически это скорость движения шарика
                     // ! почему изменение этого параметра меняет угол движения ?

    QImage image; //картинка шарика

protected:

    void paintEvent(QPaintEvent *event);

signals:

};

#endif // BALL_H
