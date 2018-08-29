//
// Configuration.h.
//
#ifndef CHISS_FACTORY_H
#define CHISS_FACTORY_H


#include "Algorithm.h"
#include "Traffic.h"
#include "Building.h"
#include "Result.h"

class Configuration
{
public:
    Configuration();
    ~Configuration();

    void parse_from_xml(const char *file_name);

    Building &building() const;
    Algorithm &algorithm() const;
    Traffic &traffic() const;

    Result &result();

private:
    Building *building_;
    Algorithm *algorithm_;
    Traffic *traffic_;
    Result result_;

};

#endif //CHISS_FACTORY_H
