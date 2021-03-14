#include "exercises.h"

unsigned long s_recursive(unsigned int n, unsigned int k) {
    if(k==1 || k==n) return 1;
    return s_recursive(n-1,k-1) + k*s_recursive(n-1,k);
}

unsigned long b_recursive(unsigned int n) {
    unsigned long res = 0;
    for(unsigned long k = 1; k <= n; k++) {
        res += s_recursive(n, k);
    }
    return res;
}

unsigned long s_dynamic(unsigned int n, unsigned int k) {
    unsigned long arr[k];
    for(unsigned long j = 0; j < k; j++)
        arr[j] = 1;

    for(unsigned long m = 2; m < n; m++)
        for(unsigned long j = k-1; j >= 1; j--)
            if(j < m) arr[j] = arr[j-1] + (j+1)*arr[j];

    return arr[k-1];
}

unsigned long b_dynamic(unsigned int n) {
    unsigned long res = 0;
    for(unsigned long k = 1; k <= n; k++) {
        res += s_dynamic(n, k);
    }
    return res;
}

/// TESTS ///
#include <gtest/gtest.h>

TEST(TP4_Ex5, testPartitioningRecursive) {
    EXPECT_EQ(1,s_recursive(3,3));
    EXPECT_EQ(3025,s_recursive(9,3));
    EXPECT_EQ(22827,s_recursive(10,6));

    EXPECT_EQ(5,b_recursive(3));
    EXPECT_EQ(203,b_recursive(6));
    EXPECT_EQ(1382958545,b_recursive(15));
}

TEST(TP4_Ex5, testPartitioningDynamic) {
    EXPECT_EQ(1,s_dynamic(3,3));
    EXPECT_EQ(3025,s_dynamic(9,3));
    EXPECT_EQ(22827,s_dynamic(10,6));
    s_dynamic(6,4);

    EXPECT_EQ(5,b_dynamic(3));
    EXPECT_EQ(203,b_dynamic(6));
    EXPECT_EQ(1382958545,b_dynamic(15));
}