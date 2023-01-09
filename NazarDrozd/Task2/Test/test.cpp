#include "pch.h"
#include "../AnyType.h"
#include "../AnyType.cpp"

class AnyTypeTest : public testing::Test
{
public:
	void SetUp() override;
//	void TearDown() override;
protected:
	AnyType any;
};

void AnyTypeTest::SetUp()
{
	any = 135;
}

TEST_F(AnyTypeTest, AnyType_constructor)
{
	EXPECT_EQ(135, any.GetValueInt());
	any = true;
	EXPECT_EQ(true, any.GetValueBool());
	any = 1.7;
	EXPECT_EQ(1.7, any.GetValueDouble());
}

TEST(AnyType, AnyType_assignment)
{
	int x = 135;
	AnyType any;
	any = x;
	EXPECT_EQ(135, any.GetValueInt());
}

TEST_F(AnyTypeTest, AnyType_copy_constructor)
{
	AnyType any2 = any;
	EXPECT_EQ(135, any.GetValueInt());
	EXPECT_EQ(135, any2.GetValueInt());
}

TEST_F(AnyTypeTest, AnyType_assignment_operator)
{
	AnyType any2 = true;
	any2 = any;
	EXPECT_EQ(135, any.GetValueInt());
	EXPECT_EQ(135, any2.GetValueInt());
}

TEST(AnyType, AnyType_move_constructor)
{
	int x = 135;
	AnyType any1(x);
	AnyType any2(std::move(any1));
	EXPECT_EQ(135, any2.GetValueInt());
}

TEST(AnyType, AnyType_move_assignment_operator)
{
	int x = 135;
	AnyType any1(x);
	AnyType any2 = true;
	any2 = std::move(any1);
	EXPECT_EQ(135, any2.GetValueInt());
}

TEST(AnyType, GetEmpty)
{
	AnyType any;
	EXPECT_THROW(any.GetValueInt(), ExceptionType);
}

TEST(AnyType, GetAnotherType)
{
	AnyType any = 1.5;
	EXPECT_THROW(any.GetValueInt(), ExceptionType);
}

TEST_F(AnyTypeTest, AnyType_assignment_1)
{
	AnyType any2 = 135;
	any += any2;
	EXPECT_EQ(270, any.GetValueInt());
}

TEST_F(AnyTypeTest, AnyType_assignment_2)
{
	AnyType any2 = 1.5;
	EXPECT_THROW(any += any2, ExceptionType);
}

TEST_F(AnyTypeTest, AnyType_assignment_3)
{
	AnyType any2;
	EXPECT_THROW(any += any2, ExceptionType);
}

TEST_F(AnyTypeTest, AnyType_swap)
{
	AnyType any2 = 1.5;
	AnyType any3;

	any.Swap(any2);
	EXPECT_EQ(1.5, any.GetValueDouble());
	EXPECT_EQ(135, any2.GetValueInt());

	any2.Swap(any3);
	EXPECT_THROW(any2.GetValueInt(), ExceptionType);
	EXPECT_EQ(135, any3.GetValueInt());
}