/********************************************************************************
** Form generated from reading UI file 'widgetviewer.ui'
**
** Created: Thu 27. Jun 01:25:29 2013
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
    QPushButton *pushButtonZoomIn;
    QPushButton *pushButtonZoomOut;

    void setupUi(QWidget *verticalLayoutWidget)
    {
        if (verticalLayoutWidget->objectName().isEmpty())
            verticalLayoutWidget->setObjectName(QString::fromUtf8("verticalLayoutWidget"));
        verticalLayoutWidget->resize(176, 43);
        verticalLayout = new QVBoxLayout(verticalLayoutWidget);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        pushButtonZoomIn = new QPushButton(verticalLayoutWidget);
        pushButtonZoomIn->setObjectName(QString::fromUtf8("pushButtonZoomIn"));
        pushButtonZoomIn->setStyleSheet(QString::fromUtf8(""));

        horizontalLayout->addWidget(pushButtonZoomIn);

        pushButtonZoomOut = new QPushButton(verticalLayoutWidget);
        pushButtonZoomOut->setObjectName(QString::fromUtf8("pushButtonZoomOut"));

        horizontalLayout->addWidget(pushButtonZoomOut);


        verticalLayout->addLayout(horizontalLayout);


        retranslateUi(verticalLayoutWidget);

        QMetaObject::connectSlotsByName(verticalLayoutWidget);
    } // setupUi

    void retranslateUi(QWidget *verticalLayoutWidget)
    {
        verticalLayoutWidget->setWindowTitle(QApplication::translate("WidgetViewer", "Form", 0, QApplication::UnicodeUTF8));
        pushButtonZoomIn->setText(QApplication::translate("WidgetViewer", "e", 0, QApplication::UnicodeUTF8));
        pushButtonZoomOut->setText(QApplication::translate("WidgetViewer", "PushButton", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class WidgetViewer: public Ui_WidgetViewer {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_WIDGETVIEWER_H
