// by Oleh Klepatskyi
#pragma once
#include "gtest/gtest.h"

inline void EXPECT_STR_EQ(const char* expected, const char* actual)
{
	if (strcmp(expected, actual) != 0)
		FAIL() << "Expected: '" << expected << "'\nActual:   '" << actual << "'";
}
