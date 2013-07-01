#ifndef COMPLETIONENGINE_H
#define COMPLETIONENGINE_H
#include <QListWidget>
#include <QStringList>
#include <QString>

class WidgetTextEdit;

class CompletionEngine : public QListWidget
{
    Q_OBJECT

public:
    CompletionEngine(WidgetTextEdit * parent);

    void proposeCommand(int top, int left, QString commandBegin);
    QString acceptedWord();

    void addCustomWordFromSource();
public slots:
 //   void setFocus(void);

protected:
    void keyPressEvent(QKeyEvent *event);

private:
    void loadFile(QString filename);
    QStringList _words;
    QStringList _customWords;
    QString _commandBegin;
};

#endif // COMPLETIONENGINE_H
