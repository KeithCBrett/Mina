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
	EXPECT_EQ (7251, calc::Ebita (77349, 51352, 17053, 1693));
}


TEST (EbitaInvalidInp, CalcTests)
{
	EXPECT_EQ (-1, calc::Ebita(0, 61054, 18348, 1645));
	EXPECT_EQ (-1, calc::Ebita(90837, 0, 18348, 1645));
	EXPECT_EQ (-1, calc::Ebita(90837, 61054, 0, 1645));
	EXPECT_EQ (-1, calc::Ebita(90837, 61054, 18348, 0));
}
