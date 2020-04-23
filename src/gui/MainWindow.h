//
// MainWindow.h
//

#ifndef CHISS_MAINWINDOW_H
#define CHISS_MAINWINDOW_H

#include <QMainWindow>
#include <QTimer>
#include <QLabel>
#include "common.h"
#include "BuildingWidget.h"
#include "CarWidget.h"


class Simulator;

class MainWindow : public QMainWindow
{
Q_OBJECT

public:
    explicit MainWindow(Simulator *, QWidget *parent = nullptr);

public slots:
    void update_from_model();
    void simulation_step();

private:
    MilliSeconds get_time() const;

private:
    Simulator *simulator_;
    BuildingWidget *buildingWidget_;
    QLabel *awtWidget;
    std::list<CarWidget *> car_widget_list_;

    MilliSeconds simulation_time_;
    QTimer *timer_;
    MilliSeconds simulation_start_time_;

};

#endif //CHISS_MAINWINDOW_H
