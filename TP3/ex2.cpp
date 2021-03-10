#include "exercises.h"

int maxSub(int A[], unsigned int n, int &i, int &j){
    if(n == 1) return A[i];
    int left_i = i, left_j = i + n/2 - 1, max_left = maxSub(A, n/2, left_i, left_j);
    int right_i = i + n/2, right_j = j, max_right = maxSub(A, n/2, right_i, right_j);

    int max_sum, i_ret, j_ret;

    if(max_left > max_right) {max_sum = max_left; i_ret = left_i; j_ret = left_j;}
    else {max_sum = max_right; i_ret = right_i; j_ret = right_j;}

    for(int k = left_i; k <= left_j; k++){
        for(int m = right_i; m <= right_j; m++){
            int sum = 0;
            for(int t = k; t <= m; t++) sum += A[t];
            if(sum > max_sum) { i_ret = k; j_ret = m; max_sum = sum; }
        }
    }

    i = i_ret; j = j_ret;
    return max_sum;

}

int maxSubsequenceDC(int A[], unsigned int n, int &i, int &j) {
    i = 0, j = n-1;
    return maxSub(A, n, i, j);
}
/// TESTS ///
#include <gtest/gtest.h>

TEST(TP3_Ex2, testMaxSubsequence) {
    int A1[] = {1, 2, 3, 4};
    unsigned int n1 = 4;
    int i, j;
    EXPECT_EQ(maxSubsequenceDC(A1,n1,i,j), 10);
    EXPECT_EQ(i, 0);
    EXPECT_EQ(j, 3);

    int A2[] = {2, -1, -3, 4};
    unsigned int n2 = 4;
    EXPECT_EQ(maxSubsequenceDC(A2,n2,i,j), 4);
    EXPECT_EQ(i, 3);
    EXPECT_EQ(j, 3);

    int A3[] = {2, -1, 3, 4};
    unsigned int n3 = 4;
    EXPECT_EQ(maxSubsequenceDC(A3,n3,i,j), 8);
    EXPECT_EQ(i, 0);
    EXPECT_EQ(j, 3);

    int A4[] = {-2, 1, -3, 4, -1, 2, 1, -5, 4};
    unsigned int n4 = 9;
    EXPECT_EQ(maxSubsequenceDC(A4,n4,i,j), 6);
    EXPECT_EQ(i, 3);
    EXPECT_EQ(j, 6);

    int A5[] = {-2, 1, -3, 4, -1, 2, 1, -5, 4, -9, 10, 5, 4, 99, -3, 4, 2, 1, -5, -6, 9, 4, -3, -10};
    unsigned int n5 = 24;
    EXPECT_EQ(maxSubsequenceDC(A5,n5,i,j), 124);
    EXPECT_EQ(i, 10);
    EXPECT_EQ(j, 21);
}