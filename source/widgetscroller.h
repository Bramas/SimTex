#ifndef WIDGETSCROLLER_H
#define WIDGETSCROLLER_H

#include <QWidget>
#include <QRectF>

class WidgetTextEdit;
class WidgetScroller : public QWidget
{
    Q_OBJECT
public:
    explicit WidgetScroller(QWidget *parent = 0);
    void setParent(QWidget *parent) {QWidget::setParent(parent); this->parent = parent; }

    void setWidgetTextEdit(WidgetTextEdit * widgetTextEdit) { this->widgetTextEdit = widgetTextEdit; }
    
signals:
    void changed(int);
public slots:
    void updateText(void);

private:
    WidgetTextEdit * widgetTextEdit;
    int scrollOffset;
    QWidget *parent;
    bool mousePressed;
    int mousePressedAt;
    QRectF overlayRect;
    QRect boudingRect;

    void paintEvent(QPaintEvent * event);
    void mousePressEvent(QMouseEvent * event);
    void mouseReleaseEvent(QMouseEvent *);
    void mouseMoveEvent(QMouseEvent *);
};

#endif // WIDGETSCROLLER_H
