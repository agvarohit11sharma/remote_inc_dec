#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFileDialog>
#include <QBuffer>
int var =10;
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent),sharedMemory("QSharedMemory_practice")
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
     ui->label->setText("whats the string, you want");
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_pushButton_increment_clicked()
{

    var++;
    QString st = QString::number(var);
         ui->label->setText(st);
        QBuffer buffer;
        buffer.open(QBuffer::ReadWrite);
        QDataStream out(&buffer);
        out << st;
        int size = buffer.size();
        sharedMemory.lock();
        char *to = (char*)sharedMemory.data();
        const char *from = buffer.data().data();
        memcpy(to, from, qMin(sharedMemory.size(), size));
        sharedMemory.unlock();
}


void MainWindow::on_pushButton_decrement_clicked()
{

}


void MainWindow::on_pushButton_connect_clicked()
{
    if (sharedMemory.isAttached())
        detach();
// ui->label->setText("whats the string, you want");
//QString st = QString::number(var);
    QString st = "23,2,3,545,5,3,6,6";

     ui->label->setText(st);
qDebug()<<st;

    // load into shared memory
    QBuffer buffer;
    buffer.open(QBuffer::ReadWrite);
    QDataStream out(&buffer);
    out << st;
    int size = buffer.size();
    qDebug()<<size;

    if (!sharedMemory.create(size)) {
        ui->label->setText(tr("Unable to create shared memory segment."));
        return;
    }
    sharedMemory.lock();
    char *to = (char*)sharedMemory.data();
    const char *from = buffer.data().data();
    memcpy(to, from, qMin(sharedMemory.size(), size));
    sharedMemory.unlock();

}

void MainWindow::detach()
{
    if (!sharedMemory.detach())
        ui->label->setText(tr("Unable to detach from shared memory."));
}
