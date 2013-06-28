/********************************************************************************
** Form generated from reading UI file 'widgetpdfviewer.ui'
**
** Created: Fri Jun 28 17:20:30 2013
**      by: Qt User Interface Compiler version 4.8.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_WIDGETPDFVIEWER_H
#define UI_WIDGETPDFVIEWER_H

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

class Ui_WidgetPdfViewer
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
        verticalLayout->setSpacing(0);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        verticalLayout->setContentsMargins(5, 0, 0, 0);
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
        verticalLayoutWidget->setWindowTitle(QApplication::translate("WidgetPdfViewer", "Form", 0, QApplication::UnicodeUTF8));
        pushButtonZoomIn->setText(QString());
        pushButtonZoomOut->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class WidgetPdfViewer: public Ui_WidgetPdfViewer {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_WIDGETPDFVIEWER_H
