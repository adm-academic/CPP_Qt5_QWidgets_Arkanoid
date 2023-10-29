#ifndef WGAMEOVER_H
#define WGAMEOVER_H

#include <QDialog>

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
    void changeEvent(QEvent* pe);
private:
    Ui::WGameOver *ui;
};

#endif // WGAMEOVER_H
