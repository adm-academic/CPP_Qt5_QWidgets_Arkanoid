#ifndef WWIN_H
#define WWIN_H

#include <QDialog>

namespace Ui {
class WWin;
}

class WWin : public QDialog
{
    Q_OBJECT

public:
    explicit WWin(QWidget *parent = nullptr);
    ~WWin();

private:
    Ui::WWin *ui;
};

#endif // WWIN_H
