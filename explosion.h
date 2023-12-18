#ifndef EXPLOSION_H
#define EXPLOSION_H

#include <QObject>
#include <QWidget>
#include <QImage>
#include <QTimer>
#include <QList>
#include <QVector>

class Explosion : public QWidget
{
    Q_OBJECT
public:
    explicit Explosion(int x_center, int y_center,
                       QWidget *parent = nullptr);
    ~Explosion();

signals:
protected:
    const int explosion_radius = 30;
    QTimer timer;
    QVector<QImage> sprite_frames;
    QImage current_frame;
    int current_frame_index;
    int max_frame_index;
    QString animation_dir_path;
    int explosion_x_center;
    int explosion_y_center;
    void paintEvent(QPaintEvent *event) override;

protected slots:
    void slot_animate_explosion();

};

#endif // EXPLOSION_H
