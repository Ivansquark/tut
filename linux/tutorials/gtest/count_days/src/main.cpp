#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include "days.h"

//-----------------------------------------------------------------------------
TEST(CountDays, test_days) {
    // Arrange
    Xray_Date lastD{11, 12, 22};
    Xray_Date curD{12, 12, 22};
    Xray_Time lastT{12, 34, 59};
    Xray_Time curT{0, 0, 0};
    // Act
    int d1 = days(lastD);
    int d2 = days(curD);
    std::cout << "days1 " << d1 << std::endl;
    std::cout << "days2 " << d2 << std::endl;
    std::cout << "days diff " << d2 - d1 << std::endl;
    int secs = time_diff_secs(d2 - d1, lastT, curT);
    std::cout << "secs diff " << secs << std::endl;
    std::cout << "hours diff " << secs / 3600 << std::endl;
    // Assert
    // ASSERT_EQ(days, 4) << "value != true sum, value = " << d;
}

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    //::testing::InitGoogleMock(&argc, argv);

    return RUN_ALL_TESTS();
}
