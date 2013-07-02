#ifndef DIALOGCLOSE_H
#define DIALOGCLOSE_H

#include <QDialog>

namespace Ui {
class DialogClose;
}

class DialogClose : public QDialog
{
    Q_OBJECT
    
public:
    explicit DialogClose(QWidget *parent = 0);
    ~DialogClose();
    bool confirmed(void) { return _confirmed; }
    void setMessage(QString message);

public slots:
    void confirmAndClose(void);
    
private:
    Ui::DialogClose *ui;

    bool _confirmed;
};

#endif // DIALOGCLOSE_H
