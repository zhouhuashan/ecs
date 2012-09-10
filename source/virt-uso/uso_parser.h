#ifndef USO_PARSER_H
#define USO_PARSER_H

#include <string>
#include <list>

#include "scenario_parser.h"
#include "types_vdb.h"

namespace virt_dashboard
{

class UsoParser : public ScenarioParser
{
private:
    typedef std::list< std::pair<ByteArray, int> > RequestMap;

public:
    UsoParser(std::string filename);
    virtual ~UsoParser() {}

    ByteArray GetRequest();
    int GetDelay();
    void NextRequest();

protected:
    virtual void ParseFileLine(std::string& line);

private:
    RequestMap requests_;
};

}

#endif