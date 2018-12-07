#ifndef STARTDIALOG_H
#define STARTDIALOG_H

#include <QDialog>
#include <QLineEdit>
#include <QPushButton>
#include <QBoxLayout>
#include <newdatabase.h>
#include <QLabel>
namespace Ui {
class startDialog;
}

class startDialog : public QDialog
{
    Q_OBJECT

public:
    explicit startDialog(QWidget *parent = nullptr);
    ~startDialog();

   // QString getInput() const;

public slots:
    void newbase(); //create new database
    void loadbase(); // load a database

private:
    Ui::startDialog *ui;
    QLabel* startLabel;


};

#endif // STARTDIALOG_H
