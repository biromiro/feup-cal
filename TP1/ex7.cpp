#include "exercises.h"

#include <algorithm>
#include <vector>
#include <numeric>

double minimumAverageCompletionTime(std::vector<unsigned int> tasks, std::vector<unsigned int> &orderedTasks) {

    sort(tasks.begin(), tasks.end());

    /* What they want you to do
    do {
        permutations.push_back(tasks);
    } while (std::next_permutation(tasks.begin(), tasks.end()));

    double bestAverage = 99999;

    for (const auto &elem: permutations) {
        double average = 0;
        for (size_t i = 1; i <= elem.size(); i++) {
            average += std::accumulate(elem.begin(), elem.begin() + i, 0);
        }
        average /= elem.size();
        if (bestAverage > average) {
            bestAverage = average;
            orderedTasks = elem;
        }
    }
    */

    //What you can do (the exercise is just stupid, the best solution will always be the sorted vector)

    double bestAverage = 0.0;

    orderedTasks = tasks;

    for (size_t i = 1; i <= tasks.size(); i++) {
        bestAverage += std::accumulate(tasks.begin(), tasks.begin() + i, 0);
    }

    return bestAverage / tasks.size();
}

/// TESTS ///
#include <gtest/gtest.h>
#include <gmock/gmock.h>

TEST(TP1_Ex7, taskOrdering) {
    std::vector<unsigned int> tasks = {15, 8, 3, 10};
    std::vector<unsigned int> orderedTasks;
    double averageTime = minimumAverageCompletionTime(tasks, orderedTasks);
    EXPECT_EQ(orderedTasks.size(), 4 );
    ASSERT_NEAR(averageTime, 17.75, 0.00001);
    ASSERT_THAT(orderedTasks,  ::testing::ElementsAre(3,8,10,15));
}