//
// main_gui.cpp.
//

#include "MainWindow.h"
#include "Configuration.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication application(argc, argv);
    application.setStyle("cleanlooks");  // Removes a annoying error message when number clicked

    Configuration configuration(&application);
    configuration.parse_from_xml(argv[1]);

    MainWindow window(&configuration);
    window.show();
    return application.exec();
}

// End of file
