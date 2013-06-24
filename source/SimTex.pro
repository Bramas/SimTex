#-------------------------------------------------
#
# Project created by QtCreator 2013-06-21T23:54:41
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = SimTex
TEMPLATE = app

INCLUDEPATH += "G:\Projects\poppler-0.22.5\poppler"
INCLUDEPATH += "G:\Projects\poppler-0.22.5"

#QT += poppler

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
    poppler/poppler-annotation.cc \
    poppler/poppler-textbox.cc \
    poppler/poppler-sound.cc \
    poppler/poppler-qiodeviceoutstream.cc \
    poppler/poppler-ps-converter.cc \
    poppler/poppler-private.cc \
    poppler/poppler-pdf-converter.cc \
    poppler/poppler-page-transition.cc \
    poppler/poppler-page.cc \
    poppler/poppler-optcontent.cc \
    poppler/poppler-movie.cc \
    poppler/poppler-media.cc \
    poppler/poppler-link-extractor.cc \
    poppler/poppler-link.cc \
    poppler/poppler-form.cc \
    poppler/poppler-fontinfo.cc \
    poppler/poppler-embeddedfile.cc \
    poppler/poppler-document.cc \
    poppler/poppler-base-converter.cc

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
    poppler/poppler-qt4.h \
    poppler/poppler-qiodeviceoutstream-private.h \
    poppler/poppler-private.h \
    poppler/poppler-page-transition-private.h \
    poppler/poppler-page-transition.h \
    poppler/poppler-page-private.h \
    poppler/poppler-optcontent-private.h \
    poppler/poppler-optcontent.h \
    poppler/poppler-media.h \
    poppler/poppler-link-extractor-private.h \
    poppler/poppler-link.h \
    poppler/poppler-form.h \
    poppler/poppler-export.h \
    poppler/poppler-embeddedfile-private.h \
    poppler/poppler-converter-private.h \
    poppler/poppler-annotation-private.h \
    poppler/poppler-annotation-helper.h \
    poppler/poppler-annotation.h

FORMS    += mainwindow.ui \
    dialogwelcome.ui \
    dialogconfig.ui
