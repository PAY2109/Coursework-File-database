#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "container.h"

List L;


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setFixedSize(500,500);
    this->setWindowTitle("File database");
    ui->tableView->setFixedSize(460,370);
    makeMenu();
    startDialog* dlg = new startDialog;
    dlg->exec();
    if (L.GetCount()==0)
        openFile();
    database_update();
    searchWidget();
    editCells();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::database_update()
{
    model = new QStandardItemModel;
    QStringList header={"Файл","Расширение","Размер","Путь"};
    model->setHorizontalHeaderLabels(header);
    for (int i=1;i<L.GetCount()+1;i++)
    {
        QStandardItem *newName = new QStandardItem(QString::fromStdString(L.getName(i)));
        QStandardItem *newExtension = new QStandardItem(QString::fromStdString(L.getExtension(i)));
        QStandardItem *newSize = new QStandardItem(QString::number(L.getSize(i)));
        QStandardItem *newPath = new QStandardItem(QString::fromStdString(L.getPath(i)));
         model->setItem(i-1,0,newName);
         model->setItem(i-1,1,newExtension);
         model->setItem(i-1,2,newSize);
         model->setItem(i-1,3,newPath);
    }
    ui->tableView->setModel(model);
    ui->tableView->resizeRowsToContents();
    ui->tableView->resizeColumnsToContents();
    editCells();
    QString tmp="Size: "+ QString::number( L.GetCount())+ " elements";
    this->statusBar()->showMessage(tmp);
}

void MainWindow::on_ButtonNewElem_clicked()
{
    newElement* newEldial =new newElement;
    newEldial->exec();
    database_update();
}

void MainWindow::on_delElemBtn_clicked()
{
    if(ui->tableView->selectionModel()->hasSelection())
    {
    qDebug()<<"Delete element";
    QModelIndexList selection = ui->tableView->selectionModel()->selectedRows();
    std::sort(selection.begin(),selection.end());
    int indexListSelection=0;
    int counterSelection = selection.size();
    while(counterSelection!=0)
    {
        L.Del(selection[indexListSelection].row()-indexListSelection+1);
        indexListSelection++;
        counterSelection--;
    }
    database_update();
    editCells();
}
}

void MainWindow::saveFile()
{
    if(L.GetCount()!=0)
        {
        QString str = QFileDialog::getSaveFileName(this,tr("Open"),"C:",tr("Text (*.txt);;Book (*.bk);;All Files (*)"));//Get file path
        QFile *file = new QFile(str);//File with file path(str)
        ui->label->setText(str);
        file->open(QFile::WriteOnly);
        QTextStream out(file);//Make text stream
        out.setFieldAlignment(QTextStream::AlignLeft);//Set alignment
        out.setFieldWidth(2);//Set space between elements
        for(int i=1; i<=L.GetCount();i++)//Write data into file
        {
            out <<qSetFieldWidth(6)<<QString::fromStdString(L.getName(i))<< qSetFieldWidth(6) << QString::fromStdString(L.getExtension(i)) << qSetFieldWidth(8) << QString::number(L.getSize(i)) << qSetFieldWidth(30) << QString::fromStdString(L.getPath(i)) << qSetFieldWidth(0) << "\r\n" << qSetFieldWidth(2);
        }
        file->close();
        qDebug()<<"Save";
        }
        else
        {
            QMessageBox message(QMessageBox::Critical, "Your list is empty","Add something and then you can save this list");
            message.exec();
        }
}

void MainWindow::makeMenu()
{
    createActions();//This function creates actions
    FileMenu = ui->menuBar->addMenu(tr("File"));
    ui->menuBar->addAction(about);
    FileMenu->addAction(newAct);//Adding action "new" into "File"
    FileMenu->addAction(openAct);//Adding action "open" into "File"
    FileMenu->addAction(saveAct);//Adding action "save" into "File"
    FileMenu->addAction(closeAct);//Adding action "close" into "File"
    //Toolbar
    ui->mainToolBar->addAction(add);//Adding action "add" on the toolbar
    ui->mainToolBar->addAction(del);//Adding action "del" on the toolbar
    ui->mainToolBar->addAction(search);//Adding action "search" on the toolbar
    ui->mainToolBar->addAction(addListAct);//Adding action "append" on the toolbar
}

