// приз который расширяет платформу
#ifndef PRIZE_LASER_H
#define PRIZE_LASER_H

#include "prize.h"
#include <QWidget>
#include "arkanoid_state.h"

// Шаблон "State"...
class State_Prize_Laser : public Arkanoid_State{
    Q_OBJECT

protected:
protected slots:
signals:

public:
    bool have_action_single();
    void action_enter();
    void action_update();
    void action_repaint();
    void action_exit();
protected:

};


class Prize_Laser : public Prize
{
    Q_OBJECT
public:
    explicit Prize_Laser(QWidget *parent = nullptr);

    bool with_expiration_time(); // истина если объект поддерживает таймаут действия


};

#endif // PRIZE_LASER_H
