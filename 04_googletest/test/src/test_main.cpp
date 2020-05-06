#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include "calc.h"

TEST(Calc, Sum) {
    unique_ptr<Calc> calc = make_unique<Calc>();
    EXPECT_EQ(3, calc->sum(1, 2));
}

TEST(Calc, Sub) {
    unique_ptr<Calc> calc = make_unique<Calc>();
    EXPECT_EQ(-1, calc->sub(1, 2));
}