void MainWindow::createActions()
{
    newAct = new QAction(tr("&new"),this);
    newAct->setShortcuts(QKeySequence::New);
    newAct->setStatusTip(tr("Create new file"));
    newAct->setIcon(QIcon("C:\\icons\\newicon"));// Load icons
    connect(newAct, SIGNAL(triggered(bool)),this,SLOT(newFile()));//Make signal of "new" tab
    openAct = new QAction(tr("&open"),this);//Editing tab's text
    openAct->setShortcuts(QKeySequence::Open);
    openAct->setStatusTip(tr("Open file"));
    openAct->setIcon(QIcon("C:\\icons\\openicon"));
    connect(openAct,SIGNAL(triggered(bool)),this,SLOT(openFile()));
    saveAct = new QAction(tr("&save"),this);
    saveAct->setShortcut(QKeySequence::Save);
    saveAct->setStatusTip(tr("Save this file"));
    saveAct->setIcon(QIcon("C:\\icons\\saveicon"));
    connect(saveAct,SIGNAL(triggered(bool)),this,SLOT(saveFile()));
    //saveAct->setEnabled(false);
    closeAct = new QAction(tr("&close"),this);
    closeAct->setShortcut(QKeySequence::Close);
    closeAct->setStatusTip(tr("Close current file"));
    closeAct->setIcon(QIcon("C:\\icons\\exiticon"));
    connect(closeAct,SIGNAL(triggered(bool)),this,SLOT(closeFile()));
   // closeAct->setEnabled(false);
    add = new QAction(tr("&add"),this);
    add->setStatusTip(tr("Add new element"));
    add->setIcon(QIcon("C:\\icons\\addelementicon"));
    connect(add,SIGNAL(triggered(bool)),this,SLOT(on_ButtonNewElem_clicked()));
   // add->setEnabled(false);
    del = new QAction(tr("&delete"),this);
    del->setStatusTip(tr("Delete element"));
    del->setIcon(QIcon("C:\\icons\\deleteicon"));
    connect(del,SIGNAL(triggered(bool)),this,SLOT(on_delElemBtn_clicked()));
   // del->setEnabled(false);
    search = new QAction(tr("&search"),this);
    search->setStatusTip(tr("Search element"));
    search->setIcon(QIcon("C:\\icons\\searchicon"));
    connect(search,SIGNAL(triggered(bool)),this,SLOT(searchElement()));
   // search->setEnabled(false);
    addListAct = new QAction(tr("&append"),this);
    addListAct->setStatusTip(tr("Append data to current list"));
    addListAct->setIcon(QIcon("C:\\icons\\listicon"));
    connect(addListAct,SIGNAL(triggered(bool)),this,SLOT(appendDB()));
   // addListAct->setEnabled(false);
    about = new QAction(tr("&About"),this);
    about->setStatusTip(tr("Show information about this work"));
    connect(about,SIGNAL(triggered(bool)),this,SLOT(showAbout()));
    msg->setWindowTitle("About");
    msg->setText("Coded by Yagunov Pavel with love");//Set text in window
}

void MainWindow::openFile()
{
    QString str = QFileDialog::getOpenFileName(this,tr("Open"),"C:",tr("Text (*.txt);;Book (*.bk);;All Files (*)"));//Get file path
    QFile file(str);//File with file path (str)
    //qDebug() << "Open file";
    if (!file.open(QIODevice::ReadOnly))
            return;
    else
    {
        openAct->setEnabled(false);
        newAct->setEnabled(false);
        saveAct->setEnabled(true);
        closeAct->setEnabled(true);
        add->setEnabled(true);
        del->setEnabled(true);
        search->setEnabled(true);
        addListAct->setEnabled(true);
        ui->label->setText(str);
        ui->label->setVisible(true);
        ui->tableView->setVisible(true);
        QStringList currentObjectList;//Contain data for object
        QString tempObj;//Contain temporary object
        while(!file.atEnd())
        {
            tempObj = file.readLine();
            currentObjectList = tempObj.split(QRegExp("[\r\n\t ]+"), QString::SkipEmptyParts);//Spliting object to parts
            L.AddTail(currentObjectList[0].toStdString(),currentObjectList[1].toStdString(),currentObjectList[2].toInt(),currentObjectList[3].toStdString());            
            database_update();
        }
    }
editCells();
}
void MainWindow::editCells()
{
    qDebug() << "Edit cells";
    QObject::connect(ui->tableView->model(),SIGNAL(dataChanged(QModelIndex,QModelIndex,QVector<int>)),this,SLOT(editCell()));//Make signal for editing cells
}

void MainWindow::editCell()
{
    qDebug() << "Edit cell";
    int j=0;
    for(int i=0;i<model->rowCount();i++)
    {
            if(QString::fromStdString(L.getName(i+1)) != model->index(i,j).data().toString())
            {
                L.setName(i+1, model->index(i,j).data().toString().toStdString());
                qDebug()<<"changename";
            }
            if(QString::fromStdString(L.getExtension(i+1)) != model->index(i,j+1).data().toString())
            {
                L.setExtension(i+1, model->index(i,j+1).data().toString().toStdString());
                qDebug()<<"changeextens";
            }
            if(L.getSize(i+1) !=model->index(i,j+2).data().toInt())
            {
                L.setSize(i+1, model->index(i,j+2).data().toInt());
                qDebug()<<"changesize";
            }
            if(QString::fromStdString(L.getPath(i+1))!=model->index(i,j+3).data().toString())
            {
                L.setPath(i+1, model->index(i,j+3).data().toString().toStdString());
                qDebug()<<"changepath";
            }
    }
    qDebug()<<"editing over";
}



