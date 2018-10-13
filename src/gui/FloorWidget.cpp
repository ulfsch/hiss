//
// FloorWidget.cpp
//

#include <QLabel>
#include <QHBoxLayout>
#include "FloorWidget.h"
#include "Floor.h"

FloorWidget::FloorWidget(Floor *floor, QWidget *parent) :
        QWidget(parent),
        floor_(floor)
{
    QPalette palette1;
    palette1.setColor(QPalette::Background, QColor(200, 255, 255));
    setAutoFillBackground(true);
    setPalette(palette1);
    setFixedWidth(100);

    update_from_model();
}

void FloorWidget::update_from_model()
{
    QHBoxLayout *layout = new QHBoxLayout(this);
    QLabel *widget = new QLabel(QString::number(floor_->number()));
    layout->addWidget(widget);

//    for (auto p : floor_->passengers())
//    {
//        QLabel *widget = new QLabel(QString::number(p->begin_floor()));
//        layout->addWidget(widget);
//    }
}

// End of file
