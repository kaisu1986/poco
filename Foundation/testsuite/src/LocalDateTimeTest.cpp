//
// LocalDateTimeTest.cpp
//
// $Id: //poco/1.3/Foundation/testsuite/src/LocalDateTimeTest.cpp#1 $
//
// Copyright (c) 2004-2006, Applied Informatics Software Engineering GmbH.
// and Contributors.
//
// Permission is hereby granted, free of charge, to any person or organization
// obtaining a copy of the software and accompanying documentation covered by
// this license (the "Software") to use, reproduce, display, distribute,
// execute, and transmit the Software, and to prepare derivative works of the
// Software, and to permit third-parties to whom the Software is furnished to
// do so, all subject to the following:
// 
// The copyright notices in the Software and this entire statement, including
// the above license grant, this restriction and the following disclaimer,
// must be included in all copies of the Software, in whole or in part, and
// all derivative works of the Software, unless such copies or derivative
// works are solely in the form of machine-executable object code generated by
// a source language processor.
// 
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE, TITLE AND NON-INFRINGEMENT. IN NO EVENT
// SHALL THE COPYRIGHT HOLDERS OR ANYONE DISTRIBUTING THE SOFTWARE BE LIABLE
// FOR ANY DAMAGES OR OTHER LIABILITY, WHETHER IN CONTRACT, TORT OR OTHERWISE,
// ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
// DEALINGS IN THE SOFTWARE.
//


#include "LocalDateTimeTest.h"
#include "CppUnit/TestCaller.h"
#include "CppUnit/TestSuite.h"
#include "Poco/LocalDateTime.h"
#include "Poco/DateTime.h"
#include "Poco/Timestamp.h"
#include "Poco/Timespan.h"
#include "Poco/Timezone.h"


using Poco::LocalDateTime;
using Poco::DateTime;
using Poco::Timestamp;
using Poco::Timespan;
using Poco::Timezone;


LocalDateTimeTest::LocalDateTimeTest(const std::string& name): CppUnit::TestCase(name)
{
}


LocalDateTimeTest::~LocalDateTimeTest()
{
}


void LocalDateTimeTest::testGregorian1()
{
	LocalDateTime dt(1970, 1, 1);
	assert (dt.year() == 1970);
	assert (dt.month() == 1);
	assert (dt.day() == 1);
	assert (dt.hour() == 0);
	assert (dt.minute() == 0);
	assert (dt.second() == 0);
	assert (dt.millisecond() == 0);
	assert (dt.dayOfWeek() == 4);
	assert (dt.tzd() == Timezone::tzd());
	assert (dt.julianDay() == 2440587.5);
	
	dt.assign(2001, 9, 9, 1, 46, 40);
	assert (dt.year() == 2001);
	assert (dt.month() == 9);
	assert (dt.day() == 9);
	assert (dt.hour() == 1);
	assert (dt.minute() == 46);
	assert (dt.second() == 40);
	assert (dt.millisecond() == 0);
	assert (dt.dayOfWeek() == 0);
	assert (dt.tzd() == Timezone::tzd());
	assertEqualDelta (dt.julianDay(), 2452161.574074, 0.000001);
}


void LocalDateTimeTest::testGregorian2()
{
	LocalDateTime dt(2*3600, 1970, 1, 1, 0, 0, 0, 0, 0);
	assert (dt.year() == 1970);
	assert (dt.month() == 1);
	assert (dt.day() == 1);
	assert (dt.hour() == 0);
	assert (dt.minute() == 0);
	assert (dt.second() == 0);
	assert (dt.millisecond() == 0);
	assert (dt.dayOfWeek() == 4);
	assert (dt.tzd() == 2*3600);
	
	dt.assign(-7*3600, 2001, 9, 9, 1, 46, 40, 0, 0);
	assert (dt.year() == 2001);
	assert (dt.month() == 9);
	assert (dt.day() == 9);
	assert (dt.hour() == 1);
	assert (dt.minute() == 46);
	assert (dt.second() == 40);
	assert (dt.millisecond() == 0);
	assert (dt.dayOfWeek() == 0);
	assert (dt.tzd() == -7*3600);
}


void LocalDateTimeTest::testConversions()
{
	LocalDateTime dt1(2*3600, 2005, 1, 28, 14, 24, 44, 234, 0);
	LocalDateTime dt2(dt1.tzd(), dt1.utc());
	LocalDateTime dt3;
	dt3 = dt1;
	LocalDateTime dt4(dt2);
	LocalDateTime dt5(-4*3600, dt1.utc());

	assert (dt2.year() == 2005);
	assert (dt2.month() == 1);
	assert (dt2.day() == 28);
	assert (dt2.hour() == 14);
	assert (dt2.minute() == 24);
	assert (dt2.second() == 44);
	assert (dt2.millisecond() == 234);
	assert (dt2.dayOfWeek() == 5);
	assert (dt2.tzd() == 2*3600);

	assert (dt5.year() == 2005);
	assert (dt5.month() == 1);
	assert (dt5.day() == 28);
	assert (dt5.hour() == 8);
	assert (dt5.minute() == 24);
	assert (dt5.second() == 44);
	assert (dt5.millisecond() == 234);
	assert (dt5.dayOfWeek() == 5);
	assert (dt5.tzd() == -4*3600);
}


