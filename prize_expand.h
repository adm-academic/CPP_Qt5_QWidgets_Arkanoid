// приз который расширяет платформу
#ifndef PRIZE_EXPAND_H
#define PRIZE_EXPAND_H

#include "prize.h"
#include <QWidget>
#include "arkanoid_state.h"

// Шаблон "State"...
class State_Prize_Expand : public Arkanoid_State{
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
protected:
    int stored_width; // здесь храним оригинальную ширину платформы
    QImage* stored_original_image; // здесь храним оригинальную картинку платформы
    QImage* stored_prize_image; // картинка призового эффекта платформы
};


class Prize_Expand : public Prize
{
    Q_OBJECT
public:
    explicit Prize_Expand(QWidget *parent = nullptr);

    bool with_expiration_time(); // истина если объект поддерживает таймаут действия


};

#endif // PRIZE_EXPAND_H
