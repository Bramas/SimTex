/********************************************************************************
** Form generated from reading UI file 'widgetfindreplace.ui'
**
** Created: Sat Jul 6 20:57:42 2013
**      by: Qt User Interface Compiler version 4.8.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_WIDGETFINDREPLACE_H
#define UI_WIDGETFINDREPLACE_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QCheckBox>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QLineEdit>
#include <QtGui/QPushButton>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_WidgetFindReplace
{
public:
    QLineEdit *lineEditFind;
    QLineEdit *lineEditReplace;
    QLabel *labelFind;
    QLabel *labelReplace;
    QPushButton *pushButtonFind;
    QPushButton *pushButtonReplaceAndFind;
    QPushButton *pushButtonReplaceAll;
    QPushButton *pushButtonReplace;
    QCheckBox *checkBoxCasse;
    QCheckBox *checkBoxRegex;
    QPushButton *pushButtonClose;

    void setupUi(QWidget *WidgetFindReplace)
    {
        if (WidgetFindReplace->objectName().isEmpty())
            WidgetFindReplace->setObjectName(QString::fromUtf8("WidgetFindReplace"));
        WidgetFindReplace->resize(723, 102);
        lineEditFind = new QLineEdit(WidgetFindReplace);
        lineEditFind->setObjectName(QString::fromUtf8("lineEditFind"));
        lineEditFind->setGeometry(QRect(90, 10, 231, 31));
        lineEditReplace = new QLineEdit(WidgetFindReplace);
        lineEditReplace->setObjectName(QString::fromUtf8("lineEditReplace"));
        lineEditReplace->setGeometry(QRect(90, 60, 231, 31));
        labelFind = new QLabel(WidgetFindReplace);
        labelFind->setObjectName(QString::fromUtf8("labelFind"));
        labelFind->setGeometry(QRect(0, 10, 91, 31));
        labelFind->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        labelReplace = new QLabel(WidgetFindReplace);
        labelReplace->setObjectName(QString::fromUtf8("labelReplace"));
        labelReplace->setGeometry(QRect(0, 60, 91, 31));
        labelReplace->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        pushButtonFind = new QPushButton(WidgetFindReplace);
        pushButtonFind->setObjectName(QString::fromUtf8("pushButtonFind"));
        pushButtonFind->setGeometry(QRect(330, 10, 91, 31));
        pushButtonReplaceAndFind = new QPushButton(WidgetFindReplace);
        pushButtonReplaceAndFind->setObjectName(QString::fromUtf8("pushButtonReplaceAndFind"));
        pushButtonReplaceAndFind->setGeometry(QRect(430, 60, 171, 31));
        pushButtonReplaceAll = new QPushButton(WidgetFindReplace);
        pushButtonReplaceAll->setObjectName(QString::fromUtf8("pushButtonReplaceAll"));
        pushButtonReplaceAll->setGeometry(QRect(610, 60, 111, 31));
        pushButtonReplace = new QPushButton(WidgetFindReplace);
        pushButtonReplace->setObjectName(QString::fromUtf8("pushButtonReplace"));
        pushButtonReplace->setGeometry(QRect(330, 60, 91, 31));
        checkBoxCasse = new QCheckBox(WidgetFindReplace);
        checkBoxCasse->setObjectName(QString::fromUtf8("checkBoxCasse"));
        checkBoxCasse->setGeometry(QRect(430, 10, 151, 21));
        checkBoxRegex = new QCheckBox(WidgetFindReplace);
        checkBoxRegex->setObjectName(QString::fromUtf8("checkBoxRegex"));
        checkBoxRegex->setGeometry(QRect(430, 30, 251, 21));
        pushButtonClose = new QPushButton(WidgetFindReplace);
        pushButtonClose->setObjectName(QString::fromUtf8("pushButtonClose"));
        pushButtonClose->setGeometry(QRect(700, 0, 21, 20));

        retranslateUi(WidgetFindReplace);

        QMetaObject::connectSlotsByName(WidgetFindReplace);
    } // setupUi

    void retranslateUi(QWidget *WidgetFindReplace)
    {
        WidgetFindReplace->setWindowTitle(QApplication::translate("WidgetFindReplace", "Form", 0, QApplication::UnicodeUTF8));
        labelFind->setText(QApplication::translate("WidgetFindReplace", "Rechercher : ", 0, QApplication::UnicodeUTF8));
        labelReplace->setText(QApplication::translate("WidgetFindReplace", "Remplacer : ", 0, QApplication::UnicodeUTF8));
        pushButtonFind->setText(QApplication::translate("WidgetFindReplace", "Rechercher", 0, QApplication::UnicodeUTF8));
        pushButtonReplaceAndFind->setText(QApplication::translate("WidgetFindReplace", "Remplacer & Rechercher", 0, QApplication::UnicodeUTF8));
        pushButtonReplaceAll->setText(QApplication::translate("WidgetFindReplace", "Remplacer Tout", 0, QApplication::UnicodeUTF8));
        pushButtonReplace->setText(QApplication::translate("WidgetFindReplace", "Remplacer", 0, QApplication::UnicodeUTF8));
        checkBoxCasse->setText(QApplication::translate("WidgetFindReplace", "Sensible \303\240 la casse", 0, QApplication::UnicodeUTF8));
        checkBoxRegex->setText(QApplication::translate("WidgetFindReplace", "Utiliser les expressions r\303\251guli\303\250res", 0, QApplication::UnicodeUTF8));
        pushButtonClose->setText(QApplication::translate("WidgetFindReplace", "x", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class WidgetFindReplace: public Ui_WidgetFindReplace {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_WIDGETFINDREPLACE_H