void LocalDateTimeTest::testCalcs()
{
	LocalDateTime dt1(2005, 1, 1);
	assert (dt1.dayOfYear() == 1);
	assert (dt1.week(DateTime::MONDAY) == 0);
	dt1.assign(2005, 1, 3);
	assert (dt1.dayOfYear() == 3);
	assert (dt1.week(DateTime::MONDAY) == 1);
	dt1.assign(2005, 1, 9);
	assert (dt1.dayOfYear() == 9);
	assert (dt1.week(DateTime::MONDAY) == 1);
	dt1.assign(2005, 1, 10);
	assert (dt1.dayOfYear() == 10);
	assert (dt1.week(DateTime::MONDAY) == 2);
	dt1.assign(2005, 2, 1);
	assert (dt1.dayOfYear() == 32);
	assert (dt1.week(DateTime::MONDAY) == 5);
	dt1.assign(2005, 12, 31);
	assert (dt1.week(DateTime::MONDAY) == 52);
	dt1.assign(2007, 1, 1);
	assert (dt1.week(DateTime::MONDAY) == 1);
	dt1.assign(2007, 12, 31);
	assert (dt1.week(DateTime::MONDAY) == 53);
	
	// Jan 1 is Mon
	dt1.assign(2001, 1, 1);  
	assert (dt1.week() == 1);
	dt1.assign(2001, 1, 7);
	assert (dt1.week() == 1);
	dt1.assign(2001, 1, 8);
	assert (dt1.week() == 2);
	dt1.assign(2001, 1, 21);
	assert (dt1.week() == 3);
	dt1.assign(2001, 1, 22);
	assert (dt1.week() == 4);

	// Jan 1 is Tue
	dt1.assign(2002, 1, 1);
	assert (dt1.week() == 1);
	dt1.assign(2002, 1, 6);
	assert (dt1.week() == 1);
	dt1.assign(2002, 1, 7);
	assert (dt1.week() == 2);
	dt1.assign(2002, 1, 20);
	assert (dt1.week() == 3);
	dt1.assign(2002, 1, 21);
	assert (dt1.week() == 4);

	// Jan 1 is Wed
	dt1.assign(2003, 1, 1);
	assert (dt1.week() == 1);
	dt1.assign(2003, 1, 5);
	assert (dt1.week() == 1);
	dt1.assign(2003, 1, 6);
	assert (dt1.week() == 2);
	dt1.assign(2003, 1, 19);
	assert (dt1.week() == 3);
	dt1.assign(2003, 1, 20);
	assert (dt1.week() == 4);
	
	// Jan 1 is Thu
	dt1.assign(2004, 1, 1);
	assert (dt1.week() == 1);
	dt1.assign(2004, 1, 4);
	assert (dt1.week() == 1);
	dt1.assign(2004, 1, 5);
	assert (dt1.week() == 2);
	dt1.assign(2004, 1, 18);
	assert (dt1.week() == 3);
	dt1.assign(2004, 1, 19);
	assert (dt1.week() == 4);

	// Jan 1 is Fri
	dt1.assign(1999, 1, 1);
	assert (dt1.week() == 0);
	dt1.assign(1999, 1, 3);
	assert (dt1.week() == 0);
	dt1.assign(1999, 1, 4);
	assert (dt1.week() == 1);
	dt1.assign(1999, 1, 17);
	assert (dt1.week() == 2);
	dt1.assign(1999, 1, 18);
	assert (dt1.week() == 3);

	// Jan 1 is Sat
	dt1.assign(2000, 1, 1);
	assert (dt1.week() == 0);
	dt1.assign(2000, 1, 2);
	assert (dt1.week() == 0);
	dt1.assign(2000, 1, 3);
	assert (dt1.week() == 1);
	dt1.assign(2000, 1, 16);
	assert (dt1.week() == 2);
	dt1.assign(2000, 1, 17);
	assert (dt1.week() == 3);
	
	// Jan 1 is Sun
	dt1.assign(1995, 1, 1);
	assert (dt1.week() == 0);
	dt1.assign(1995, 1, 2);
	assert (dt1.week() == 1);
	dt1.assign(1995, 1, 3);
	assert (dt1.week() == 1);
	dt1.assign(1995, 1, 15);
	assert (dt1.week() == 2);
	dt1.assign(1995, 1, 16);
	assert (dt1.week() == 3);
}


