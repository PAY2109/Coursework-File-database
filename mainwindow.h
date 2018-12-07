#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTableView>
#include "QStandardItemModel"
#include "QStandardItem"
#include <QStringList>
#include <QFile>
#include <QFileDialog>
#include <QTextStream>
#include <QMessageBox>
#include <QAction>
#include <QMenu>
#include <QDebug>
#include "startdialog.h"
#include "container.h"
#include "newelement.h"
#include <QStatusBar>

extern List L;


namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();


private slots:
    void appendDB(); //append database from other file
    void closeFile(); // close file
    void newFile(); // New database
    void editCell(); // edit cell
    void showAbout(); // show About window
    void openFile(); // open file
    void saveFile(); // save file
    void on_ButtonNewElem_clicked(); // add new element
    void on_delElemBtn_clicked(); // delete element(s)
    void searchButton();
    void cancelSearchButton();
    void searchElement();


private:
    Ui::MainWindow *ui;
    QLineEdit* m_edit;
    startDialog* sDialogue;
    QStandardItemModel *model;
    QAction *newAct;
    QAction *openAct;
    QAction *saveAct;
    QAction *closeAct;
    QAction *about;
    QAction *add;
    QAction *del;
    QAction *search;
    QAction *addListAct;
    QMessageBox *msg = new QMessageBox();
    QMenu *FileMenu;
    QWidget *search_Widget = new QWidget;
    QVBoxLayout *searchVLayout = new QVBoxLayout;
    QHBoxLayout *searchHLayout = new QHBoxLayout;
    QLineEdit *searchName=new QLineEdit;  
    QLineEdit * searchExtension= new QLineEdit;
    QLineEdit* searchSize= new QLineEdit;
    QLineEdit* searchPath= new QLineEdit;
    QPushButton *search_button = new QPushButton;
    QPushButton *search_cancel = new QPushButton;
    void editCells(); //connect editCell()
    void createActions();
    void makeMenu();
    void searchWidget();
    void database_update(); // update database
};

#endif // MAINWINDOW_H
