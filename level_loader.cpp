#include "level_loader.h"
#include <algorithm>
#include <QDir>
#include <QDebug>
#include "global_widgets.h"
#include "global_forms.h"

Level_Loader::Level_Loader(QObject *parent)
    : QObject{parent}
{

}


bool Level_Loader::initialize_loader(){
    this->initialized = false;
    QList<int> int_levels_indexes; // список индексов уровней игры
    QDir dir("levels/");  // объявляем объект работы с каталогами
    // прочитаем каталог с уровнями игры
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
        // заполним список с дескрипторами файлов
        Level_File_Descriptor lfd;
        lfd.csv_file = "levels/" + QString::number(basename) + ".csv";
        lfd.backround_image = "levels/" + QString::number(basename) + ".jpg";
        this->level_files_decriptors.append(lfd);
        i++;
    };

    this->first_level_number = 0; // установим первый уровень
    this->last_level_number = this->level_files_decriptors.count()-1; // установим последний уровень

    this->initialized = true; // пометим объект как инициализированный
    return true;// вернём истину
}

bool Level_Loader::is_initialized(){
    return this->initialized;
}

int Level_Loader::get_first_level_index(){
    return this->first_level_number;
}

int Level_Loader::get_last_level_index(){
    return this->last_level_number;
}

bool Level_Loader::load_level_in_gameframe(int level_index){
    if ( !this->initialized ) // объект должен быть инициализирован!
        return false;

    if ( level_index < this->first_level_number and \
         level_index > this->last_level_number ){ // выход с ошибкой если индекс не попадает в действующий диапазон
        return false;
    };

    // откроем файл указанного уровня
    QString filePath = level_files_decriptors[level_index].csv_file;
    QFile file(filePath);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
        return false;

    // прочитаем данные из CSV-файла и разобъём их по ячейкам
    QList<QStringList> data;
    QTextStream stream( &file );
    stream.setCodec("UTF-8");
    while (!stream. atEnd())
    {
        QString line = stream.readLine();
        QStringList row = line.split(',');
        data.append(row);
    }
    // закроем CSV-файл
    file.close();

    // загрузим фоновую картинку для переданного уровня
    gameframe->set_backround_image_file( level_files_decriptors[level_index].backround_image );
    gameframe->repaint();

    // обработаем дополнительную информацию об уровне!
    //qDebug() << data[0][1]; // версия формата файла
    LevelInfo li;
    li.LevelNameEn=data[1][1]; //описание уровня на английском языке
    li.LevelNameRu=data[2][1]; //описание уровня на русском языке
    wmain->show_level_info(li);

    int start_row=6;
    int start_col=0;

    // для начала определим размеры массива с данными о блоках
    int datablock_row_count = 0;
    int datablock_col_count = 0;
    for ( int row=start_row; row<data.count(); row++ ){ // перебираем строки массива данных
        datablock_col_count = 0;
        for ( int col=start_col; col<data[row].count(); col++ ){ // перебираем столбцы массива данных
            datablock_col_count++;
        };
        datablock_row_count++;
    };

    // теперь проинициализируем вектор блоков на игровом фрейме
    gameframe->reinitialize_blocks_vector_size( datablock_col_count, datablock_row_count );

    int out_row = 0; // выходная строка
    int out_col = 0; // выходной столбец
    // теперь отобразим на игровом фрейме блоки из файла
    for ( int row=start_row; row < data.count(); row++ ){
        out_col=0;
        for ( int col=start_col; col < data[row].count(); col++ ){
            if ( data[row][col] != "" )
                gameframe->append_block(out_row, out_col);
            out_col++;
        };
        out_row++;
    };
    return true;
}


