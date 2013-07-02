#-------------------------------------------------
#
# Project created by QtCreator 2013-06-21T23:54:41
#
#-------------------------------------------------

QT       += core gui


greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = SimTex
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    widgetlinenumber.cpp \
    widgettextedit.cpp \
    syntaxhighlighter.cpp \
    widgetscroller.cpp \
    blockdata.cpp \
    filestructure.cpp \
    file.cpp \
    builder.cpp \
    dialogwelcome.cpp \
    dialogconfig.cpp \
    configmanager.cpp \
    viewer.cpp \
    widgetpdfdocument.cpp \
    synctex_parser.c \
    synctex_parser_utils.c \
    widgetpdfviewer.cpp \
    completionengine.cpp \
    widgetconsole.cpp \
    dialogclose.cpp

HEADERS  += mainwindow.h \
    widgetlinenumber.h \
    widgettextedit.h \
    syntaxhighlighter.h \
    widgetscroller.h \
    blockdata.h \
    filestructure.h \
    file.h \
    builder.h \
    dialogwelcome.h \
    dialogconfig.h \
    configmanager.h \
    viewer.h \
    widgetpdfdocument.h \
    synctex_parser.h \
    synctex_parser_utils.h \
    synctex_parser_local.h \
    widgetpdfviewer.h \
    completionengine.h \
    widgetconsole.h \
    dialogclose.h

FORMS    += mainwindow.ui \
    dialogwelcome.ui \
    dialogconfig.ui \
    widgetpdfviewer.ui \
    dialogclose.ui

#LIBS         += -LG:\poppler -lpoppler-qt4
#LIBS         += -LG:\poppler\cpp\bin -lpoppler-cpp
#LIBS         += -LG:\poppler\cpp\bin -lpoppler-cpp
#LIBS         += G:\poppler\bin\poppler-cpp.dll
#LIBS         += G:\poppler\bin\libpng14-14.dll

target.path = SimTexwin32

INSTALLS = target


RESOURCES += \
    data.qrc \
    completion.qrc

win32 {

    INCLUDEPATH += C:/dev/Tools/poppler/include/poppler/qt4
    INCLUDEPATH += C:/dev/Qt/Tools/zlib/include
    LIBS += -LC:/dev/Tools/poppler/lib -lpoppler-qt4

    RC_FILE = win.rc
}
unix{
    LIBS += -L/usr/local/lib -lpoppler-qt4
}
