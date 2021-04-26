//
// Created by ulf on 11/1/19.
//

#include <QLabel>
#include <QHBoxLayout>
#include "Simulator.h"
#include "Car.h"
#include "CarWidget.h"
#include "ElevatorWidget.h"

/**
 *
 * @param car
 * @param simulator
 * @param column
 * @param parent
 */
CarWidget::CarWidget(Car *car, Simulator *simulator, int column, BuildingWidget *parent) :
        QFrame(parent),
        car_(car),
        simulator_(simulator),
        building_widget_(parent),
        index_(column)
{
    QPalette palette1;
    palette1.setColor(QPalette::Background, QColor(255, 255, 255));
    setFrameShape(Shape::Box);
    setLineWidth(2);
    setAutoFillBackground(true);
    setPalette(palette1);

    auto *layout = new QGridLayout(this);
    label_ = new QLabel(QString::number(7), this);
    layout->addWidget(label_);
    layout->setSpacing(0);
    layout->setContentsMargins(0, 0, 0, 0);

    connect(car, SIGNAL(car_moved()), this, SLOT(update_car_position()));
}

/**
 * Slot called when car position has changed.
 */
void CarWidget::update_car_position()
{
    ElevatorWidget *widget = building_widget_->elevator_widget(0, index_);
    QSize size = widget->size();
    QPoint pos = widget->pos();

    int y = (int)std::round(car_->normalized_height() * (size.height() + 6));
    pos += QPoint(0, -y);
    move(pos);
    setFixedSize(size);
}

/**
 *
 */
void CarWidget::tick()
{
    QString str = QString("->%1: ").arg(car_->next_floor());
    for (const auto &passenger : simulator_->passengers())
    {
        if (passenger->car() == car_)
        {
            if (str.isEmpty())
                str.append(QString(" %1").arg(passenger->end_floor()));
            else
                str.append(QString(", %1").arg(passenger->end_floor()));
        }
    }
    label_->setText(str);
}

// End of file
