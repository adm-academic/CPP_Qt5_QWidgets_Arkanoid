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
    bool have_single_action();
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

    void expand_game_mechanics();// Расширяет игровую механику
    void revert_game_mechanics();// Возвращает  назад игровую механику
    void single_action_of_a_prize();// Добавляет приз в игру, к примеру жизнь или очки


protected:


};

#endif // PRIZE_CATCH_H
