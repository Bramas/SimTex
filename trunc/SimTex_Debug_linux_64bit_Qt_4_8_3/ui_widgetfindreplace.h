/********************************************************************************
** Form generated from reading UI file 'widgetfindreplace.ui'
**
** Created: Sun Jul 7 11:19:38 2013
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
#include <QtGui/QGroupBox>
#include <QtGui/QHBoxLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QLineEdit>
#include <QtGui/QPushButton>
#include <QtGui/QVBoxLayout>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_WidgetFindReplace
{
public:
    QHBoxLayout *horizontalLayout;
    QVBoxLayout *verticalLayout;
    QLineEdit *lineEditFind;
    QLineEdit *lineEditReplace;
    QGroupBox *groupBox;
    QPushButton *pushButtonReplace;
    QPushButton *pushButtonFind;
    QPushButton *pushButtonReplaceAndFind;
    QPushButton *pushButtonReplaceAll;
    QPushButton *pushButtonClose;
    QCheckBox *checkBoxRegex;
    QCheckBox *checkBoxCasse;

    void setupUi(QWidget *WidgetFindReplace)
    {
        if (WidgetFindReplace->objectName().isEmpty())
            WidgetFindReplace->setObjectName(QString::fromUtf8("WidgetFindReplace"));
        WidgetFindReplace->resize(721, 87);
        horizontalLayout = new QHBoxLayout(WidgetFindReplace);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        horizontalLayout->setSizeConstraint(QLayout::SetDefaultConstraint);
        horizontalLayout->setContentsMargins(5, 2, 5, 2);
        verticalLayout = new QVBoxLayout();
        verticalLayout->setSpacing(0);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        lineEditFind = new QLineEdit(WidgetFindReplace);
        lineEditFind->setObjectName(QString::fromUtf8("lineEditFind"));

        verticalLayout->addWidget(lineEditFind);

        lineEditReplace = new QLineEdit(WidgetFindReplace);
        lineEditReplace->setObjectName(QString::fromUtf8("lineEditReplace"));

        verticalLayout->addWidget(lineEditReplace);


        horizontalLayout->addLayout(verticalLayout);

        groupBox = new QGroupBox(WidgetFindReplace);
        groupBox->setObjectName(QString::fromUtf8("groupBox"));
        groupBox->setMinimumSize(QSize(400, 0));
        pushButtonReplace = new QPushButton(groupBox);
        pushButtonReplace->setObjectName(QString::fromUtf8("pushButtonReplace"));
        pushButtonReplace->setGeometry(QRect(0, 50, 91, 31));
        pushButtonFind = new QPushButton(groupBox);
        pushButtonFind->setObjectName(QString::fromUtf8("pushButtonFind"));
        pushButtonFind->setGeometry(QRect(0, 10, 91, 31));
        pushButtonReplaceAndFind = new QPushButton(groupBox);
        pushButtonReplaceAndFind->setObjectName(QString::fromUtf8("pushButtonReplaceAndFind"));
        pushButtonReplaceAndFind->setGeometry(QRect(100, 50, 171, 31));
        pushButtonReplaceAll = new QPushButton(groupBox);
        pushButtonReplaceAll->setObjectName(QString::fromUtf8("pushButtonReplaceAll"));
        pushButtonReplaceAll->setGeometry(QRect(280, 50, 111, 31));
        pushButtonClose = new QPushButton(groupBox);
        pushButtonClose->setObjectName(QString::fromUtf8("pushButtonClose"));
        pushButtonClose->setGeometry(QRect(380, 0, 21, 20));
        checkBoxRegex = new QCheckBox(groupBox);
        checkBoxRegex->setObjectName(QString::fromUtf8("checkBoxRegex"));
        checkBoxRegex->setGeometry(QRect(100, 20, 251, 21));
        checkBoxCasse = new QCheckBox(groupBox);
        checkBoxCasse->setObjectName(QString::fromUtf8("checkBoxCasse"));
        checkBoxCasse->setGeometry(QRect(100, 0, 151, 21));

        horizontalLayout->addWidget(groupBox);


        retranslateUi(WidgetFindReplace);

        QMetaObject::connectSlotsByName(WidgetFindReplace);
    } // setupUi

    void retranslateUi(QWidget *WidgetFindReplace)
    {
        pushButtonReplace->setText(QApplication::translate("WidgetFindReplace", "Remplacer", 0, QApplication::UnicodeUTF8));
        pushButtonFind->setText(QApplication::translate("WidgetFindReplace", "Rechercher", 0, QApplication::UnicodeUTF8));
        pushButtonReplaceAndFind->setText(QApplication::translate("WidgetFindReplace", "Remplacer & Rechercher", 0, QApplication::UnicodeUTF8));
        pushButtonReplaceAll->setText(QApplication::translate("WidgetFindReplace", "Remplacer Tout", 0, QApplication::UnicodeUTF8));
        pushButtonClose->setText(QApplication::translate("WidgetFindReplace", "x", 0, QApplication::UnicodeUTF8));
        checkBoxRegex->setText(QApplication::translate("WidgetFindReplace", "Utiliser les expressions r\303\251guli\303\250res", 0, QApplication::UnicodeUTF8));
        checkBoxCasse->setText(QApplication::translate("WidgetFindReplace", "Sensible \303\240 la casse", 0, QApplication::UnicodeUTF8));
        Q_UNUSED(WidgetFindReplace);
    } // retranslateUi

};

namespace Ui {
    class WidgetFindReplace: public Ui_WidgetFindReplace {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_WIDGETFINDREPLACE_H
