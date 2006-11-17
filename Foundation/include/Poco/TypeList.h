//
// TypeList.h
//
// $Id: //poco/1.3/Foundation/include/Poco/TypeList.h#1 $
//
// Library: Foundation
// Package: Core
// Module:  TypeList
//
// Implementation of the TypeList template.
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


#ifndef  Foundation_TypeList_INCLUDED
#define  Foundation_TypeList_INCLUDED


#include "Poco/Foundation.h"
#include "Poco/MetaProgramming.h"


namespace Poco {



template <class Head, class Tail> 
struct TypeList;

	
struct NullTypeList
{
	enum
	{
		length = 0
	};

	bool operator == (const NullTypeList&) const
	{
		return true;
	}

	bool operator != (const NullTypeList&) const
	{
		return false;
	}

	bool operator < (const NullTypeList&) const
	{
		return false;
	}
};


template <class Head, class Tail> 
struct TypeList
	/// Compile Time List of Types
{
	typedef Head HeadType;
	typedef Tail TailType;
	typedef typename TypeWrapper<HeadType>::CONSTTYPE ConstHeadType;
	typedef typename TypeWrapper<TailType>::CONSTTYPE ConstTailType;
	enum
	{
		length = TailType::length+1
	};

	TypeList():head(), tail()
	{
	}

	TypeList(ConstHeadType& h, ConstTailType& t):head(h), tail(t)
	{
	}

	TypeList(const TypeList& tl): head(tl.head), tail(tl.tail)
	{
	}

	TypeList& operator = (const TypeList& tl)
	{
		if (this != &tl)
		{
			TypeList tmp(tl);
			swap(tmp);
		}
		return *this;
	}

	bool operator == (const TypeList& tl) const
	{
		return tl.head == head && tl.tail == tail;
	}

	bool operator != (const TypeList& tl) const
	{
		return !(*this == tl);
	}

	bool operator < (const TypeList& tl) const
	{
		bool smaller = (head < tl.head);
		if (smaller)
			return smaller;
		return tail < tl.tail;
	}

	void swap(TypeList& tl)
	{
		std::swap(head, tl.head);
		std::swap(tail, tl.tail);
	}
	
	HeadType head;
	TailType tail;
};


} // namespace Poco


#endif
