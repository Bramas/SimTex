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

    const QTextCharFormat& getTextCharFormats(QString key)
    {
        return this->textCharFormats->value(key,this->textCharFormats->value("normal"));
    }

    ~ConfigManager();

    void changePointSizeBy(int delta);
    void setPointSize(int size);

    void setMainWindow(QWidget * mainWindow);
    void save(void);
    bool load(void);
    QString colorToString(const QColor & color) { return "rgb("+QString::number(color.red())+","+QString::number(color.green())+","+QString::number(color.blue())+")";}

    QString textCharFormatToString(QTextCharFormat charFormat, QTextCharFormat defaultFormat = QTextCharFormat());
    QTextCharFormat stringToTextCharFormat(QString string, QTextCharFormat defaultFormat = QTextCharFormat());

private:
    ConfigManager();

    QWidget * mainWindow;
    QSettings settings;
    QMap<QString,QTextCharFormat> * textCharFormats;
};



#endif // CONFIGMANAGER_H
