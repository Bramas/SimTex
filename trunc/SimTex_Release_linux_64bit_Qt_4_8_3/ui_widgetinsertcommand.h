/********************************************************************************
** Form generated from reading UI file 'widgetinsertcommand.ui'
**
** Created: Fri Jul 5 23:01:17 2013
**      by: Qt User Interface Compiler version 4.8.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_WIDGETINSERTCOMMAND_H
#define UI_WIDGETINSERTCOMMAND_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QHeaderView>
#include <QtGui/QTabWidget>
#include <QtGui/QTableWidget>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_WidgetInsertCommand
{
public:
    QTabWidget *tabWidget;
    QWidget *tab;
    QTableWidget *tableWidget;
    QWidget *tab_2;

    void setupUi(QWidget *WidgetInsertCommand)
    {
        if (WidgetInsertCommand->objectName().isEmpty())
            WidgetInsertCommand->setObjectName(QString::fromUtf8("WidgetInsertCommand"));
        WidgetInsertCommand->resize(463, 250);
        tabWidget = new QTabWidget(WidgetInsertCommand);
        tabWidget->setObjectName(QString::fromUtf8("tabWidget"));
        tabWidget->setGeometry(QRect(0, 0, 461, 251));
        tabWidget->setTabPosition(QTabWidget::West);
        tabWidget->setTabShape(QTabWidget::Rounded);
        tabWidget->setTabsClosable(false);
        tab = new QWidget();
        tab->setObjectName(QString::fromUtf8("tab"));
        tableWidget = new QTableWidget(tab);
        if (tableWidget->columnCount() < 3)
            tableWidget->setColumnCount(3);
        QTableWidgetItem *__qtablewidgetitem = new QTableWidgetItem();
        tableWidget->setHorizontalHeaderItem(0, __qtablewidgetitem);
        QTableWidgetItem *__qtablewidgetitem1 = new QTableWidgetItem();
        tableWidget->setHorizontalHeaderItem(1, __qtablewidgetitem1);
        QTableWidgetItem *__qtablewidgetitem2 = new QTableWidgetItem();
        tableWidget->setHorizontalHeaderItem(2, __qtablewidgetitem2);
        if (tableWidget->rowCount() < 1)
            tableWidget->setRowCount(1);
        QTableWidgetItem *__qtablewidgetitem3 = new QTableWidgetItem();
        tableWidget->setVerticalHeaderItem(0, __qtablewidgetitem3);
        QTableWidgetItem *__qtablewidgetitem4 = new QTableWidgetItem();
        tableWidget->setItem(0, 0, __qtablewidgetitem4);
        QTableWidgetItem *__qtablewidgetitem5 = new QTableWidgetItem();
        tableWidget->setItem(0, 1, __qtablewidgetitem5);
        QTableWidgetItem *__qtablewidgetitem6 = new QTableWidgetItem();
        tableWidget->setItem(0, 2, __qtablewidgetitem6);
        tableWidget->setObjectName(QString::fromUtf8("tableWidget"));
        tableWidget->setEnabled(true);
        tableWidget->setGeometry(QRect(0, 0, 431, 251));
        tableWidget->horizontalHeader()->setVisible(false);
        tableWidget->verticalHeader()->setVisible(false);
        tabWidget->addTab(tab, QString());
        tab_2 = new QWidget();
        tab_2->setObjectName(QString::fromUtf8("tab_2"));
        tabWidget->addTab(tab_2, QString());

        retranslateUi(WidgetInsertCommand);

        tabWidget->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(WidgetInsertCommand);
    } // setupUi

    void retranslateUi(QWidget *WidgetInsertCommand)
    {
        WidgetInsertCommand->setWindowTitle(QApplication::translate("WidgetInsertCommand", "Form", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem = tableWidget->horizontalHeaderItem(0);
        ___qtablewidgetitem->setText(QApplication::translate("WidgetInsertCommand", "Nouvelle colonne", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem1 = tableWidget->horizontalHeaderItem(1);
        ___qtablewidgetitem1->setText(QApplication::translate("WidgetInsertCommand", "Nouvelle colonne", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem2 = tableWidget->horizontalHeaderItem(2);
        ___qtablewidgetitem2->setText(QApplication::translate("WidgetInsertCommand", "Nouvelle colonne", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem3 = tableWidget->verticalHeaderItem(0);
        ___qtablewidgetitem3->setText(QApplication::translate("WidgetInsertCommand", "Nouvelle ligne", 0, QApplication::UnicodeUTF8));

        const bool __sortingEnabled = tableWidget->isSortingEnabled();
        tableWidget->setSortingEnabled(false);
        QTableWidgetItem *___qtablewidgetitem4 = tableWidget->item(0, 0);
        ___qtablewidgetitem4->setText(QApplication::translate("WidgetInsertCommand", "\\epsilon", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem5 = tableWidget->item(0, 1);
        ___qtablewidgetitem5->setText(QApplication::translate("WidgetInsertCommand", "\\alpha", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem6 = tableWidget->item(0, 2);
        ___qtablewidgetitem6->setText(QApplication::translate("WidgetInsertCommand", "\\beta", 0, QApplication::UnicodeUTF8));
        tableWidget->setSortingEnabled(__sortingEnabled);

        tabWidget->setTabText(tabWidget->indexOf(tab), QApplication::translate("WidgetInsertCommand", "Symboles", 0, QApplication::UnicodeUTF8));
        tabWidget->setTabText(tabWidget->indexOf(tab_2), QApplication::translate("WidgetInsertCommand", "Tab 2", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class WidgetInsertCommand: public Ui_WidgetInsertCommand {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_WIDGETINSERTCOMMAND_H
