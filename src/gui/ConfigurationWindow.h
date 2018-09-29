//
// ConfigurationWindow.h
//

#ifndef CHISS_CONFIGURATIONWINDOW_H
#define CHISS_CONFIGURATIONWINDOW_H

#include <QMainWindow>
#include "BuildingWidget.h"

class Configuration;

class ConfigurationWindow : public QMainWindow
{
Q_OBJECT

public:
    explicit ConfigurationWindow(Configuration *, QWidget *parent = nullptr);

public slots:

    void update_from_model();

private:
    Configuration *configuration_;
    BuildingWidget *buildingWidget_;
};

#endif //CHISS_CONFIGURATIONWINDOW_H
