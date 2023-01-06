// by Klepatskyi Oleh
#include "pch.h"
#include "AnyType.h"

TEST(TryConvertTest, ConvertsToBiggerType)
{
	EXPECT_NO_THROW((tryConvert<char, short>(std::numeric_limits<char>::max())));
	EXPECT_NO_THROW((tryConvert<char, short>(std::numeric_limits<char>::min())));
	EXPECT_NO_THROW((tryConvert<short, int>(std::numeric_limits<short>::max())));
	EXPECT_NO_THROW((tryConvert<short, int>(std::numeric_limits<short>::min())));
	EXPECT_NO_THROW((tryConvert<int, long>(std::numeric_limits<int>::max())));
	EXPECT_NO_THROW((tryConvert<int, long>(std::numeric_limits<int>::min())));
	EXPECT_NO_THROW((tryConvert<long, long long>(std::numeric_limits<long>::max())));
	EXPECT_NO_THROW((tryConvert<long, long long>(std::numeric_limits<long>::min())));

	EXPECT_NO_THROW((tryConvert<float, double>(0.1234567890F)));
	EXPECT_NO_THROW((tryConvert<double, long double>(0.12345678901234)));
}


TEST(TryConvertTest, ThrowsIfValueIsBiggerThanMaxConvertedToSmallerType)
{
	EXPECT_THROW((tryConvert<short, char>(std::numeric_limits<char>::max() + 1)), TypeConversionException);
	EXPECT_THROW((tryConvert<int, short>(std::numeric_limits<short>::max() + 1)), TypeConversionException);
	EXPECT_THROW((tryConvert<long long, int>(std::numeric_limits<long long>::max() + 1L)), TypeConversionException);
}

TEST(TryConvertTest, ConvertsUnsignedToSignedCorrectlyIfItIsLEThanSignedMax)
{
	EXPECT_NO_THROW((tryConvert<unsigned char, char>(std::numeric_limits<char>::max())));
	EXPECT_NO_THROW((tryConvert<unsigned char, char>(0)));
	EXPECT_NO_THROW((tryConvert<unsigned short, short>(std::numeric_limits<short>::max())));
	EXPECT_NO_THROW((tryConvert<unsigned short, short>(0)));
	EXPECT_NO_THROW((tryConvert<unsigned int, int>(std::numeric_limits<int>::max())));
	EXPECT_NO_THROW((tryConvert<unsigned int, int>(0)));
	EXPECT_NO_THROW((tryConvert<unsigned long, long>(std::numeric_limits<long>::max())));
	EXPECT_NO_THROW((tryConvert<unsigned long, long>(0)));
	EXPECT_NO_THROW((tryConvert<unsigned long long, long long>(std::numeric_limits<long long>::max())));
	EXPECT_NO_THROW((tryConvert<unsigned long long, long long>(0)));
}

TEST(TryConvertTest, ThrowsConvertUnsignedToSignedIfItIsBiggerThanSignedMax)
{
	EXPECT_THROW((tryConvert<unsigned char, char>(std::numeric_limits<char>::max() + 1)), TypeConversionException);
	EXPECT_THROW((tryConvert<unsigned short, short>(std::numeric_limits<short>::max() + 1)), TypeConversionException);
	EXPECT_THROW((tryConvert<unsigned int, int>(std::numeric_limits<int>::max() + 1)), TypeConversionException);
	EXPECT_THROW((tryConvert<unsigned long, long>(std::numeric_limits<long>::max() + 1)), TypeConversionException);
	EXPECT_THROW((tryConvert<unsigned long long, long long>(std::numeric_limits<long long>::max() + 1)), TypeConversionException);
}

TEST(TryConvertTest, ThrowsConvertNegativeToUnsigned)
{
	EXPECT_THROW((tryConvert<char, unsigned char>(std::numeric_limits<char>::min())), TypeConversionException);
	EXPECT_THROW((tryConvert<short, unsigned short>(std::numeric_limits<short>::min())), TypeConversionException);
	EXPECT_THROW((tryConvert<int, unsigned int>(std::numeric_limits<int>::min())), TypeConversionException);
	EXPECT_THROW((tryConvert<long, unsigned long>(std::numeric_limits<long>::min())), TypeConversionException);
	EXPECT_THROW((tryConvert<long long, unsigned long long>(std::numeric_limits<long long>::min())), TypeConversionException);
}

TEST(TryConvertTest, DoubleConvertsToFloatWithLessThan7Digits)
{
	EXPECT_NO_THROW((tryConvert<double, float>(0.1234567F)));
	EXPECT_NO_THROW((tryConvert<double, float>(0.123456700F)));
	EXPECT_NO_THROW((tryConvert<double, float>(1000)));
}

TEST(TryConvertTest, ThrowsDoubleToFloatIfHasMoreThan7DigitsPrecision)
{
	EXPECT_THROW((tryConvert<double, float>(0.123456700)), TypeConversionException);
	EXPECT_THROW((tryConvert<double, float>(1234.5678)), TypeConversionException);
}

TEST(TryConvertTest, ConvertsFloatingPointToIntegerTypeIfThereIsNoDigitsAfterDecimalPoint)
{
	EXPECT_NO_THROW((tryConvert<float, int>(5.0F)));
	EXPECT_NO_THROW((tryConvert<double, int>(5.0)));
	EXPECT_NO_THROW((tryConvert<long double, int>(5.0)));

	EXPECT_THROW((tryConvert<float, int>(5.1F)), TypeConversionException);
	EXPECT_THROW((tryConvert<double, int>(5.1)), TypeConversionException);
	EXPECT_THROW((tryConvert<long double, int>(5.1)), TypeConversionException);
}

TEST(TryConvertTest, CorrectlyConvertsToUnsignedOfSmallerType)
{
	EXPECT_NO_THROW((tryConvert<short, unsigned char>(std::numeric_limits<unsigned char>::max())));
	EXPECT_NO_THROW((tryConvert<int, unsigned short>(std::numeric_limits<unsigned short>::max())));
	EXPECT_NO_THROW((tryConvert<long long, unsigned int>(std::numeric_limits<unsigned int>::max())));
}