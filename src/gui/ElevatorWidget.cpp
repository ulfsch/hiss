//
// ElevatorWidget.cpp
//

#include <QVBoxLayout>
#include <QLabel>
#include "ElevatorWidget.h"
#include "Elevator.h"
#include "Floor.h"

ElevatorWidget::ElevatorWidget(Elevator *elevator, FloorNumber floor, QWidget *parent) :
        QWidget(parent),
        elevator_(elevator),
        floorNumber_(floor)
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

    widget_ = new QLabel(QString::number(floorNumber_), this);
    layout->addWidget(widget_, 0, 0, Qt::AlignCenter);
    widget_->setAlignment(Qt::AlignCenter);
    widget_->setStyleSheet("background:white");
    //widget_->setFixedSize(42, 42);

    // floorLayout->setContentsMargins(0, 0, 0, 0);
}

void ElevatorWidget::update_car()
{
    if (elevator_->current_floor() == floorNumber_)
    {
        widget_->setStyleSheet("background:red");
    }
    else
    {
        widget_->setStyleSheet("background:white");
    }

}

void ElevatorWidget::update_passenger(const std::list<Passenger *> &passengers)
{
    QString text = QString::number(floorNumber_) + ":";
    for (auto p : passengers)
    {
        if (p->elevator() == elevator_ && elevator_->current_floor() == floorNumber_)
        {
            text += " (" +
                    QString::number(p->begin_floor()->number()) + "," +
                    QString::number(p->end_floor()->number()) +
                    ")";
        }
    }
    widget_->setText(text);
}

// End of file
