QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

DEFINES += QT_DEPRECATED_WARNINGS

LIBS += $$top_builddir/components/$(OBJECTS_DIR)/libcomponents.a
INCLUDEPATH += $$top_srcdir/components/
TARGET = SnookerScoring
PRE_TARGETDEPS += $$top_builddir/components/$(OBJECTS_DIR)/libcomponents.a

FORMS+=snookerscoring.ui \
    snookeraccueil.ui \
    snookersettings.ui

SOURCES += \
    Joueur.cpp \
    main.cpp \
    snookeraccueil.cpp \
    snookerscoring.cpp \
    snookersettings.cpp \
    timerclass.cpp

HEADERS += \
    Joueur.h \
    snookeraccueil.h \
    snookerscoring.h \
    snookersettings.h \
    timerclass.h

RESOURCES += \
    ressource.qrc

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
