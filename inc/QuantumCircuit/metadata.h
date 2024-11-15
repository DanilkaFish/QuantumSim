#ifndef _METADATA
#define _METADATA
#include <memory>

class MetaData{
public:
    virtual ~MetaData() {};
};

typedef std::shared_ptr<MetaData> MetaDataPtr;
#endif