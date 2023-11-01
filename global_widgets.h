// глобальные переменные-виджеты
#ifndef GLOBAL_WIDGETS_H
#define GLOBAL_WIDGETS_H
#include "gameframe.h"
#include "gamestate.h"

extern GameFrame* gameframe;
extern GameState* gamestate;

struct LevelInfo{
    QString LevelNameEn;
    QString LevelNameRu;
};


#endif // GLOBAL_WIDGETS_H
