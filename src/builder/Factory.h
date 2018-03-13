//
// Factory.h.
//
#ifndef CHISS_FACTORY_H
#define CHISS_FACTORY_H


#include "../model/Building.h"
#include "../simulator/Algorithm.h"
#include "../simulator/Traffic.h"

class Factory {
public:
    Factory();
    ~Factory();

    void build_from_xml(const char *file_name);

    Building &building() const;
    Algorithm &algorithm() const;
    Traffic &traffic() const;

private:
    Building *building_;
    Algorithm *algorithm_;
    Traffic *traffic_;
};


#endif //CHISS_FACTORY_H
