#ifndef CONFIGMANAGER_H
#define CONFIGMANAGER_H


#include <QMap>
#include <QString>
#include <QTextCharFormat>
#include <QSettings>


class QWidget;

class ConfigManager
{
public:

    static ConfigManager Instance;

    QMap<QString,QTextCharFormat> * getTextCharFormats() { return this->textCharFormats; }

    ~ConfigManager();

    void changePointSizeBy(int delta);
    void setPointSize(int size);

    void setMainWindow(QWidget * mainWindow);
    void save(void);
    QString colorToString(const QColor & color) { return "rgb("+QString::number(color.red())+","+QString::number(color.green())+","+QString::number(color.blue())+")";}

    static QString textCharFormatToString(QTextCharFormat charFormat);

private:
    ConfigManager();

    QWidget * mainWindow;
    QSettings settings;
    QMap<QString,QTextCharFormat> * textCharFormats;
};



#endif // CONFIGMANAGER_H
