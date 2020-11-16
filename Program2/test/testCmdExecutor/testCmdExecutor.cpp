#include "cmd_executor.hpp"
#include "testCmdExecutor.h"
#include <gmock/gmock.h>

using ::testing::_;
using ::testing::Return;
using namespace DrawerNS;

CmdExecutorTest::CmdExecutorTest()
{
}

CmdExecutorTest::~CmdExecutorTest(){};

void CmdExecutorTest::SetUp(){};

void CmdExecutorTest::TearDown(){};

TEST_F(CmdExecutorTest, testNewImage)
{
    CmdExecutor cmdexec(&m_drawer);
    string cmd = "test";

    EXPECT_CALL(m_drawer, NewImage()).Times(1);
    cmdexec.ExecuteNewImage(cmd);
}

TEST_F(CmdExecutorTest, testSaveCurrentImage)
{
    CmdExecutor cmdexec(&m_drawer);
    string cmd = "test";
    EXPECT_CALL(m_drawer, SaveCurrentImage(cmd));
    cmdexec.ExecuteRender(cmd);
}
TEST_F(CmdExecutorTest, testExecuteDrawRectangle)
{
    CmdExecutor cmdexec(&m_drawer);
    string cmd = "40 40 150 150";
    point_t p1(40, 40);
    point_t p2(150, 150);
    EXPECT_CALL(m_drawer, DrawRectangle(p1, p2)).Times(1);
    cmdexec.ExecuteDrawRectangle(cmd);
}
TEST_F(CmdExecutorTest, testExecuteDrawTriangle)
{
    CmdExecutor cmdexec(&m_drawer);
    string cmd = "80 80 170 80 240 240";
    point_t p1(80, 80);
    point_t p2(170, 80);
    point_t p3(240, 240);
    EXPECT_CALL(m_drawer, DrawTriangle(p1, p2, p3)).Times(1);
    cmdexec.ExecuteDrawTriangle(cmd);
}
TEST_F(CmdExecutorTest, testExecuteSetWidth)
{
    CmdExecutor cmdexec(&m_drawer);
    string cmd = "80";
    EXPECT_CALL(m_drawer,SetImageWidth(stoi(cmd))).Times(1);
    cmdexec.ExecuteSetWidth(cmd);
}
TEST_F(CmdExecutorTest, testExecuteSetHeight)
{
    CmdExecutor cmdexec(&m_drawer);
    string cmd = "80";
    EXPECT_CALL(m_drawer, SetImageHeight(stoi(cmd))).Times(1);
    cmdexec.ExecuteSetHeight(cmd);
}
