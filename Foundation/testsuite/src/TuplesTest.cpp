//
// TuplesTest.cpp
//
// $Id: //poco/1.3/Foundation/testsuite/src/TuplesTest.cpp#1 $
//
// Copyright (c) 2006, Applied Informatics Software Engineering GmbH.
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


#include "TuplesTest.h"
#include "CppUnit/TestCaller.h"
#include "CppUnit/TestSuite.h"
#include "Poco/Tuple.h"
#include "Poco/Void.h"


using Poco::Tuple;
using Poco::Void;


TuplesTest::TuplesTest(const std::string& name): CppUnit::TestCase(name)
{
}


TuplesTest::~TuplesTest()
{
}


void TuplesTest::testSimpleTuple()
{
	Tuple<int> t;
	assert (t.length == 1);
	t.set<0>(-1);
	assert (t.get<0>() == -1);
	
	Tuple<int> t2(-1);
	assert (t2.get<0>() == -1);

	Tuple<int> tCpy (t2);
	assert (t2.get<0>() == tCpy.get<0>());
	assert (t2 == tCpy);

	Tuple<int> tCpy2 = t2;
	assert (t2.get<0>() == tCpy2.get<0>());
	assert (t2 == tCpy2);
	tCpy2.set<0>(888);
	assert (t2 != tCpy2);
	assert (t < tCpy2);

	Tuple<int, std::string> t3(0);
	assert (t3.get<1>().empty());

	Tuple<int, std::string, std::vector<std::string> > t4(0);
	assert (t4.get<1>().empty());
	assert (t4.get<2>().empty());
}


void TuplesTest::testTupleSize5()
{
	Tuple<int, Void, Void, Void, Void> dummy1;
	assert (dummy1.length == 5);
	dummy1.set<0>(-1);
	assert (dummy1.get<0>() == -1);
	//test partial init
	Tuple<int, Void, Void, Void, Void> dummy11(0);

	Tuple<Void, int, Void, Void, Void> dummy2;
	dummy2.set<1>(-1);
	assert (dummy2.get<1>() == -1);

	Tuple<Void, Void, Void, Void, int> dummy3;
	dummy3.set<4>(-1);
	assert (dummy3.get<4>() == -1);

	Tuple<std::string, int, bool, float, char> aTuple;
	aTuple.set<0>("str");
	aTuple.set<1>(1);
	aTuple.set<2>(true);
	aTuple.set<3>(3.14f);
	aTuple.set<4>(' ');
	assert (aTuple.get<0>() == "str");
	assert (aTuple.get<1>() == 1);
	assert (aTuple.get<2>());
	assert (aTuple.get<3>() >= 3.13f && aTuple.get<3>() <= 3.15f);
	assert (aTuple.get<4>() == ' ');

	Tuple<std::string, int, bool, float, char> aTuple2(aTuple);
	assert (aTuple == aTuple2);
	aTuple2.set<2>(false);
	assert (aTuple != aTuple2);
	aTuple2.set<1>(100000);
	assert (aTuple < aTuple2);
}


void TuplesTest::testTupleSize10()
{
	Tuple<std::string, int, bool, float, char, long, double, short, std::string, int> aTuple;
	assert (aTuple.length == 10);
	Tuple<std::string, int, bool, float, char, long, double, short, std::string, int> aTuple2("1", 1, true, 3.14f, 'c', 999, 33.14, 32700, "2", 2);
	assert (aTuple != aTuple2);
	aTuple = aTuple2;
	assert (aTuple == aTuple2);
	aTuple2.get<1>()++;
	assert (aTuple < aTuple2);
}


void TuplesTest::testMemOverhead()
{
	Tuple<short> small(0);
	int sz = sizeof(small);
	assert (sz == 4 || sz == 8); //depending on architecture and alignment
	Tuple<long> notSoSmall(0);
	sz = sizeof(notSoSmall);
	assert (sz == 8);
}

void TuplesTest::setUp()
{
}


void TuplesTest::tearDown()
{
}


CppUnit::Test* TuplesTest::suite()
{
	CppUnit::TestSuite* pSuite = new CppUnit::TestSuite("TuplesTest");

	CppUnit_addTest(pSuite, TuplesTest, testSimpleTuple);
	CppUnit_addTest(pSuite, TuplesTest, testTupleSize5);
	CppUnit_addTest(pSuite, TuplesTest, testTupleSize10);
	CppUnit_addTest(pSuite, TuplesTest, testMemOverhead);


	return pSuite;
}
