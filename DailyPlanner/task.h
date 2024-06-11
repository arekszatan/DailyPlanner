#ifndef MYFRAME_H
#define MYFRAME_H

#include <QFrame>
#include <QLabel>
#include <QPushButton>
#include <QGridLayout>

class Task : public QFrame {
    Q_OBJECT

public:
    Task(QWidget *parent = nullptr, QString taskText = "None", QString timeText = "00:00");
    ~Task();

private:
    QString _taskText;
    QString _timeText;
    QLabel *textLabel;
    QLabel *timeLabel;
    QPushButton *editButton;
    QPushButton *deleteButton;
    QGridLayout *gridLayout;

private slots:
    void buttonClicked();
public slots:
    void removeAllSlot();
};

#endif // MYFRAME_H
