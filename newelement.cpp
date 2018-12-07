#include "newelement.h"
#include "ui_newelement.h"
#include "mainwindow.h"



newElement::newElement(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::newElement)
{
    ui->setupUi(this);
    this->setWindowTitle("New element");
    QBoxLayout* layout = new QVBoxLayout;
    nameLine = new QLineEdit;
    nameLine->setPlaceholderText("Enter file`s name");
    extensionLine = new QLineEdit;
    extensionLine->setPlaceholderText("Enter extension");
    sizeLine = new QLineEdit;
    sizeLine->setPlaceholderText("Enter size");
    sizeLine->setValidator( new QIntValidator(0, 10000000, this) );
    pathLine = new QLineEdit;
    pathLine->setPlaceholderText("Enter path");
    indexLine= new QLineEdit;
    indexLine->setPlaceholderText("OR enter index here");
    indexLine->setValidator( new QIntValidator(0, L.GetCount()+1, this) );
    layout->addWidget( nameLine );
    layout->addWidget(extensionLine);
    layout->addWidget(sizeLine);
    layout->addWidget(pathLine);
    QPushButton* headBtn = new QPushButton( "Вставить в начало");
    connect (headBtn, SIGNAL(clicked()),SLOT(firstElement()));
    layout->addWidget(headBtn);
    QPushButton* tailBtn = new QPushButton( "Вставить в конец");
    connect (tailBtn, SIGNAL(clicked()),SLOT(lastElement()));
    layout->addWidget(tailBtn);
    layout->addWidget(indexLine);
    QPushButton* randBtn = new QPushButton( "Вставить по индексу");
    connect (randBtn, SIGNAL(clicked()),SLOT(randElement()));
    layout->addWidget(randBtn);
    setLayout( layout );
}

newElement::~newElement()
{
    delete ui;
}

void newElement::firstElement()
{
    L.AddHead(nameLine->text().toStdString(), extensionLine->text().toStdString(), sizeLine->text().toInt(),pathLine->text().toStdString());
    this->close();
}
void newElement::lastElement()
{
    L.AddTail(nameLine->text().toStdString(), extensionLine->text().toStdString(), sizeLine->text().toInt(),pathLine->text().toStdString());
    this->close();
}
void newElement::randElement()
{
    L.InsertWithConditions(indexLine->text().toInt(),nameLine->text().toStdString(), extensionLine->text().toStdString(), sizeLine->text().toInt(),pathLine->text().toStdString());
    this->close();
}
