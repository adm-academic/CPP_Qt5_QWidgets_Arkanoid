#ifndef QLANGUAGE_H
#define QLANGUAGE_H

#include <QDialog>

namespace Ui {
class QLanguage;
}

class QLanguage : public QDialog
{
    Q_OBJECT

public:
    explicit QLanguage(QWidget *parent = nullptr);
    ~QLanguage();

private:
    Ui::QLanguage *ui;
};

#endif // QLANGUAGE_H
