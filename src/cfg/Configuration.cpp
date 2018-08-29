//
// Configuration.cpp.
//

#include "Configuration.h"
#include "tinyxml2.h"
#include "UpDownButtonAlgorithm.h"
#include "ConstantTraffic.h"
#include "CallButtonAlgorithm.h"

using namespace tinyxml2;

Configuration::Configuration() :
        building_(nullptr),
        algorithm_(nullptr),
        traffic_(nullptr)
{
}


Configuration::~Configuration()
{
    if (building_)
    {
        delete building_;
    }
    if (algorithm_)
    {
        delete algorithm_;
    }
    if (traffic_)
    {
        delete traffic_;
    }
}


void Configuration::from_xml(const char *file_name)
{
    XMLDocument doc;
    doc.LoadFile(file_name);

    const XMLElement *elem = doc.FirstChildElement("configuration");

    elem = elem->FirstChildElement("building");
    if (elem)
    {
        FloorNumber floors = 10;
        elem->QueryAttribute("floors", &floors);
        building_ = new Building(floors);

        for (const XMLElement *p = elem->FirstChildElement("elevator"); p; p = p->NextSiblingElement("elevator"))
        {
            FloorNumber min_floor = 0;
            FloorNumber max_floor = floors;
            p->QueryAttribute("min_floor", &min_floor);
            p->QueryAttribute("max_floor", &max_floor);
            Elevator elevator(min_floor, max_floor);
            building_->add_elevator(elevator);
        }
    }

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

    elem = elem->NextSiblingElement("traffic");
    if (elem)
    {
        traffic_ = new ConstantTraffic(10, 100, 1);
    }
}

Traffic &Configuration::traffic() const
{
    return *traffic_;
}

Algorithm &Configuration::algorithm() const
{
    return *algorithm_;
}

Building &Configuration::building() const
{
    return *building_;
}

// End of file
