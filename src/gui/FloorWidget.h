//
// FloorWidget.h
//

#ifndef CHISS_FLOORWIDGET_H
#define CHISS_FLOORWIDGET_H

#include <QWidget>
#include <QLabel>
#include <Passenger.h>

class Floor;

class FloorWidget : public QWidget
{
Q_OBJECT

public:
    explicit FloorWidget(Floor *, QWidget *parent = nullptr);
    void update_passenger(const std::list<Passenger *> &list);

public slots:

    void update_from_model();

private:
    Floor *floor_;
    QLabel *widget_;

};

#endif //CHISS_FLOORWIDGET_H
