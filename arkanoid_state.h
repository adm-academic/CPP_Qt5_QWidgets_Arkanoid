#ifndef ARKANOID_STATE_H
#define ARKANOID_STATE_H

#include <QObject>

// Шаблон "State"...
class Arkanoid_State : public QObject{
    Q_OBJECT
public:
    virtual      ~Arkanoid_State() {}
    virtual bool have_single_action() {return false;}
    virtual void single_action() {}
    virtual void action_enter() {}
    virtual void action_update() {}
    virtual void action_repaint() {}
    virtual void action_exit() {}
protected:
protected slots:
signals:
};

#endif // ARKANOID_STATE_H
