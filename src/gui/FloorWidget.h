//
// FloorWidget.h
//

#ifndef CHISS_FLOORWIDGET_H
#define CHISS_FLOORWIDGET_H

#include <QWidget>

class Floor;

class FloorWidget : public QWidget
{
Q_OBJECT

public:
    explicit FloorWidget(Floor *, QWidget *parent = nullptr);

public slots:

    void update_from_model();

private:
    Floor *floor_;

};

#endif //CHISS_FLOORWIDGET_H
