#include <QApplication>
#include "gtest/gtest.h"
#include "gmock/gmock.h"
#include "common/teamcity_messages.h"
#include "common/teamcity_gtest.h"

#if defined(__linux__) || defined(__APPLE__)
int main(int ac, char **av)
{
    QApplication app(ac, av);

    testing::InitGoogleTest(&ac, av);
    if (jetbrains::teamcity::underTeamcity())
    {
        ::testing::TestEventListeners& listeners = ::testing::UnitTest::GetInstance()->listeners();
        // Add unique flowId parameter if you want to run test processes in parallel
        // See http://confluence.jetbrains.net/display/TCD6/Build+Script+Interaction+with+TeamCity#BuildScriptInteractionwithTeamCity-MessageFlowId
        listeners.Append(new jetbrains::teamcity::TeamcityGoogleTestEventListener());
    }
    return RUN_ALL_TESTS();
}
#elif _WIN32
#include <Windows.h>
int main(int ac, char **av)
{
    QApplication app(ac, av);
    testing::InitGoogleTest(&ac, av);
//    if (jetbrains::teamcity::underTeamcity())
//    {
//        ::testing::TestEventListeners& listeners = ::testing::UnitTest::GetInstance()->listeners();
        // Add unique flowId parameter if you want to run test processes in parallel
        // See http://confluence.jetbrains.net/display/TCD6/Build+Script+Interaction+with+TeamCity#BuildScriptInteractionwithTeamCity-MessageFlowId
//        listeners.Append(new jetbrains::teamcity::TeamcityGoogleTestEventListener());
//    }
    auto res = RUN_ALL_TESTS();
    system("Pause");
    return res;
}
#endif
