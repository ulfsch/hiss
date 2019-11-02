//
// Created by ulf on 11/1/19.
//

#include "CarWidget.h"


CarWidget::CarWidget(Car *car, QWidget *parent) :
        QWidget(parent),
        car_(car)
{
    update_from_simulation();
}

void CarWidget::update_from_simulation()
{

}
