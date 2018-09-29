//
// BuildingWidget.cpp
//

#include <QHBoxLayout>
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
    // QObject::connect(building, SIGNAL(changed()), this, SLOT(update_from_model()));
}

void BuildingWidget::update_from_model()
{
    floors1_.clear();
    floors2_.clear();
    elevators_.clear();

    QHBoxLayout *layout = new QHBoxLayout(this);
    QVBoxLayout *floorLayout1 = new QVBoxLayout();
    QHBoxLayout *elevatorLayout = new QHBoxLayout();
    QVBoxLayout *floorLayout2 = new QVBoxLayout();

    layout->addLayout(floorLayout1);
    layout->addLayout(elevatorLayout);
    layout->addLayout(floorLayout2);

    for (auto elevator : building_->elevators())
    {
        auto widget = new ElevatorWidget(elevator);
        elevatorLayout->addWidget(widget);
        elevators_.push_back(widget);
    }

    for (auto floor : building_->floors())
    {
        auto widget1 = new FloorWidget(floor);
        floors1_.push_back(widget1);

        auto widget2 = new FloorWidget(floor);
        floors2_.push_back(widget2);
    }

    for (auto i_floor = floors1_.rbegin(); i_floor != floors1_.rend(); i_floor++)
    {
        floorLayout1->addWidget(*i_floor);
    }
    for (auto i_floor = floors2_.rbegin(); i_floor != floors2_.rend(); i_floor++)
    {
        floorLayout2->addWidget(*i_floor);
    }
}

// End of file
