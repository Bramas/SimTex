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

    void setMainWindow(QWidget * mainWindow);
    void save(void);

    static QString textCharFormatToString(QTextCharFormat charFormat);

private:
    ConfigManager();

    QWidget * mainWindow;
    QSettings settings;
    QMap<QString,QTextCharFormat> * textCharFormats;
};



#endif // CONFIGMANAGER_H
