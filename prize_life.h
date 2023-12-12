// приз, который добавляет ещё одну жизнь
#ifndef PRIZE_LIFE_H
#define PRIZE_LIFE_H

#include "prize.h"
#include <QWidget>


class Prize_Life : public Prize
{
    Q_OBJECT
public:
    Prize_Life(QWidget *parent = nullptr);

    bool with_expiration_time(); // истина если объект поддерживает таймаут действия

    void single_action_of_a_prize();// Добавляет приз в игру, к примеру жизнь или очки


protected:


};

#endif // PRIZE_LIFE_H
