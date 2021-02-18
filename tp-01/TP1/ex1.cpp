// By: Gonçalo Leão

#include "exercises.h"

bool sum3(unsigned int T, unsigned int nums[3]) {
    nums[0] = T/3;
    nums[1] = (T - nums[0])/2;
    nums[2] = T - nums[0] - nums[1];
    if(nums[0] <= 0 || nums[1] <= 0 || nums[2] <= 0) return false;
    else return true;
}

bool sum3_a(unsigned int T, unsigned int nums[3]) {
    for(int i=1; ; i++){
        for(int j=1; j<=i; j++){
            for(int k=1;k<=j; k++){
                int sum = i + j + k;
                if(sum == T){
                    nums[0] = i; nums[1] = j; nums[2] = k;
                    return true;
                }else if(sum > T) return false;
            }
        }
    }
}

/// TESTS ///
#include <gtest/gtest.h>

void compareSums(unsigned int selected[3], unsigned int expectedSum) {
    EXPECT_EQ(selected[0] + selected[1] + selected[2], expectedSum);
}

TEST(TP1_Ex1, 3sumExists) {
    unsigned int selected[3];

    unsigned int T = 10;
    EXPECT_EQ(sum3(T,selected), true);
    compareSums(selected,T);

    T = 18;
    EXPECT_EQ(sum3(T,selected), true);
    compareSums(selected,T);
}

TEST(TP1_Ex1, 3sumNotExists) {
    unsigned int selected[3];

    unsigned int T = 1;
    EXPECT_EQ(sum3(T,selected), false);
}