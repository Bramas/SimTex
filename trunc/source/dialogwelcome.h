#ifndef DIALOGWELCOME_H
#define DIALOGWELCOME_H

#include <QDialog>

namespace Ui {
class DialogWelcome;
}
class QPushButton;

class DialogWelcome : public QDialog
{
    Q_OBJECT
    
public:
    explicit DialogWelcome(QWidget *parent = 0);
    ~DialogWelcome();
    QPushButton * getActionOpenLast();
    QPushButton * getActionOpen();
    QPushButton *getActionNew();
private:
    Ui::DialogWelcome *ui;
};

#endif // DIALOGWELCOME_H
