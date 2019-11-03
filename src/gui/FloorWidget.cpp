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
    setMinimumWidth(150);

    update_from_model();
}

void FloorWidget::update_from_model()
{
    QHBoxLayout *layout = new QHBoxLayout(this);
    widget_ = new QLabel(QString::number(floor_->number()));
    layout->addWidget(widget_);

}

void FloorWidget::update_passenger(const std::list<Passenger *> &passengers)
{
    QString text = QString::number(floor_->number()) + ":";
    for (auto p : passengers)
    {
        if (p->begin_floor() == floor_->number() && p->on_start_floor())
        {
            text += " (" +
                    QString::number(p->begin_floor()) + "," +
                    QString::number(p->end_floor()) +
                    ")";
        }
    }
    widget_->setText(text);
}

// End of file
