#include "pch.h"
#include "../Project1/AnyType.h"
#include "../Project1/AnyType.cpp"
TEST(AnyType, Conctructor) {
	AnyType any = (short)1;
	EXPECT_EQ(1, any.ToShort());
	
	any = (int)12;
	EXPECT_EQ(12, any.ToInt());

	any = (long long)77243;
	EXPECT_EQ(77243, any.ToLongLong());

	any = (float)23.43f;
	EXPECT_EQ(23.43f, any.ToFloat());

	any = (double)2356.273;
	EXPECT_EQ(2356.273, any.ToDouble());

	any = (long double)63437.437;
	EXPECT_EQ(63437.437, any.ToLongDouble());

	any = 'x';
	EXPECT_EQ('x', any.ToChar());

	any = true;
	EXPECT_EQ(true, any.ToBool());
}

TEST(AnyType, Assignment) {
	short t_short = 1; int t_int = 12; long long t_long_long = 942;
	float t_float = 14.12f; double t_double = 924.12; long double t_long_double = 21.412;
	char t_char = 'j'; bool t_bool = false;
	AnyType any;

	any = t_short;
	EXPECT_EQ(t_short, any.ToShort());
	
	any = t_int;
	EXPECT_EQ(t_int, any.ToInt());

	any = t_long_long;
	EXPECT_EQ(t_long_long, any.ToLongLong());

	any = t_float;
	EXPECT_EQ(t_float, any.ToFloat());

	any = t_double;
	EXPECT_EQ(t_double, any.ToDouble());

	any = t_long_double;
	EXPECT_EQ(t_long_double, any.ToLongDouble());

	any = t_char;
	EXPECT_EQ(t_char, any.ToChar());

	any = t_bool;
	EXPECT_EQ(t_bool, any.ToBool());
}

TEST(AnyType, CopyConstructor) {
	AnyType ob1 = (bool)false, ob2 = ob1;
	EXPECT_EQ(false, ob1.ToBool());
	EXPECT_EQ(false, ob2.ToBool());
}

TEST(AnyType, AssignmentOperator) {
	AnyType ob1 = 34.53, ob2 = (bool)false;
	ob1 = ob2;
	EXPECT_EQ(false, ob1.ToBool());
	EXPECT_EQ(false, ob2.ToBool());
}

TEST(AnyType, MoveConstructor) {
	AnyType ob1((bool)true);
	AnyType ob2(std::move(ob1));
	EXPECT_EQ(true, ob2.ToBool());
}

TEST(AnyType, MoveAssignmentOperator) {
	bool t_bool = true;
	AnyType ob1(t_bool);
	AnyType ob2 = 3.14;
	ob2 = std::move(ob1);
	EXPECT_EQ(true, ob2.ToBool());
}

TEST(AnyType, ErrorException) {
	AnyType any;
	EXPECT_THROW(any.ToShort(), AnyTypeException);
}

TEST(AnyType, WrongType) {
	AnyType any = (bool)true;
	EXPECT_THROW(any.ToLongDouble(), AnyTypeException);
}

TEST(AnyType, SwapObjects) {
	AnyType ob1 = (bool)false, ob2 = 'x', ob3 = 8;

	ob1.SwapObjects(ob2);
	EXPECT_EQ('x', ob1.ToChar());
	EXPECT_EQ(false, ob2.ToBool());

	ob2.SwapObjects(ob3);
	EXPECT_THROW(ob2.ToBool(), AnyTypeException);
	EXPECT_EQ(false, ob3.ToBool());
}
