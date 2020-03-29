//
// FloorWidget.h
//

#ifndef CHISS_FLOORWIDGET_H
#define CHISS_FLOORWIDGET_H

#include <QWidget>
#include <QLabel>
#include "Simulator.h"
#include "Passenger.h"

class Floor;

class FloorWidget : public QWidget
{
Q_OBJECT

public:
    explicit FloorWidget(Floor *, Simulator* simulator, QWidget *parent = nullptr);

public slots:
    void update_from_model();

private:
    Floor *floor_;
    Simulator *simulator_;
    QLabel *widget_;

};

#endif //CHISS_FLOORWIDGET_H
