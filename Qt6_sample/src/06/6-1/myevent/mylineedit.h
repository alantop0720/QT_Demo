#ifndef MYLINEEDIT_H
#define MYLINEEDIT_H

#include <QLineEdit>

class MyLineEdit : public QLineEdit
{
    Q_OBJECT
public:
    explicit MyLineEdit(QWidget *parent = nullptr);
protected:
    void keyPressEvent(QKeyEvent *event) override;
};

#endif // MYLINEEDIT_H
