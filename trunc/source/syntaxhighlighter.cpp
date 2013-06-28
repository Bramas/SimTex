#include "syntaxhighlighter.h"
#include <QTextCharFormat>
#include <QDebug>
#include "blockdata.h"
#include "configmanager.h"

SyntaxHighlighter::SyntaxHighlighter(QTextEdit *parent) :
    QSyntaxHighlighter(parent)
{
}

void SyntaxHighlighter::highlightBlock(const QString &text)
{

    BlockData *blockData = new BlockData;
    if(this->previousBlockState() == 1)
    {
        blockData->insertDollar(-1);
    }

    int dollarPos = text.indexOf( '$' );
    while ( dollarPos != -1 )
    {
        blockData->insertDollar(dollarPos);
        dollarPos = text.indexOf( '$', dollarPos+1 );
    }


    int leftPos = text.indexOf( '{' );
    while ( leftPos != -1 )
      {
      ParenthesisInfo *info = new ParenthesisInfo;
      info->character = '{';
      info->position = leftPos;

      blockData->insertPar( info );
      leftPos = text.indexOf( '{', leftPos+1 );
      }

    int rightPos = text.indexOf('}');
    while ( rightPos != -1 )
      {
      ParenthesisInfo *info = new ParenthesisInfo;
      info->character = '}';
      info->position = rightPos;

      blockData->insertPar( info );
      rightPos = text.indexOf( '}', rightPos+1 );
      }

    leftPos = text.indexOf( "\\begin{" );
    while ( leftPos != -1 )
      {
      LatexBlockInfo *info = new LatexBlockInfo;
      info->character = 'b';
      info->position = leftPos;

      blockData->insertLat( info );
      leftPos = text.indexOf("\\begin{", leftPos+1 );
      }

    rightPos = text.indexOf("\\end{");
    while ( rightPos != -1 )
      {
      LatexBlockInfo *info = new LatexBlockInfo;
      info->character = 'e';
      info->position = rightPos;

      blockData->insertLat( info );
      rightPos = text.indexOf("\\end{", rightPos+1 );
      }

    setCurrentBlockUserData(blockData);







    QTextCharFormat formatNormal = ConfigManager::Instance.getTextCharFormats()->value("normal");
    QTextCharFormat formatCommand = ConfigManager::Instance.getTextCharFormats()->value("command");
    QTextCharFormat formatComment = ConfigManager::Instance.getTextCharFormats()->value("comment");
    QTextCharFormat formatMath = ConfigManager::Instance.getTextCharFormats()->value("math");
    QTextCharFormat formatStructure = ConfigManager::Instance.getTextCharFormats()->value("structure");

     setFormat(0, text.size(), formatNormal);



     QString patternCommand = "\\\\[a(-zA-Z]+";
     QString patternStructure = "\\\\(sub){0,3}section\\{[^\\}]*\\}";

     this->highlightExpression(text,patternCommand,formatCommand);
     this->highlightExpression(text,patternStructure,formatStructure);



    int length=0;
    int lastindex = 0;
    int index=-1;
    int commentIndex = text.size();
    {
        QString patternComment =  "\\%.*$";
        QRegExp expression(patternComment);
        index = text.indexOf(expression);
        if(index >= 0)
        {
            length = expression.matchedLength();
            setFormat(index, length, formatComment);
            commentIndex = index;
        }
    }



    length=0;
    lastindex = 0;
    index=-1;



    QString mathLeftDelimiters = "\\$\\$|\\$|\\\\\\[";
    QString mathRightDelimiters = "\\$\\$|\\$|\\\\\\]";

    if(this->previousBlockState() == 1)
    {
        QString patternMathStart = "^((?!("+mathRightDelimiters+"|\\%)).)*("+mathRightDelimiters+")";
        QRegExp expression(patternMathStart);
        index = text.indexOf(expression);
        if(index >= 0 && index < commentIndex)
        {
            length = expression.matchedLength();
            setFormat(0, length, formatMath);
        }
    }

    QString patternMath = "("+mathLeftDelimiters+")((?!("+mathRightDelimiters+"|\\%)).)*("+mathRightDelimiters+")";
    lastindex = index = length;
    length = 0;
    {
        QRegExp expression(patternMath);
        index = text.indexOf(expression,index);
        while (index >= 0 && index < commentIndex) {
            lastindex = index;
            length = expression.matchedLength();
            setFormat(index, length, formatMath);
            index = text.indexOf(expression, index + length);
        }
    }
    QString patternMathEnd =  "("+mathLeftDelimiters+")((?!("+mathRightDelimiters+")).)*([\\%].*){0,1}$";
    QRegExp expression(patternMathEnd);
    index = text.indexOf(expression,lastindex+length);
    if(index >= 0 && index < commentIndex)
    {
        setFormat(index, text.length() - index, formatMath);
        this->setCurrentBlockState(1);
    }
    else
    {
        this->setCurrentBlockState(-1);
    }

    setFormat(commentIndex, text.size() - commentIndex, formatComment);

}
void SyntaxHighlighter::highlightExpression(const QString &text, const QString &pattern, const QTextCharFormat &format)
{
    int length;
    QRegExp expression(pattern);
    int index = text.indexOf(expression);
    while (index >= 0) {
        int length = expression.matchedLength();
        setFormat(index, length, format);
        index = text.indexOf(expression, index + length);
    }
}


