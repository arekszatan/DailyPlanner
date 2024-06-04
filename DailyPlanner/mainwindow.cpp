#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFrame>
#include <QLabel>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_nextDatButton_clicked()
{

}


void MainWindow::on_previousDayButton_clicked()
{

}


void MainWindow::on_addDay1_clicked()
{
    QFrame *frame = new QFrame(this);
    frame->setFrameShape(QFrame::Box);
    frame->setLineWidth(2);
    QGridLayout *gridLayout = new QGridLayout(frame);
    QLabel *label = new QLabel("My Frame", this);
    QPushButton *button1 = new QPushButton("Button 1", this);
    QPushButton *button2 = new QPushButton("Button 2", this);
    gridLayout->addWidget(label, 0, 0, 1, 2);
    gridLayout->addWidget(button1, 1, 0);
    gridLayout->addWidget(button2, 1, 1);
    ui->day1layout->addWidget(frame);

}
void MainWindow::on_addDay2_clicked()
{

}


void MainWindow::on_addDay3_clicked()
{

}