void MainWindow::appendDB()
{
    QString str = QFileDialog::getOpenFileName(this,tr("Open"),"C:",tr("Text (*.txt);;Book (*.bk);;All Files (*)"));//Get file path
    QFile file(str);//File with file path (str)
    //qDebug() << "Open file";
    if (!file.open(QIODevice::ReadOnly))
            return;
    else
    {
        openAct->setEnabled(false);
        newAct->setEnabled(false);
        saveAct->setEnabled(true);
        closeAct->setEnabled(true);
        add->setEnabled(true);
        del->setEnabled(true);
        search->setEnabled(true);
        addListAct->setEnabled(true);
       ui->label->setText(str);
        ui->label->setVisible(true);
        ui->tableView->setVisible(true);
        QStringList currentObjectList;
        QString tempObj;
        while(!file.atEnd())
        {
            tempObj = file.readLine();//Read line into List tempObj
            currentObjectList = tempObj.split(QRegExp("[\r\n\t ]+"), QString::SkipEmptyParts);//Spliting object to parts
            L.AddTail(currentObjectList[0].toStdString(),currentObjectList[1].toStdString(),currentObjectList[2].toInt(),currentObjectList[3].toStdString());
            database_update();
        }
    }
    editCells();
}


void MainWindow::searchElement()
{
    qDebug() << "Search";
    search_Widget->show();
}

void MainWindow::searchWidget()
{
    search_Widget->setWindowTitle("Search");
    search_Widget->resize(225,150);
    searchName->setPlaceholderText("File name");
    searchExtension->setPlaceholderText("Extension");
    searchSize->setPlaceholderText("Size");
    searchPath->setPlaceholderText("Path");
    search_button->setText("search");
    search_cancel->setText("cancel");
    connect(search_button,SIGNAL(clicked(bool)),this,SLOT(searchButton()));//Make signal of search button
    connect(search_cancel,SIGNAL(clicked(bool)),this,SLOT(cancelSearchButton()));//Make signal of cancel button
    search_Widget->setLayout(searchVLayout);
    searchVLayout->addWidget(searchName);
    searchVLayout->addWidget(searchExtension);
    searchVLayout->addWidget(searchSize);
    searchVLayout->addWidget(searchPath);
    searchHLayout->addWidget(search_button);
    searchHLayout->addWidget(search_cancel);
    searchVLayout->addLayout(searchHLayout);
}

void MainWindow::searchButton()
{
    qDebug() << "search";
    ui->tableView->setSelectionMode(QAbstractItemView::MultiSelection);
    int j=0;
    for(int i=0;i<ui->tableView->model()->rowCount();i++)//Select rows
    {
        if(ui->tableView->model()->index(i,j).data().toString()== searchName->text() || ui->tableView->model()->index(i,j+1).data().toString()== searchExtension->text() || ui->tableView->model()->index(i,j+2).data().toString()== searchSize->text() || ui->tableView->model()->index(i,j+3).data().toString()== searchPath->text())
        {
            ui->tableView->selectRow(i);
        }
    }
    search_Widget->close();
    ui->tableView->setSelectionMode(QAbstractItemView::ExtendedSelection);
    searchName->setText("");
    searchExtension->setText("");
    searchSize->setText("");
    searchPath->setText("");
}

void MainWindow::cancelSearchButton()
{
    qDebug() << "cancel";
    search_Widget->close();
    searchName->setText("");
    searchExtension->setText("");
    searchSize->setText("");
    searchPath->setText("");
}

void MainWindow::showAbout()
{
    qDebug()<<"About";
    msg->show();
}

void MainWindow::closeFile()
{
    qDebug()<<"Close";
    add->setEnabled(false);
    del->setEnabled(false);
    search->setEnabled(false);
    addListAct->setEnabled(false);
    newAct->setEnabled(true);
    closeAct->setEnabled(false);
    saveAct->setEnabled(false);
    openAct->setEnabled(true);
    ui->label->setVisible(false);
    ui->tableView->setVisible(false);
    model->removeRows(0,L.GetCount());
    L.DelAll();
}


void MainWindow::newFile()
{
    qDebug()<<"New";
    add->setEnabled(true);
    del->setEnabled(true);
    search->setEnabled(true);
    addListAct->setEnabled(true);
    newAct->setEnabled(false);
    closeAct->setEnabled(true);
    saveAct->setEnabled(true);
    openAct->setEnabled(false);
    ui->label->setText("NewFile");
    ui->label->setVisible(true);
    ui->tableView->setVisible(true);
}
