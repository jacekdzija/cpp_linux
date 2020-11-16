#pragma once
#include <string>

using namespace std;

namespace DrawerNS
{
    class ICmdExecutor
    {
    public:
        virtual ~ICmdExecutor(){};
        virtual void ExecuteSetWidth(string &cmd) = 0;
        virtual void ExecuteSetHeight(string &cmd) = 0;
        virtual void ExecuteDrawRectangle(string &cmd) = 0;
        virtual void ExecuteDrawTriangle(string &cmd) = 0;
        virtual void ExecuteRender(string &cmd) = 0;
        virtual void ExecuteNewImage(string &cmd) = 0;
    };
} // namespace DrawerNS