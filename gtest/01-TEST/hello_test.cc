#include <gtest/gtest.h>

// Demonstrate some basic assertions.
TEST(HelloTest, Case1) {
  // Expect two strings not to be equal.
  EXPECT_STRNE("hello", "world");
  // Expect equality.
  EXPECT_EQ(7 * 6, 42);
}


TEST(HelloTest, Case2) {
  // Expect two strings not to be equal.
  EXPECT_STREQ("hello", "hello"); // ok
  // Expect equality.
  EXPECT_EQ(7 * 6, 42); // ok

  ASSERT_NE(11, 0); // ok

  ASSERT_EQ(1, 1); // ok
}


TEST(HelloTest, Case3) {
  // Expect equality.
  EXPECT_NE(7 * 6, 42); // error, go on next assert

  ASSERT_NE(0, 0); // error break Case2

  ASSERT_EQ(0, 0); // ok
}

