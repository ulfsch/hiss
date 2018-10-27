//
// BuildingWidget.h
//

#ifndef CHISS_BUILDINGWIDGET_H
#define CHISS_BUILDINGWIDGET_H

#include <QWidget>
#include <Passenger.h>

class Building;
class ElevatorWidget;
class FloorWidget;


class BuildingWidget : public QWidget
{
Q_OBJECT

public:
    explicit BuildingWidget(Building *, QWidget *parent = nullptr);
    void update_passenger(const std::list<Passenger *> &passengers);

public slots:
    void update_from_model();

private:
    Building *building_;
    std::vector<ElevatorWidget *> elevators_;
    std::vector<FloorWidget *> floors1_;
    std::vector<FloorWidget *> floors2_;

};

#endif //CHISS_BUILDINGWIDGET_H
