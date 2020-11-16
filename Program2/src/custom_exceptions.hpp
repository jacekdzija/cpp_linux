#ifndef CUSTOM_EXCEPTIONS_CPP
#define CUSTOM_EXCEPTIONS_CPP

#include <exception>
#include <string>
using namespace std;
namespace DrawerNS
{
    struct CmdExceptionBase : public exception
    {
        public:
        string msg;
        CmdExceptionBase(){}
        CmdExceptionBase(string message)
        {
            this->msg = message;
        }
        const char *what() const throw()
        {
            return msg.c_str();
        }
    };

    struct CmdException : public CmdExceptionBase
    {
        CmdException(string message)
        {
            this->msg = "Command not found. Original command:" + message;
        }
        
    };

    struct ExitException : public exception
    {
    };
} // namespace DrawerNS
#endif