#ifndef PRIZE_SLOW_H
#define PRIZE_SLOW_H

#include "prize.h"
#include <QObject>
#include <QWidget>

class Prize_Slow : public Prize
{
    Q_OBJECT
public:
    Prize_Slow(QWidget *parent = nullptr);

    bool with_expiration_time(); // истина если объект поддерживает таймаут действия

    void expand_game_mechanics();// Расширяет игровую механику
    void revert_game_mechanics();// Возвращает  назад игровую механику
private:
    int saved_deltha = 0;
};

#endif // PRIZE_SLOW_H
