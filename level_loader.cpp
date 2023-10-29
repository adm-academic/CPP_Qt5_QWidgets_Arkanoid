#include "level_loader.h"
#include <algorithm>
#include <QDir>
#include <QDebug>
#include "global_widgets.h"

Level_Loader::Level_Loader(QObject *parent)
    : QObject{parent}
{

}


bool Level_Loader::initialize_loader(){
    QList<int> int_levels_indexes; // список индексов уровней игры
    QDir dir("levels/");  // объявляем объект работы с папками
    dir.setFilter(QDir::Files | QDir::NoSymLinks);
    dir.setNameFilters(QStringList()<<"*.csv");
    foreach (QFileInfo finfo, dir.entryInfoList()){
        int_levels_indexes.append( finfo.baseName().toInt() );
    };

    std::sort(int_levels_indexes.begin(), int_levels_indexes.end()); // отсортируем имена файлов в числовом порядке

    if ( int_levels_indexes.count()<1 ) // файлы с уровнями не найдены! вернём ложь.
        return false;

    if ( !( int_levels_indexes[0]==0 and \
         int_levels_indexes.count()-1 == \
         int_levels_indexes[ int_levels_indexes.count()-1 ] ) \
         ){ // нарушен порядок и нумерация файлов в папке с уровнями,
            // завершим метод и вернём ошибку!
        return false;
    };

    // заполним список дексрипторов файлов корректными данными
    int i=0;
    foreach( int basename, int_levels_indexes ){
        if ( i != basename ){ // нарушен порядок и нумерация файлов в папке с уровнями,
                              // завершим метод и вернём ошибку!
            return false;
        }
        Level_File_Descriptor lfd;
        lfd.csv_file = "levels/" + QString::number(basename) + ".csv";
        lfd.backround_image = "levels/" + QString::number(basename) + ".jpg";
        this->level_files_decriptors.append(lfd);
        i++;
    };

    this->first_level_number = 0;
    this->last_level_number = this->level_files_decriptors.count()-1;

    return true;

}

int Level_Loader::get_first_level_index(){
    return this->first_level_number;
}

int Level_Loader::get_last_level_index(){
    return this->last_level_number;
}

bool Level_Loader::load_level(int level_index){
    // здесь загружаем уровень игры из файлов фона и CSV по его индексу
    if ( level_index < this->first_level_number and \
         level_index > this->last_level_number ){ // выход с ошибкой если индекс не попадает в действующий диапазон
        return false;
    };
    QString filePath = level_files_decriptors[level_index].csv_file;
    QFile file(filePath);
    QList<QStringList> data;

    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
        return false;

    QTextStream stream( &file );
    while (!stream. atEnd())
    {
        QString line = stream. readLine();
        QStringList row = line.split(',');
        data.append(row);
    }

    file.close();

    ///!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
    ///!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
    ///!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
    // В data находится спарсеный CSV-файл, осталось только его загрузить в игровой фрейм

    return false;
}


