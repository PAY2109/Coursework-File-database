#ifndef NEWELEMENT_H
#define NEWELEMENT_H

#include <QDialog>
#include <QLineEdit>
#include <QPushButton>
#include <QBoxLayout>
#include <QLabel>

namespace Ui {
class newElement;
}

class newElement : public QDialog
{
    Q_OBJECT

public:
    explicit newElement(QWidget *parent = nullptr);
    ~newElement();
public slots:
    void firstElement(); //add element to head
    void lastElement(); //add element to tail
    void randElement(); //add element by index
private:
    Ui::newElement *ui;
    QLineEdit* nameLine;
    QLineEdit* extensionLine;
    QLineEdit* sizeLine;
    QLineEdit* pathLine;
    QLineEdit* indexLine;
};

#endif // NEWELEMENT_H