void LocalDateTimeTest::testAMPM()
{
	LocalDateTime dt1(2005, 1, 1, 0, 15, 30);
	assert (dt1.isAM());
	assert (!dt1.isPM());
	assert (dt1.hourAMPM() == 12);
	
	dt1.assign(2005, 1, 1, 12, 15, 30);
	assert (!dt1.isAM());
	assert (dt1.isPM());
	assert (dt1.hourAMPM() == 12);

	dt1.assign(2005, 1, 1, 13, 15, 30);
	assert (!dt1.isAM());
	assert (dt1.isPM());
	assert (dt1.hourAMPM() == 1);
}


void LocalDateTimeTest::testRelational1()
{
	LocalDateTime dt1(2005, 1, 1, 0, 15, 30);
	LocalDateTime dt2(2005, 1, 2, 0, 15, 30);
	LocalDateTime dt3(dt1);
	
	assert (dt1 < dt2);
	assert (dt1 <= dt2);
	assert (dt2 > dt1);
	assert (dt2 >= dt1);
	assert (dt1 != dt2);
	assert (!(dt1 == dt2));
	
	assert (dt1 == dt3);
	assert (!(dt1 != dt3));
	assert (dt1 >= dt3);
	assert (dt1 <= dt3);
	assert (!(dt1 > dt3));
	assert (!(dt1 < dt3));
}


void LocalDateTimeTest::testRelational2()
{
	LocalDateTime dt1(2*3600, 2005, 1, 1, 15, 30, 0, 0, 0);
	LocalDateTime dt2(2*3600, 2005, 1, 1, 17, 30, 0, 0, 0);
	LocalDateTime dt3(5*3600, 2005, 1, 1, 18, 30, 0, 0, 0);

	assert (dt1 < dt2);
	assert (dt1 <= dt2);
	assert (dt2 > dt1);
	assert (dt2 >= dt1);
	assert (dt1 != dt2);
	assert (!(dt1 == dt2));
	
	assert (dt1 == dt3);
	assert (!(dt1 != dt3));
	assert (dt1 >= dt3);
	assert (dt1 <= dt3);
	assert (!(dt1 > dt3));
	assert (!(dt1 < dt3));
}


void LocalDateTimeTest::testArithmetics1()
{
	LocalDateTime dt1(2005, 1, 1, 0, 15, 30);
	LocalDateTime dt2(2005, 1, 2, 0, 15, 30);
	
	Timespan s = dt2 - dt1;
	assert (s.days() == 1);
	
	LocalDateTime dt3 = dt1 + s;
	assert (dt3 == dt2);
	
	dt3 -= s;
	assert (dt3 == dt1);
	dt1 += s;
	assert (dt1 == dt2);
}


void LocalDateTimeTest::testArithmetics2()
{
	LocalDateTime dt1(2*3600, 2005, 1, 1, 15, 30, 0, 0, 0);
	LocalDateTime dt2(5*3600, 2005, 1, 2, 18, 30, 0, 0, 0);
	
	Timespan s = dt2 - dt1;
	assert (s.days() == 1);
	
	LocalDateTime dt3 = dt1 + s;
	assert (dt3 == dt2);
	
	dt3 -= s;
	assert (dt3 == dt1);
	dt1 += s;
	assert (dt1 == dt2);
}


void LocalDateTimeTest::testSwap()
{
	LocalDateTime dt1(2005, 1, 1, 0, 15, 30);
	LocalDateTime dt2(2005, 1, 2, 0, 15, 30);
	
	assert (dt1 < dt2);
	dt1.swap(dt2);
	assert (dt2 < dt1);
}


void LocalDateTimeTest::setUp()
{
}


void LocalDateTimeTest::tearDown()
{
}


CppUnit::Test* LocalDateTimeTest::suite()
{
	CppUnit::TestSuite* pSuite = new CppUnit::TestSuite("LocalDateTimeTest");

	CppUnit_addTest(pSuite, LocalDateTimeTest, testGregorian1);
	CppUnit_addTest(pSuite, LocalDateTimeTest, testGregorian2);
	CppUnit_addTest(pSuite, LocalDateTimeTest, testConversions);
	CppUnit_addTest(pSuite, LocalDateTimeTest, testCalcs);
	CppUnit_addTest(pSuite, LocalDateTimeTest, testAMPM);
	CppUnit_addTest(pSuite, LocalDateTimeTest, testRelational1);
	CppUnit_addTest(pSuite, LocalDateTimeTest, testRelational2);
	CppUnit_addTest(pSuite, LocalDateTimeTest, testArithmetics1);
	CppUnit_addTest(pSuite, LocalDateTimeTest, testArithmetics2);
	CppUnit_addTest(pSuite, LocalDateTimeTest, testSwap);

	return pSuite;
}
