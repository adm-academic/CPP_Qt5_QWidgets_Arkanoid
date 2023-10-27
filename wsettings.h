// Окно "Настройки приложения"
#ifndef WSETTINGS_H
#define WSETTINGS_H

#include <QDialog>

namespace Ui {
class WSettings;
}

class WSettings : public QDialog
{
    Q_OBJECT

public:
    explicit WSettings(QWidget *parent = nullptr);
    ~WSettings();
protected:
    void changeEvent(QEvent* pe);
private:
    Ui::WSettings *ui;
};

#endif // WSETTINGS_H
