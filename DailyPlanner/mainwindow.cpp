#include "mainwindow.h"
#include "ui_mainwindow.h"

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



void MainWindow::on_addDayWindow1_clicked()
{
    QTime startTime = ui->timeStartWindow1->time();
    QTime endTime = ui->timeEndWindow1->time();
    if (startTime >= endTime)
    {
        QMessageBox::information(nullptr, "Problem", "Czas startu nie może być mniejszy niż czas końca czynności");
        return;
    }
    QString text = ui->textWindow1->text();
    if (text.isEmpty())
    {
        QMessageBox::information(nullptr, "Problem", "Treść zadania nie może być pusta");
        return;
    }
    QString timeText = startTime.toString("HH:mm") + "->" + endTime.toString("HH:mm");
    Task *task = new Task(nullptr, ui->textWindow1->text(), timeText);
    ui->day1layout->addWidget(task);
}


void MainWindow::on_addDayWindow2_clicked()
{
    QTime startTime = ui->timeStartWindow2->time();
    QTime endTime = ui->timeEndWindow2->time();
    if (startTime >= endTime)
    {
        QMessageBox::information(nullptr, "Problem", "Czas startu nie może być mniejszy niż czas końca czynności");
        return;
    }
    QString text = ui->textWindow2->text();
    if (text.isEmpty())
    {
        QMessageBox::information(nullptr, "Problem", "Treść zadania nie może być pusta");
        return;
    }
    QString timeText = startTime.toString("HH:mm") + "->" + endTime.toString("HH:mm");
    Task *task = new Task(nullptr, ui->textWindow2->text(), timeText);
    ui->day2layout->addWidget(task);
}


void MainWindow::on_addDayWindow3_clicked()
{
    QTime startTime = ui->timeStartWindow3->time();
    QTime endTime = ui->timeEndWindow3->time();
    if (startTime >= endTime)
    {
        QMessageBox::information(nullptr, "Problem", "Czas startu nie może być mniejszy niż czas końca czynności");
        return;
    }
    QString text = ui->textWindow3->text();
    if (text.isEmpty())
    {
        QMessageBox::information(nullptr, "Problem", "Treść zadania nie może być pusta");
        return;
    }
    QString timeText = startTime.toString("HH:mm") + "->" + endTime.toString("HH:mm");
    Task *task = new Task(nullptr, ui->textWindow3->text(), timeText);
    ui->day3layout->addWidget(task);
}

