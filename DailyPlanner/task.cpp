#include "task.h"
#include <QDebug>

Task::Task(QWidget *parent, QString taskText, QString timeText, int indexTime, int daySince)
    : QFrame(parent)
{
    _taskText = taskText;
    _timeText = timeText;
    _indexTime = indexTime;
    _daySince = daySince;
    this->setFrameShape(QFrame::Box);
    this->setLineWidth(3);
    etykieta1 = new QLabel("Zadanie:");
    etykieta1->setAlignment(Qt::AlignCenter);
    etykieta2 = new QLabel("Czas zadania:");
    etykieta2->setAlignment(Qt::AlignCenter);
    textLabel = new QLabel(_taskText);
    textLabel->setAlignment(Qt::AlignCenter);
    timeLabel = new QLabel(_timeText);
    timeLabel->setAlignment(Qt::AlignCenter);
    deleteButton = new QPushButton("Usuń");
    connect(deleteButton, &QPushButton::clicked, this, &Task::buttonClicked);
    gridLayout = new QGridLayout(this);
    gridLayout->addWidget(etykieta1, 0, 0);
    gridLayout->addWidget(textLabel, 1, 0);
    gridLayout->addWidget(etykieta2, 2, 0);
    gridLayout->addWidget(timeLabel, 3, 0);
    gridLayout->addWidget(deleteButton, 4, 0);
}

Task::~Task()
{
    delete textLabel;
    delete timeLabel;
    delete deleteButton;
    delete gridLayout;
}

int Task::getIndexTime()
{
    return _indexTime;
}

int Task::getDaySince()
{
    return _daySince;
}

void Task::buttonClicked()
{
    emit removeFromDb(this);
    delete this;
}

void Task::removeAllSlot()
{
    delete this;
}
