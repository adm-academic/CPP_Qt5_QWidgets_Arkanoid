// глобальные переменные-формы
#ifndef GLOBAL_FORMS_H
#define GLOBAL_FORMS_H

#include "settings.h"
#include "wmain.h"
#include "wlanguage.h"
#include "wabout.h"
#include "wsettings.h"
#include "wgameover.h"

extern Settings   app_settings;// единый объект с настройками приложения
extern WMain*     wmain;
extern WLanguage* wlanguage;// указатель на окно с выбором локали и языка
extern WAbout*    wabout;// указатель на окно "О Программе"
extern WSettings*  wsettings;// указатель на окно с настройками
extern WGameOver*  wgameover;// указатель на окно с информацией о завершении игры


#endif // GLOBAL_FORMS_H
