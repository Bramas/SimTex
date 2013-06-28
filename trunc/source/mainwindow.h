#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

class QMimeData;
class WidgetTextEdit;
class WidgetLineNumber;
class WidgetScroller;
class WidgetPdfViewer;
class WidgetConsole;
class DialogWelcome;
class DialogConfig;
class QVBoxLayout;

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
    WidgetConsole * _widgetConsole;
    DialogWelcome * dialogWelcome;
    DialogConfig * dialogConfig;
    QVBoxLayout * _leftLayout;
    int _editorWidth;
    bool _mousePressed;
    bool _resizeConsole;
};

#endif // MAINWINDOW_H
