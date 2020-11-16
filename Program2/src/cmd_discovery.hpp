#ifndef CMD_DISCOVERY_CPP
#define CMD_DISCOVERY_CPP

#include <string>
#include <list>
#include <iostream>
#include <algorithm>
#include <cstring>
#include <functional>
#include <memory>
#include "custom_exceptions.hpp"
#include "icmd_discovery.h"
#include "icmd_executor.h"
using namespace std;

namespace DrawerNS
{
    class CmdDiscovery : public ICmdDiscovery
    {
        typedef void (CmdDiscovery::*executeCmd)(string &cmd);

    private:
        ICmdExecutor* cmdExecutor;
        list<pair<string, executeCmd>> cmdList;
        char space = char(' ');
        void FillCmdList()
        {
            this->cmdList.clear();
            this->cmdList.push_back(pair<string, executeCmd>("SET_WIDTH", &CmdDiscovery::ExecuteSetWidth));
            this->cmdList.push_back(pair<string, executeCmd>("SET_HEIGHT", &CmdDiscovery::ExecuteSetHeight));
            this->cmdList.push_back(pair<string, executeCmd>("DRAW_RECTANGLE", &CmdDiscovery::ExecuteDrawRectangle));
            this->cmdList.push_back(pair<string, executeCmd>("DRAW_TRIANGLE", &CmdDiscovery::ExecuteDrawTriangle));
            this->cmdList.push_back(pair<string, executeCmd>("RENDER", &CmdDiscovery::ExecuteRender));
            this->cmdList.push_back(pair<string, executeCmd>("NEWIMAGE", &CmdDiscovery::ExecuteNewImage));
            this->cmdList.push_back(pair<string, executeCmd>("EXIT", &CmdDiscovery::Exit));
        }
        void ExecuteSetWidth(string &cmd)
        {
            this->cmdExecutor->ExecuteSetWidth(cmd);
        }
        void ExecuteSetHeight(string &cmd)
        {
            this->cmdExecutor->ExecuteSetHeight(cmd);
        }
        void ExecuteDrawRectangle(string &cmd)
        {
            this->cmdExecutor->ExecuteDrawRectangle(cmd);
        }
        void ExecuteDrawTriangle(string &cmd)
        {
            this->cmdExecutor->ExecuteDrawTriangle(cmd);
        }
        void ExecuteRender(string &cmd)
        {
           this->cmdExecutor->ExecuteRender(cmd);
        }
        void ExecuteNewImage(string &cmd)
        {
            this->cmdExecutor->ExecuteNewImage(cmd);
        }
        string GetCmd(const string &cmd)
        {
            size_t pos = cmd.find(space);
            return cmd.substr(0, pos);
        }
        string RemoveCmd(const string &cmd)
        {
            size_t pos = cmd.find(space);
            return cmd.substr(pos + 1, cmd.size());
        }

        void Exit(string& cmd)
        {
            throw ExitException();
        }
    public:
        CmdDiscovery(ICmdExecutor *cmdExecutor)
        {
            this->cmdExecutor = cmdExecutor;
            this->FillCmdList();
        }

        void ProccessCmd(string &cmd)
        {
            bool found = false;
            for (pair<string, executeCmd> val : this->cmdList)
            {
                if (val.first==this->GetCmd(cmd))
                {
                    found = true;
                    cmd = RemoveCmd(cmd);
                    invoke(val.second, this, cmd);
                }
            }
            if (!found)
            {
                throw CmdException(cmd);
            }
        }
    };

} // namespace DrawerNS
#endif