#ifndef DRAWER_CPP
#define DRAWER_CPP

#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <string>
#include "idrawer.h"
#include "bitmap_image.hpp"

namespace DrawerNS
{
    class Drawer : public IDrawer
    {
    private:
        const int max_with = 1024;
        const int max_height = 1024;
        int current_width = 1024;
        int currant_height = 1024;
        bitmap_image image;        
    public:

        Drawer()
        {
            this->NewImage();
        }
        void NewImage()
        {
            this->image.setwidth_height(max_with, max_height, true);
        }

        void SaveCurrentImage(const string &image_name)
        {
            image.save_image(image_name);
        }

        void SetImageWidth(const int &image_width)
        {
            this->current_width = image_width;
        }
        void SetImageHeight(const int &image_height)
        {
            this->currant_height = image_height;
        }
        void DrawTriangle(const point_t& point1, const point_t& point2 , const point_t& point3)
        {
            image_drawer draw(image);
            draw.pen_width(2);
            draw.pen_color(0, 255, 255);
            draw.triangle(point1.first,point1.second,point2.first,point2.second,point3.first,point3.second);

        }
        void DrawRectangle(const point_t& point1,const point_t& point2)
        {
            image_drawer draw(image);
            draw.pen_width(1);
            draw.pen_color(255, 255, 0);
            draw.rectangle(point1.first,point1.second, point2.first, point2.second);

        }
        ~Drawer()
        {

        }
    };
 
}
#endif