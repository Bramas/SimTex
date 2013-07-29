/***************************************************************************
 *   copyright       : (C) 2013 by Quentin BRAMAS                          *
 *   http://www.simtex.fr                                                  *
 *                                                                         *
 *   This file is part of SimTex.                                          *
 *                                                                         *
 *   SimTex is free software: you can redistribute it and/or modify        *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation, either version 3 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 *   SimTex is distributed in the hope that it will be useful,             *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of        *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         *
 *   GNU General Public License for more details.                          *
 *                                                                         *
 *   You should have received a copy of the GNU General Public License     *
 *   along with SimTex.  If not, see <http://www.gnu.org/licenses/>.       *                         *
 *                                                                         *
 ***************************************************************************/

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
    mainWindow(0),
    textCharFormats(new QMap<QString,QTextCharFormat>())
{

    qDebug()<<"Init ConfigManager";

    QCoreApplication::setOrganizationName("Ultratools");
    QCoreApplication::setOrganizationDomain("ultratools.org");
    QCoreApplication::setApplicationName("SimTex");
    QSettings::setDefaultFormat(QSettings::IniFormat);

    checkRevision();

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

}
void ConfigManager::setMainWindow(QWidget * mainWindow)
{
    this->mainWindow = mainWindow;
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
    QSettings settings;
    settings.beginGroup("theme");
    QSettings file(dataLocation+dir.separator()+settings.value("theme").toString()+".sim-theme",QSettings::IniFormat);

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

    DEBUG_THEME_PARSER(qDebug()<<"Style normal :");
    QTextCharFormat normal = this->stringToTextCharFormat(file.value("normal").toString());
    this->textCharFormats->insert("normal", normal);
    foreach(const QString& key, keys)
    {
        if(!key.compare("normal"))
        {
            continue;
        }

        DEBUG_THEME_PARSER(qDebug()<<"Style "<<key<<" :");
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


void ConfigManager::checkRevision()
{
    QSettings settings;

    int fromVersion = settings.value("revision",0).toInt();

    switch(fromVersion)
    {

        case 0:
            qDebug()<<"First launch of SimTex";
            QString dataLocation("");
            QString documentLocation("");
        #if QT_VERSION < 0x050000
            dataLocation = QDesktopServices::storageLocation(QDesktopServices::DataLocation);
            documentLocation = QDesktopServices::storageLocation(QDesktopServices::DocumentsLocation);
        #else
            dataLocation = QStandardPaths::writableLocation(QStandardPaths::DataLocation);
            documentLocation = QStandardPaths::writableLocation(QStandardPaths::DocumentsLocation);
        #endif
            if(dataLocation.isEmpty())
            {
                return;
            }
            QDir dir;
            dir.mkpath(dataLocation);
            QFile theme;
            theme.copy(":data/theme/dark.sim-theme", dataLocation+dir.separator()+"dark.sim-theme");
            theme.copy(":data/theme/light.sim-theme", dataLocation+dir.separator()+"light.sim-theme");

            settings.setValue("lastFolder",documentLocation);

     }
     settings.setValue("revision",1);
}

