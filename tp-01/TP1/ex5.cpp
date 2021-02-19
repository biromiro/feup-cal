// By: Gonçalo Leão

#include "exercises.h"
#include <iostream>
#include <algorithm>
#include <set>
#include <numeric>

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
            std::vector<unsigned int, std::allocator<unsigned int>> solution(usedCoins, usedCoins + n);
            if(solutions.empty() || std::accumulate(solution.begin(), solution.end(), 0) < std::accumulate(solutions[0].begin(), solutions[0].end(), 0)) solutions.push_back(solution);
        }
    }
}

unsigned int sumArray(unsigned int a[], unsigned int n) {
    unsigned int sum = 0;
    for(unsigned int i = 0; i < n; i++) {
        sum += a[i];
    }
    return sum;
}

bool isCanonical(unsigned int C[], unsigned int n) {
    if(n < 3) return true;
    int lowerBound = C[2], upperBound = C[n-2] + C[n-1];
    unsigned int *stock = static_cast<unsigned int *>(malloc(sizeof(unsigned int) * n));
    unsigned int *usedCoins = static_cast<unsigned int *>(malloc(sizeof(unsigned int) * n));
    std::vector<std::vector<unsigned int>> solutions;
    for(; lowerBound < upperBound; lowerBound++){
        for(size_t i=0; i < n; i++) {
            usedCoins[i] = 0;
            stock[i] = lowerBound / C[0];
        }
        calculateSolutions(C,stock,n,lowerBound, usedCoins, solutions);
        if(solutions.size() > 1) return false;
        else solutions.clear();
    }
    free(stock);
    return true;
}


/// TESTS ///
#include <gtest/gtest.h>

TEST(TP1_Ex5, canonicalTrue) {
    unsigned int C[] = {1,2,5};
    EXPECT_EQ(isCanonical(C,3), true);

    unsigned int C2[] = {1,2,5,10};
    EXPECT_EQ(isCanonical(C2,4), true);
}

TEST(TP1_Ex5, canonicalFalse) {
    unsigned int C[] = {1,4,5};
    EXPECT_EQ(isCanonical(C,3), false);
}