#include "exercises.h"

std::string calcSum(int sequence[], unsigned long n) {
    std::string ret = "";

    for(unsigned long k = 1; k <= n; k++) {

        unsigned long i = 0,  min_sum = 0, current_sum;

        for (unsigned long j = 0; j < k; j++) {
            min_sum += sequence[j];
        }

        current_sum = min_sum;

        for (unsigned long j = k; j < n; j++) {
            current_sum = current_sum - sequence[j - k] + sequence[j];
            if (current_sum < min_sum) {
                i = j - k + 1;
                min_sum = current_sum;
            }
        }

        ret += std::to_string(min_sum) + ',' + std::to_string(i) + ';';
    }

    return ret;
}

void testPerformanceCalcSum() {
    //TODO
}

/// TESTS ///
#include <gtest/gtest.h>

TEST(TP4_Ex4, CalcSumArrayTest) {
    int sequence[5] = {4,7,2,8,1};
    int sequence2[9] = {6,1,10,3,2,6,7,2,4};

    EXPECT_EQ("1,4;9,1;11,2;18,1;22,0;",calcSum(sequence, 5));
    EXPECT_EQ("1,1;5,3;11,3;16,1;20,3;24,3;31,1;35,1;41,0;",calcSum(sequence2, 9));
	
	testPerformanceCalcSum();
}