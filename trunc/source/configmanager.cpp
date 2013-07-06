#include "configmanager.h"
#include <QFont>
#include <QColor>
#include <QSettings>
#include <QDesktopServices>
#if QT_VERSION < 0x050000
    #include <QDesktopServices>
#else
    #include <QStandardPaths>
#endif

#include <QMapIterator>
#include <QDir>
#include <QUrl>
#include <QMessageBox>
#include <QDebug>
#include <QCoreApplication>

#define DEBUG_THEME_PARSER(a)

ConfigManager ConfigManager::Instance;

ConfigManager::ConfigManager() :
    textCharFormats(new QMap<QString,QTextCharFormat>()),
    mainWindow(0)
{

    qDebug()<<"Init ConfigManager";

    QCoreApplication::setOrganizationName("Ultratools");
    QCoreApplication::setOrganizationDomain("ultratools.org");
    QCoreApplication::setApplicationName("TexSim");
    QSettings::setDefaultFormat(QSettings::IniFormat);

    QSettings settings;
    settings.beginGroup("theme");




    if(!settings.contains("theme"))
    {
        settings.setValue("theme",QString("dark"));
    }
    if(!this->load())
    {
        QFont font("Consolas");
        font.setPointSize(settings.value("pointSize",12).toInt());
        QTextCharFormat charFormat;

        charFormat.setForeground(QColor(53,52,41));
        charFormat.setFont(font);
        charFormat.setBackground(QColor(250,250,250));
        textCharFormats->insert("normal",charFormat);
    }
    return;
    /*
    if(!settings.value("theme").toString().compare("dark"))
    {
        //font.setBold(QFont::Normal);
        charFormat.setForeground(QColor(248,248,242));
        charFormat.setFont(font);
        charFormat.setBackground(QColor(58,60,50));
        textCharFormats->insert("linenumber",charFormat);

        charFormat.setForeground(QColor(14,16,15));
        charFormat.setFont(font);
        textCharFormats->insert("textedit-border",charFormat);


        charFormat.setBackground(QColor(48,50,44));
        textCharFormats->insert("selected-line",charFormat);

        charFormat.setForeground(QColor(248,248,242));
        charFormat.setFont(font);
        charFormat.setBackground(QColor(39,40,34));
        textCharFormats->insert("normal",charFormat);




        charFormat.setForeground(QColor(117,113,94));
        charFormat.setFont(font);
        textCharFormats->insert("comment",charFormat);


        charFormat.setForeground(QColor(118,227,75));
        charFormat.setFont(font);
        textCharFormats->insert("math",charFormat);

        charFormat.setForeground(QColor(249,39,114));
        charFormat.setFont(font);
        textCharFormats->insert("command",charFormat);


        font.setBold(QFont::Bold);
        charFormat.setForeground(QColor(249,39,114));
        charFormat.setFont(font);
        textCharFormats->insert("structure",charFormat);

    //    font.setBold(QFont::Normal);
        font.setBold(QFont::Bold);
        charFormat.setForeground(QColor(158,158,152));
        charFormat.setBackground(QColor(58,60,50));
        charFormat.setFont(font);
        textCharFormats->insert("leftStructure",charFormat);
    }
    else
    {

        //font.setBold(QFont::Normal);
        charFormat.setForeground(QColor(63,62,51));
        charFormat.setFont(font);
        charFormat.setBackground(QColor(220,220,220));
        textCharFormats->insert("linenumber",charFormat);

        charFormat.setForeground(QColor(200,200,200));
        charFormat.setFont(font);
        textCharFormats->insert("textedit-border",charFormat);

        charFormat.setBackground(QColor(230,230,230));
        textCharFormats->insert("selected-line",charFormat);

        charFormat.setForeground(QColor(53,52,41));
        charFormat.setFont(font);
        charFormat.setBackground(QColor(250,250,250));
        textCharFormats->insert("normal",charFormat);


        charFormat.setForeground(QColor(117,113,94));
        charFormat.setFont(font);
        textCharFormats->insert("comment",charFormat);



        charFormat.setForeground(QColor(229,30,104));
        charFormat.setFont(font);
        textCharFormats->insert("command",charFormat);


        font.setBold(QFont::DemiBold);
        charFormat.setForeground(QColor(38,133,0));
        charFormat.setFont(font);
        textCharFormats->insert("math",charFormat);

        font.setBold(QFont::Bold);
        charFormat.setForeground(QColor(209,24,94));
        charFormat.setFont(font);
        textCharFormats->insert("structure",charFormat);


    //    font.setBold(QFont::Normal);
        font.setBold(QFont::Bold);
        charFormat.setForeground(QColor(153,152,151));
        charFormat.setBackground(QColor(235,235,235));
        charFormat.setFont(font);
        textCharFormats->insert("leftStructure",charFormat);
    }// */

}
void ConfigManager::setMainWindow(QWidget * mainWindow)
{
    this->mainWindow = mainWindow;

    //this->save();
}


