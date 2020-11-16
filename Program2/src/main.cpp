#include <iostream>

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <strings.h>
#include <string.h>
#include "drawer.hpp"
#include "cmd_discovery.hpp"
#include "custom_exceptions.hpp"
#include "cmd_executor.hpp"

using namespace DrawerNS;

int main(int argc, char *argv[])
{
    unique_ptr<IDrawer> drawerPtr(new Drawer());
    unique_ptr<ICmdExecutor> cmdExecutorPtr(new CmdExecutor(drawerPtr.get()));
    unique_ptr<ICmdDiscovery> discovery( new CmdDiscovery(cmdExecutorPtr.get()));

    while (true)
    {
        try
        {
            for (string line; getline(std::cin, line);)
            {
                discovery.get()->ProccessCmd(line);
                cout << "OK" << '\n';
            }
        }
        catch (const CmdException &e)
        {
            cout << e.what() << '\n';
        }
        catch (const ExitException &e)
        {
            //cerr << "Child EXITing...";
            break;
        }
        catch (const std::exception &e)
        {
            cout << "Command is invalid" << '\n';
        }
    }
    return 0;
}
