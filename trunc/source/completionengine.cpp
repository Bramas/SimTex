#include "completionengine.h"
#include <QListWidgetItem>
#include <QHeaderView>
#include <QFile>
#include <QDebug>
#include <QTextStream>
#include "widgettextedit.h"

CompletionEngine::CompletionEngine(WidgetTextEdit *parent) :
    QListWidget(parent),
    _commandBegin(QString(""))
{
    this->setVisible(false);


    this->loadFile(":/completion/tex.cwl");
    this->loadFile(":/completion/latex-document.cwl");
    this->loadFile(":/completion/latex-mathsymbols.cwl");
    this->loadFile(":/completion/amsmath.cwl");


    _words.removeDuplicates();
    _words.sort();
    qDebug()<<"Completion engine Initialized : "<<_words.count()<<" words";
}
void CompletionEngine::loadFile(QString filename)
{
    QFile userTagsfile(filename);

    if (!userTagsfile.open(QFile::ReadOnly)) return;

    QString line;
    QTextStream in(&userTagsfile);
    while (!in.atEnd())
    {
        line = in.readLine();
        if (!line.isEmpty()) _words.append(line.remove("\n"));
    }

}

void CompletionEngine::proposeCommand(int top, int left, QString commandBegin)
{
    this->_commandBegin = commandBegin;
    if(commandBegin.length()<4)
    {
        this->parentWidget()->setFocus();
        return;
    }
    QRegExp commandRegex = QRegExp("^\\"+QString(commandBegin).replace('{',"\\{"));
    this->addCustomWordFromSource(); //dont know where to put it but it seems to be a fast function so it's ok!
    QStringList found = this->_words.filter(commandRegex);//, Qt::CaseInsensitive));
    QStringList customFound = this->_customWords.filter(commandRegex);//, Qt::CaseInsensitive));
    found.append(customFound);
    found.sort();

    if(found.empty() ||
            found.count() == 1 && (found.first().length() == commandBegin.length() || found.first().indexOf('#')  == commandBegin.length()))
    {
        found.clear();
        this->parentWidget()->setFocus();
        return;
    }

    this->clear();
    this->setVisible(true);
    int idx = 0;
    int dieseIndex;
    foreach(const QString &word, found)
    {
        if(dieseIndex = word.indexOf(QRegExp("#")) != -1)
        {
            this->insertItem(idx++,word.left(word.length() - dieseIndex - 1));
        }
        else
        {
            this->insertItem(idx++,word);
        }

    }
    this->setItemSelected(this->item(0),true);
    this->setCurrentRow(0,QItemSelectionModel::Rows);
    this->setGeometry(top,left,300,300);
}

QString CompletionEngine::acceptedWord()
{
    if(!this->selectedItems().count())
    {
        return QString("");
    }
    QString word = this->selectedItems().first()->text();
    return word.right(word.size() - _commandBegin.size());
}

void CompletionEngine::keyPressEvent(QKeyEvent *event)
{

    if(event->key() == Qt::Key_Alt ||
            event->key() == Qt::Key_AltGr ||
            event->key() == Qt::Key_Control ||
            event->key() == Qt::Key_Shift)
    {
        return;
    }
    if(event->key() == Qt::Key_Return ||
            event->key() == Qt::Key_Enter ||
            event->key() == Qt::Key_Up ||
            event->key() == Qt::Key_Down)
    {
        QListWidget::keyPressEvent(event);
        return;
    }
    if(event->text().contains(QRegExp("[^a-zA-Z\\{\\-_]")) || event->text().isEmpty())
    {
        this->setVisible(false);
        dynamic_cast<WidgetTextEdit*>(this->parentWidget())->setFocus(event);
        return;
    }
    dynamic_cast<WidgetTextEdit*>(this->parent())->insertPlainText(event->text());
}

void CompletionEngine::addCustomWordFromSource()
{
    _customWords.clear();
    QString source = dynamic_cast<WidgetTextEdit*>(this->parent())->toPlainText();
    QRegExp patternCommand("\\\\(re){0,1}newcommand\\{([^\\}]*)\\}");
    int index = source.indexOf(patternCommand);
    while(index != -1)
    {
        _customWords.append(patternCommand.capturedTexts().last());
        index = source.indexOf(patternCommand, index + 1);
    }


    QRegExp patternLabel("\\\\label\\{([^\\}]*)\\}");
    index = source.indexOf(patternLabel);
    while(index != -1)
    {
        _customWords.append("\\ref{"+patternLabel.capturedTexts().last()+"}");
        index = source.indexOf(patternLabel, index + 1);
    }
}
