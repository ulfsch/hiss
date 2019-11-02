//
// ElevatorWidget.cpp
//

#include <QVBoxLayout>
#include <QLabel>
#include "ElevatorWidget.h"
#include "Elevator.h"
#include "Floor.h"
#include "Car.h"

ElevatorWidget::ElevatorWidget(Elevator *elevator, QWidget *parent) :
        QWidget(parent),
        elevator_(elevator)
{
    QPalette palette1;
    palette1.setColor(QPalette::Background, QColor(255, 255, 200));
    setAutoFillBackground(true);
    setPalette(palette1);
    setFixedWidth(200);

    update_from_model();
}

void ElevatorWidget::update_from_model()
{
    //setFixedSize(100, 50);
    QGridLayout *layout = new QGridLayout(this);

    widget_ = new QLabel(QString::number(7), this);
    layout->addWidget(widget_, 0, 0, Qt::AlignCenter);
    widget_->setAlignment(Qt::AlignCenter);
    widget_->setStyleSheet("background:white");
    //widget_->setFixedSize(42, 42);

    // floorLayout->setContentsMargins(0, 0, 0, 0);
}

/*
void ElevatorWidget::update_car()
{
    if (car_->current_floor() == floorNumber_)
    {
        widget_->setStyleSheet("background:red");
    }
    else
    {
        widget_->setStyleSheet("background:white");
    }
}

void ElevatorWidget::update_passenger(const PassengerList &passengers)
{
    QString text = QString::number(floorNumber_) + ":";
    for (auto p : passengers)
    {
        if (p->car() == car_ && car_->current_floor() == floorNumber_)
        {
            text += " (" +
                    QString::number(p->begin_floor()) + "," +
                    QString::number(p->end_floor()) +
                    ")";
        }
    }
    widget_->setText(text);
}
*/

// End of file
