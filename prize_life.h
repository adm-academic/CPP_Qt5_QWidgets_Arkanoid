// приз, который добавляет ещё одну жизнь
#ifndef PRIZE_LIFE_H
#define PRIZE_LIFE_H

#include "prize.h"
#include <QWidget>
#include "arkanoid_state.h"

// Шаблон "State"...
class State_Prize_Life : public Arkanoid_State{
    Q_OBJECT

protected:
protected slots:
signals:

public:
    bool have_action_single();
    void action_single();
};

class Prize_Life : public Prize
{
    Q_OBJECT
public:
    Prize_Life(QWidget *parent = nullptr);

    bool with_expiration_time(); // истина если объект поддерживает таймаут действия

};

#endif // PRIZE_LIFE_H
