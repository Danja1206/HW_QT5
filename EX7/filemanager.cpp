#include "filemanager.h"
#include <QDir>
#include <QFileSystemModel>
#include <QMessageBox>
#include <QMouseEvent>

FileManager::FileManager(QWidget *parent) : QWidget(parent)
{
    QString sPath = "C:/";
    dirmodel = new QFileSystemModel(this);
    dirmodel->setRootPath(sPath);

    gridLay = new QGridLayout(this);
    this->setLayout(gridLay);
    tree = new QTreeView(this);
    gridLay->addWidget(tree, 1, 0, 10, 10);

    setMinimumSize(500, 300); // ограничиваем размер виджета
    tree->setModel(dirmodel);

}

void FileManager::show()
{
   tree->show();
}

void FileManager::hide()
{
   tree->hide();
}
