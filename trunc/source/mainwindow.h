#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

class QMimeData;
class WidgetTextEdit;
class WidgetLineNumber;
class WidgetScroller;
class WidgetPdfViewer;
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
    void openLast(void);
    void focus(void);

protected:
    void mousePressEvent(QMouseEvent *);
    void mouseMoveEvent(QMouseEvent *);
    void mouseReleaseEvent(QMouseEvent *);
    
private:
    Ui::MainWindow *ui;

    WidgetLineNumber * widgetLineNumber;
    WidgetTextEdit * widgetTextEdit;
    WidgetScroller * widgetScroller;
    WidgetPdfViewer * _widgetPdfViewer;
    DialogWelcome * dialogWelcome;
    DialogConfig * dialogConfig;
    int _editorWidth;
    bool _mousePressed;
};

#endif // MAINWINDOW_H
