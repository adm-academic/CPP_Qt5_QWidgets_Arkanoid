// Умеет загружать указанную или следующую сцену в игру
#ifndef SCENELOADER_H
#define SCENELOADER_H

#include <QObject>




class SceneLoader : public QObject
{
    Q_OBJECT
public:
    explicit SceneLoader(QObject *parent = nullptr);

protected:

signals:

};

#endif // SCENELOADER_H
