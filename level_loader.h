#ifndef LEVEL_LOADER_H
#define LEVEL_LOADER_H
#include <QObject>
#include <QVector>
#include <QMap>
#include <QList>

struct Level_File_Descriptor{ // дескриптор файлов уровней
    QString csv_file; // имя файла с данными
    QString backround_image; // имя фоновой картинки
};

class Level_Loader : public QObject
{
    Q_OBJECT
public:
    explicit Level_Loader(QObject *parent = nullptr);
    bool initialize_loader(); // инициализирует объект-загрузчик уровней
                       // возвращает истину если количество уровней папке правильное, и ошибки нет
                       // если есть ошибка - вернёт ложь
    int get_first_level_index(); // возвращает индекс первого уровня
    int get_last_level_index();  // возвращает индекс последнего уровня
    bool load_level(int level_index); // загружает уровень по его индексу
             // возвращает истину если загрузка прошла без ошибок иначе вернёт ложь

private:
    QList<Level_File_Descriptor> level_files_decriptors;
    int first_level_number; // номер первого уровня
    int last_level_number; // номер последнего уровня


protected:

signals:

};

#endif // LEVEL_LOADER_H
