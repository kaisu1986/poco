//
// PriorityEvent.h
//
// $Id: //poco/1.3/Foundation/include/Poco/PriorityEvent.h#1 $
//
// Library: Foundation
// Package: Events
// Module:  PriorityEvent
//
// Implementation of the PriorityEvent template.
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


#ifndef  Foundation_PriorityEvent_INCLUDED
#define  Foundation_PriorityEvent_INCLUDED


#include "Poco/AbstractEvent.h"
#include "Poco/DefaultStrategy.h"
#include "Poco/AbstractPriorityDelegate.h"
#include "Poco/CompareFunctions.h"


namespace Poco {


template <class TArgs> 
class PriorityEvent: public AbstractEvent < 
	TArgs,
	DefaultStrategy<TArgs, AbstractPriorityDelegate< TArgs>, p_less<AbstractPriorityDelegate<TArgs> > >,
	AbstractPriorityDelegate<TArgs> 
>
	/// A PriorityEvent uses internally a DefaultStrategy which 
	/// invokes delegates in a manner determined by the priority field 
	/// in the PriorityDelegates (lower priorities first).
	/// PriorityEvents can only be used together with PriorityDelegates.
	/// PriorityDelegates are sorted according to the priority value, when
	/// two delegates have the same priority, they are invoked in
	/// an arbitrary manner.
	/// Note that one object can register several methods as long as they differ
	/// in their priority value:
	///     PriorityEvent<int> tmp;
	///     MyClass myObject;
	///     tmp += PriorityDelegate<MyClass, int>(&myObject, &MyClass::myMethod1, 1);
	///     tmp += PriorityDelegate<MyClass, int>(&myObject, &MyClass::myMethod2, 2);
{
public:
	PriorityEvent()
	{
	}

	~PriorityEvent()
	{
	}

private:
	PriorityEvent(const PriorityEvent& e);
	PriorityEvent& operator = (const PriorityEvent& e);
};


} // namespace Poco


#endif
