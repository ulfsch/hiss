//
// Created by ulf on 11/1/19.
//

#ifndef CHISS_CARWIDGET_H
#define CHISS_CARWIDGET_H

#include <QWidget>
#include "Car.h"


class CarWidget : public QWidget
{
Q_OBJECT

public:
    explicit CarWidget(Car *car, QWidget *parent = nullptr);

public slots:

    void update_from_simulation();

private:
    Car *car_;

};


#endif //CHISS_CARWIDGET_H
