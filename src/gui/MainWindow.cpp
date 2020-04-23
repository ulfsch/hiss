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

const int GUI_UPDATE_RATE = 50;  // 50 ms = 20Hz

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
    timer_->start(GUI_UPDATE_RATE);

    simulation_start_time_ = get_time();
}

void MainWindow::update_from_model()
{
}

/*
 * Execute one simulation step.
 */
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
        MilliSeconds time = get_time();
        MilliSeconds total_time = time - simulation_start_time_;

        // Execute one simulation step
        simulator_->tick(time);

        // Update car and building widgets
        std::for_each(car_widget_list_.begin(), car_widget_list_.end(), std::mem_fun(&CarWidget::tick));
        buildingWidget_->tick();

        // Update simulation result
        Result result;
        result.compute_result(total_time, simulator_->passengers());
        awtWidget->setText(QString("   AWT: %1,  ATT: %2")
                                   .arg(result.average_waiting_time() / 1000, 0, 'g', 2)
                                   .arg(result.average_traveling_time() / 1000, 0, 'g', 2)
        );
    }

}

MilliSeconds MainWindow::get_time() const
{
    MilliSeconds ms = std::chrono::duration_cast<std::chrono::milliseconds>(
            std::chrono::system_clock::now().time_since_epoch()).count();
    return ms;
}

// End of file
