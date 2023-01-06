// by Klepatskyi Oleh
#include "pch.h"
#include "AnyType.h"

TEST(AnyTypeTest, EmptyThrowsException)
{
	AnyType a;
	EXPECT_THROW(a.getBool(), EmptyValueException);
	EXPECT_THROW(a.toBool(), EmptyValueException);
	EXPECT_THROW(a.getChar(), EmptyValueException);
	EXPECT_THROW(a.toChar(), EmptyValueException);
	EXPECT_THROW(a.getUChar(), EmptyValueException);
	EXPECT_THROW(a.toUChar(), EmptyValueException);
	EXPECT_THROW(a.getShort(), EmptyValueException);
	EXPECT_THROW(a.toShort(), EmptyValueException);
	EXPECT_THROW(a.getUShort(), EmptyValueException);
	EXPECT_THROW(a.toUShort(), EmptyValueException);
	EXPECT_THROW(a.getInt(), EmptyValueException);
	EXPECT_THROW(a.toInt(), EmptyValueException);
	EXPECT_THROW(a.getUInt(), EmptyValueException);
	EXPECT_THROW(a.toUInt(), EmptyValueException);
	EXPECT_THROW(a.getLong(), EmptyValueException);
	EXPECT_THROW(a.toLong(), EmptyValueException);
	EXPECT_THROW(a.getULong(), EmptyValueException);
	EXPECT_THROW(a.toULong(), EmptyValueException);
	EXPECT_THROW(a.getLLong(), EmptyValueException);
	EXPECT_THROW(a.toLLong(), EmptyValueException);
	EXPECT_THROW(a.getULLong(), EmptyValueException);
	EXPECT_THROW(a.toULLong(), EmptyValueException);
	EXPECT_THROW(a.getFloat(), EmptyValueException);
	EXPECT_THROW(a.toFloat(), EmptyValueException);
	EXPECT_THROW(a.getDouble(), EmptyValueException);
	EXPECT_THROW(a.toDouble(), EmptyValueException);
	EXPECT_THROW(a.getLDouble(), EmptyValueException);
	EXPECT_THROW(a.toLDouble(), EmptyValueException);
}

TEST(AnyTypeTest, ClearedThrowsException)
{
	AnyType a(5);
	a.clear();
	EXPECT_THROW(a.getBool(), EmptyValueException);
	EXPECT_THROW(a.toBool(), EmptyValueException);
	EXPECT_THROW(a.getChar(), EmptyValueException);
	EXPECT_THROW(a.toChar(), EmptyValueException);
	EXPECT_THROW(a.getUChar(), EmptyValueException);
	EXPECT_THROW(a.toUChar(), EmptyValueException);
	EXPECT_THROW(a.getShort(), EmptyValueException);
	EXPECT_THROW(a.toShort(), EmptyValueException);
	EXPECT_THROW(a.getUShort(), EmptyValueException);
	EXPECT_THROW(a.toUShort(), EmptyValueException);
	EXPECT_THROW(a.getInt(), EmptyValueException);
	EXPECT_THROW(a.toInt(), EmptyValueException);
	EXPECT_THROW(a.getUInt(), EmptyValueException);
	EXPECT_THROW(a.toUInt(), EmptyValueException);
	EXPECT_THROW(a.getLong(), EmptyValueException);
	EXPECT_THROW(a.toLong(), EmptyValueException);
	EXPECT_THROW(a.getULong(), EmptyValueException);
	EXPECT_THROW(a.toULong(), EmptyValueException);
	EXPECT_THROW(a.getLLong(), EmptyValueException);
	EXPECT_THROW(a.toLLong(), EmptyValueException);
	EXPECT_THROW(a.getULLong(), EmptyValueException);
	EXPECT_THROW(a.toULLong(), EmptyValueException);
	EXPECT_THROW(a.getFloat(), EmptyValueException);
	EXPECT_THROW(a.toFloat(), EmptyValueException);
	EXPECT_THROW(a.getDouble(), EmptyValueException);
	EXPECT_THROW(a.toDouble(), EmptyValueException);
	EXPECT_THROW(a.getLDouble(), EmptyValueException);
	EXPECT_THROW(a.toLDouble(), EmptyValueException);
}

TEST(AnyTypeTest, GetThrowsOnIncorrectType)
{
	AnyType a;
	a = 5;
	EXPECT_THROW(a.getBool(), StoredTypeMismatchException);
	EXPECT_NO_THROW(a.getInt());
}

