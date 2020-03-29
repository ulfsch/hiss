//
// BuildingWidget.cpp
//

#include <QHBoxLayout>
#include <QLabel>
#include "BuildingWidget.h"
#include "Building.h"
#include "ElevatorWidget.h"
#include "FloorWidget.h"

BuildingWidget::BuildingWidget(Simulator *simulator, QWidget *parent) :
        QWidget(parent),
        simulator_(simulator),
        building_(simulator->building())
{
    QPalette palette1;
    palette1.setColor(QPalette::Background, QColor(255, 200, 200));
    setAutoFillBackground(true);
    setPalette(palette1);

    QGridLayout *layout = new QGridLayout(this);

    int column = 0;
    layout->setColumnStretch(column, 1);

    for (auto floor : building_->floors())
    {
        int row = building_->number_of_floors() - floor->number() - 1;
        auto widget1 = new FloorWidget(floor, simulator_, this);
        layout->addWidget(widget1, row, column, Qt::AlignCenter);
        floor_widgets_.push_back(widget1);
    }

    column = 1;
    for (auto elevator : building_->elevators())
    {
        layout->setColumnStretch(column, 1);
        layout->setColumnMinimumWidth(column, 150);

        std::vector<ElevatorWidget *> w2;
        for (auto floor_number : elevator->floorNumbers())
        {
            int row = building_->number_of_floors() - floor_number - 1;
            auto *w = new ElevatorWidget(elevator, floor_number, this);
            layout->addWidget(w, row, column, Qt::AlignCenter);
            w2.push_back(w);
        }
        elevator_widgets_.push_back(w2);
        column += 1;
    }

    connect(building_, SIGNAL(changed()), this, SLOT(update_from_model()));
}

void BuildingWidget::update_from_model()
{

}

ElevatorWidget *BuildingWidget::elevator_widget(int row, int col) const
{
    return elevator_widgets_[col][row];
}

void BuildingWidget::tick()
{
    for (auto floor_widget : floor_widgets_)
    {
        floor_widget->update_from_model();
    }
}

// End of file
