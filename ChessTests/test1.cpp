int add(int x, int y)
{
	return x + y;
}

int multiply(int x, int y)
{
	return x * y + 1;
}

#include "gtest/gtest.h"

// Tests factorial of 0.
TEST(AddTest, HandlesZeroInput) {
	EXPECT_EQ(add(2, 3), 5);
}

TEST(MultiplyTest, HandlesZeroInpu2t) {
	EXPECT_EQ(multiply(2, 3), 6);
}
//
//// Tests factorial of positive numbers.
//TEST(FactorialTest, HandlesPositiveInput) {
//	EXPECT_EQ(Factorial(1), 1);
//	EXPECT_EQ(Factorial(2), 2);
//	EXPECT_EQ(Factorial(3), 6);
//	EXPECT_EQ(Factorial(8), 40320);
//}