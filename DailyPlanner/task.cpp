#include "task.h"
#include <QDebug>

Task::Task(QWidget *parent, QString taskText, QString timeText, int indexTime)
    : QFrame(parent)
{
    _taskText = taskText;
    _timeText = timeText;
    _indexTime = indexTime;
    this->setFrameShape(QFrame::Box);
    this->setLineWidth(2);

    textLabel = new QLabel(_taskText);

    timeLabel = new QLabel(_timeText);
    editButton = new QPushButton("Edytuj");
    deleteButton = new QPushButton("Usuń");
    connect(deleteButton, &QPushButton::clicked, this, &Task::buttonClicked);
    gridLayout = new QGridLayout(this);
    gridLayout->addWidget(textLabel, 0, 0, 1, 2);
    gridLayout->addWidget(timeLabel, 1, 0, 1, 2);
    gridLayout->addWidget(editButton, 2, 0);
    gridLayout->addWidget(deleteButton, 2, 1);
}

Task::~Task()
{
    delete textLabel;
    delete timeLabel;
    delete editButton;
    delete deleteButton;
    delete gridLayout;
}

int Task::getIndexTime()
{
    return _indexTime;
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
