//
// FloorWidget.cpp
//

#include <QLabel>
#include <QHBoxLayout>
#include "FloorWidget.h"
#include "Floor.h"

FloorWidget::FloorWidget(Floor *floor, Simulator *simulator, QWidget *parent) :
        QWidget(parent),
        floor_(floor),
        simulator_(simulator)
{
    QPalette palette1;
    palette1.setColor(QPalette::Background, QColor(200, 255, 255));
    setAutoFillBackground(true);
    setPalette(palette1);
    setMinimumWidth(150);

    QHBoxLayout *layout = new QHBoxLayout(this);
    widget_ = new QLabel(QString::number(floor_->number()));
    layout->addWidget(widget_);
}

void FloorWidget::update_from_model()
{
    QString str;
    for (const auto &passenger : simulator_->passengers())
    {
        if (passenger->begin_floor() == floor_->number() &&
            passenger->on_start_floor())
        {
            if (str.isEmpty())
                str.append(QString(" %1").arg(passenger->end_floor()));
            else
                str.append(QString(", %1").arg(passenger->end_floor()));
        }
    }
    widget_->setText(str);
}


// End of file
