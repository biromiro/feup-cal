#include "exercises.h"
#include <algorithm>
#include <set>
#include <numeric>

std::set<std::vector<int>> generateCombinations(std::vector<int> values) {
    std::vector<int> current(values.size(), 0);
    std::set<std::vector<int>> result;

    int currentIndex = values.size() - 1, maxIndex = currentIndex;


    while (current != values) {
        result.insert(current);
        if (current[currentIndex] < values[currentIndex]) {
            current[currentIndex] += 1;
        } else {
            while (current[currentIndex] == values[currentIndex]) currentIndex--;
            current[currentIndex]++;
            while (currentIndex != maxIndex) {
                currentIndex++;
                current[currentIndex] = 0;
            }
        }
    }
    result.insert(current);

    return result;
}


bool changeMakingBF(unsigned int C[], unsigned int Stock[], unsigned int n, unsigned int T, unsigned int usedCoins[]) {
    int minCoins = -1;
    std::vector<int> availCoins(Stock, Stock + n);
    std::vector<int> coinValues(C, C + n);
    auto combinations = generateCombinations(availCoins);
    std::vector<int> result;
    for (const auto &val: combinations) {
        auto res = std::inner_product(coinValues.begin(), coinValues.end(), val.begin(), 0);
        if (res == T) {
            if (result.empty() ||
                std::accumulate(val.begin(), val.end(), 0) < std::accumulate(result.begin(), result.end(), 0)) {
                result = val;
            }
        }
    }
    if (result.empty()) return false;
    else {
        for (size_t i = 0; i < n; i++) {
            usedCoins[i] = result[i];
        }
        return true;
    }

}

/// TESTS ///
#include <gtest/gtest.h>

TEST(TP1_Ex3, hasBFChangeCanonical) {
    unsigned int C[] = {1,2,5,10};
    unsigned int Stock[] = {1,1,1,1};
    unsigned int n = 4;
    unsigned int usedCoins[4];

    EXPECT_EQ(changeMakingBF(C,Stock,n,13,usedCoins), true);
    EXPECT_EQ(usedCoins[0], 1);
    EXPECT_EQ(usedCoins[1], 1);
    EXPECT_EQ(usedCoins[2], 0);
    EXPECT_EQ(usedCoins[3], 1);

    unsigned int Stock2[] = {1,2,4,2};
    EXPECT_EQ(changeMakingBF(C,Stock2,n,38,usedCoins), true);
    EXPECT_EQ(usedCoins[0], 1);
    EXPECT_EQ(usedCoins[1], 1);
    EXPECT_EQ(usedCoins[2], 3);
    EXPECT_EQ(usedCoins[3], 2);

    unsigned int Stock3[] = {10,2,4,2};
    EXPECT_EQ(changeMakingBF(C,Stock3,n,10,usedCoins), true);
    EXPECT_EQ(usedCoins[0], 0);
    EXPECT_EQ(usedCoins[1], 0);
    EXPECT_EQ(usedCoins[2], 0);
    EXPECT_EQ(usedCoins[3], 1);
}

TEST(TP1_Ex3, hasBFChangeNonCanonical) {
    unsigned int C[] = {1,4,5};
    unsigned int Stock[] = {2,2,1};
    unsigned int n = 3;
    unsigned int usedCoins[3];

    EXPECT_EQ(changeMakingBF(C,Stock,n,6,usedCoins), true);
    EXPECT_EQ(usedCoins[0], 1);
    EXPECT_EQ(usedCoins[1], 0);
    EXPECT_EQ(usedCoins[2], 1);

    EXPECT_EQ(changeMakingBF(C,Stock,n,8,usedCoins), true);
    EXPECT_EQ(usedCoins[0], 0);
    EXPECT_EQ(usedCoins[1], 2);
    EXPECT_EQ(usedCoins[2], 0);

    unsigned int Stock2[] = {8,2,1};
    EXPECT_EQ(changeMakingBF(C,Stock2,n,7,usedCoins), true);
    EXPECT_EQ(usedCoins[0], 2);
    EXPECT_EQ(usedCoins[1], 0);
    EXPECT_EQ(usedCoins[2], 1);

    EXPECT_EQ(changeMakingBF(C,Stock2,n,8,usedCoins), true);
    EXPECT_EQ(usedCoins[0], 0);
    EXPECT_EQ(usedCoins[1], 2);
    EXPECT_EQ(usedCoins[2], 0);
}

TEST(TP1_Ex3, hasNoBFChange) {
    unsigned int C[] = {1,2,5,10};
    unsigned int Stock[] = {0,1,1,1};
    unsigned int n = 4;
    unsigned int usedCoins[4];

    EXPECT_EQ(changeMakingBF(C,Stock,n,18,usedCoins), false);
    EXPECT_EQ(changeMakingBF(C,Stock,n,1,usedCoins), false);
}