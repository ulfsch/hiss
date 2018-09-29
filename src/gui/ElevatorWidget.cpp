//
// ElevatorWidget.cpp
//

#include <QVBoxLayout>
#include <QLabel>
#include "ElevatorWidget.h"
#include "Elevator.h"

ElevatorWidget::ElevatorWidget(Elevator *elevator, QWidget *parent) :
        QWidget(parent),
        elevator_(elevator)
{
    QPalette palette1;
    palette1.setColor(QPalette::Background, QColor(255, 255, 200));
    setAutoFillBackground(true);
    setPalette(palette1);
    setFixedWidth(100);

    update_from_model();
}

void ElevatorWidget::update_from_model()
{
    QVBoxLayout *floorLayout = new QVBoxLayout(this);

    auto floors = elevator_->floorNumbers();
    for (auto i_floor = floors.rbegin(); i_floor != floors.rend(); i_floor++)
    {
        QWidget *w = new QWidget(this);
        //w->setFixedSize(100, 50);
        QGridLayout *layout = new QGridLayout(w);

        QLabel *lbl = new QLabel(QString::number(*i_floor), w);
        layout->addWidget(lbl, 0, 0, Qt::AlignCenter);
        lbl->setAlignment(Qt::AlignCenter);
        lbl->setStyleSheet("background:white");
        lbl->setFixedSize(42, 42);


        floorLayout->addWidget(w);
    }
    floorLayout->setContentsMargins(0, 0, 0, 0);
}

// End of file
