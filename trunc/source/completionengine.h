#ifndef COMPLETIONENGINE_H
#define COMPLETIONENGINE_H
#include <QListWidget>
#include <QStringList>

class WidgetTextEdit;

class CompletionEngine : public QListWidget
{
    Q_OBJECT

public:
    CompletionEngine(WidgetTextEdit * parent);


    void proposeCommand(int top, int left, QString commandBegin);
    QString acceptedWord();
public slots:
 //   void setFocus(void);

protected:
    void keyPressEvent(QKeyEvent *event);

private:
    QStringList _words;
    QString _commandBegin;
};

#endif // COMPLETIONENGINE_H
