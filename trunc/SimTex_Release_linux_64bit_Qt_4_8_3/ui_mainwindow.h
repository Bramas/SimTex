/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created: Sun Jul 7 17:24:38 2013
**      by: Qt User Interface Compiler version 4.8.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QGridLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QMainWindow>
#include <QtGui/QMenu>
#include <QtGui/QMenuBar>
#include <QtGui/QStatusBar>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QAction *actionOpen;
    QAction *actionSaveAs;
    QAction *actionSave;
    QAction *actionPdfLatex;
    QAction *actionSettings;
    QAction *actionAutoView;
    QAction *actionNouveau;
    QAction *actionEncodage;
    QAction *actionExit;
    QAction *actionUndo;
    QAction *actionRedo;
    QAction *actionCut;
    QAction *actionCopy;
    QAction *actionPaste;
    QAction *actionFindReplace;
    QAction *actionView;
    QAction *actionOpenConfigFolder;
    QAction *actionDeleteLastOpenFiles;
    QWidget *gridLayoutWidget;
    QGridLayout *gridLayout;
    QMenuBar *menuBar;
    QMenu *menuFichier;
    QMenu *menuOuvrir_R_cent;
    QMenu *menuBuild;
    QMenu *menuOptions;
    QMenu *menuTh_me;
    QMenu *menuEdition;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(991, 633);
        MainWindow->setMouseTracking(true);
        MainWindow->setStyleSheet(QString::fromUtf8(""));
        actionOpen = new QAction(MainWindow);
        actionOpen->setObjectName(QString::fromUtf8("actionOpen"));
        actionSaveAs = new QAction(MainWindow);
        actionSaveAs->setObjectName(QString::fromUtf8("actionSaveAs"));
        actionSave = new QAction(MainWindow);
        actionSave->setObjectName(QString::fromUtf8("actionSave"));
        actionPdfLatex = new QAction(MainWindow);
        actionPdfLatex->setObjectName(QString::fromUtf8("actionPdfLatex"));
        actionSettings = new QAction(MainWindow);
        actionSettings->setObjectName(QString::fromUtf8("actionSettings"));
        actionAutoView = new QAction(MainWindow);
        actionAutoView->setObjectName(QString::fromUtf8("actionAutoView"));
        actionAutoView->setCheckable(true);
        actionNouveau = new QAction(MainWindow);
        actionNouveau->setObjectName(QString::fromUtf8("actionNouveau"));
        actionEncodage = new QAction(MainWindow);
        actionEncodage->setObjectName(QString::fromUtf8("actionEncodage"));
        actionExit = new QAction(MainWindow);
        actionExit->setObjectName(QString::fromUtf8("actionExit"));
        actionUndo = new QAction(MainWindow);
        actionUndo->setObjectName(QString::fromUtf8("actionUndo"));
        actionRedo = new QAction(MainWindow);
        actionRedo->setObjectName(QString::fromUtf8("actionRedo"));
        actionCut = new QAction(MainWindow);
        actionCut->setObjectName(QString::fromUtf8("actionCut"));
        actionCopy = new QAction(MainWindow);
        actionCopy->setObjectName(QString::fromUtf8("actionCopy"));
        actionPaste = new QAction(MainWindow);
        actionPaste->setObjectName(QString::fromUtf8("actionPaste"));
        actionFindReplace = new QAction(MainWindow);
        actionFindReplace->setObjectName(QString::fromUtf8("actionFindReplace"));
        actionView = new QAction(MainWindow);
        actionView->setObjectName(QString::fromUtf8("actionView"));
        actionOpenConfigFolder = new QAction(MainWindow);
        actionOpenConfigFolder->setObjectName(QString::fromUtf8("actionOpenConfigFolder"));
        actionDeleteLastOpenFiles = new QAction(MainWindow);
        actionDeleteLastOpenFiles->setObjectName(QString::fromUtf8("actionDeleteLastOpenFiles"));
        gridLayoutWidget = new QWidget(MainWindow);
        gridLayoutWidget->setObjectName(QString::fromUtf8("gridLayoutWidget"));
        gridLayoutWidget->setMouseTracking(true);
        gridLayout = new QGridLayout(gridLayoutWidget);
        gridLayout->setSpacing(0);
        gridLayout->setContentsMargins(11, 11, 11, 11);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        gridLayout->setSizeConstraint(QLayout::SetDefaultConstraint);
        gridLayout->setContentsMargins(9, 5, 0, 0);
        MainWindow->setCentralWidget(gridLayoutWidget);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QString::fromUtf8("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 991, 25));
        menuFichier = new QMenu(menuBar);
        menuFichier->setObjectName(QString::fromUtf8("menuFichier"));
        menuOuvrir_R_cent = new QMenu(menuFichier);
        menuOuvrir_R_cent->setObjectName(QString::fromUtf8("menuOuvrir_R_cent"));
        menuBuild = new QMenu(menuBar);
        menuBuild->setObjectName(QString::fromUtf8("menuBuild"));
        menuOptions = new QMenu(menuBar);
        menuOptions->setObjectName(QString::fromUtf8("menuOptions"));
        menuTh_me = new QMenu(menuOptions);
        menuTh_me->setObjectName(QString::fromUtf8("menuTh_me"));
        menuEdition = new QMenu(menuBar);
        menuEdition->setObjectName(QString::fromUtf8("menuEdition"));
        MainWindow->setMenuBar(menuBar);
        statusBar = new QStatusBar(MainWindow);
        statusBar->setObjectName(QString::fromUtf8("statusBar"));
        statusBar->setMouseTracking(true);
        MainWindow->setStatusBar(statusBar);

        menuBar->addAction(menuFichier->menuAction());
        menuBar->addAction(menuEdition->menuAction());
        menuBar->addAction(menuBuild->menuAction());
        menuBar->addAction(menuOptions->menuAction());
        menuFichier->addAction(actionNouveau);
        menuFichier->addSeparator();
        menuFichier->addAction(actionOpen);
        menuFichier->addAction(menuOuvrir_R_cent->menuAction());
        menuFichier->addSeparator();
        menuFichier->addAction(actionSave);
        menuFichier->addAction(actionSaveAs);
        menuFichier->addSeparator();
        menuFichier->addAction(actionEncodage);
        menuFichier->addSeparator();
        menuFichier->addAction(actionExit);
        menuOuvrir_R_cent->addSeparator();
        menuOuvrir_R_cent->addAction(actionDeleteLastOpenFiles);
        menuBuild->addAction(actionPdfLatex);
        menuBuild->addSeparator();
        menuBuild->addAction(actionAutoView);
        menuBuild->addAction(actionView);
        menuOptions->addAction(actionSettings);
        menuOptions->addAction(menuTh_me->menuAction());
        menuTh_me->addSeparator();
        menuTh_me->addAction(actionOpenConfigFolder);
        menuEdition->addAction(actionUndo);
        menuEdition->addAction(actionRedo);
        menuEdition->addSeparator();
        menuEdition->addAction(actionCut);
        menuEdition->addAction(actionCopy);
        menuEdition->addAction(actionPaste);
        menuEdition->addSeparator();
        menuEdition->addAction(actionFindReplace);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "SimTex", 0, QApplication::UnicodeUTF8));
        actionOpen->setText(QApplication::translate("MainWindow", "Ouvrir", 0, QApplication::UnicodeUTF8));
        actionOpen->setShortcut(QApplication::translate("MainWindow", "Ctrl+O", 0, QApplication::UnicodeUTF8));
        actionSaveAs->setText(QApplication::translate("MainWindow", "Enregistrer Sous", 0, QApplication::UnicodeUTF8));
        actionSaveAs->setShortcut(QApplication::translate("MainWindow", "Ctrl+Shift+S", 0, QApplication::UnicodeUTF8));
        actionSave->setText(QApplication::translate("MainWindow", "Enregistrer", 0, QApplication::UnicodeUTF8));
        actionSave->setShortcut(QApplication::translate("MainWindow", "Ctrl+S", 0, QApplication::UnicodeUTF8));
        actionPdfLatex->setText(QApplication::translate("MainWindow", "PdfLatex", 0, QApplication::UnicodeUTF8));
        actionPdfLatex->setShortcut(QApplication::translate("MainWindow", "Ctrl+B", 0, QApplication::UnicodeUTF8));
        actionSettings->setText(QApplication::translate("MainWindow", "Pr\303\251f\303\251rences", 0, QApplication::UnicodeUTF8));
        actionAutoView->setText(QApplication::translate("MainWindow", "Afficher automatiquement le pdf", 0, QApplication::UnicodeUTF8));
        actionNouveau->setText(QApplication::translate("MainWindow", "Nouveau", 0, QApplication::UnicodeUTF8));
        actionEncodage->setText(QApplication::translate("MainWindow", "Encodage", 0, QApplication::UnicodeUTF8));
        actionExit->setText(QApplication::translate("MainWindow", "Quitter", 0, QApplication::UnicodeUTF8));
        actionUndo->setText(QApplication::translate("MainWindow", "Annuler", 0, QApplication::UnicodeUTF8));
        actionRedo->setText(QApplication::translate("MainWindow", "Refaire", 0, QApplication::UnicodeUTF8));
        actionCut->setText(QApplication::translate("MainWindow", "Couper", 0, QApplication::UnicodeUTF8));
        actionCopy->setText(QApplication::translate("MainWindow", "Copier", 0, QApplication::UnicodeUTF8));
        actionPaste->setText(QApplication::translate("MainWindow", "Coller", 0, QApplication::UnicodeUTF8));
        actionFindReplace->setText(QApplication::translate("MainWindow", "Rechercher / Remplacer", 0, QApplication::UnicodeUTF8));
        actionFindReplace->setShortcut(QApplication::translate("MainWindow", "Ctrl+F", 0, QApplication::UnicodeUTF8));
        actionView->setText(QApplication::translate("MainWindow", "Voir le pdf", 0, QApplication::UnicodeUTF8));
        actionView->setShortcut(QApplication::translate("MainWindow", "Ctrl+D", 0, QApplication::UnicodeUTF8));
        actionOpenConfigFolder->setText(QApplication::translate("MainWindow", "Ouvrir le dossier th\303\250me", 0, QApplication::UnicodeUTF8));
        actionDeleteLastOpenFiles->setText(QApplication::translate("MainWindow", "Supprimer l'historique", 0, QApplication::UnicodeUTF8));
        menuFichier->setTitle(QApplication::translate("MainWindow", "Fichier", 0, QApplication::UnicodeUTF8));
        menuOuvrir_R_cent->setTitle(QApplication::translate("MainWindow", "Ouvrir R\303\251cent", 0, QApplication::UnicodeUTF8));
        menuBuild->setTitle(QApplication::translate("MainWindow", "Compiler", 0, QApplication::UnicodeUTF8));
        menuOptions->setTitle(QApplication::translate("MainWindow", "Options", 0, QApplication::UnicodeUTF8));
        menuTh_me->setTitle(QApplication::translate("MainWindow", "Th\303\250me", 0, QApplication::UnicodeUTF8));
        menuEdition->setTitle(QApplication::translate("MainWindow", "Edition", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
