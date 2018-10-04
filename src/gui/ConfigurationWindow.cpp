//
// ConfigurationWindow.cpp
//

#include <QVBoxLayout>
#include "ConfigurationWindow.h"
#include "Configuration.h"
#include "BuildingWidget.h"
#include "Simulator.h"

#define SIMULATION_RATE 1   // Seconds/tick


ConfigurationWindow::ConfigurationWindow(Configuration *configuration, QWidget *parent) :
        QMainWindow(parent),
        configuration_(configuration),
        buildingWidget_(nullptr),
        simulation_timer_(nullptr)
{
    update_from_model();
    connect(configuration, SIGNAL(changed()), this, SLOT(update_from_model()));

    start_simulation(); // TODO
}

void ConfigurationWindow::update_from_model()
{
    QWidget *central = new QWidget(this);

    Building *building = configuration_->building();
    delete buildingWidget_;
    buildingWidget_ = new BuildingWidget(building);

    QVBoxLayout *layout = new QVBoxLayout(central);
    layout->addWidget(buildingWidget_);

    setCentralWidget(central);
    setWindowTitle(tr("hiss"));
}

void ConfigurationWindow::start_simulation()
{
    simulator_ = new Simulator(configuration_->traffic(), configuration_->algorithm(), configuration_->building());

    auto *simulation_timer_ = new QTimer(this);
    connect(simulation_timer_, SIGNAL(timeout()), this, SLOT(tick()));
    simulation_timer_->start(1000);

}

void ConfigurationWindow::tick()
{
    if (simulator_->done())
    {
        simulation_timer_->stop();
        delete simulation_timer_;
        simulation_timer_ = nullptr;
    }
    else
    {
        simulator_->tick(simulation_time_, SIMULATION_RATE);
        simulation_time_ += SIMULATION_RATE;
    }

}

// End of file
