#ifndef BUILDER_H
#define BUILDER_H
#include <QObject>
#include <QString>
#include <QProcess>

class File;

class Builder : public QObject
{
        Q_OBJECT
public:
    Builder(File * file);
public slots:
    void pdflatex();
    void onFinished(int exitCode,QProcess::ExitStatus exitStatus);

signals:
    void statusChanged(QString);
    void pdfChanged();

private:
    File * file;
    QProcess * process;
};

#endif // BUILDER_H