ConfigManager::~ConfigManager()
{
    delete this->textCharFormats;
}

QString ConfigManager::textCharFormatToString(QTextCharFormat charFormat, QTextCharFormat defaultFormat)
{
    QString config;

    if(charFormat.font() != defaultFormat.font())
    {
        config += QString("font(");
        if(charFormat.font().family().compare(defaultFormat.font().family()))
        {
            config += QString("\"")+charFormat.font().family()+QString("\" ");
        }
        if(charFormat.font().pointSize() != defaultFormat.font().pointSize())
        {
            config += QString::number(charFormat.font().pointSize())+QString(" ");
        }
        if(charFormat.font().bold() != defaultFormat.font().bold())
        {
            config += (charFormat.font().bold()?"bold":"normal")+QString(" ");
        }
        config +=QString(") ");
    }

    if(charFormat.foreground().style() != Qt::NoBrush)
    {
        config += " foreground("+QString::number(charFormat.foreground().color().red())+
                ", "+QString::number(charFormat.foreground().color().green())+
                ", "+QString::number(charFormat.foreground().color().blue())+
                ") ";
    }
    if(charFormat.background().style() != Qt::NoBrush)
    {
        config += " background("+QString::number(charFormat.background().color().red())+
                    ", "+QString::number(charFormat.background().color().green())+
                    ", "+QString::number(charFormat.background().color().blue())+
                    ") ";
    }
    if(config.isEmpty())
    {
        config = "inherit";
    }
    return config;
}

