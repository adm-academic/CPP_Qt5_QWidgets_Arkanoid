// Приз который делает платформу липкой и заставляет её ловить мяч а не отбивать
#ifndef PRIZE_CATCH_H
#define PRIZE_CATCH_H

#include "prize.h"
#include <QWidget>
#include "arkanoid_state.h"

// Шаблон "State"...
class State_Prize_Catch : public Arkanoid_State{
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
};


class Prize_Catch : public Prize
{
    Q_OBJECT
public:
    Prize_Catch(QWidget *parent = nullptr);

    bool with_expiration_time(); // истина если объект поддерживает таймаут действия


protected:


};

#endif // PRIZE_CATCH_H
