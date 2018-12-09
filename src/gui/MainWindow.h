//
// MainWindow.h
//

#ifndef CHISS_MAINWINDOW_H
#define CHISS_MAINWINDOW_H

#include <QMainWindow>
#include <QTimer>
#include <QLabel>
#include "BuildingWidget.h"
#include "common.h"

class Configuration;

class Simulator;

class MainWindow : public QMainWindow
{
Q_OBJECT

public:
    explicit MainWindow(Configuration *, QWidget *parent = nullptr);

public slots:
    void update_from_model();
    void start_simulation();
    void tick();

private:
    Configuration *configuration_;
    BuildingWidget *buildingWidget_;
    Simulator *simulator_;
    Time simulation_time_;
    QTimer *timer_;
    QLabel *awtWidget;
};

#endif //CHISS_MAINWINDOW_H
