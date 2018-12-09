//
// Created by ulf on 8/30/18.
//

#ifndef CHISS_ELEVATORWIDGET_H
#define CHISS_ELEVATORWIDGET_H

#include <QWidget>
#include <QLabel>
#include "common.h"
#include "Passenger.h"

class Elevator;

class ElevatorWidget : public QWidget
{
Q_OBJECT

public:
    explicit ElevatorWidget(Elevator *, FloorNumber floor, QWidget *parent = nullptr);
    void update_car();
    void update_passenger(const std::list<Passenger *> &passengers);

public slots:
    void update_from_model();

private:
    Elevator *elevator_;
    FloorNumber floorNumber_;
    QLabel *widget_;

};

#endif //CHISS_ELEVATORWIDGET_H
