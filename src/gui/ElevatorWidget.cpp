//
// ElevatorWidget.cpp
//

#include <QVBoxLayout>
#include <QLabel>
#include "ElevatorWidget.h"
#include "Elevator.h"


ElevatorWidget::ElevatorWidget(Elevator *elevator, FloorNumber floor_number, QWidget *parent) :
        QWidget(parent),
        elevator_(elevator),
        floor_number_(floor_number)
{
    QPalette palette1;
    palette1.setColor(QPalette::Background, QColor(255, 255, 100));
    setPalette(palette1);
    setAutoFillBackground(true);

    //setContentsMargins(0, 0, 0, 0);
    setMinimumWidth(150);

    QHBoxLayout *layout = new QHBoxLayout(this);
    widget_ = new QLabel(QString::number(floor_number_), this);
    layout->addWidget(widget_, 0, Qt::AlignCenter);
}

void ElevatorWidget::update_from_model()
{
}

// End of file
