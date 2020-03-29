//
// main_gui.cpp.
//

#include "MainWindow.h"
#include "Configuration.h"
#include "Simulator.h"
#include <QApplication>
#include <QObject>

int main(int argc, char *argv[])
{
    QApplication application(argc, argv);
    application.setStyle("cleanlooks");  // Removes a annoying error message when number clicked

    Configuration configuration(&application);
    bool ok = configuration.parse_from_xml(argv[1]);
    if (ok)
    {
        Simulator simulator(configuration.traffic(), configuration.algorithm(), configuration.building());

        MainWindow window(&simulator);
        window.connect(&configuration, SIGNAL(changed()), &window, SLOT(update_from_model()));

        window.show();
        return application.exec();
    }
}

// End of file
