#ifndef WWIN_H
#define WWIN_H

#include <QDialog>
#include <QImage>

namespace Ui {
class WWin;
}

class WWin : public QDialog
{
    Q_OBJECT

public:
    explicit WWin(QWidget *parent = nullptr);
    ~WWin();


protected:
    void paintEvent(QPaintEvent *event);
    void changeEvent(QEvent* pe);
    QImage image;
private:
    Ui::WWin *ui;
};

#endif // WWIN_H
