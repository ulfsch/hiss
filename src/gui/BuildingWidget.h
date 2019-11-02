//
// BuildingWidget.h
//

#ifndef CHISS_BUILDINGWIDGET_H
#define CHISS_BUILDINGWIDGET_H

#include <QWidget>
#include <Car.h>
#include <Passenger.h>

class Building;
class ElevatorWidget;
class FloorWidget;


class BuildingWidget : public QWidget
{
Q_OBJECT

public:
    explicit BuildingWidget(Building *building, QWidget *parent = nullptr);

public slots:
    void update_from_model();

private:
    Building *building_;
    std::vector<ElevatorWidget *> elevatorWidgets_;
    std::vector<FloorWidget *> floorWidgets_;

};

#endif //CHISS_BUILDINGWIDGET_H
