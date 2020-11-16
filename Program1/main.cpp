#include "main.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fstream>
#include <iostream>
#include <algorithm>
#include <functional>
#include <memory>
#include <sys/wait.h>
#include <unistd.h>
#include <exception>

using namespace std;

#define INBUFSIZE 256
#define RD 0
#define WR 1

struct CmdExceptionBase : public exception
{
public:
    string msg;
    CmdExceptionBase() {}
    CmdExceptionBase(string msg)
    {
        this->msg = "Got exception:" + msg;
    }
    const char *what() const throw()
    {
        return msg.c_str();
    }
};
string RemoveChar(string cmd, const char &toRemove)
{
    std::string::iterator end_pos = remove(cmd.begin(), cmd.end(), toRemove);
    cmd.erase(end_pos, cmd.end());
    return cmd;
}
int main(int argc, char *argv[])
{
    string cmdFileName;
    const string exitCmd = "EXIT";
    const string cmdOk = "OK";
    pid_t childpid;
    char inbuf[INBUFSIZE];
    int rd;
    int rdup;
    int wdup;
    char *eol;
    int ptocpipe[2];
    int ctoppipe[2];
#define PARENT_READ ptocpipe[RD]
#define CHILD_WRITE ctoppipe[WR]
#define CHILD_READ ctoppipe[RD]
#define PARENT_WRITE ptocpipe[WR]

    if (argc == 2)
    {
        cmdFileName = argv[1];
    }

    if (pipe(ptocpipe) < 0)
    {
        fprintf(stderr, "pipe Parent->Child failed!\n");
        return 2;
    }

    if (pipe(ctoppipe) < 0)
    {
        fprintf(stderr, "pipe Child->Parent failed!\n");
        return 2;
    }

    switch (childpid = fork())
    {
    case -1: // Error
        fprintf(stderr, "Parent: fork() failed!\n");
        return 3;

    case 0:
        close(PARENT_WRITE);
        close(CHILD_READ);
        close(0);
        if ((rdup = dup(PARENT_READ)) < 0)
        {
            fprintf(stderr, "Failed dup(stdin)\n");
            return 4;
        }
        close(1);
        if ((wdup = dup(CHILD_WRITE)) < 0)
        {
            fprintf(stderr, "Failed dup(stdout)\n");
            return 5;
        }
        execlp("./Program2", "Program2", (char *)NULL);
        fprintf(stderr, "Parent: execl() failed!\n");
        return 4;
    }

    close(PARENT_READ);
    close(CHILD_WRITE);
    string input_line;
    ofstream logFile("log.txt", ios::out);
    ifstream cmdFile;
    char buff[INBUFSIZE + 100];
    bool readFromFile = false;
    try
    {
        if (cmdFileName.size() != 0)
        {
            cout << "Opening file:" << cmdFileName << '\n';
            cmdFile.open(cmdFileName);
            readFromFile = cmdFile.is_open();
            if (!readFromFile)
            {
                throw CmdExceptionBase("FileNotFound");
            }
        }
        do
        {

            if (!readFromFile)
            {
                getline(cin, input_line);
            }
            else
            {
                if (!getline(cmdFile, input_line))
                {
                    input_line = exitCmd;
                }
            }
            input_line = RemoveChar(input_line, '\r');
            input_line.append("\n");
            write(PARENT_WRITE, input_line.c_str(), input_line.length());

            if (input_line == exitCmd)
            {
                break;
            }
            if ((rd = read(CHILD_READ, inbuf, INBUFSIZE)) > 0)
            {
                if ((eol = rindex(inbuf, '\n')) != NULL)
                    *eol = '\0';

                snprintf(buff, sizeof(buff), "Command Status \"%s\"\n", inbuf);
                cout << buff;
                if (strncmp(inbuf, cmdOk.c_str(), cmdOk.size()) != 0)
                {
                    logFile << buff;
                    logFile.flush();
                }
            }
        } while (cin && rd > 0);
    }
    catch (const CmdExceptionBase &e)
    {
        write(PARENT_WRITE, exitCmd.c_str(), exitCmd.length());
        std::cerr << e.what() << '\n';
        logFile << "Got an exceptoion " << e.what() << '\n';
    }
    catch (const exception &e)
    {
        write(PARENT_WRITE, exitCmd.c_str(), exitCmd.length());
        std::cerr << e.what() << '\n';
        logFile << "Got an exceptoion " << e.what() << '\n';
    }

    if (cmdFile.is_open())
    {
        cmdFile.close();
    }
    if (logFile.is_open())
    {
        logFile.close();
    }
    
    cout << "Exiting...\n";
    return 0;
}
