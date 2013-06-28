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





    QFile userTagsfile(":/completion/latex-document.cwl");

    if (!userTagsfile.open(QFile::ReadOnly)) return;

    QString line;
    QTextStream in(&userTagsfile);
    while (!in.atEnd())
    {
        line = in.readLine();
        if (!line.isEmpty()) _words.append(line.remove("\n"));
    }

    _words.removeDuplicates();
    _words.sort();
    qDebug()<<"Completion engine Initialized : "<<_words.count()<<" words";
}

void CompletionEngine::proposeCommand(int top, int left, QString commandBegin)
{
    this->_commandBegin = commandBegin;
    if(commandBegin.length()<4)
    {
        this->parentWidget()->setFocus();
        return;
    }
    QStringList found = this->_words.filter(QRegExp("^\\"+commandBegin));

    if(found.empty() ||
       found.count() == 1 && found.first() == commandBegin)
    {
        found.clear();
        this->parentWidget()->setFocus();
        return;
    }

    this->clear();
    this->setVisible(true);
    int idx = 0;
    foreach(const QString &word, found)
    {
        this->insertItem(idx++,word);
    }
    this->setItemSelected(this->item(0),true);
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
    if(event->key() == Qt::Key_Return || event->key() == Qt::Key_Enter || event->key() == Qt::Key_Up || event->key() == Qt::Key_Down)
    {
        QListWidget::keyPressEvent(event);
        return;
    }
    if(event->text().contains(QRegExp("[^a-zA-Z]")) || event->text().isEmpty())
    {
        this->setVisible(false);
        dynamic_cast<WidgetTextEdit*>(this->parentWidget())->setFocus(event);
        return;
    }
    dynamic_cast<WidgetTextEdit*>(this->parent())->insertPlainText(event->text());
}
