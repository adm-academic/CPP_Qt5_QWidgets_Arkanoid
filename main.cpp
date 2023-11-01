#include "wmain.h"

#include <QApplication>
#include <QLocale>
#include <QTranslator>
#include <QDebug>
#include <QFontDatabase>
#include <QFile>

#include "global_forms.h"
#include "settings.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    app_settings.find_basedir_and_changedir();

    app_settings.load_current_config_file_locale();

    // загрузим кастомные шрифты из ресурсов приложения
    QFontDatabase::addApplicationFont("fonts/ArkanoidSolid.ttf");
    QFontDatabase::addApplicationFont("fonts/Xolonium-Regular.otf");
    QFontDatabase::addApplicationFont("fonts/Practice-font-Mono.otf");//"Practice-font Mono"
    QFontDatabase::addApplicationFont("fonts/Practice-font.otf");//"Practice-font"
    QFontDatabase::addApplicationFont("fonts/Orbit B BT.ttf");//"Orbit-B BT"
    QFontDatabase db;
    for(int i=0; i<db.families().size(); i++)
    {
        qDebug() << "FD:" << db.families().at(i);
    };

    // загрузим главную таблицу стилей оформления игры из ресурсов приложения
    QFile file("styles/black.qss");
    file.open(QFile::ReadOnly);
    QString styleSheet = QLatin1String(file.readAll());
    qApp->setStyleSheet(styleSheet);

    wlanguage = new WLanguage();
    wabout    = new WAbout();
    wsettings = new WSettings();
    wgameover = new WGameOver();
    wmain     = new WMain();
    wwin      = new WWin();
    wmain->show();
    return a.exec();
}
