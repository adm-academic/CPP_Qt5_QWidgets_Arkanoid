#include "wscorestatistic.h"
#include "ui_wscorestatistic.h"
#include "QtSql/QSqlDatabase"
#include <QSqlQuery>
#include <QDebug>
#include <QInputDialog>
#include <QtGui>


WScoreStatistic::WScoreStatistic(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::WScoreStatistic)
{
    ui->setupUi(this);

    // Подключаем базу данных в конструкторе класса
    this->db = QSqlDatabase::addDatabase("QSQLITE");
    this->db.setDatabaseName("wins_statistic.db");
    this->db.open();

}

WScoreStatistic::~WScoreStatistic()
{
    delete ui;
}


void WScoreStatistic::changeEvent(QEvent* pe)
{
    if (pe->type() == QEvent::LanguageChange){
        ui->retranslateUi(this);
    };
    QWidget::changeEvent(pe);
}


void WScoreStatistic::show_all_results(){
    // Показать все записи из БД в экранной таблице.

    // Осуществляем запрос к таблице со статистикой выигрышей
    QSqlQuery query;
    query.exec("SELECT * FROM wins_statistic order by high_score desc;");

    int query_row_counts = 0; // Qt SQlite не поддерживает метод size(),
                              // поэтому выполним запрос и проитерируем его
    while (query.next()) {
      QString gamer_name = query.value(0).toString();
      QString high_score = query.value(1).toString();
      QString win_score  = query.value(2).toString();
      query_row_counts++;
    };

    // установим верхние заголовки таблицы
    this->ui->tw_statistic->setColumnCount( 3 );
    this->ui->tw_statistic->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    QStringList headers_titles;
    headers_titles << tr("Gamer Name") << tr("*High Score*") << tr("Win Score");
    this->ui->tw_statistic->setHorizontalHeaderLabels( headers_titles );


    // установим боковые заголовки таблицы
    QStringList rows_titles;
    this->ui->tw_statistic->setRowCount( query_row_counts );
    QStringList row_titles;
    for ( int i=1; i<=query.size(); i++ ){
        row_titles.append( QString::number(i) );
    };
    this->ui->tw_statistic->setVerticalHeaderLabels( row_titles );

    // заново выполним и проитерируем запрос и выведем в таблицу данные из SQL-запроса
    query.exec("SELECT * FROM wins_statistic order by high_score desc;");
    while (query.next()) {
      QString gamer_name = query.value(0).toString();
      QString high_score = query.value(1).toString();
      QString win_score  = query.value(2).toString();

      QTableWidgetItem *item = new QTableWidgetItem(gamer_name);
      item->setFlags(item->flags() & ~Qt::ItemIsEditable);
      this->ui->tw_statistic->setItem( query.at(), 0, item );

                        item = new QTableWidgetItem(high_score);
      item->setFlags(item->flags() & ~Qt::ItemIsEditable);
      this->ui->tw_statistic->setItem( query.at(), 1, item );

                        item = new QTableWidgetItem(win_score);
      item->setFlags(item->flags() & ~Qt::ItemIsEditable);
      this->ui->tw_statistic->setItem( query.at(), 2, item );


    };
}


// добавить новую запись в БД и обновить экранную таблицу
void WScoreStatistic::append_new_result(Game_Result result){

    bool ok; // флаг успешного ввода имени игрока
    QString gamer_name = QInputDialog::getText(this,
                                 tr("Input Gamer Name For Save your Score."),
                                 tr("Gamer Name:"),
                                 QLineEdit::Normal,
                                 "",
                                 &ok); // диалог ввода имени игрока
    if (ok && !gamer_name.isEmpty()){ // если имя игрока введено успешно
        // То осуществляем вставку в таблицу со статистикой выигрышей
        QSqlQuery query;
        QString query_str = "insert into wins_statistic (gamer_name,high_score,win_score) values " + \
        QString(" ( '%1' , %2 , %3 ) ").arg(gamer_name).arg(result.high_score).arg(result.score);
        query.exec(query_str);
    };
    this->show_all_results();
}

void WScoreStatistic::append_new_result(int high_score, int score){
    Game_Result game_result;
    game_result.high_score=high_score;
    game_result.score=score;
    this->append_new_result(game_result);
}

void WScoreStatistic::showEvent( QShowEvent * event ){
    this->show_all_results();
}


