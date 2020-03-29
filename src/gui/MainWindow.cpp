//
// MainWindow.cpp
//

#include <QVBoxLayout>
#include <QLabel>
#include <QStatusBar>
#include <Result.h>
#include "MainWindow.h"
#include "Configuration.h"
#include "BuildingWidget.h"
#include "Simulator.h"
#include "CarWidget.h"

#define SIMULATION_RATE 1   // Seconds/tick


MainWindow::MainWindow(Simulator *simulator, QWidget *parent) :
        QMainWindow(parent),
        simulator_(simulator),
        buildingWidget_(nullptr),
        timer_(nullptr)
{
    QWidget *central = new QWidget(this);
    setCentralWidget(central);

    delete buildingWidget_;
    buildingWidget_ = new BuildingWidget(simulator_, this);

    QVBoxLayout *layout = new QVBoxLayout(central);
    layout->addWidget(buildingWidget_);

    int column = 0;
    for (Car *car : simulator_->cars())
    {
        CarWidget *car_widget = new CarWidget(car, simulator_, column++, buildingWidget_);
        car_widget_list_.push_back(car_widget);
    }

    QStatusBar *status_bar = statusBar();
    awtWidget = new QLabel("AWT: 55");
    status_bar->addWidget(awtWidget);

    setWindowTitle(tr("hiss"));

    // Start simulation
    timer_ = new QTimer(this);
    connect(timer_, SIGNAL(timeout()), this, SLOT(tick()));
    timer_->start(1000);
}

void MainWindow::update_from_model()
{
}

void MainWindow::tick()
{
    if (simulator_->done())
    {
        timer_->stop();
        delete timer_;
        timer_ = nullptr;
    }
    else
    {
        simulator_->tick(simulation_time_, SIMULATION_RATE);

        for (CarWidget *car_widget : car_widget_list_)
        {
            car_widget->tick();
        }
        buildingWidget_->tick();

        simulation_time_ += SIMULATION_RATE;

        Result result;
        result.compute_result(simulation_time_, simulator_->passengers());
        awtWidget->setText(QString("   AWT: %1,  ATT: %2")
                                   .arg(result.average_waiting_time(), 0, 'g', 2)
                                   .arg(result.average_traveling_time(), 0, 'g', 2)
        );
    }

}

// End of file
