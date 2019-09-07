//
// Configuration.cpp.
//

#include "Configuration.h"
#include "StandardAlgorithm.h"
#include "ConstantTraffic.h"
#include "TrivialAlgorithm.h"


Configuration::Configuration(QObject *parent) :
        QObject(parent),
        building_(nullptr),
        algorithm_(nullptr),
        traffic_(nullptr)
{
}


Configuration::~Configuration()
{
    delete building_;
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
        ok = parse_xml_stream(xml);
    }
    return ok;
}

bool Configuration::parse_xml_stream(QXmlStreamReader &xml)
{
    bool ok = xml.readNextStartElement() && xml.name() == QLatin1String("configuration");

    while (xml.readNextStartElement() && ok)
    {
        if (xml.name() == QLatin1String("building"))
        {
            int floors = xml.attributes().value("floors").toString().toInt(&ok);
            building_ = new Building(floors, this);

            while (xml.readNextStartElement() && ok)
            {
                if (xml.name() == "elevator")
                {
                    int min_floor = xml.attributes().value("min_floor").toString().toInt(&ok);
                    int max_floor = xml.attributes().value("max_floor").toString().toInt(&ok);
                    building_->add_elevator(new Elevator(min_floor, max_floor, building_));
                    xml.readNext();
                }
                else
                {
                    ok = false;
                    break;
                }
            }
        }
        else if (xml.name() == QLatin1String("algorithm"))
        {
            QStringRef type = xml.attributes().value("type");
            if (type == "Trivial")
            {
                algorithm_ = new TrivialAlgorithm();
            }
            else if (type == "Standard")
            {
                algorithm_ = new StandardAlgorithm();
            }
            else
            {
                ok = false;
                break;
            }
            xml.readNext();
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
                ok = false;
                break;
            }
            xml.readNext();
        }
        else
        {
            ok = false;
            break;
        }
    }

    return ok && !xml.hasError();
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
                algorithm_ = new TrivialAlgorithm();
            }
            else if (elem->Attribute("type", "UpDownButton"))
            {
                algorithm_ = new StandardAlgorithm();
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
