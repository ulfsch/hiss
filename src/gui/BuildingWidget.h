//
// BuildingWidget.h
//

#ifndef CHISS_BUILDINGWIDGET_H
#define CHISS_BUILDINGWIDGET_H

#include <QWidget>
#include <Car.h>
#include <Passenger.h>
#include <QGridLayout>
#include <Simulator.h>

class Building;
class ElevatorWidget;
class FloorWidget;


class BuildingWidget : public QWidget
{
Q_OBJECT

public:
    explicit BuildingWidget(Simulator* simulator, QWidget *parent = nullptr);

    ElevatorWidget* elevator_widget(int row, int col) const;
    void simulation_step();

public slots:
    void update_from_model();

private:
    Simulator *simulator_;
    Building *building_;
    std::vector<std::vector<ElevatorWidget *> > elevator_widgets_;
    std::vector<FloorWidget *> floor_widgets_;

};

#endif //CHISS_BUILDINGWIDGET_H
