// By: Gonçalo Leão

#include "exercises.h"

int maxSubsequence(int A[], unsigned int n, unsigned int &i, unsigned int &j) {

    int maxSum = A[0];
    i = 0;
    j = 0;

    for(int ki=0; ki < n; ki++){
        for(int kj=ki; kj < n; kj++){
            int currentIndex = ki, currentSum = 0;
            while(currentIndex <= kj){
                currentSum += A[currentIndex];
                currentIndex++;
            }
            if(currentSum > maxSum){
                i = ki;
                j = kj;
                maxSum = currentSum;
            }
        }
    }

    return maxSum;
}


/// TESTS ///
#include <gtest/gtest.h>

TEST(TP1_Ex2, maxSubsequence) {
    int A[] = {-2, 1, -3, 4, -1, 2, 1, -5, 4};
    unsigned int n = 9;
    unsigned int i, j;
    EXPECT_EQ(maxSubsequence(A,n,i,j), 6);
    EXPECT_EQ(i, 3);
    EXPECT_EQ(j, 6);
}
