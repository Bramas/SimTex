#ifndef CONFIGMANAGER_H
#define CONFIGMANAGER_H


#include <QObject>
#include <QMap>
#include <QString>
#include <QTextCharFormat>
#include <QSettings>
#include <QDebug>
#include <QMutex>


class QWidget;

class ConfigManager : public QObject
{
    Q_OBJECT

public:

    static ConfigManager Instance;

    QTextCharFormat getTextCharFormats(QString key)
    {
        //_charFormatMutex.lock();
        QTextCharFormat format(this->textCharFormats->value(key,this->textCharFormats->value("normal")));
        //_charFormatMutex.unlock();
        return format;
    }

    ~ConfigManager();

    void changePointSizeBy(int delta);
    void setPointSize(int size);

    void setMainWindow(QWidget * mainWindow);
    void save(void);
    bool load(QString theme = QString());
    QString colorToString(const QColor & color) { return "rgb("+QString::number(color.red())+","+QString::number(color.green())+","+QString::number(color.blue())+")";}

    QString textCharFormatToString(QTextCharFormat charFormat, QTextCharFormat defaultFormat = QTextCharFormat());
    QTextCharFormat stringToTextCharFormat(QString string, QTextCharFormat defaultFormat = QTextCharFormat());

    QStringList themesList();
    const QString& theme() { return _theme; }

public slots:
    void openThemeFolder();

private:
    ConfigManager();

    QWidget * mainWindow;
    QSettings settings;
    QMap<QString,QTextCharFormat> * textCharFormats;
    QString _theme;
    QMutex _charFormatMutex;
};



#endif // CONFIGMANAGER_H
