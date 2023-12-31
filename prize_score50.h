#ifndef PRIZE_SCORE50_H
#define PRIZE_SCORE50_H

#include "prize.h"
#include <QObject>
#include <QWidget>
#include "arkanoid_state.h"

// Шаблон "State"...
class State_Prize_Score50 : public Arkanoid_State{
    Q_OBJECT

protected:
protected slots:
signals:

public:
    bool have_action_single();
    void action_single();
};

class Prize_Score50 : public Prize
{
    Q_OBJECT
public:
    Prize_Score50(QWidget *parent = nullptr);

    bool with_expiration_time(); // истина если объект поддерживает таймаут действия

};

#endif // PRIZE_SCORE50_H
