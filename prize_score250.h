#ifndef PRIZE_SCORE250_H
#define PRIZE_SCORE250_H

#include "prize.h"
#include <QObject>
#include <QWidget>

class Prize_Score250 : public Prize
{
    Q_OBJECT
public:
    Prize_Score250(QWidget *parent = nullptr);

    bool with_expiration_time(); // истина если объект поддерживает таймаут действия

    void single_action_of_a_prize();// Добавляет приз в игру, к примеру жизнь или очки


};

#endif // PRIZE_SCORE250_H
