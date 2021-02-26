#include "exercises.h"

#include <algorithm>

bool Activity::operator==(const Activity &a2) const {
    return start == a2.start && finish == a2.finish;
}

bool Activity::operator<(const Activity &a2) const {
    return finish < a2.finish;
}

std::vector<Activity> earliestFinishScheduling(std::vector<Activity> A) {

    std::vector<Activity> res;

    while (!A.empty()) {
        res.push_back(*std::min_element(A.begin(), A.end()));
        std::vector<Activity> newAvailableActivities;
        for (const auto &elem: A) {
            if (elem.start >= res.back().finish) newAvailableActivities.push_back(elem);
        }
        A = newAvailableActivities;
    }

    return res;
}
/// TESTS ///
#include <gtest/gtest.h>
#include <gmock/gmock.h>

TEST(TP1_Ex6, activityScheduling) {
    std::vector<Activity> A = {{10,20}, {30, 35}, {5, 15}, {10, 40}, {40, 50}};
    std::vector<Activity> V = earliestFinishScheduling(A);
    EXPECT_EQ(V.size(), 3 );
    ASSERT_THAT(V,  ::testing::ElementsAre(Activity(5, 15), Activity(30, 35), Activity(40, 50)));
}