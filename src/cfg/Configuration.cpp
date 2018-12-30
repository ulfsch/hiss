//
// Configuration.cpp.
//

#include "Configuration.h"
#include "tinyxml2.h"
#include "UpDownButtonAlgorithm.h"
#include "ConstantTraffic.h"
#include "CallButtonAlgorithm.h"

using namespace tinyxml2;

Configuration::Configuration(QObject *parent) :
        QObject(parent),
        building_(nullptr),
        algorithm_(nullptr),
        traffic_(nullptr)
{
}


Configuration::~Configuration()
{
    // delete building_;
    delete algorithm_;
    delete traffic_;
}


bool Configuration::parse_from_xml(const char *file_name)
{
    bool ok = false;
    QFile file(file_name);

    if (file.open(QFile::ReadOnly | QFile::Text))
    {
        QXmlStreamReader xml(&file);
        Q_ASSERT(xml.readNextStartElement() && xml.name() == QLatin1String("configuration"));

        while (xml.readNextStartElement())
        {
            if (xml.name() == QLatin1String("building"))
            {
                int floors = xml.attributes().value("floors").toString().toInt(&ok);
                building_ = new Building(floors, this);

                while (xml.readNextStartElement())
                {
                    if (xml.name() == "Elevator")
                    {
                        int min_floor = 0;
                        int max_floor = 10;
                        building_->add_elevator(new Elevator(min_floor, max_floor, building_));

                        xml.readNext();
                    }
                }
            }
            else if (xml.name() == QLatin1String("algorithm"))
            {
                QStringRef type = xml.attributes().value("type");
                if (type == "CallButton")
                {
                    algorithm_ = new CallButtonAlgorithm();
                }
                else if (type == "UpDownButton")
                {
                    algorithm_ = new UpDownButtonAlgorithm();
                }
                else
                {
                    break;  // Error
                }

            }
            else if (xml.name() == QLatin1String("traffic"))
            {
                QStringRef type = xml.attributes().value("type");
                if (type == "Random")
                {
                    double rate = xml.attributes().value("rate").toString().toFloat(&ok);
                    traffic_ = new ConstantTraffic(10, 100, rate);
                }
                else
                {
                    break;  // Error
                }

            }
            else
            {
                break; // Error
            }
        }
        ok = ok && !xml.hasError();
    }

    return ok;
}

#if 0
bool Configuration::parse_from_xml_old(const char *file_name)
{
    XMLDocument doc;
    doc.LoadFile(file_name);

    const XMLElement *elem = doc.FirstChildElement("configuration");
    if (elem)
    {
        elem = elem->FirstChildElement("building");
        if (elem)
        {
            FloorNumber floors = 10;
            elem->QueryAttribute("floors", &floors);
            building_ = new Building(floors, this);

            for (const XMLElement *p = elem->FirstChildElement("elevator"); p; p = p->NextSiblingElement("elevator"))
            {
                FloorNumber min_floor = 0;
                FloorNumber max_floor = floors;
                p->QueryAttribute("min_floor", &min_floor);
                p->QueryAttribute("max_floor", &max_floor);
                Elevator *elevator = new Elevator(min_floor, max_floor, building_);
                building_->add_elevator(elevator);
            }
        }
    }

    if (elem)
    {
        elem = elem->NextSiblingElement("algorithm");
        if (elem)
        {
            if (elem->Attribute("type", "CallButton"))
            {
                algorithm_ = new CallButtonAlgorithm();
            }
            else if (elem->Attribute("type", "UpDownButton"))
            {
                algorithm_ = new UpDownButtonAlgorithm();
            }
        }
    }

    if (elem)
    {
        elem = elem->NextSiblingElement("traffic");
        if (elem)
        {
            double rate;
            elem->QueryAttribute("rate", &rate);
            traffic_ = new ConstantTraffic(10, 100, rate);
        }
    }

    emit changed();
    return (building_ && algorithm_ && traffic_);
}
#endif

Traffic *Configuration::traffic() const
{
    return traffic_;
}

Algorithm *Configuration::algorithm() const
{
    return algorithm_;
}

Building *Configuration::building() const
{
    return building_;
}

// End of file
