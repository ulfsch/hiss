//
// MainWindow.cpp
//

#include <QVBoxLayout>
#include <QLabel>
#include <QStatusBar>
#include <Result.h>
#include <chrono>
#include "MainWindow.h"
#include "Configuration.h"
#include "BuildingWidget.h"
#include "Simulator.h"
#include "CarWidget.h"

#define SIMULATION_RATE 1   // Seconds/simulation_step


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
    connect(timer_, SIGNAL(timeout()), this, SLOT(simulation_step()));
    timer_->start(100);

    simulation_start_time_ = get_time();
}

void MainWindow::update_from_model()
{
}

void MainWindow::simulation_step()
{
    if (simulator_->done())
    {
        timer_->stop();
        delete timer_;
        timer_ = nullptr;
    }
    else
    {
        MilliSeconds time = get_time();
        MilliSeconds simulation_time = time - simulation_start_time_;

        // Simulate
        simulator_->tick(time);
        std::for_each(car_widget_list_.begin(), car_widget_list_.end(), std::mem_fun(&CarWidget::tick));
        buildingWidget_->tick();

        // Show result
        Result result;
        result.compute_result(simulation_time, simulator_->passengers());
        awtWidget->setText(QString("   AWT: %1,  ATT: %2")
                                   .arg(result.average_waiting_time() / 1000, 0, 'g', 2)
                                   .arg(result.average_traveling_time() / 1000, 0, 'g', 2)
        );
    }

}

MilliSeconds MainWindow::get_time() const
{
    MilliSeconds time_ms = std::chrono::duration_cast<std::chrono::milliseconds>(
            std::chrono::system_clock::now().time_since_epoch()).count();
    return time_ms;
}

// End of file
