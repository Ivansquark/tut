#include "calculator.h"
#include <fstream>
#include <gmock/gmock.h>
#include <gtest/gtest.h>
#include <stdlib.h>
#include <vector>
// https://blog.andreiavram.ro/gtest-parameterized-tests-json/
using namespace std;
/*
TEST(CalculatorSimpleTest, Sum) {
    const auto actual = calculator::sum(1, 2);
    const auto expected = 3;
    EXPECT_EQ(actual, expected);
}

TEST(CalculatorTableDrivenTest, Sum) {
    struct Test {
        int a;
        int b;
        int sum;
    };

    const std::vector<Test> tests{{
        {1, 2, 3}, // 1
        {4, 5, 9}, // 2
        {1, 5, 9}, // 3
    }};

    static std::size_t test_case = 0;
    for (const auto& test : tests) {
        const auto actual = calculator::sum(test.a, test.b);
        const auto expected = test.sum;
        test_case++;
        EXPECT_EQ(actual, expected) << "test case: " << test_case;
    }
}

struct Test {
    int a;
    int b;
    int sum;
};

class CalculatorParameterizedTest : public testing::TestWithParam<Test> {};

TEST_P(CalculatorParameterizedTest, Sum) {
    const auto actual = calculator::sum(GetParam().a, GetParam().b);
    const auto expected = GetParam().sum;
    EXPECT_EQ(actual, expected);
}
INSTANTIATE_TEST_SUITE_P(InlineValues, CalculatorParameterizedTest,
                         testing::Values(Test{1, 2, 3}, Test{4, 5, 9},
                                         Test{2, 1, 9}));
*/
struct Test {
    int a;
    int b;
    int sum;
};

/*
namespace {
std::vector<Test> GetTests() {
    return {
        {1, 2, 3},
        {4, 5, 9},
        {1, 5, 9},
    };
}
} // namespace

INSTANTIATE_TEST_SUITE_P(Container, CalculatorParameterizedTest,
                         testing::ValuesIn(GetTests()));
*/
namespace {
std::vector<Test> GetTests(const std::string& path) {
    std::ifstream input(path);
    vector<Test> t;
    Test temp;
    std::string line;
    std::string tt = "";
    std::vector<string> vStr;
    while (std::getline(input, line)) {
        vStr.clear();
        size_t count = 0;
        for (auto&& i : line) {
            count++;
            if ((i != ' ')) {
                tt += i;
                if (count >= line.size()) {
                    vStr.push_back(tt);
                    tt.clear();
                }
            } else {
                vStr.push_back(tt);
                tt.clear();
            }
        }
        temp.a = std::stoi(vStr[0]);
        temp.b = std::stoi(vStr[1]);
        temp.sum = std::stoi(vStr[2]);

        t.push_back(temp);
    }
    /*
        while (input >> noskipws >> ch) {
            if (curCount == Count::FIRST) {
                curCount = Count::SECOND;
                temp.a = ch - 0x30;
                std::cout << temp.a << std::endl;
            } else if (curCount == Count::SECOND) {
                curCount = Count::THIRD;
                temp.b = ch - 0x30;
                std::cout << temp.b << std::endl;
            } else {
                curCount = Count::FIRST;
                temp.sum = ch - 0x30;
                std::cout << temp.sum << std::endl;
                t.push_back(temp);
            }
        }
    */

    return t;
}
} // namespace

class CalculatorParameterizedTest : public testing::TestWithParam<Test> {};
TEST_P(CalculatorParameterizedTest, Sum) {
    const auto actual = calculator::sum(GetParam().a, GetParam().b);
    const auto expected = GetParam().sum;
    EXPECT_EQ(actual, expected);
}
INSTANTIATE_TEST_SUITE_P(Txt, CalculatorParameterizedTest,
                         testing::ValuesIn(GetTests("input.txt")));

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    //::testing::InitGoogleMock(&argc, argv);

    return RUN_ALL_TESTS();
}
