#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "task.h"
#include <QMessageBox>

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

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
