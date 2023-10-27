// Класс исчезающих блоков
#ifndef BLOCK_H
#define BLOCK_H

#include <QWidget>
#include <QImage>


class Block : public QWidget
{
    Q_OBJECT
public:
    explicit Block(QWidget *parent = nullptr);


private:

    QImage image; // картинка блока

protected:
    void paintEvent(QPaintEvent *event);


signals:

};

#endif // BLOCK_H
