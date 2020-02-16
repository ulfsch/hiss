//
// Floor.h.
//
#ifndef CHISS_FLOOR_H
#define CHISS_FLOOR_H

#include "common.h"
#include <set>
#include <QtCore>

class Floor : public QObject
{
Q_OBJECT

public:
    explicit Floor(FloorNumber floor_number, QObject *parent = nullptr);

    FloorNumber number() const { return number_; }

private:
    FloorNumber number_;

};

#endif //CHISS_FLOOR_H
