// Умеет перечислять игровые сцены на диске
// и загужать указанную сцену в игру по её номеру
#ifndef SCENELOADER_H
#define SCENELOADER_H
#include <QObject>
#include <QVector>
#include <QMap>
#include <QList>



class SceneLoader : public QObject
{
    Q_OBJECT
public:
    explicit SceneLoader(QObject *parent = nullptr);


protected:

signals:

};

#endif // SCENELOADER_H
