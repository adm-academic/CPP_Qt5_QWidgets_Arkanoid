#ifndef PRIZE_SCORE100_H
#define PRIZE_SCORE100_H

#include "prize.h"
#include <QObject>
#include <QWidget>
#include "arkanoid_state.h"

// Шаблон "State"...
class State_Prize_Score100 : public Arkanoid_State{
    Q_OBJECT

protected:
protected slots:
signals:

public:
    bool have_single_action();
    void single_action();
};

class Prize_Score100 : public Prize
{
    Q_OBJECT
public:
    Prize_Score100(QWidget *parent = nullptr);

    bool with_expiration_time(); // истина если объект поддерживает таймаут действия

    void single_action_of_a_prize();// Добавляет приз в игру, к примеру жизнь или очки

};

#endif // PRIZE_SCORE100_H
