#ifndef SHOOT_H
#define SHOOT_H

#include <QObject>
#include <QWidget>
#include <QTimer>
#include "global_widgets.h"
#include "elementar_moving_algebra.h"

class Shoot : public QWidget
{
    Q_OBJECT
public:
    explicit Shoot(int x_lefttop, int y_lefttop,
                   QWidget *parent = nullptr);
    virtual ~Shoot();

protected:
    int speed_dy;
    QTimer timer;
    QImage sprite;
    void paintEvent(QPaintEvent *event) override;


protected slots:
    void slot_shoot_move();

signals:

};

#endif // SHOOT_H
