// Класс приза. Меняет на время механику игры.
#ifndef PRIZE_H
#define PRIZE_H

#include <QWidget>
#include <QList>
#include "arkanoid_state.h"


class Prize : public QWidget
{
    Q_OBJECT
public:
    explicit Prize(QWidget *parent = nullptr );
    virtual  ~Prize();

    virtual void  set_timeout_seconds(uint timeout_value); // устанавливает
                        // таймаут жизни для объекта приза
    virtual void  reset_timeout(); // устанавливает таймаут по умолчанию
    virtual uint  get_timestamp(); // возвращает временную метку в секундах
    virtual uint  get_timer_value(); // возвращает величину таймаута в секундах
    virtual uint  get_remaining_time(); // возвращает величину таймаута в секундах
    virtual bool  actual(); // возвращает истину если объект приза до сих пор актуален
    virtual void  increment_gravity(); // сдвигает приз вниз как бы под действием гравитации
    virtual void set_drawing_progress(bool draw_progess); // устанавливаем отрисовку прогрессбара
    virtual bool get_drawing_progress(); // получаем настройку отрисовки прогрессбара

    virtual bool with_expiration_time(); // истина если объект поддерживает таймаут действия
    virtual QString get_class_name(); // возвращает текстовый идентификатор класса

    virtual Arkanoid_State* get_arkanoid_state();

    QList<QString> antagonists_classnames; // хранит список имён классов объектов-антагонистов к текущему.
                                           // это нужно для удаления всех несовместимых (антогонистов)
                                           // объектов когда пойман новый приз

protected:

    const int default_timeout = 15; // таймаут о умолчанию  секундах
    const int prize_width = 80; // ширина приза в пикселях
    const int prize_height = 30; // высота приза в пикселях
    const int increent_gravity_value = 10; // приращение при движении по экрану
    uint timeout_seconds; // значение таймаута в секундах
    uint timeout_start_timestamp; // время когда таймаут был выставлен
    bool drawing_progress=false; // отрисовывать прогрессбар в событии рисования
    QImage image; // в производных классах здесь хранится картинка приза

    void paintEvent(QPaintEvent *event); // метод в котором мы отрисовываем виджет
    virtual void draw_progress(QPainter &painter); // метод в котором мы отрисовываем прогрессбар

    Arkanoid_State* arkanoid_state = nullptr; // хранит шаблонный объект-состояние или его наследников

signals:
};

#endif // PRIZE_H
