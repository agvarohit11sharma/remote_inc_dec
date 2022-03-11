#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QDialog>
#include <QSharedMemory>
#include<QDebug>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
      QSharedMemory sharedMemory;
    ~MainWindow();

private slots:
    void on_pushButton_increment_clicked();

    void on_pushButton_decrement_clicked();

    void on_pushButton_connect_clicked();

private:
    Ui::MainWindow *ui;
   void detach();
};
#endif // MAINWINDOW_H
