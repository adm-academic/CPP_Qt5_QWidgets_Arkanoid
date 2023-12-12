#ifndef PRIZE_SLOW_H
#define PRIZE_SLOW_H

#include "prize.h"
#include <QObject>
#include <QWidget>
#include "arkanoid_state.h"

// Шаблон "State"...
class State_Prize_Slow : public Arkanoid_State{
    Q_OBJECT

protected:
protected slots:
signals:

public:
    bool have_single_action();
    void action_enter();
    void action_update();
    void action_repaint();
    void action_exit();
private:
    int saved_deltha = 0;
};

class Prize_Slow : public Prize
{
    Q_OBJECT
public:
    Prize_Slow(QWidget *parent = nullptr);

    bool with_expiration_time(); // истина если объект поддерживает таймаут действия

};

#endif // PRIZE_SLOW_H