QTextCharFormat ConfigManager::stringToTextCharFormat(QString string, QTextCharFormat defaultFormat)
{
    QTextCharFormat charFormat(defaultFormat);

    DEBUG_THEME_PARSER(qDebug()<<string);
    QRegExp pattern("([a-z]*)\\(([^\\)]*)\\)");
    QRegExp familyPattern("\\\"([^\\\"]*)\\\"");
    QRegExp pointSizePattern("[^0-9]([0-9]+)[^0-9]");
    int index;
    int length;
    index = string.indexOf(pattern);
    while(index != -1)
    {
        length = pattern.matchedLength();
        if(pattern.captureCount() < 2)
        {
            qDebug()<<(QString::fromUtf8("Erreur lors de la lecture du fichier Theme près de la ligne : ")+string).toLatin1();
            continue;
            //QMessageBox::warning(0, QObject::trUtf8("Erreur"), QObject::tr((QString::fromUtf8("Erreur lors de la lecture du fichier Theme près de la ligne : ")+string).toLatin1()));
        }
        if(!pattern.capturedTexts().at(1).compare("foreground"))
        {
            QStringList colors = pattern.capturedTexts().last().split(",");

            if(colors.count() < 3)
            {
                qDebug()<<(QString::fromUtf8("Erreur lors de la lecture du fichier Theme près de la ligne : ")+string).toLatin1();
                continue;
            }
            charFormat.setForeground(QBrush(QColor(colors.at(0).trimmed().toInt(),
                                                   colors.at(1).trimmed().toInt(),
                                                   colors.at(2).trimmed().toInt())));
            DEBUG_THEME_PARSER(qDebug()<<"Color : "<<colors.at(0).trimmed().toInt()<<", "<<colors.at(1).trimmed().toInt()<<", "<<colors.at(2).trimmed().toInt());
        }
        else if(!pattern.capturedTexts().at(1).compare("background"))
        {
            QStringList colors = pattern.capturedTexts().last().split(",");

            if(colors.count() < 3)
            {
                qDebug()<<(QString::fromUtf8("Erreur lors de la lecture du fichier Theme près de la ligne : ")+string).toLatin1();
                continue;
            }
            charFormat.setBackground(QBrush(QColor(colors.at(0).trimmed().toInt(),
                                                   colors.at(1).trimmed().toInt(),
                                                   colors.at(2).trimmed().toInt())));
            DEBUG_THEME_PARSER(qDebug()<<"BackgroundColor : "<<colors.at(0).trimmed().toInt()<<", "<<colors.at(1).trimmed().toInt()<<", "<<colors.at(2).trimmed().toInt());
        }
        else if(!pattern.capturedTexts().at(1).compare("font"))
        {
            QFont font(charFormat.font());
            if(pattern.capturedTexts().last().contains("bold",Qt::CaseInsensitive))
            {
                font.setBold(QFont::Bold);
                DEBUG_THEME_PARSER(qDebug()<<"Bold : bold");
            }
            else if(pattern.capturedTexts().last().contains("normal",Qt::CaseInsensitive))
            {
                font.setBold(QFont::Normal);
                DEBUG_THEME_PARSER(qDebug()<<"Bold : normal");
            }
            if(pattern.capturedTexts().last().indexOf(familyPattern) != -1)
            {
                font.setFamily(familyPattern.capturedTexts().last());
                DEBUG_THEME_PARSER(qDebug()<<"Family : "<<familyPattern.capturedTexts().last());
            }
            if(pattern.capturedTexts().last().indexOf(pointSizePattern) != -1)
            {
                font.setPointSize(pointSizePattern.capturedTexts().last().toInt());
                DEBUG_THEME_PARSER(qDebug()<<"PointSize : "<<pointSizePattern.capturedTexts().last().toInt());
            }
            charFormat.setFont(font);
        }
        index = string.indexOf(pattern, index + length);
    }
    return charFormat;
/*
    if(charFormat.font() != defaultFormat.font())
    {
        config += QString("font(");
        if(charFormat.font().family().compare(defaultFormat.font().family()))
        {
            config += QString("\"")+charFormat.font().family()+QString("\" ");
        }
        if(charFormat.font().pointSize() != defaultFormat.font().pointSize())
        {
            config += QString::number(charFormat.font().pointSize())+QString(" ");
        }
        if(charFormat.font().bold() != defaultFormat.font().bold())
        {
            config += (charFormat.font().bold()?"bold":"normal")+QString(" ");
        }
        config +=QString(") ");
    }

    if(charFormat.foreground().style() != Qt::NoBrush)
    {
        config += " foreground("+QString::number(charFormat.foreground().color().red())+
                ", "+QString::number(charFormat.foreground().color().green())+
                ", "+QString::number(charFormat.foreground().color().blue())+
                ") ";
    }
    if(charFormat.background().style() != Qt::NoBrush)
    {
        config += " background("+QString::number(charFormat.background().color().red())+
                    ", "+QString::number(charFormat.background().color().green())+
                    ", "+QString::number(charFormat.background().color().blue())+
                    ") ";
    }
    if(config.isEmpty())
    {
        config = "inherit";
    }
    return config;*/
}

void ConfigManager::changePointSizeBy(int delta)
{
    foreach(const QString &key, this->textCharFormats->keys())
    {
        QTextCharFormat format(this->textCharFormats->value(key));
        QFont font(format.font());
        font.setPointSize(font.pointSize()+delta);
        format.setFont(font);
        this->textCharFormats->insert(key,format);
    }
}

void ConfigManager::setPointSize(int size)
{
    foreach(const QString &key, this->textCharFormats->keys())
    {
        QTextCharFormat format(this->textCharFormats->value(key));
        QFont font(format.font());
        font.setPointSize(size);
        format.setFont(font);
        this->textCharFormats->insert(key,format);
    }
}


