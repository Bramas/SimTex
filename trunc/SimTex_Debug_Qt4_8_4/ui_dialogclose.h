/********************************************************************************
** Form generated from reading UI file 'dialogclose.ui'
**
** Created: Tue 2. Jul 20:07:32 2013
**      by: Qt User Interface Compiler version 4.8.4
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DIALOGCLOSE_H
#define UI_DIALOGCLOSE_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QDialog>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QPushButton>

QT_BEGIN_NAMESPACE

class Ui_DialogClose
{
public:
    QLabel *label;
    QLabel *warningLabel;
    QPushButton *confirmAndClose;
    QPushButton *cancel;

    void setupUi(QDialog *DialogClose)
    {
        if (DialogClose->objectName().isEmpty())
            DialogClose->setObjectName(QString::fromUtf8("DialogClose"));
        DialogClose->resize(379, 161);
        label = new QLabel(DialogClose);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(30, 50, 311, 41));
        label->setWordWrap(true);
        warningLabel = new QLabel(DialogClose);
        warningLabel->setObjectName(QString::fromUtf8("warningLabel"));
        warningLabel->setGeometry(QRect(30, 10, 61, 16));
        confirmAndClose = new QPushButton(DialogClose);
        confirmAndClose->setObjectName(QString::fromUtf8("confirmAndClose"));
        confirmAndClose->setGeometry(QRect(230, 120, 121, 31));
        cancel = new QPushButton(DialogClose);
        cancel->setObjectName(QString::fromUtf8("cancel"));
        cancel->setGeometry(QRect(100, 120, 121, 31));
        cancel->setDefault(true);

        retranslateUi(DialogClose);

        QMetaObject::connectSlotsByName(DialogClose);
    } // setupUi

    void retranslateUi(QDialog *DialogClose)
    {
        DialogClose->setWindowTitle(QApplication::translate("DialogClose", "Dialog", 0, QApplication::UnicodeUTF8));
        label->setText(QApplication::translate("DialogClose", "n'a pas \303\251t\303\251 enregistr\303\251", 0, QApplication::UnicodeUTF8));
        warningLabel->setText(QApplication::translate("DialogClose", "Attention !", 0, QApplication::UnicodeUTF8));
        confirmAndClose->setText(QApplication::translate("DialogClose", "Ignorer et fermer", 0, QApplication::UnicodeUTF8));
        cancel->setText(QApplication::translate("DialogClose", "Annuler", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class DialogClose: public Ui_DialogClose {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DIALOGCLOSE_H
