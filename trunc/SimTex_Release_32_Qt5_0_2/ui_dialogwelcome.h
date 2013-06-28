/********************************************************************************
** Form generated from reading UI file 'dialogwelcome.ui'
**
** Created by: Qt User Interface Compiler version 5.0.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DIALOGWELCOME_H
#define UI_DIALOGWELCOME_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialog>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QPushButton>

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
            DialogWelcome->setObjectName(QStringLiteral("DialogWelcome"));
        DialogWelcome->resize(400, 300);
        pushButtonOpenLast = new QPushButton(DialogWelcome);
        pushButtonOpenLast->setObjectName(QStringLiteral("pushButtonOpenLast"));
        pushButtonOpenLast->setGeometry(QRect(20, 40, 331, 51));
        pushButtonOpen = new QPushButton(DialogWelcome);
        pushButtonOpen->setObjectName(QStringLiteral("pushButtonOpen"));
        pushButtonOpen->setGeometry(QRect(20, 120, 331, 51));
        pushButtonNew = new QPushButton(DialogWelcome);
        pushButtonNew->setObjectName(QStringLiteral("pushButtonNew"));
        pushButtonNew->setGeometry(QRect(20, 200, 331, 51));

        retranslateUi(DialogWelcome);

        QMetaObject::connectSlotsByName(DialogWelcome);
    } // setupUi

    void retranslateUi(QDialog *DialogWelcome)
    {
        DialogWelcome->setWindowTitle(QApplication::translate("DialogWelcome", "Dialog", 0));
        pushButtonOpenLast->setText(QApplication::translate("DialogWelcome", "Ouvrir le dernier document.", 0));
        pushButtonOpen->setText(QApplication::translate("DialogWelcome", "Ouvrir un autre document.", 0));
        pushButtonNew->setText(QApplication::translate("DialogWelcome", "Creer un nouveau document.", 0));
    } // retranslateUi

};

namespace Ui {
    class DialogWelcome: public Ui_DialogWelcome {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DIALOGWELCOME_H
