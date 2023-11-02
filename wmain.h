// Главное окно приложения, содержит код главного меню и все виджеты
#ifndef WMAIN_H
#define WMAIN_H

#include <QMainWindow>
#include <QEvent>
#include <QVector2D>
#include <QFont>
#include "block.h"
#include "gameframe.h"
#include "global_widgets.h"


QT_BEGIN_NAMESPACE
namespace Ui { class WMain; }
QT_END_NAMESPACE

class WMain : public QMainWindow
{
    Q_OBJECT

public:
    WMain(QWidget *parent = nullptr);
    ~WMain();
    GameFrame* get_gameframe();
    void show_level_info(LevelInfo level_info);

protected:
    void changeEvent(QEvent* pe);
    void resizeEvent( QResizeEvent *event );


private slots:


    void on_actionLocale_triggered();

    void on_actionExit_triggered();

    void on_actionAbout_triggered();

    void on_actionSettings_Window_triggered();

    void on_actionNew_Game_triggered();

    void on_pushButton_pressed();

    void on_actionWins_Statistic_triggered();

private:
    Ui::WMain *ui;
};
#endif // WMAIN_H
