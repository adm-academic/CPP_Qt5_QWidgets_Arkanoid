#ifndef WGAMEOVER_H
#define WGAMEOVER_H

#include <QDialog>
#include <QImage>

namespace Ui {
class WGameOver;
}

class WGameOver : public QDialog
{
    Q_OBJECT

public:
    explicit WGameOver(QWidget *parent = nullptr);
    ~WGameOver();
protected:
    void paintEvent(QPaintEvent *event);
    void changeEvent(QEvent* pe);
    QImage image;
private:
    Ui::WGameOver *ui;
};

#endif // WGAMEOVER_H
