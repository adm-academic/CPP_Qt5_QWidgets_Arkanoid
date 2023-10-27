// виджет для отображения фона прибора на панели
#ifndef DEVICE_BACKGROUND_H
#define DEVICE_BACKGROUND_H

#include <QWidget>
#include <QTimer>


class Device_Background : public QWidget
{
    Q_OBJECT
public:
    explicit Device_Background(QWidget *parent = nullptr);

private:
    QTimer device_timer;
protected:

    int points_count = 0;
    void paintEvent(QPaintEvent *event);
private slots:
    void slot_on_timer();
signals:

};

#endif // DEVICE_BACKGROUND_H
