#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
class QMimeData;
class WidgetTextEdit;
class WidgetLineNumber;
class WidgetScroller;
class DialogWelcome;
class DialogConfig;

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

public slots:

    void save(void);
    void saveAs(void);
    void open(QString filename = "");
    void openLast();

    
private:
    Ui::MainWindow *ui;

    WidgetLineNumber * widgetLineNumber;
    WidgetTextEdit * widgetTextEdit;
    WidgetScroller * widgetScroller;
    DialogWelcome * dialogWelcome;
    DialogConfig * dialogConfig;
};

#endif // MAINWINDOW_H
