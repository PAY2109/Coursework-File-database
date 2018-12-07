#include "startdialog.h"
#include "ui_startdialog.h"
#include <mainwindow.h>

startDialog::startDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::startDialog)
{
    ui->setupUi(this);

    this->resize(300,150);
    this->setWindowTitle("Start");
    QBoxLayout* layout = new QHBoxLayout;
    startLabel = new QLabel("Создать новую базу или загрузить существующую?");
    layout->addWidget(startLabel);
    QPushButton* newdbBtn = new QPushButton( "Новая база");
    connect (newdbBtn, SIGNAL(clicked()),SLOT(newbase()));
    layout->addWidget(newdbBtn);
    QPushButton* loaddbBtn = new QPushButton( "Загрузить базу");
    connect (loaddbBtn, SIGNAL(clicked()),SLOT(loadbase()));
    layout->addWidget(loaddbBtn);
    setLayout( layout );
}

startDialog::~startDialog()
{
    delete ui;
}

void startDialog::newbase()
{
    newdatabase* newBaseDlg =new newdatabase;
    this->close();
    newBaseDlg->exec();  //Start the "New base" dialog
}

void startDialog::loadbase()
{
    this->close();
}

