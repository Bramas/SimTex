#include "configmanager.h"
#include <QFont>
#include <QColor>
#include <QSettings>
#if QT_VERSION < 0x050000
    #include <QDesktopServices>
#else
    #include <QStandardPaths>
#endif

#include <QMapIterator>
#include <QDir>
#include <QMessageBox>
#include <QDebug>
#include <QCoreApplication>

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

    QFont font("Consolas");
    font.setPointSize(settings.value("pointSize",12).toInt());
    QTextCharFormat charFormat;


    if(!settings.contains("theme"))
    {
        settings.setValue("theme",QString("dark"));
    }

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
    }

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

QString ConfigManager::textCharFormatToString(QTextCharFormat charFormat)
{
    return QString(charFormat.font().bold()?"Bold":"Normal")+
            " foreground("+QString::number(charFormat.foreground().color().red())+
            ", "+QString::number(charFormat.foreground().color().green())+
            ", "+QString::number(charFormat.foreground().color().blue())+
            ") "+
            " background("+QString::number(charFormat.background().color().red())+
            ", "+QString::number(charFormat.background().color().green())+
            ", "+QString::number(charFormat.background().color().blue())+
            ") ";
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
            QMessageBox::warning(this->mainWindow,QObject::tr("Attention"), QObject::tr("QStandardPaths::DataLocation est introuvable."));
    }
    if(!dir.exists(dataLocation))
    {
        dir.mkpath(dataLocation);
    }
    //qDebug()<<QStandardPaths::writableLocation(QStandardPaths::DataLocation);
    //return;
    QSettings file(dataLocation+dir.separator()+"theme.txt",QSettings::IniFormat);
    file.beginGroup("Theme");

    QMapIterator<QString,QTextCharFormat> it(*this->textCharFormats);
    QString key;
    QTextCharFormat val;
    while(it.hasNext())
    {
        it.next();
        file.setValue(it.key(),ConfigManager::textCharFormatToString(it.value()));
    }

}


