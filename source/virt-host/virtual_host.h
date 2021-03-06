#ifndef VIRTUAL_HOST_H
#define VIRTUAL_HOST_H

#include "virtual_device.h"

namespace ecs
{

class ProtocolHost;

class VirtualHost : public VirtualDevice
{
public:
    VirtualHost(const ProgramOptions& options) : VirtualDevice(options) {}
    virtual ~VirtualHost();

    virtual void Start();

protected:
    virtual void CreateProtocol();

private:
    ProtocolHost* protocol_;

    DISALLOW_COPY_AND_ASSIGN(VirtualHost)
};

}

#endif
