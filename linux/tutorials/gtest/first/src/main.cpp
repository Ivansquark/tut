#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include "test1.h"
#include <fstream>

using namespace std;

TEST(TestGroupName, increment_by_6) {
    // Arrange
    int value = 100;
    int increment = 6;
    // Act
    value = value + increment;
    // Assert
    ASSERT_EQ(value, 106);
}
//-----------------------------------------------------------------------------
class MyClass {
    string id;

  public:
    MyClass(string _id) : id(_id) {}
    string getId() { return id; }
    void setId(const string& str) { id = str; }
};

TEST(TestGroupName, string_compare1) {
    // Arrange
    MyClass mc("root");
    // Act
    string value = mc.getId();
    // Assert
    EXPECT_EQ(value, "root");
    EXPECT_STREQ(value.c_str(), "root"); // строки сравнивают с _STREQ
}
TEST(TestGroupName, string_compare2) {
    // Arrange
    MyClass mc("root");
    // Act
    string value = mc.getId();
    mc.setId("opa");
    // Assert
    EXPECT_EQ(value, "root");
    EXPECT_EQ(mc.getId(), "opa");
}

//-----------------------------------------------------------------------------
int foo(int* arr, size_t len) {
    int sum = 0;
    vector<int> buf;
    for (int i = 0; i < len; ++i) {
        buf.push_back(arr[i]);
    }
    for (auto&& i : buf) {
        sum += i;
    }
    return std::forward<int>(sum);
}
TEST(TestGroupName, foo_test) {
    // Arrange
    int buf[5] = {1, 2, 3, 4, 5};
    // Act
    int value = foo(buf, sizeof(buf)/sizeof(int));
    // Assert
    ASSERT_EQ(value, 0) << "value != true sum, value = " << value;
}
//-----------------------------------------------------------------------------
TEST(TwoNum, test_template) {
    // Arrange
    TwoNum<string> t("1","opa");
    // Act
    string value = t.getSum();
    // Assert
    ASSERT_EQ(value, "3") << "value != true sum, value = " << value;
}
std::ifstream inputValuesFromFile("input.txt");
INSTANTIATE_TEST_CASE_P(FromFileStream,
                        TwoNum<int>,
                        ValuesIn(std::istream_iterator<int>(inputValuesFromFile),
                                 std::istream_iterator<int>()));
int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    //::testing::InitGoogleMock(&argc, argv);

    return RUN_ALL_TESTS();
}