TEST(AnyTypeTest, GetCorrectlyReturnsValue)
{
	const int i = 5;
	AnyType a = i;
	EXPECT_EQ(a.getInt(), i);
	const float f = 5.5;
	a = f;
	EXPECT_EQ(a.getFloat(), f);
}

TEST(AnyTypeTest, CorrectlySwaps)
{
	int i = 5;
	float f = 5.5;
	AnyType a = i, b = f;
	a.swap(b);
	EXPECT_EQ(a.getFloat(), f);
	EXPECT_EQ(b.getInt(), i);
}

TEST(AnyTypeTest, CorrectlyReturnsTypeAfterAssignment)
{
	bool b = true;
	char c = 5;
	unsigned char uc = c;
	short s = c;
	unsigned short us = c;
	int i = c;
	unsigned int ui = c;
	long l = c;
	unsigned long ul = c;
	long long ll = c;
	unsigned long long ull = c;
	float f = c;
	double d = c;
	long double ld = c;
	
	AnyType a = b;
	EXPECT_EQ(AnyType::Type::BOOL, a.valueType());
	a = c;
	EXPECT_EQ(AnyType::Type::CHAR, a.valueType());
	a = uc;
	EXPECT_EQ(AnyType::Type::UCHAR, a.valueType());
	a = s;
	EXPECT_EQ(AnyType::Type::SHORT, a.valueType());
	a = us;
	EXPECT_EQ(AnyType::Type::USHORT, a.valueType());
	a = i;
	EXPECT_EQ(AnyType::Type::INT, a.valueType());
	a = ui;
	EXPECT_EQ(AnyType::Type::UINT, a.valueType());
	a = l;
	EXPECT_EQ(AnyType::Type::LONG, a.valueType());
	a = ul;
	EXPECT_EQ(AnyType::Type::ULONG, a.valueType());
	a = ll;
	EXPECT_EQ(AnyType::Type::LLONG, a.valueType());
	a = ull;
	EXPECT_EQ(AnyType::Type::ULLONG, a.valueType());
	a = f;
	EXPECT_EQ(AnyType::Type::FLOAT, a.valueType());
	a = d;
	EXPECT_EQ(AnyType::Type::DOUBLE, a.valueType());
	a = ld;
	EXPECT_EQ(AnyType::Type::LDOUBLE, a.valueType());
}

TEST(AnyTypeTest, CorrectlyReturnsUnsigned)
{
	unsigned char uc = std::numeric_limits<unsigned char>::max();
	unsigned short us = std::numeric_limits<unsigned short>::max();
	unsigned int ui = std::numeric_limits<unsigned int>::max();
	unsigned long ul = std::numeric_limits<unsigned long>::max();
	unsigned long long ull = std::numeric_limits<unsigned long long>::max();
	AnyType a = uc;
	EXPECT_EQ(a.getUChar(), uc);
	a = us;
	EXPECT_EQ(a.getUShort(), us);
	a = ui;
	EXPECT_EQ(a.toUInt(), ui);
	a = ul;
	EXPECT_EQ(a.toULong(), ul);
	a = ull;
	EXPECT_EQ(a.toULLong(), ull);
}

TEST(AnyTypeTest, CorrectlyCopies)
{
	const int value = 5;
	AnyType a(value),
			b(a);
	ASSERT_EQ(b.getInt(), a.getInt());
	ASSERT_EQ(a.getInt(), value);
}

TEST(AnyTypeTest, CorrectlyMoves)
{
	const int value = 5;
	AnyType a(value),
		b(std::move(a));
	ASSERT_EQ(b.getInt(), value);
	ASSERT_EQ(a.valueType(), AnyType::Type::EMPTY);
}

TEST(AnyTypeTest, ToCorrectlyConvertsType)
{
	const float f = 5.0;
	AnyType a = f;
	ASSERT_NO_THROW(a.toInt());
	EXPECT_EQ(a.toInt(), (int) f);
}

TEST(AnyTypeTest, ToConvertsBoolToInt)
{
	const bool b = true;
	AnyType a = b;
	ASSERT_NO_THROW(a.toInt());
	EXPECT_EQ(a.toInt(), (int) b);
}

TEST(AnyTypeTest, ToConvertsBoolToChar)
{
	const bool b = true;
	AnyType a = b;
	ASSERT_NO_THROW(a.toChar());
	EXPECT_EQ(a.toChar(), (char) b);
}