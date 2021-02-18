// By: Gonçalo Leão

#include "exercises.h"
#include <algorithm>


void calculateSolutions(unsigned int C[], unsigned int Stock[], unsigned int n, unsigned int T, unsigned int usedCoins[], std::vector<std::vector<unsigned int>>& solutions){
    int currentVal = 0, currentWorkingIndex = n-1, currentMaxIndex = n-1;
    for(;;){
        if (currentVal < T){
            if(Stock[currentWorkingIndex] > usedCoins[currentWorkingIndex]) usedCoins[currentWorkingIndex] += 1;
            else{
                if(currentWorkingIndex > 0) currentWorkingIndex -= 1;
                else{
                    if(currentMaxIndex == 0) break;
                    for(size_t i = 0; i<n; i++){
                        usedCoins[i] = 0;
                    }
                    currentWorkingIndex = currentMaxIndex - 1;
                    currentMaxIndex -= 1;
                    currentVal = 0;
                    continue;
                }
                if(Stock[currentWorkingIndex] > usedCoins[currentWorkingIndex]) usedCoins[currentWorkingIndex] += 1;
            }
        } else {
            usedCoins[currentWorkingIndex] -= 1;
            if(currentWorkingIndex > 0) currentWorkingIndex -= 1;
            else{
                if(currentMaxIndex == 0) break;
                for(size_t i = 0; i<n; i++){
                    usedCoins[i] = 0;
                }
                currentWorkingIndex = currentMaxIndex - 1;
                currentMaxIndex -= 1;
                currentVal = 0;
                continue;
            }
            if(Stock[currentWorkingIndex] > usedCoins[currentWorkingIndex]) usedCoins[currentWorkingIndex] += 1;
        }
        currentVal = 0;
        for(size_t i=0; i<n; i++){
            currentVal += C[i] * usedCoins[i];
        }
        if(currentVal == T ) {
            solutions.emplace_back(usedCoins, usedCoins + n);
        }
    }
}

bool changeMakingBF(unsigned int C[], unsigned int Stock[], unsigned int n, unsigned int T, unsigned int usedCoins[]) {
    for(size_t i = 0; i<n; i++){
        usedCoins[i] = 0;
    }
    std::vector<std::vector<unsigned int>> solutions;
    calculateSolutions(C,Stock,n,T,usedCoins, solutions);
    if(solutions.size() == 0){
        return false;
    }else{
        int min_coins = 999999;
        for(const std::vector<unsigned int>& elem: solutions){
            int sum_of_elems = 0;
            std::for_each(elem.begin(), elem.end(), [&] (int n) {
                sum_of_elems += n;
            });
            if(sum_of_elems <= min_coins){
                min_coins = sum_of_elems;
                for(unsigned int index=0; index < n; index++){
                    usedCoins[index] = elem[index];
                }
            }
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
}

TEST(TP1_Ex3, hasBFChangeNonCanonical) {
    unsigned int C[] = {1,4,5};
    unsigned int Stock[] = {3,2,1};
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
}

TEST(TP1_Ex3, hasNoBFChange) {
    unsigned int C[] = {1,2,5,10};
    unsigned int Stock[] = {0,1,1,1};
    unsigned int n = 4;
    unsigned int usedCoins[4];

    EXPECT_EQ(changeMakingBF(C,Stock,n,18,usedCoins), false);
    EXPECT_EQ(changeMakingBF(C,Stock,n,1,usedCoins), false);
}