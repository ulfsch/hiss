//
// main_gui.cpp.
//

#include "ConfigurationWindow.h"
#include "Configuration.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication application(argc, argv);
    application.setStyle("cleanlooks");  // Removes a annoying error message when number clicked

    Configuration configuration;
    configuration.parse_from_xml(argv[1]);

    ConfigurationWindow window(&configuration);
    window.show();

    return application.exec();
}

// End of file
