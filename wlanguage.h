// Окно "Выбор Локали"
#ifndef WLANGUAGE_H
#define WLANGUAGE_H

#include <QDialog>

namespace Ui {
class WLanguage;
}

class WLanguage : public QDialog
{
    Q_OBJECT

public:
    explicit WLanguage(QWidget *parent = nullptr);
    ~WLanguage();

private slots:
    void on_buttonBox_rejected();

    void on_buttonBox_accepted();

    void on_rb_en_US_toggled(bool checked);

    void on_rb_ru_RU_toggled(bool checked);
protected:
    void showEvent( QShowEvent * event );
private:
    Ui::WLanguage *ui;
};

#endif // WLANGUAGE_H
