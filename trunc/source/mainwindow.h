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
class SyntaxHighlighter;

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
    void changeTheme(void);

protected:
    void mousePressEvent(QMouseEvent *);
    void mouseMoveEvent(QMouseEvent *);
    void mouseReleaseEvent(QMouseEvent *);
    void closeEvent(QCloseEvent *);
    
private:
    Ui::MainWindow *ui;
    void initTheme();

    WidgetLineNumber * widgetLineNumber;
    WidgetTextEdit * widgetTextEdit;
    WidgetScroller * widgetScroller;
    WidgetPdfViewer * _widgetPdfViewer;
    WidgetConsole * _widgetConsole;
    DialogWelcome * dialogWelcome;
    DialogConfig * dialogConfig;
    QVBoxLayout * _leftLayout;
    SyntaxHighlighter * _syntaxHighlighter;
    int _editorWidth;
    bool _mousePressed;
    bool _resizeConsole;
};

#endif // MAINWINDOW_H
