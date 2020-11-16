#include "gmock/gmock.h"
#include "idrawer.h"
#include "definitions.h"

using namespace DrawerNS;

class MockDrawer: public IDrawer
{
public:
    MOCK_METHOD(void,NewImage,());
    MOCK_METHOD1(SaveCurrentImage, void(const string& image_name));
    MOCK_METHOD1(SetImageWidth, void(const int& image_with));
    MOCK_METHOD1(SetImageHeight, void(const int& image_height));
    MOCK_METHOD3(DrawTriangle, void(const point_t& point1, const point_t& point2, const point_t& point3));
    MOCK_METHOD2(DrawRectangle, void(const point_t& point1, const point_t& point2));
};
