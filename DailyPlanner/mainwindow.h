#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "task.h"
#include <QMessageBox>
#include <QDebug>
#include "db.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_nextDatButton_clicked();

    void on_previousDayButton_clicked();

    void on_addDayWindow1_clicked();

    void on_addDayWindow2_clicked();

    void on_addDayWindow3_clicked();

signals:
    void removeAll();

private:
    Ui::MainWindow *ui;
    int busyTime[1440];
    DB db;
    bool addTaskToDataBase(int timeStart, int timeEnd, QString text, int day);
    QString path = "C:/Users/ASZA-LAPTOP/Documents/dataBase.db";
    QDate currentDate = QDate::currentDate();
    void getValueFromDb();
};
#endif // MAINWINDOW_H
