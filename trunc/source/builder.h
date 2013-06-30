#ifndef BUILDER_H
#define BUILDER_H
#include <QObject>
#include <QString>
#include <QProcess>
#include <QStringList>

class File;

class Builder : public QObject
{
        Q_OBJECT
public:
    Builder(File * file);
    const QStringList & simpleOutput() const { return _simpleOutPut; }
public slots:
    void pdflatex();
    void onFinished(int exitCode,QProcess::ExitStatus exitStatus);
    void onStandartOutputReady();

signals:
    void statusChanged(QString);
    void outputReady(QString);
    void pdfChanged();
    void error();
    void success();
    void started();

private:
    bool checkOutput();
    File * file;
    QString _basename;
    QProcess * process;
    QString _lastOutput;
    QStringList _simpleOutPut;
};

#endif // BUILDER_H
