//
// ConfigurationWindow.cpp
//

#include <QVBoxLayout>
#include "ConfigurationWindow.h"
#include "Configuration.h"
#include "BuildingWidget.h"

ConfigurationWindow::ConfigurationWindow(Configuration *configuration, QWidget *parent) :
        QMainWindow(parent),
        configuration_(configuration),
        buildingWidget_(nullptr)
{
    update_from_model();
    // connect(configuration, SIGNAL(changed()), this, SLOT(update_from_model()));
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

// End of file
