QT       += core gui xml

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

QTITANDIR = D:/Projects/LIBS/QtitanComponents2025.1.0

include($$QTITANDIR/src/shared/qtitanstyle.pri)
include($$QTITANDIR/src/shared/qtitanfastinfoset.pri)
include($$QTITANDIR/src/shared/qtitangrid.pri)
include($$QTITANDIR/src/shared/qtitandocking.pri)
include($$QTITANDIR/src/shared/qtitanribbon.pri)

!debug_and_release|build_pass {
    CONFIG(debug, debug|release) {
        TARGET = $$member(TARGET, 0)
    }
}

SOURCES += \
    logpanel.cpp \
    main.cpp \
    mainwindow.cpp \
    settingsdialog.cpp \
    tasklistpanel.cpp \
    treeitem.cpp \
    treemodel.cpp

HEADERS += \
    logpanel.h \
    mainwindow.h \
    settingsdialog.h \
    tasklistpanel.h \
    treeitem.h \
    treemodel.h

TRANSLATIONS +=
CONFIG += lrelease
CONFIG += embed_translations

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    resourses.qrc
