//
// Created by ulf on 11/1/19.
//

#include <QLabel>
#include <QHBoxLayout>
#include "Simulator.h"
#include "Car.h"
#include "CarWidget.h"
#include "ElevatorWidget.h"


CarWidget::CarWidget(Car *car, Simulator* simulator, int column, BuildingWidget *parent) :
        QWidget(parent),
        car_(car),
        simulator_(simulator),
        building_widget_(parent),
        index_(column)
{
    QPalette palette1;
    palette1.setColor(QPalette::Background, QColor(255, 255, 255));
    setAutoFillBackground(true);
    setPalette(palette1);

    setStyleSheet("margin:0px; padding:0px; border-width: 2px;background-color: white;border-color: black; border-style: solid;");
    auto *layout = new QGridLayout(this);
    label_ = new QLabel(QString::number(7), this);
    layout->addWidget(label_);
    layout->setSpacing(0);
    layout->setContentsMargins(0, 0, 0, 0);
}

void CarWidget::tick()
{
    FloorNumber floorNumber = car_->current_floor();
    ElevatorWidget* widget = building_widget_->elevator_widget(floorNumber, index_);
    move(widget->pos());
    resize(widget->width(), widget->height());

    QString str;
    for (const auto &item : simulator_->passengers())
    {
        if (item->car() == car_)
        {
            if (str.isEmpty())
                str.append(QString(" %1").arg(item->end_floor()));
            else
                str.append(QString(", %1").arg(item->end_floor()));

//            if (car_->is_idle())
//                setStyleSheet("background:white");
//            else
//                setStyleSheet("background:lightblue");
        }
    }
    label_->setText(str);
}
