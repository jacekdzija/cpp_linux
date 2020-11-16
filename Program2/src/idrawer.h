#ifndef I_DRAWER_H
#define I_DRAWER_H

#pragma once

#include <string>
#include "definitions.h"

using namespace std;

namespace DrawerNS
{
    class IDrawer
    {
    public:
        virtual ~IDrawer() {};
        virtual void NewImage() = 0;
        virtual void SaveCurrentImage(const string& image_name) = 0;
        virtual void SetImageWidth(const int& image_with) = 0;
        virtual void SetImageHeight(const int& image_height) = 0;
        virtual void DrawTriangle(const point_t& point1, const point_t& point2, const point_t& point3) = 0;
        virtual void DrawRectangle(const point_t& point1, const point_t& point2) = 0;
    };
}

#endif // !I_DRAWER_H