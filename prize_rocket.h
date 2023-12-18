// приз который расширяет платформу
#ifndef PRIZE_ROCKET_H
#define PRIZE_ROCKET_H

#include "prize.h"
#include <QWidget>
#include "arkanoid_state.h"

// Шаблон "State"...
class State_Prize_Rocket : public Arkanoid_State{
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
    uint rocket_launched_last_timestamp;
    const uint rockets_delay_milliseconds = 1000;
};


class Prize_Rocket : public Prize
{
    Q_OBJECT
public:
    explicit Prize_Rocket(QWidget *parent = nullptr);

    bool with_expiration_time(); // истина если объект поддерживает таймаут действия


};

#endif // PRIZE_ROCKET_H


