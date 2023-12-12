// приз который расширяет платформу
#ifndef PRIZE_EXPAND_H
#define PRIZE_EXPAND_H

#include "prize.h"
#include <QWidget>


class Prize_Expand : public Prize
{
    Q_OBJECT
public:
    explicit Prize_Expand(QWidget *parent = nullptr);

    bool with_expiration_time(); // истина если объект поддерживает таймаут действия

    void expand_game_mechanics();// Расширяет игровую механику
    void revert_game_mechanics();// Возвращает  назад игровую механику
    void single_action_of_a_prize();// Добавляет приз в игру, к примеру жизнь или очки

protected:
    int stored_width; // здесь храним оригинальную ширину платформы
    QImage* stored_original_image; // здесь храним оригинальную картинку платформы
    QImage* stored_prize_image; // картинка призового эффекта платформы

};

#endif // PRIZE_EXPAND_H
