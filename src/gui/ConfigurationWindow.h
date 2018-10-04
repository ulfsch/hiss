//
// ConfigurationWindow.h
//

#ifndef CHISS_CONFIGURATIONWINDOW_H
#define CHISS_CONFIGURATIONWINDOW_H

#include <QMainWindow>
#include <QTimer>
#include "BuildingWidget.h"
#include "common.h"

class Configuration;

class Simulator;

class ConfigurationWindow : public QMainWindow
{
Q_OBJECT

public:
    explicit ConfigurationWindow(Configuration *, QWidget *parent = nullptr);

public slots:
    void update_from_model();

    void start_simulation();

    void tick();

private:
    Configuration *configuration_;
    BuildingWidget *buildingWidget_;
    Simulator *simulator_;
    Time simulation_time_;
    QTimer *simulation_timer_;

};

#endif //CHISS_CONFIGURATIONWINDOW_H
