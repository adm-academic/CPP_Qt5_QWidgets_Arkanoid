#ifndef PRIZE_FAST_H
#define PRIZE_FAST_H

#include "prize.h"
#include <QObject>
#include <QWidget>

class Prize_Fast : public Prize
{
    Q_OBJECT
public:
    Prize_Fast(QWidget *parent = nullptr);
    bool with_expiration_time(); // истина если объект поддерживает таймаут действия
    QString get_class_id(); // возвращает текстовый идентификато класса

    void expand_game_mechanics();// Расширяет игровую механику
    void revert_game_mechanics();// Возвращает  назад игровую механику
private:
    int saved_deltha = 0;
};

#endif // PRIZE_FAST_H
