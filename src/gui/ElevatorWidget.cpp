//
// ElevatorWidget.cpp
//

#include <QVBoxLayout>
#include <QLabel>
#include "ElevatorWidget.h"
#include "Elevator.h"

ElevatorWidget::ElevatorWidget(Elevator *elevator, FloorNumber floor, QWidget *parent) :
        QWidget(parent),
        elevator_(elevator),
        floorNumber_(floor)
{
    QPalette palette1;
    palette1.setColor(QPalette::Background, QColor(255, 255, 200));
    setAutoFillBackground(true);
    setPalette(palette1);
    setFixedWidth(100);

    update_from_model();
}

void ElevatorWidget::update_from_model()
{
    //setFixedSize(100, 50);
    QGridLayout *layout = new QGridLayout(this);

    QLabel *lbl = new QLabel(QString::number(floorNumber_), this);
    layout->addWidget(lbl, 0, 0, Qt::AlignCenter);
    lbl->setAlignment(Qt::AlignCenter);
    lbl->setStyleSheet("background:white");
    lbl->setFixedSize(42, 42);

    // floorLayout->setContentsMargins(0, 0, 0, 0);
}

// End of file
