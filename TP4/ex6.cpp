#include "exercises.h"

#include <vector>
#include <cmath>
#include <iostream>
#include <fstream>
#include <chrono>
#include <random>

int maxSubsequenceDP(int A[], unsigned int n, unsigned int &i, unsigned int &j) {
    int g_max = INT_MIN, l_max = 0, i_start = 0;
    for (int i_fr = 0; i_fr < n; i_fr++) {
        if (A[i_fr] > A[i_fr] + l_max) {
            l_max = A[i_fr];
            i_start = i_fr;
        } else {
            l_max += A[i_fr];
        }
        if (g_max < l_max) {
            g_max = l_max;
            i = i_start;
            j = i_fr;
        }
    }

    return g_max;
}

int maxSubsequenceBF(int A[], unsigned int n, unsigned int &i, unsigned int &j) {

    int maxSum = A[0];
    i = 0;
    j = 0;

    for (int ki = 0; ki < n; ki++) {
        for (int kj = ki; kj < n; kj++) {
            int currentIndex = ki, currentSum = 0;
            while (currentIndex <= kj) {
                currentSum += A[currentIndex];
                currentIndex++;
            }
            if (currentSum > maxSum) {
                i = ki;
                j = kj;
                maxSum = currentSum;
            }
        }
    }

    return maxSum;
}

int maxSub(int A[], unsigned int n, int &i, int &j) {
    if (n == 1) return A[i];
    int left_i = i, left_j = i + n / 2 - 1, max_left = maxSub(A, n / 2, left_i, left_j);
    int right_i = i + n / 2, right_j = j, max_right = maxSub(A, n / 2, right_i, right_j);

    int max_sum, i_ret, j_ret, i_ret_left = left_i, j_ret_right = right_j, current_sum = 0;

    if (max_left > max_right) {
        max_sum = max_left;
        i_ret = left_i;
        j_ret = left_j;
    }
    else {
        max_sum = max_right;
        i_ret = right_i;
        j_ret = right_j;
    }

    max_left = A[i + n / 2 - 1];
    max_right = A[i + n / 2];

    for (int k = i + n / 2 - 1; k >= left_i; k--) {
        current_sum += A[k];
        if (current_sum > max_left) {
            max_left = current_sum;
            i_ret_left = k;
        }
    }

    current_sum = 0;

    for (int k = i + n / 2; k <= (int) right_j; k++) {
        current_sum += A[k];
        if (current_sum > max_right) {
            max_right = current_sum;
            j_ret_right = k;
        }
    }

    if (max_sum < max_right + max_left) {
        max_sum = max_right + max_left;
        i_ret = i_ret_left;
        j_ret = j_ret_right;
    }

    i = i_ret;
    j = j_ret;
    return max_sum;


}

int maxSubsequenceDC(int A[], unsigned int n, unsigned int &i, unsigned int &j) {
    int i2 = 0, j2 = n - 1;
    int res = maxSub(A, n, i2, j2);
    i = (unsigned int) i2, j = (unsigned int) j2;
    return res;
}

int *generateRandomArray(size_t size, int lowerBound, int upperBound) {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> distrib(lowerBound, upperBound);

    int *array = new int[size];

    for (size_t i = 0; i < size; i++) {
        array[i] = distrib(gen);
    }

    return array;
}

void testPerformanceMaxSubsequence() {
    std::ofstream myfile;
    myfile.open("time_complexity2.csv");
    myfile << "n,Brute Force\n";

    const int maxTestSize = (int) pow(10, 4);

    int *array = generateRandomArray(maxTestSize, -10000, 10000);

    auto functions = {maxSubsequenceBF};

    for (size_t n = 50; n <= maxTestSize; n += 100) {

        myfile << n;

        for (auto function: functions) {
            unsigned int i = 0, j = 0;
            auto start = std::chrono::high_resolution_clock::now();
            function(array, n, i, j);
            auto finish = std::chrono::high_resolution_clock::now();
            auto milli = std::chrono::duration_cast<std::chrono::milliseconds>(finish - start).count();

            myfile << "," << milli;
        }

        myfile << "\n";
    }

    myfile.close();
    delete array;
}

/// TESTS ///
#include <gtest/gtest.h>

TEST(TP4_Ex6, testMaxSubsequence) {
    int A1[] = {1, 2, 3, 4};
    unsigned int n1 = 4;
    unsigned int i, j;
    EXPECT_EQ(maxSubsequenceDP(A1, n1, i, j), 10);
    EXPECT_EQ(i, 0);
    EXPECT_EQ(j, 3);

    int A2[] = {2, -1, -3, 4};
    unsigned int n2 = 4;
    EXPECT_EQ(maxSubsequenceDP(A2, n2, i, j), 4);
    EXPECT_EQ(i, 3);
    EXPECT_EQ(j, 3);

    int A3[] = {2, -1, 3, 4};
    unsigned int n3 = 4;
    EXPECT_EQ(maxSubsequenceDP(A3, n3, i, j), 8);
    EXPECT_EQ(i, 0);
    EXPECT_EQ(j, 3);

    int A4[] = {-2, 1, -3, 4, -1, 2, 1, -5, 4};
    unsigned int n4 = 9;
    EXPECT_EQ(maxSubsequenceDP(A4, n4, i, j), 6);
    EXPECT_EQ(i, 3);
    EXPECT_EQ(j, 6);

}
/*
TEST(TP4_Ex6, testPerformance) {
    testPerformanceMaxSubsequence();
}*/