void ConfigManager::save()
{
    QDir dir;
    QString dataLocation("");
#if QT_VERSION < 0x050000
    dataLocation = QDesktopServices::storageLocation(QDesktopServices::DataLocation);
#else
    dataLocation = QStandardPaths::writableLocation(QStandardPaths::DataLocation);
#endif
    if(dataLocation.isEmpty())
    {
            //QMessageBox::warning(this->mainWindow,QObject::tr("Attention"), QObject::tr("QStandardPaths::DataLocation est introuvable."));
            return;
    }
    if(!dir.exists(dataLocation))
    {
        dir.mkpath(dataLocation);
    }
    //qDebug()<<QStandardPaths::writableLocation(QStandardPaths::DataLocation);
    //return;
    QSettings settings;
    settings.beginGroup("theme");
    QSettings file(dataLocation+dir.separator()+settings.value("theme").toString()+".sim-theme",QSettings::IniFormat);
//    file.beginGroup("Theme");

    QMapIterator<QString,QTextCharFormat> it(*this->textCharFormats);
    QString key;
    QTextCharFormat val;
    while(it.hasNext())
    {
        it.next();
        file.setValue(it.key(),ConfigManager::textCharFormatToString(it.value(),this->textCharFormats->value("normal")));
    }
    file.setValue("normal",this->textCharFormatToString(this->textCharFormats->value("normal"),QTextCharFormat()));

}


bool ConfigManager::load(QString theme)
{
    QDir dir;
    QString dataLocation("");
#if QT_VERSION < 0x050000
    dataLocation = QDesktopServices::storageLocation(QDesktopServices::DataLocation);
#else
    dataLocation = QStandardPaths::writableLocation(QStandardPaths::DataLocation);
#endif
    if(dataLocation.isEmpty())
    {
            //QMessageBox::warning(this->mainWindow,QObject::tr("Attention"), QObject::tr("QStandardPaths::DataLocation est introuvable."));
            return false;
    }
    if(theme.isEmpty())
    {
        QSettings settings;
        settings.beginGroup("theme");
        theme = settings.value("theme").toString();
    }
    else
    {
        QSettings settings;
        settings.beginGroup("theme");
        settings.setValue("theme",theme);
    }
    this->_theme = theme;
    QSettings file(dataLocation+dir.separator()+theme+".sim-theme",QSettings::IniFormat);

    if(!file.contains("normal"))
    {
        return false;
    }

    QStringList keys = file.allKeys();

    QTextCharFormat normal = this->stringToTextCharFormat(file.value("normal").toString());
    this->textCharFormats->insert("normal", normal);
    foreach(const QString& key, keys)
    {
        if(!key.compare("normal"))
        {
            continue;
        }
        QTextCharFormat val = ConfigManager::stringToTextCharFormat(file.value(key).toString(), normal);
        this->textCharFormats->insert(key, val);
    }

    return true;
}

void ConfigManager::openThemeFolder()
{
    QString dataLocation;
#if QT_VERSION < 0x050000
    dataLocation = QDesktopServices::storageLocation(QDesktopServices::DataLocation);
#else
    dataLocation = QStandardPaths::writableLocation(QStandardPaths::DataLocation);
#endif
    if(dataLocation.isEmpty())
    {
            return;
    }

    QDesktopServices::openUrl(QUrl("file:///" + dataLocation));
}

QStringList ConfigManager::themesList()
{
    QString dataLocation("");
#if QT_VERSION < 0x050000
    dataLocation = QDesktopServices::storageLocation(QDesktopServices::DataLocation);
#else
    dataLocation = QStandardPaths::writableLocation(QStandardPaths::DataLocation);
#endif
    if(dataLocation.isEmpty())
    {
            //QMessageBox::warning(this->mainWindow,QObject::tr("Attention"), QObject::tr("QStandardPaths::DataLocation est introuvable."));
        return QStringList();
    }
    QDir dir(dataLocation);
    return dir.entryList(QDir::Files | QDir::Readable, QDir::Name).filter(QRegExp("\\.sim-theme"));
}

