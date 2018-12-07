#include "newdatabase.h"
#include "ui_newdatabase.h"
#include "mainwindow.h"



newdatabase::newdatabase(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::newdatabase)
{
    ui->setupUi(this);
    this->setWindowTitle("New Database");
    QBoxLayout* layout = new QVBoxLayout;
    nameLine = new QLineEdit;
    nameLine->setPlaceholderText("Enter first file`s name");
    extensionLine = new QLineEdit;
    extensionLine->setPlaceholderText("Enter extension");
    sizeLine = new QLineEdit;
    sizeLine->setPlaceholderText("Enter size");
    sizeLine->setValidator( new QIntValidator(0, 10000000, this) );
    pathLine = new QLineEdit;
    pathLine->setPlaceholderText("Enter path");
    nameLabel = new QLabel;
    nameLabel->setText("Введите имя первого файла");
    extensionLabel = new QLabel("Введите его расширение");
    sizeLabel = new QLabel("Введите размер файла");
    pathLabel = new QLabel("Введите путь к файлу");
    layout->addWidget(nameLabel);
    layout->addWidget( nameLine );
    layout->addWidget(extensionLabel);
    layout->addWidget(extensionLine);
    layout->addWidget(sizeLabel);
    layout->addWidget(sizeLine);
    layout->addWidget(pathLabel);
    layout->addWidget(pathLine);
    setLayout( layout );
    QPushButton* createBtn = new QPushButton( "Новая база");
    connect (createBtn, SIGNAL(clicked()),SLOT(firstElement()));
    layout->addWidget(createBtn);
    setLayout( layout );
}

newdatabase::~newdatabase()
{
    delete ui;
}

void newdatabase::firstElement()
{
    L.AddHead(nameLine->text().toStdString(), extensionLine->text().toStdString(), sizeLine->text().toInt(),pathLine->text().toStdString());
    this->close();
}

