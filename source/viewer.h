#ifndef VIEWER_H
#define VIEWER_H
#include <QObject>
#include <QProcess>

class File;


class Viewer : public QObject
{
    Q_OBJECT
public:
    Viewer(File * file);
    void setLine(int line) { this->currentLine = line; }

public slots:
    void view(QString s="");
    void onFinished(int, QProcess::ExitStatus exitStatus);

signals:
    void finished(void);

private:

    QProcess * process;
    File * file;
    int currentLine;
};

#endif // VIEWER_H
