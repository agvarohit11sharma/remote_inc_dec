#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFileDialog>
#include <QBuffer>
int var =10;
int ind =0;
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    ,sharedMemory("QSharedMemory_practice")
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
     ui->label->setText("whats the string, you want");
//     sharedMemory("QSharedMemory_practice");
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
    st="\0";
    if (sharedMemory.isAttached())
        detach();
// ui->label->setText("whats the string, you want");
//QString st = QString::number(var);
//    QString st = "23,2,3,545,5,3,6,6";
//     QString st;
  switch (ind){

    case 0:
                st="0,";
                st+=QString::number(arr[0]);
                break;
    case 1:
            st="1,";
            st+=QString::number(arr[1]);
            break;
    case 2:
            st="2,";
            st+=QString::number(arr[2]);
            break;
    case 3:
            st="3,";
            st+=QString::number(arr[3]);
            break;
    case 4:
            st="4,";
            st+=QString::number(arr[4]);
            break;
    case 5:
            st="5,";
            st+=QString::number(arr[5]);
            break;
    case 6:
            st="6,";
            st+=QString::number(arr[6]);
            break;
    case 7:
            st="7,";
            st+=QString::number(arr[7]);
            break;
    default:
        qDebug()<<"unknown option selected";
    }

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

void MainWindow::on_comboBox_currentIndexChanged(int index)
{
    ind=index;

    qDebug()<<index+1;

}

