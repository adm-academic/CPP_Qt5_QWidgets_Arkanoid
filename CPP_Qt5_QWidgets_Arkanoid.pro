QT       += core gui multimedia sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

CONFIG += console

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    ball.cpp \
    block.cpp \
    device_background.cpp \
    device_prizes_list.cpp \
    elementar_moving_algebra.cpp \
    gameframe.cpp \
    gamestate.cpp \
    global_forms.cpp \
    global_widgets.cpp \
    level_loader.cpp \
    main.cpp \
    platform.cpp \
    prize.cpp \
    prize_catch.cpp \
    prize_expand.cpp \
    prize_fast.cpp \
    prize_life.cpp \
    prize_score100.cpp \
    prize_score250.cpp \
    prize_score50.cpp \
    prize_score500.cpp \
    prize_slow.cpp \
    settings.cpp \
    wabout.cpp \
    wgameover.cpp \
    wlanguage.cpp \
    wmain.cpp \
    wscorestatistic.cpp \
    wsettings.cpp \
    wwin.cpp

HEADERS += \
    ball.h \
    block.h \
    device_background.h \
    device_prizes_list.h \
    elementar_moving_algebra.h \
    gameframe.h \
    gamestate.h \
    global_forms.h \
    global_widgets.h \
    level_loader.h \
    platform.h \
    prize.h \
    prize_catch.h \
    prize_expand.h \
    prize_fast.h \
    prize_life.h \
    prize_score100.h \
    prize_score250.h \
    prize_score50.h \
    prize_score500.h \
    prize_slow.h \
    settings.h \
    wabout.h \
    wgameover.h \
    wlanguage.h \
    wmain.h \
    wscorestatistic.h \
    wsettings.h \
    wwin.h

FORMS += \
    wabout.ui \
    wgameover.ui \
    wlanguage.ui \
    wmain.ui \
    wscorestatistic.ui \
    wsettings.ui \
    wwin.ui

TRANSLATIONS += \
    CPP_Qt5_QWidgets_Arkanoid_ru_RU.ts
CONFIG += lrelease
CONFIG += embed_translations

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

DISTFILES += \
    README.md \
    TODO.txt \
    settings.conf \
    styles/black.qss \
    wins_statistic.db \
    wins_statitic.sql

RESOURCES += \
    resources.qrc
