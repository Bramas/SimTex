/********************************************************************************
** Form generated from reading UI file 'dialogconfig.ui'
**
** Created: Fri Jun 28 22:31:53 2013
**      by: Qt User Interface Compiler version 4.8.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DIALOGCONFIG_H
#define UI_DIALOGCONFIG_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QDialog>
#include <QtGui/QFormLayout>
#include <QtGui/QGridLayout>
#include <QtGui/QHBoxLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QListWidget>
#include <QtGui/QPushButton>
#include <QtGui/QRadioButton>
#include <QtGui/QSpinBox>
#include <QtGui/QStackedWidget>
#include <QtGui/QTableWidget>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_DialogConfig
{
public:
    QListWidget *listWidget;
    QStackedWidget *stackedWidget;
    QWidget *page;
    QWidget *gridLayoutWidget;
    QGridLayout *gridLayout;
    QTableWidget *tableWidget;
    QFormLayout *formLayout;
    QLabel *label;
    QSpinBox *spinBoxPointSize;
    QLabel *label_2;
    QHBoxLayout *horizontalLayout;
    QRadioButton *radioButtonDarkTheme;
    QRadioButton *radioButtonLightTheme;
    QWidget *page_2;
    QPushButton *pushButton;
    QPushButton *pushButton_2;

    void setupUi(QDialog *DialogConfig)
    {
        if (DialogConfig->objectName().isEmpty())
            DialogConfig->setObjectName(QString::fromUtf8("DialogConfig"));
        DialogConfig->resize(753, 467);
        listWidget = new QListWidget(DialogConfig);
        listWidget->setObjectName(QString::fromUtf8("listWidget"));
        listWidget->setGeometry(QRect(20, 20, 171, 391));
        stackedWidget = new QStackedWidget(DialogConfig);
        stackedWidget->setObjectName(QString::fromUtf8("stackedWidget"));
        stackedWidget->setGeometry(QRect(200, 20, 521, 391));
        page = new QWidget();
        page->setObjectName(QString::fromUtf8("page"));
        gridLayoutWidget = new QWidget(page);
        gridLayoutWidget->setObjectName(QString::fromUtf8("gridLayoutWidget"));
        gridLayoutWidget->setGeometry(QRect(0, 0, 521, 391));
        gridLayout = new QGridLayout(gridLayoutWidget);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        gridLayout->setContentsMargins(0, 0, 0, 0);
        tableWidget = new QTableWidget(gridLayoutWidget);
        if (tableWidget->columnCount() < 1)
            tableWidget->setColumnCount(1);
        QTableWidgetItem *__qtablewidgetitem = new QTableWidgetItem();
        tableWidget->setHorizontalHeaderItem(0, __qtablewidgetitem);
        if (tableWidget->rowCount() < 2)
            tableWidget->setRowCount(2);
        QTableWidgetItem *__qtablewidgetitem1 = new QTableWidgetItem();
        tableWidget->setVerticalHeaderItem(0, __qtablewidgetitem1);
        QTableWidgetItem *__qtablewidgetitem2 = new QTableWidgetItem();
        tableWidget->setVerticalHeaderItem(1, __qtablewidgetitem2);
        QTableWidgetItem *__qtablewidgetitem3 = new QTableWidgetItem();
        tableWidget->setItem(0, 0, __qtablewidgetitem3);
        QTableWidgetItem *__qtablewidgetitem4 = new QTableWidgetItem();
        tableWidget->setItem(1, 0, __qtablewidgetitem4);
        tableWidget->setObjectName(QString::fromUtf8("tableWidget"));

        gridLayout->addWidget(tableWidget, 3, 0, 1, 1);

        formLayout = new QFormLayout();
        formLayout->setObjectName(QString::fromUtf8("formLayout"));
        formLayout->setFieldGrowthPolicy(QFormLayout::AllNonFixedFieldsGrow);
        label = new QLabel(gridLayoutWidget);
        label->setObjectName(QString::fromUtf8("label"));

        formLayout->setWidget(1, QFormLayout::LabelRole, label);

        spinBoxPointSize = new QSpinBox(gridLayoutWidget);
        spinBoxPointSize->setObjectName(QString::fromUtf8("spinBoxPointSize"));

        formLayout->setWidget(1, QFormLayout::FieldRole, spinBoxPointSize);

        label_2 = new QLabel(gridLayoutWidget);
        label_2->setObjectName(QString::fromUtf8("label_2"));

        formLayout->setWidget(2, QFormLayout::LabelRole, label_2);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        radioButtonDarkTheme = new QRadioButton(gridLayoutWidget);
        radioButtonDarkTheme->setObjectName(QString::fromUtf8("radioButtonDarkTheme"));
        radioButtonDarkTheme->setChecked(true);

        horizontalLayout->addWidget(radioButtonDarkTheme);

        radioButtonLightTheme = new QRadioButton(gridLayoutWidget);
        radioButtonLightTheme->setObjectName(QString::fromUtf8("radioButtonLightTheme"));

        horizontalLayout->addWidget(radioButtonLightTheme);


        formLayout->setLayout(2, QFormLayout::FieldRole, horizontalLayout);


        gridLayout->addLayout(formLayout, 0, 0, 1, 1);

        stackedWidget->addWidget(page);
        page_2 = new QWidget();
        page_2->setObjectName(QString::fromUtf8("page_2"));
        stackedWidget->addWidget(page_2);
        pushButton = new QPushButton(DialogConfig);
        pushButton->setObjectName(QString::fromUtf8("pushButton"));
        pushButton->setGeometry(QRect(540, 430, 75, 23));
        pushButton_2 = new QPushButton(DialogConfig);
        pushButton_2->setObjectName(QString::fromUtf8("pushButton_2"));
        pushButton_2->setGeometry(QRect(630, 430, 75, 23));

        retranslateUi(DialogConfig);

        QMetaObject::connectSlotsByName(DialogConfig);
    } // setupUi

    void retranslateUi(QDialog *DialogConfig)
    {
        DialogConfig->setWindowTitle(QApplication::translate("DialogConfig", "Dialog", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem = tableWidget->horizontalHeaderItem(0);
        ___qtablewidgetitem->setText(QApplication::translate("DialogConfig", "Couleur", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem1 = tableWidget->verticalHeaderItem(0);
        ___qtablewidgetitem1->setText(QApplication::translate("DialogConfig", "Couleur du texte", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem2 = tableWidget->verticalHeaderItem(1);
        ___qtablewidgetitem2->setText(QApplication::translate("DialogConfig", "Couleur du fond", 0, QApplication::UnicodeUTF8));

        const bool __sortingEnabled = tableWidget->isSortingEnabled();
        tableWidget->setSortingEnabled(false);
        QTableWidgetItem *___qtablewidgetitem3 = tableWidget->item(0, 0);
        ___qtablewidgetitem3->setText(QApplication::translate("DialogConfig", "#ffffff", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem4 = tableWidget->item(1, 0);
        ___qtablewidgetitem4->setText(QApplication::translate("DialogConfig", "#000000", 0, QApplication::UnicodeUTF8));
        tableWidget->setSortingEnabled(__sortingEnabled);

        label->setText(QApplication::translate("DialogConfig", "Taille du texte", 0, QApplication::UnicodeUTF8));
        label_2->setText(QApplication::translate("DialogConfig", "Th\303\250me", 0, QApplication::UnicodeUTF8));
        radioButtonDarkTheme->setText(QApplication::translate("DialogConfig", "Sombre", 0, QApplication::UnicodeUTF8));
        radioButtonLightTheme->setText(QApplication::translate("DialogConfig", "Clair", 0, QApplication::UnicodeUTF8));
        pushButton->setText(QApplication::translate("DialogConfig", "Valider", 0, QApplication::UnicodeUTF8));
        pushButton_2->setText(QApplication::translate("DialogConfig", "Annler", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class DialogConfig: public Ui_DialogConfig {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DIALOGCONFIG_H
