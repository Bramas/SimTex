/********************************************************************************
** Form generated from reading UI file 'widgetviewer.ui'
**
** Created: Wed 26. Jun 23:58:43 2013
**      by: Qt User Interface Compiler version 4.8.4
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_WIDGETVIEWER_H
#define UI_WIDGETVIEWER_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QHBoxLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QPushButton>
#include <QtGui/QVBoxLayout>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_WidgetViewer
{
public:
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout;
    QPushButton *pushButton;
    QPushButton *pushButton_2;

    void setupUi(QWidget *verticalLayoutWidget)
    {
        if (verticalLayoutWidget->objectName().isEmpty())
            verticalLayoutWidget->setObjectName(QString::fromUtf8("verticalLayoutWidget"));
        verticalLayout = new QVBoxLayout(verticalLayoutWidget);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        pushButton = new QPushButton(verticalLayoutWidget);
        pushButton->setObjectName(QString::fromUtf8("pushButton"));

        horizontalLayout->addWidget(pushButton);

        pushButton_2 = new QPushButton(verticalLayoutWidget);
        pushButton_2->setObjectName(QString::fromUtf8("pushButton_2"));

        horizontalLayout->addWidget(pushButton_2);


        verticalLayout->addLayout(horizontalLayout);


        retranslateUi(verticalLayoutWidget);

        QMetaObject::connectSlotsByName(verticalLayoutWidget);
    } // setupUi

    void retranslateUi(QWidget *verticalLayoutWidget)
    {
        verticalLayoutWidget->setWindowTitle(QApplication::translate("WidgetViewer", "Form", 0, QApplication::UnicodeUTF8));
        pushButton->setText(QApplication::translate("WidgetViewer", "PushButton", 0, QApplication::UnicodeUTF8));
        pushButton_2->setText(QApplication::translate("WidgetViewer", "PushButton", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class WidgetViewer: public Ui_WidgetViewer {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_WIDGETVIEWER_H
