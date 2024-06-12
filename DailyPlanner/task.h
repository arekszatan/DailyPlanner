#ifndef MYFRAME_H
#define MYFRAME_H

#include <QFrame>
#include <QLabel>
#include <QPushButton>
#include <QGridLayout>
#include "db.h"

class Task : public QFrame {
    Q_OBJECT

public:
    Task(QWidget *parent = nullptr, QString taskText = "None", QString timeText = "00:00", int indexTime = -1, int daySince = -1);
    ~Task();
    int getIndexTime();
    int getDaySince();

private:
    QString _taskText;
    QString _timeText;
    int _daySince;
    QLabel *textLabel;
    QLabel *timeLabel;
    QLabel *etykieta1;
    QLabel *etykieta2;
    QPushButton *deleteButton;
    QGridLayout *gridLayout;
    int _indexTime;
    //DB db;
signals:
    void removeFromDb(Task *task);
private slots:
    void buttonClicked();
public slots:
    void removeAllSlot();
};

#endif // MYFRAME_H
