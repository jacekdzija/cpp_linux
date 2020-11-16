#ifndef I_CMD_DISCOVERY_H
#define I_CMD_DISCOVERY_H

#pragma once

#include <string>
#include "definitions.h"

using namespace std;

namespace DrawerNS
{
    class ICmdDiscovery
    {
    public:
        virtual ~ICmdDiscovery() {};
        virtual void ProccessCmd(string &cmd) = 0;
    };
}
#endif