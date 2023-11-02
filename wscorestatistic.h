#ifndef WSCORESTATISTIC_H
#define WSCORESTATISTIC_H

#include <QDialog>
#include <QStandardItemModel>
#include <QStandardItem>
#include "QtSql/QSqlDatabase"
#include <QSqlQuery>

namespace Ui {
class WScoreStatistic;
}

struct Game_Result{
    int high_score;
    int score;
};

class WScoreStatistic : public QDialog
{
    Q_OBJECT

public:
    explicit WScoreStatistic(QWidget *parent = nullptr);
    ~WScoreStatistic();

    void show_all_results(); // показать все записи из БД в экранной таблице.
    void append_new_result(Game_Result result); // добавить новую запись в БД и
                                                // обновить экранную таблицу
    void append_new_result(int high_score, int score);

protected:
    void changeEvent(QEvent* pe);
    QSqlDatabase db;
    void showEvent( QShowEvent * event );


private:
    Ui::WScoreStatistic *ui;
};

#endif // WSCORESTATISTIC_H
