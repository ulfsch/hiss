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
//    QPalette palette1;
//    palette1.setColor(QPalette::Background, QColor(255, 255, 200));
//    setAutoFillBackground(true);
//    setPalette(palette1);

    setStyleSheet("background-color: blue; margin:8");

    setFixedWidth(200);

    update_from_model();
}

void ElevatorWidget::update_from_model()
{
    QGridLayout *layout = new QGridLayout(this);
    widget_ = new QLabel(QString::number(floor_number_), this);
    layout->addWidget(widget_, 0, 0, Qt::AlignCenter);
}

// End of file
