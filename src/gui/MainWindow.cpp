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

#define SIMULATION_RATE 1   // Seconds/tick


MainWindow::MainWindow(Configuration *configuration, QWidget *parent) :
        QMainWindow(parent),
        configuration_(configuration),
        buildingWidget_(nullptr),
        timer_(nullptr)
{
    update_from_model();
    connect(configuration, SIGNAL(changed()), this, SLOT(update_from_model()));

    start_simulation(); // TODO
}

void MainWindow::update_from_model()
{
    QWidget *central = new QWidget(this);

    Building *building = configuration_->building();
    delete buildingWidget_;
    buildingWidget_ = new BuildingWidget(building);

    QVBoxLayout *layout = new QVBoxLayout(central);
    layout->addWidget(buildingWidget_);

    setCentralWidget(central);

    QStatusBar *status_bar = statusBar();
    awtWidget = new QLabel("AWT: 55");
    status_bar->addWidget(awtWidget);

    setWindowTitle(tr("hiss"));
}

void MainWindow::start_simulation()
{
    simulator_ = new Simulator(configuration_->traffic(), configuration_->algorithm(), configuration_->building());

    timer_ = new QTimer(this);
    connect(timer_, SIGNAL(timeout()), this, SLOT(tick()));
    timer_->start(1000);

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
        buildingWidget_->update_car();
        buildingWidget_->update_passenger(simulator_->passengers());
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
