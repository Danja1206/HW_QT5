#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFileDialog>
#include <QMessageBox>
#include <QShortcut>
#include <QTranslator>
#include "filemanager.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->label->hide();
    MainWindow::key4 = new QShortcut(QKeySequence(Qt::CTRL + Qt::Key_Q), this, SLOT(close()));
    MainWindow::key2 = new QShortcut(QKeySequence(Qt::CTRL + Qt::Key_O), this, SLOT(openFile()));
    MainWindow::key1 = new QShortcut(QKeySequence(Qt::CTRL + Qt::Key_N), this, SLOT(createFile()));
    MainWindow::key3 = new QShortcut(QKeySequence(Qt::CTRL + Qt::Key_S), this, SLOT(saveFile()));
    ui->pushButton_10->hide();
    ui->pushButton_9->hide();
    ui->pushButton_8->hide();
    ui->pushButton_7->hide();
    ui->pushButton_6->hide();
    MainWindow::fileManager = new FileManager(this);
    fileManager->hide();
}

MainWindow::~MainWindow()
{
    delete ui;
}

QString path;
int changeID;

void MainWindow::on_pushButton_clicked()
{
    openFile();
    ui->plainTextEdit->setReadOnly(0);

}

void MainWindow::on_pushButton_2_clicked()
{
    saveFile();
}

void MainWindow::on_pushButton_3_clicked()
{
    QFile file(":/infoTxt/FAO.txt");
    if(file.open(QIODevice::ReadOnly))
    {
        QByteArray ba = file.readAll();
        QString text(ba);
            QMessageBox::about(this,"",text);
    }
}

void MainWindow::createFile()
{
    QString fileName = QFileDialog::getSaveFileName(this, tr("Создать файл"),path, "*.txt");
    if(fileName.isEmpty()) return;
    QFile file(fileName);
    if(file.open(QIODevice::WriteOnly))
    {
        QString text = ui->plainTextEdit->toPlainText();
        QByteArray ba = text.toUtf8();
        file.write(ba,ba.length());
    }

}

void MainWindow::openFile()
{
    path = QFileDialog::getOpenFileName(this,"Открыть файл", QDir::currentPath(), "*.txt");
    if(path.isEmpty()) return;
    ui->label->setText(path);
    ui->label->show();
    QFile file(path);
    if(file.open(QIODevice::ReadOnly))
    {
        QByteArray ba = file.readAll();
        QString text(ba);
        ui->plainTextEdit->setPlainText(text);
    }
}

void MainWindow::saveFile()
{
    QString fileName = QFileDialog::getSaveFileName(this, tr("Сохранить файл как"),path, "*.txt;;*.html");
    if(fileName.isEmpty()) return;
    QFile file(fileName);
    if(file.open(QIODevice::WriteOnly))
    {
        QString text = ui->plainTextEdit->toPlainText();
        QByteArray ba = text.toUtf8();
        file.write(ba,ba.length());
    }
}

void MainWindow::on_pushButton_4_clicked()
{
    openFile();
    ui->plainTextEdit->setReadOnly(1);
}

void MainWindow::on_pushButton_5_clicked()
{
    ui->pushButton_10->show();
    ui->pushButton_9->show();
    ui->pushButton_8->show();
    ui->pushButton_7->show();
    ui->pushButton_6->show();
    ui->pushButton_5->hide();
}

void MainWindow::keyPressEvent(QKeyEvent *event)
{
    bool check = false;
    switch (changeID) {
    case 1:
        delete key1;
        MainWindow::key1 = new QShortcut(QKeySequence(event->key()), this, SLOT(createFile()));
        check = true;
        break;
    case 2:
        delete key2;
        MainWindow::key2 = new QShortcut(QKeySequence(event->key()), this, SLOT(openFile()));
        check = true;
        break;
    case 3:
        delete key3;
        MainWindow::key3 = new QShortcut(QKeySequence(event->key()), this, SLOT(saveFile()));
        check = true;
        break;
    case 4:
        delete key4;
        MainWindow::key4 = new QShortcut(QKeySequence(event->key()), this, SLOT(close()));
        check = true;
        break;
    }
    changeID = 0;
    if(check)
        QMessageBox::about(this,tr("Обновление сочетания клавиш"),tr("Сочетание изменено!"));
}

void MainWindow::on_pushButton_9_clicked()
{
    changeID = 1;
}

void MainWindow::on_pushButton_8_clicked()
{
    changeID = 2;
}

void MainWindow::on_pushButton_6_clicked()
{
    changeID = 3;
}

void MainWindow::on_pushButton_10_clicked()
{
    ui->pushButton_10->hide();
    ui->pushButton_9->hide();
    ui->pushButton_8->hide();
    ui->pushButton_7->hide();
    ui->pushButton_6->hide();
    ui->pushButton_5->show();
}
bool isTranslated = false;
void MainWindow::on_pushButton_11_clicked()
{
    QTranslator translator;
    if(!isTranslated)
    {
    translator.load(":/tr/QtLanguage_en.qm");
    qApp->installTranslator(&translator);
    ui->retranslateUi(this);
    isTranslated = true;
    ui->pushButton_11->setText("ru");
    }
    else
    {
        translator.load(":/tr/QtLanguage_ru.qm");
        qApp->installTranslator(&translator);
        ui->retranslateUi(this);
        isTranslated = false;
        ui->pushButton_11->setText("en");
    }


}

bool isDarkTheme = false;

void MainWindow::on_pushButton_12_clicked()
{
    if(!isDarkTheme)
    {
        this->setStyleSheet("QMainWindow{background-color:black} QPlainTextEdit{background-color:black; color:white}");
        isDarkTheme = true;
        ui->pushButton_12->setText("Светлая тема");
    }
    else
    {
        this->setStyleSheet("QMainWindow{background-color:white} QPlainTextEdit{background-color:white;}");
        isDarkTheme = false;
        ui->pushButton_12->setText("Темная тема");
    }
}
bool isFileManagerOpen = false;

void MainWindow::on_pushButton_13_clicked()
{

    if(!isFileManagerOpen)
    {
       fileManager->show();
       isFileManagerOpen = true;
    }
    else
    {
       fileManager->hide();
       isFileManagerOpen = false;
    }
}
