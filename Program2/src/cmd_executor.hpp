
#ifndef CMD_EXECUTOR_CPP
#define CMD_EXECUTOR_CPP

#include <string>
#include <list>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <algorithm>
#include <functional>
#include <memory>
#include <vector>
#include "custom_exceptions.hpp"
#include "icmd_executor.h"
#include "idrawer.h"

namespace DrawerNS
{
    class CmdExecutor : public ICmdExecutor
    {
    private:
        IDrawer *drawer;
        char space = char(' ');
    public:
        CmdExecutor(IDrawer *drawer)
        {
            this->drawer = drawer;
        }
        string RemoveChar(string cmd,const char& toRemove)
        {
            std::string::iterator end_pos = remove(cmd.begin(), cmd.end(), toRemove);
            cmd.erase(end_pos, cmd.end());
            return cmd;
        }

        size_t Split(const string &cmd, vector<int> &vect, char ch)
        {
            size_t pos = cmd.find(ch);
            size_t initialPos = 0;
            vect.clear();

            while (pos != string::npos)
            {
                vect.push_back(stoi(cmd.substr(initialPos, pos - initialPos)));
                initialPos = pos + 1;

                pos = cmd.find(ch, initialPos);
            }

            string ss = cmd.substr(initialPos, std::min(pos, cmd.size()) - initialPos + 1);
            size_t any = ss.find(ch);
            if (any != string::npos|| ss.size() == 0)
            {
                throw CmdExceptionBase("Invalid Command");
            }
            vect.push_back(stoi(cmd.substr(initialPos, std::min(pos, cmd.size()) - initialPos + 1)));

            return vect.size();
        }
        void ExecuteSetWidth(string &cmd)
        {
            vector<int> points;
            Split(cmd, points, space);
            this->drawer->SetImageWidth(points.at(0));
        }
        void ExecuteSetHeight(string &cmd)
        {
            vector<int> points;
            Split(cmd, points, space);
            this->drawer->SetImageHeight(points.at(0));
        }
        void ExecuteDrawRectangle(string &cmd)
        {
            vector<point_t> res = this->GetPoint(cmd, 2);
            this->drawer->DrawRectangle(res.at(0), res.at(1));
        }
        void ExecuteDrawTriangle(string &cmd)
        {
            vector<point_t> res = this->GetPoint(cmd, 3);
            this->drawer->DrawTriangle(res.at(0), res.at(1), res.at(2));
        }
        void ExecuteRender(string &cmd)
        {
            cmd = this->RemoveChar(cmd,space);
            cmd = this->RemoveChar(cmd,'\n');
            cmd = this->RemoveChar(cmd,'\r');
            this->drawer->SaveCurrentImage(cmd);
        }
        void ExecuteNewImage(string &cmd)
        {
            this->drawer->NewImage();
        }
        vector<point_t> GetPoint(string cmd, int points)
        {
            vector<int> tempvect;
            Split(cmd, tempvect, space);

            if(tempvect.size()>points*2)
            {
                throw CmdExceptionBase("Command is invalid");
            }
            vector<point_t> res;
            for (size_t i = 0; i < points; i++)
            {
                res.push_back({tempvect.at(i * 2), tempvect.at(i * 2 + 1)});
            }
            return res;
        }
    };
} // namespace DrawerNS
#endif