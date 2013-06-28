/********************************************************************************
** Form generated from reading UI file 'dialogwelcome.ui'
**
** Created: Fri Jun 28 17:20:30 2013
**      by: Qt User Interface Compiler version 4.8.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DIALOGWELCOME_H
#define UI_DIALOGWELCOME_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QDialog>
#include <QtGui/QHeaderView>
#include <QtGui/QPushButton>

QT_BEGIN_NAMESPACE

class Ui_DialogWelcome
{
public:
    QPushButton *pushButtonOpenLast;
    QPushButton *pushButtonOpen;
    QPushButton *pushButtonNew;

    void setupUi(QDialog *DialogWelcome)
    {
        if (DialogWelcome->objectName().isEmpty())
            DialogWelcome->setObjectName(QString::fromUtf8("DialogWelcome"));
        DialogWelcome->resize(400, 300);
        pushButtonOpenLast = new QPushButton(DialogWelcome);
        pushButtonOpenLast->setObjectName(QString::fromUtf8("pushButtonOpenLast"));
        pushButtonOpenLast->setGeometry(QRect(20, 40, 331, 51));
        pushButtonOpen = new QPushButton(DialogWelcome);
        pushButtonOpen->setObjectName(QString::fromUtf8("pushButtonOpen"));
        pushButtonOpen->setGeometry(QRect(20, 120, 331, 51));
        pushButtonNew = new QPushButton(DialogWelcome);
        pushButtonNew->setObjectName(QString::fromUtf8("pushButtonNew"));
        pushButtonNew->setGeometry(QRect(20, 200, 331, 51));

        retranslateUi(DialogWelcome);

        QMetaObject::connectSlotsByName(DialogWelcome);
    } // setupUi

    void retranslateUi(QDialog *DialogWelcome)
    {
        DialogWelcome->setWindowTitle(QApplication::translate("DialogWelcome", "Bienvenue", 0, QApplication::UnicodeUTF8));
        pushButtonOpenLast->setText(QApplication::translate("DialogWelcome", "Ouvrir le dernier document.", 0, QApplication::UnicodeUTF8));
        pushButtonOpen->setText(QApplication::translate("DialogWelcome", "Ouvrir un autre document.", 0, QApplication::UnicodeUTF8));
        pushButtonNew->setText(QApplication::translate("DialogWelcome", "Creer un nouveau document.", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class DialogWelcome: public Ui_DialogWelcome {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DIALOGWELCOME_H
