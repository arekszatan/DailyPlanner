#include "mainwindow.h"
#include "db.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    QDate nextDate = currentDate.addDays(1);
    QDate previousDay = currentDate.addDays(-1);
    ui->dayLabel1->setText(previousDay.toString("yyyy-MM-dd"));
    ui->dayLabel2->setText(currentDate.toString("yyyy-MM-dd"));
    ui->dayLabel3->setText(nextDate.toString("yyyy-MM-dd"));

    getValueFromDb();
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_nextDatButton_clicked()
{
    currentDate = currentDate.addDays(1);
    QDate nextDate = currentDate.addDays(1);
    QDate previousDay = currentDate.addDays(-1);
    ui->dayLabel1->setText(previousDay.toString("yyyy-MM-dd"));
    ui->dayLabel2->setText(currentDate.toString("yyyy-MM-dd"));
    ui->dayLabel3->setText(nextDate.toString("yyyy-MM-dd"));
    getValueFromDb();
}


void MainWindow::on_previousDayButton_clicked()
{
    currentDate = currentDate.addDays(-1);
    QDate nextDate = currentDate.addDays(1);
    QDate previousDay = currentDate.addDays(-1);
    ui->dayLabel1->setText(previousDay.toString("yyyy-MM-dd"));
    ui->dayLabel2->setText(currentDate.toString("yyyy-MM-dd"));
    ui->dayLabel3->setText(nextDate.toString("yyyy-MM-dd"));
    getValueFromDb();
}



void MainWindow::on_addDayWindow1_clicked()
{
    QTime startTime = ui->timeStartWindow1->time();
    QTime endTime = ui->timeEndWindow1->time();
    int startTimeInt = startTime.msecsSinceStartOfDay() / (1000 * 60);
    int endTimeInt = endTime.msecsSinceStartOfDay() / (1000 * 60);
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
    QDate previousDay = currentDate.addDays(-1);
    int julianDay = previousDay.toJulianDay();
    if (!addTaskToDataBase(startTimeInt, endTimeInt, text, julianDay))
        return;
    QString timeText = startTime.toString("HH:mm") + "->" + endTime.toString("HH:mm");
    Task *task = new Task(nullptr, ui->textWindow1->text(), timeText);
    connect(this, &MainWindow::removeAll, task, &Task::removeAllSlot);
    ui->day1layout->addWidget(task);
    ui->textWindow1->clear();
}


void MainWindow::on_addDayWindow2_clicked()
{
    QTime startTime = ui->timeStartWindow2->time();
    QTime endTime = ui->timeEndWindow2->time();
    int startTimeInt = startTime.msecsSinceStartOfDay() / (1000 * 60);
    int endTimeInt = endTime.msecsSinceStartOfDay() / (1000 * 60);
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
    int julianDay = currentDate.toJulianDay();
    if (!addTaskToDataBase(startTimeInt, endTimeInt, text, julianDay))
        return;
    QString timeText = startTime.toString("HH:mm") + "->" + endTime.toString("HH:mm");
    Task *task = new Task(nullptr, ui->textWindow2->text(), timeText);
    connect(this, &MainWindow::removeAll, task, &Task::removeAllSlot);
    ui->day2layout->addWidget(task);
    ui->textWindow2->clear();
}


void MainWindow::on_addDayWindow3_clicked()
{
    QTime startTime = ui->timeStartWindow3->time();
    QTime endTime = ui->timeEndWindow3->time();
    int startTimeInt = startTime.msecsSinceStartOfDay() / (1000 * 60);
    int endTimeInt = endTime.msecsSinceStartOfDay() / (1000 * 60);
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
    QDate nextDay = currentDate.addDays(-1);
    int julianDay = nextDay.toJulianDay();
    if (!addTaskToDataBase(startTimeInt, endTimeInt, text, julianDay))
        return;
    QString timeText = startTime.toString("HH:mm") + "->" + endTime.toString("HH:mm");
    Task *task = new Task(nullptr, ui->textWindow3->text(), timeText);
    connect(this, &MainWindow::removeAll, task, &Task::removeAllSlot);
    ui->day3layout->addWidget(task);
    ui->textWindow3->clear();
}

bool MainWindow::addTaskToDataBase(int timeStart, int timeEnd, QString text, int day)
{
    if (db.connect(path))
    {
        QStringList values = {
            QString::number(timeStart),
            QString::number(timeEnd),
            QString("'%1'").arg(text),
            QString::number(day)
        };

        db.insertData("tasks", values);
        db.disconnect();
        return true;
    }

    return false;
}

void MainWindow::getValueFromDb()
{
    emit removeAll();

    if (db.connect(path))
    {
        QList<QList<QString>> data = db.fetchData("tasks");
        int julianDay = currentDate.toJulianDay();
        for (const auto &row : data) {
            if (julianDay - 1 == row.at(3).toInt()) // actual
            {
                QTime startTime = QTime(0, row.at(0).toInt() / 60, row.at(0).toInt() % 60);
                QTime endTime = QTime(0, row.at(1).toInt() / 60, row.at(1).toInt() % 60);
                QString timeText = startTime.toString("HH:mm") + "->" + endTime.toString("HH:mm");
                Task *task = new Task(nullptr, row.at(2), timeText);
                connect(this, &MainWindow::removeAll, task, &Task::removeAllSlot);
                ui->day1layout->addWidget(task);
            }
            else if (julianDay == row.at(3).toInt()) // prev
            {
                QTime startTime = QTime(0, row.at(0).toInt() / 60, row.at(0).toInt() % 60);
                QTime endTime = QTime(0, row.at(1).toInt() / 60, row.at(1).toInt() % 60);
                QString timeText = startTime.toString("HH:mm") + "->" + endTime.toString("HH:mm");
                Task *task = new Task(nullptr, row.at(2), timeText);
                connect(this, &MainWindow::removeAll, task, &Task::removeAllSlot);
                ui->day2layout->addWidget(task);
            }
            else if (julianDay + 1 == row.at(3).toInt()) // next
            {
                QTime startTime = QTime(0, row.at(0).toInt() / 60, row.at(0).toInt() % 60);
                QTime endTime = QTime(0, row.at(1).toInt() / 60, row.at(1).toInt() % 60);
                QString timeText = startTime.toString("HH:mm") + "->" + endTime.toString("HH:mm");
                Task *task = new Task(nullptr, row.at(2), timeText);
                connect(this, &MainWindow::removeAll, task, &Task::removeAllSlot);
                ui->day3layout->addWidget(task);
            }
            qInfo() << row.at(0);
        }
        db.disconnect();
    }
}

