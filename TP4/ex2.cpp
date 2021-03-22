#include "exercises.h"
#include <array>


bool changeMakingUnlimitedDP(unsigned int C[], unsigned int n, unsigned int T, unsigned int usedCoins[]) {
    int minCoins[n+1][T+1];
    int lastCoin[n+1][T+1];

    for(int i = 0; i <= n; i++){
        for(int j = 0; j <= T; j++){
            if(j == 0) { minCoins[i][j] = 0; lastCoin[i][j] = -1; }
            else if(i == 0) { minCoins[i][j] = T+1; lastCoin[i][j] = -1; }
            else {
                unsigned int a = T + 1, b = T + 1;
                int offset = j - (int)C[i-1];
                if (offset >= 0) a = minCoins[i][offset] + 1;
                if (i - 1 >= 0) b = minCoins[i - 1][j];
                minCoins[i][j] = std::min(a, b);
                if (a < b) lastCoin[i][j] = i-1;
                else lastCoin[i][j] = lastCoin[i-1][j];
            }
        }
    }
    for(int i = 0; i < n; i++) usedCoins[i] = 0;

    int i = T;
    while(i > 0){
        if(lastCoin[n][i] != -1) usedCoins[lastCoin[n][i]] += 1;
        else return false;
        i -= C[lastCoin[n][i]];
    }
    return true;
}


/// TESTS ///
#include <gtest/gtest.h>

TEST(TP4_Ex2, hasChangeCanonical) {
    unsigned int C[] = {1,2,5,10};
    unsigned int n = 4;
    unsigned int usedCoins[4];

    EXPECT_EQ(changeMakingUnlimitedDP(C,n,13,usedCoins), true);
    EXPECT_EQ(usedCoins[0], 1);
    EXPECT_EQ(usedCoins[1], 1);
    EXPECT_EQ(usedCoins[2], 0);
    EXPECT_EQ(usedCoins[3], 1);

    EXPECT_EQ(changeMakingUnlimitedDP(C,n,38,usedCoins), true);
    EXPECT_EQ(usedCoins[0], 1);
    EXPECT_EQ(usedCoins[1], 1);
    EXPECT_EQ(usedCoins[2], 1);
    EXPECT_EQ(usedCoins[3], 3);

    EXPECT_EQ(changeMakingUnlimitedDP(C,n,10,usedCoins), true);
    EXPECT_EQ(usedCoins[0], 0);
    EXPECT_EQ(usedCoins[1], 0);
    EXPECT_EQ(usedCoins[2], 0);
    EXPECT_EQ(usedCoins[3], 1);
}

TEST(TP4_Ex2, hasChangeNonCanonical) {
    unsigned int C[] = {1,4,5};
    unsigned int n = 3;
    unsigned int usedCoins[3];

    EXPECT_EQ(changeMakingUnlimitedDP(C,n,6,usedCoins), true);
    EXPECT_EQ(usedCoins[0], 1);
    EXPECT_EQ(usedCoins[1], 0);
    EXPECT_EQ(usedCoins[2], 1);

    EXPECT_EQ(changeMakingUnlimitedDP(C,n,8,usedCoins), true);
    EXPECT_EQ(usedCoins[0], 0);
    EXPECT_EQ(usedCoins[1], 2);
    EXPECT_EQ(usedCoins[2], 0);

    EXPECT_EQ(changeMakingUnlimitedDP(C,n,7,usedCoins), true);
    EXPECT_EQ(usedCoins[0], 2);
    EXPECT_EQ(usedCoins[1], 0);
    EXPECT_EQ(usedCoins[2], 1);
}

TEST(TP4_Ex2, hasNoChange) {
    unsigned int C[] = {5,10};
    unsigned int n = 2;
    unsigned int usedCoins[2];

    EXPECT_EQ(changeMakingUnlimitedDP(C,n,1,usedCoins), false);
}