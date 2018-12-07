#ifndef NEWDATABASE_H
#define NEWDATABASE_H

#include <QDialog>
#include <QLineEdit>
#include <QPushButton>
#include <QBoxLayout>
#include <QLabel>
namespace Ui {
class newdatabase;
}

class newdatabase : public QDialog
{
    Q_OBJECT

public:
    explicit newdatabase(QWidget *parent = nullptr);
    ~newdatabase();

private:
    Ui::newdatabase *ui;
    QLineEdit* nameLine;
    QLineEdit* extensionLine;
    QLineEdit* sizeLine;
    QLineEdit* pathLine;
    QLabel* nameLabel;
    QLabel* extensionLabel;
    QLabel* sizeLabel;
    QLabel* pathLabel;
public slots:
    void firstElement();

};

#endif // NEWDATABASE_H
