#ifndef PRIZE_FAST_H
#define PRIZE_FAST_H

#include "prize.h"
#include <QObject>
#include <QWidget>
#include "arkanoid_state.h"

// Шаблон "State"...
class State_Prize_Fast : public Arkanoid_State{
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

class Prize_Fast : public Prize
{
    Q_OBJECT
public:
    Prize_Fast(QWidget *parent = nullptr);
    bool with_expiration_time(); // истина если объект поддерживает таймаут действия

};

#endif // PRIZE_FAST_H
