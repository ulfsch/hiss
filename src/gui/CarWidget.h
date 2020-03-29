//
// Created by ulf on 11/1/19.
//

#ifndef CHISS_CARWIDGET_H
#define CHISS_CARWIDGET_H

#include <QLabel>
#include <QWidget>
#include "BuildingWidget.h"
#include "Car.h"
#include "Simulator.h"


class CarWidget : public QWidget
{
Q_OBJECT

public:
    CarWidget(Car *car, Simulator* simulator, int column, BuildingWidget *parent);

    void tick();

public slots:

private:
    Car *car_;
    Simulator *simulator_;
    BuildingWidget *building_widget_;
    int index_;
    QLabel* label_;

};


#endif //CHISS_CARWIDGET_H
