//
// BuildingWidget.cpp
//

#include <QHBoxLayout>
#include <QLabel>
#include "BuildingWidget.h"
#include "Building.h"
#include "ElevatorWidget.h"
#include "FloorWidget.h"

BuildingWidget::BuildingWidget(Building *building, QWidget *parent) :
        QWidget(parent),
        building_(building)
{
    QPalette palette1;
    palette1.setColor(QPalette::Background, QColor(255, 200, 200));
    setAutoFillBackground(true);
    setPalette(palette1);

    update_from_model();
    connect(building, SIGNAL(changed()), this, SLOT(update_from_model()));
}

void BuildingWidget::update_from_model()
{
    floorWidgets_.clear();
    elevatorWidgets_.clear();

    QGridLayout *layout = new QGridLayout(this);

    int column = 0;
    for (auto floor : building_->floors())
    {
        int row = building_->number_of_floors() - floor->number() - 1;
        auto widget1 = new FloorWidget(floor, this);
        layout->addWidget(widget1, row, column, Qt::AlignCenter);
        floorWidgets_.push_back(widget1);
    }

    column = 1;
    for (auto elevator : building_->elevators())
    {
        for (auto floor_number : elevator->floorNumbers())
        {
            int row = building_->number_of_floors() - floor_number - 1;
            auto widget = new ElevatorWidget(elevator, floor_number, this);
            layout->addWidget(widget, row, column, Qt::AlignCenter);
            elevatorWidgets_.push_back(widget);
        }
        column += 1;
    }

//    for (auto floor : building_->floors())
//    {
//        int row = building_->number_of_floors() - floor->number() - 1;
//        auto widget2 = new FloorWidget(floor, this);
//        layout->addWidget(widget2, row, column, Qt::AlignCenter);
//        floorWidgets_.push_back(widget2);
//    }
}

void BuildingWidget::update_car()
{
    for (auto elevator : elevatorWidgets_)
    {
        elevator->update_car();
    }
}

void BuildingWidget::update_passenger(const std::list<Passenger *> &passengers)
{
    for (auto floor : floorWidgets_)
    {
        floor->update_passenger(passengers);
    }
    for (auto elevator : elevatorWidgets_)
    {
        elevator->update_passenger(passengers);
    }
}

// End of file
