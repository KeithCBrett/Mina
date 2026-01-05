#include <gtest/gtest.h>


#include "action.h"
#include "calc.h"


TEST (DisplaySynopsisValidInp, ActionTests)
{
	EXPECT_EQ (0, action::DisplaySynopsis ());
}


TEST (EbitaValidInp, CalcTests)
{
	EXPECT_EQ (9790, calc::Ebita (90837, 61054, 18348, 1645));
}
