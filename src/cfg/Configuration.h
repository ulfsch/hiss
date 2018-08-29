//
// Configuration.h.
//
#ifndef CHISS_FACTORY_H
#define CHISS_FACTORY_H


#include "Algorithm.h"
#include "Traffic.h"
#include "Building.h"

class Configuration
{
public:
    Configuration();
    ~Configuration();

    void from_xml(const char *file_name);

    Building &building() const;
    Algorithm &algorithm() const;
    Traffic &traffic() const;

private:
    Building *building_;
    Algorithm *algorithm_;
    Traffic *traffic_;
};


#endif //CHISS_FACTORY_H
