#ifndef PRIZE_SCORE500_H
#define PRIZE_SCORE500_H

#include "prize.h"
#include <QObject>
#include <QWidget>
#include "arkanoid_state.h"

// Шаблон "State"...
class State_Prize_Score500 : public Arkanoid_State{
    Q_OBJECT

protected:
protected slots:
signals:

public:
    bool have_single_action();
    void single_action();
};

class Prize_Score500 : public Prize
{
    Q_OBJECT
public:
    Prize_Score500(QWidget *parent = nullptr);

    bool with_expiration_time(); // истина если объект поддерживает таймаут действия

};

#endif // PRIZE_SCORE500_H
