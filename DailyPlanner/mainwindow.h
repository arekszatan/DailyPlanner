#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include "task.h"
#include <QMainWindow>
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

public slots:
    void rmDbItem(Task *task);

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
    QDate currentDate = QDate::currentDate();
    QString path = "C:/Users/ASZA-LAPTOP/Documents/dataBase.db";
    int getIndexToSort(QHBoxLayout *layout, int timeActualItem);
    void getValueFromDb();
};
#endif // MAINWINDOW_H
