#ifndef ROCKET_H
#define ROCKET_H

#include <QObject>
#include <QWidget>
#include <QTimer>
#include "global_widgets.h"
#include "elementar_moving_algebra.h"

class Rocket : public QWidget
{
    Q_OBJECT
public:
    explicit Rocket(int x_lefttop, int y_lefttop,
                   QWidget *parent = nullptr);
    virtual ~Rocket();

protected:
    int speed_dy;
    QTimer timer;
    QImage sprite;
    void paintEvent(QPaintEvent *event) override;


protected slots:
    void slot_rocket_move();

signals:

};

#endif // ROCKET_H
