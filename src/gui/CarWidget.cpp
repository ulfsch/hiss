//
// Created by ulf on 11/1/19.
//

#include <QLabel>
#include <QHBoxLayout>
#include <chrono>
#include "Simulator.h"
#include "Car.h"
#include "CarWidget.h"
#include "ElevatorWidget.h"


CarWidget::CarWidget(Car *car, Simulator* simulator, int column, BuildingWidget *parent) :
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

    QTimer *timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(update()));
    timer->start(100);

}

void CarWidget::update()
{
    ElevatorWidget* widget = building_widget_->elevator_widget(0, index_);
    QSize size = widget->size();
    QPoint pos = widget->pos();

    int y = car_->normalized_height() * (size.height() + 7);
    pos += QPoint(0, -y);
    move(pos);
    setFixedSize(size);
}

void CarWidget::tick()
{
    QString str;
    for (const auto &item : simulator_->passengers())
    {
        if (item->car() == car_)
        {
            if (str.isEmpty())
                str.append(QString(" %1").arg(item->end_floor()));
            else
                str.append(QString(", %1").arg(item->end_floor()));
        }
    }
    label_->setText(str);
}

// End of file
