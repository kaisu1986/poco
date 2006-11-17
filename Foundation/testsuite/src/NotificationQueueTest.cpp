//
// NotificationQueueTest.cpp
//
// $Id: //poco/1.3/Foundation/testsuite/src/NotificationQueueTest.cpp#1 $
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


#include "NotificationQueueTest.h"
#include "CppUnit/TestCaller.h"
#include "CppUnit/TestSuite.h"
#include "Poco/NotificationQueue.h"
#include "Poco/Notification.h"
#include "Poco/Thread.h"
#include "Poco/Runnable.h"
#include "Poco/RunnableAdapter.h"


using Poco::NotificationQueue;
using Poco::Notification;
using Poco::Thread;
using Poco::RunnableAdapter;


class QTestNotification: public Notification
{
public:
	QTestNotification(const std::string& data): _data(data)
	{
	}
	~QTestNotification()
	{
	}
	const std::string& data() const
	{
		return _data;
	}

private:
	std::string _data;
};


NotificationQueueTest::NotificationQueueTest(const std::string& name): CppUnit::TestCase(name)
{
}


NotificationQueueTest::~NotificationQueueTest()
{
}


void NotificationQueueTest::testQueueDequeue()
{
	NotificationQueue queue;
	assert (queue.empty());
	assert (queue.size() == 0);
	Notification* pNf = queue.dequeueNotification();
	assertNullPtr(pNf);
	queue.enqueueNotification(new Notification);
	assert (!queue.empty());
	assert (queue.size() == 1);
	pNf = queue.dequeueNotification();
	assertNotNullPtr(pNf);
	assert (queue.empty());
	assert (queue.size() == 0);
	pNf->release();
	
	queue.enqueueNotification(new QTestNotification("first"));
	queue.enqueueNotification(new QTestNotification("second"));
	assert (!queue.empty());
	assert (queue.size() == 2);
	QTestNotification* pTNf = dynamic_cast<QTestNotification*>(queue.dequeueNotification());
	assertNotNullPtr(pTNf);
	assert (pTNf->data() == "first");
	pTNf->release();
	assert (!queue.empty());
	assert (queue.size() == 1);
	pTNf = dynamic_cast<QTestNotification*>(queue.dequeueNotification());
	assertNotNullPtr(pTNf);
	assert (pTNf->data() == "second");
	pTNf->release();
	assert (queue.empty());
	assert (queue.size() == 0);

	pNf = queue.dequeueNotification();
	assertNullPtr(pNf);
}


void NotificationQueueTest::testQueueDequeueUrgent()
{
	NotificationQueue queue;	
	queue.enqueueNotification(new QTestNotification("first"));
	queue.enqueueNotification(new QTestNotification("second"));
	queue.enqueueUrgentNotification(new QTestNotification("third"));
	assert (!queue.empty());
	assert (queue.size() == 3);
	QTestNotification* pTNf = dynamic_cast<QTestNotification*>(queue.dequeueNotification());
	assertNotNullPtr(pTNf);
	assert (pTNf->data() == "third");
	pTNf->release();
	assert (!queue.empty());
	assert (queue.size() == 2);
	pTNf = dynamic_cast<QTestNotification*>(queue.dequeueNotification());
	assert (pTNf->data() == "first");
	pTNf->release();
	assert (!queue.empty());
	assert (queue.size() == 1);
	pTNf = dynamic_cast<QTestNotification*>(queue.dequeueNotification());
	assertNotNullPtr(pTNf);
	assert (pTNf->data() == "second");
	pTNf->release();
	assert (queue.empty());
	assert (queue.size() == 0);

	Notification* pNf = queue.dequeueNotification();
	assertNullPtr(pNf);
}


void NotificationQueueTest::testWaitDequeue()
{
	NotificationQueue queue;
	queue.enqueueNotification(new QTestNotification("third"));
	queue.enqueueNotification(new QTestNotification("fourth"));
	assert (!queue.empty());
	assert (queue.size() == 2);
	QTestNotification* pTNf = dynamic_cast<QTestNotification*>(queue.waitDequeueNotification(10));
	assertNotNullPtr(pTNf);
	assert (pTNf->data() == "third");
	pTNf->release();
	assert (!queue.empty());
	assert (queue.size() == 1);
	pTNf = dynamic_cast<QTestNotification*>(queue.waitDequeueNotification(10));
	assertNotNullPtr(pTNf);
	assert (pTNf->data() == "fourth");
	pTNf->release();
	assert (queue.empty());
	assert (queue.size() == 0);

	Notification* pNf = queue.waitDequeueNotification(10);
	assertNullPtr(pNf);
}


void NotificationQueueTest::testThreads()
{
	Thread t1("thread1");
	Thread t2("thread2");
	Thread t3("thread3");
	
	RunnableAdapter<NotificationQueueTest> ra(*this, &NotificationQueueTest::work);
	t1.start(ra);
	t2.start(ra);
	t3.start(ra);
	for (int i = 0; i < 5000; ++i)
	{
		_queue.enqueueNotification(new Notification);
	}
	while (!_queue.empty()) Thread::sleep(50);
	Thread::sleep(20);
	_queue.wakeUpAll();
	t1.join();
	t2.join();
	t3.join();
	assert (_handled.size() == 5000);
	assert (_handled.count("thread1") > 50);
	assert (_handled.count("thread2") > 50);
	assert (_handled.count("thread3") > 10);
}


void NotificationQueueTest::testDefaultQueue()
{
	NotificationQueue& queue = NotificationQueue::defaultQueue();
	assert (queue.empty());
	assert (queue.size() == 0);
}


void NotificationQueueTest::setUp()
{
	_handled.clear();
}


void NotificationQueueTest::tearDown()
{
}


void NotificationQueueTest::work()
{
	Thread::sleep(50);
	Notification* pNf = _queue.waitDequeueNotification();
	while (pNf)
	{
		pNf->release();
		_mutex.lock();
		_handled.insert(Thread::current()->name());
		_mutex.unlock();
		Thread::yield();
		pNf = _queue.waitDequeueNotification();
	}
}


CppUnit::Test* NotificationQueueTest::suite()
{
	CppUnit::TestSuite* pSuite = new CppUnit::TestSuite("NotificationQueueTest");

	CppUnit_addTest(pSuite, NotificationQueueTest, testQueueDequeue);
	CppUnit_addTest(pSuite, NotificationQueueTest, testQueueDequeueUrgent);
	CppUnit_addTest(pSuite, NotificationQueueTest, testWaitDequeue);
	CppUnit_addTest(pSuite, NotificationQueueTest, testThreads);
	CppUnit_addTest(pSuite, NotificationQueueTest, testDefaultQueue);

	return pSuite;
}
