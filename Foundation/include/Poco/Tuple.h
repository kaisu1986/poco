//
// Tuple.h
//
// $Id: //poco/1.3/Foundation/include/Poco/Tuple.h#1 $
//
// Library: Foundation
// Package: Core
// Module:  Tuple
//
// Definition of the Tuple class.
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


#ifndef Foundation_Tuple_INCLUDED
#define Foundation_Tuple_INCLUDED


#include "Poco/Foundation.h"
#include "Poco/TypeList.h"


namespace Poco {


#if defined(POCO_OS_FAMILY_WINDOWS)
#define POCO_TYPEWRAPPER_DEFAULTVALUE(T) TypeWrapper<T>::TYPE()
#else
#define POCO_TYPEWRAPPER_DEFAULTVALUE(T) typename TypeWrapper<T>::TYPE()
#endif


template<int n> 
struct Getter
{
	template<class Ret, class Head, class Tail>
	inline static Ret& get(TypeList<Head, Tail>& val)
	{
		return Getter<n-1>::template get<Ret, typename Tail::HeadType, typename Tail::TailType>(val.tail);
	}

	template<class Ret, class Head, class Tail>
	inline static const Ret& get(const TypeList<Head, Tail>& val)
	{
		return Getter<n-1>::template get<Ret, typename Tail::HeadType, typename Tail::TailType>(val.tail);
	}
};


template<> 
struct Getter<0>
{
	template<class Ret, class Head, class Tail>
	inline static Ret& get(TypeList<Head, Tail>& val)
	{
		return val.head;
	}

	template<class Ret, class Head, class Tail>
	inline static const Ret& get(const TypeList<Head, Tail>& val)
	{
		return val.head;
	}
};

template <int N, class Head> 
struct TypeGetter;


template <int N, class Head, class Tail> 
struct TypeGetter<N, TypeList<Head, Tail> >
{
	typedef typename TypeGetter<N-1, Tail>::HeadType HeadType;
	typedef typename TypeWrapper<HeadType>::CONSTTYPE ConstHeadType;
};


template <class Head, class Tail> 
struct TypeGetter<0, TypeList<Head, Tail> >
{
	typedef typename TypeList<Head, Tail>::HeadType HeadType;
	typedef typename TypeWrapper<HeadType>::CONSTTYPE ConstHeadType;
};


template<	class T0,
			class T1 = NullTypeList,
			class T2 = NullTypeList,
			class T3 = NullTypeList,
			class T4 = NullTypeList,
			class T5 = NullTypeList,
			class T6 = NullTypeList,
			class T7 = NullTypeList,
			class T8 = NullTypeList,
			class T9 = NullTypeList>
struct Tuple
{
	typedef TypeList<T0, TypeList<T1, TypeList<T2, TypeList<T3, TypeList<T4, TypeList<T5, TypeList<T6, TypeList<T7, TypeList<T8, TypeList<T9, NullTypeList> > > > > > > > > > Type;

	enum
	{
		length = Type::length
	};

	Tuple():_data()
	{
	}

	Tuple(typename TypeWrapper<T0>::CONSTTYPE& t0,
		typename TypeWrapper<T1>::CONSTTYPE& t1 = POCO_TYPEWRAPPER_DEFAULTVALUE(T1),
		typename TypeWrapper<T2>::CONSTTYPE& t2 = POCO_TYPEWRAPPER_DEFAULTVALUE(T2),
		typename TypeWrapper<T3>::CONSTTYPE& t3 = POCO_TYPEWRAPPER_DEFAULTVALUE(T3),
		typename TypeWrapper<T4>::CONSTTYPE& t4 = POCO_TYPEWRAPPER_DEFAULTVALUE(T4),
		typename TypeWrapper<T5>::CONSTTYPE& t5 = POCO_TYPEWRAPPER_DEFAULTVALUE(T5),
		typename TypeWrapper<T6>::CONSTTYPE& t6 = POCO_TYPEWRAPPER_DEFAULTVALUE(T6),
		typename TypeWrapper<T7>::CONSTTYPE& t7 = POCO_TYPEWRAPPER_DEFAULTVALUE(T7),
		typename TypeWrapper<T8>::CONSTTYPE& t8 = POCO_TYPEWRAPPER_DEFAULTVALUE(T8),
		typename TypeWrapper<T9>::CONSTTYPE& t9 = POCO_TYPEWRAPPER_DEFAULTVALUE(T9)):
		_data(t0, 
			TypeList<T1, TypeList<T2, TypeList<T3, TypeList<T4, TypeList<T5, TypeList<T6, TypeList<T7, TypeList<T8, TypeList<T9, NullTypeList> > > > > > > > >
			(t1, TypeList<T2, TypeList<T3, TypeList<T4, TypeList<T5, TypeList<T6, TypeList<T7, TypeList<T8, TypeList<T9, NullTypeList> > > > > > > >
			(t2, TypeList<T3, TypeList<T4, TypeList<T5, TypeList<T6, TypeList<T7, TypeList<T8, TypeList<T9, NullTypeList> > > > > > >
			(t3, TypeList<T4, TypeList<T5, TypeList<T6, TypeList<T7, TypeList<T8, TypeList<T9, NullTypeList> > > > > >
			(t4, TypeList<T5, TypeList<T6, TypeList<T7, TypeList<T8, TypeList<T9, NullTypeList> > > > >
			(t5, TypeList<T6, TypeList<T7, TypeList<T8, TypeList<T9, NullTypeList> > > >
			(t6, TypeList<T7, TypeList<T8, TypeList<T9, NullTypeList> > >
			(t7, TypeList<T8, TypeList<T9, NullTypeList> >
			(t8, TypeList<T9, NullTypeList>
			(t9, NullTypeList()))))))))))
	{
	}

	template<int N>
	typename TypeGetter<N, Type>::ConstHeadType& get() const
	{
		return Getter<N>::template get<typename TypeGetter<N, Type>::HeadType, typename Type::HeadType, typename Type::TailType>(_data);
	}

	template<int N>
	typename TypeGetter<N, Type>::HeadType& get()
	{
		return Getter<N>::template get<typename TypeGetter<N, Type>::HeadType, typename Type::HeadType, typename Type::TailType>(_data);
	}

	template<int N>
	void set(typename TypeGetter<N, Type>::ConstHeadType& val)
	{
		Getter<N>::template get<typename TypeGetter<N, Type>::HeadType, typename Type::HeadType, typename Type::TailType>(_data) = val;
	}

	bool operator == (const Tuple& other) const
	{
		return _data == other._data;
	}

	bool operator != (const Tuple& other) const
	{
		return !(_data == other._data);
	}

	bool operator < (const Tuple& other) const
	{
		return _data < other._data;
	}

private:
	Type _data;
};


template<	class T0,
			class T1,
			class T2,
			class T3,
			class T4,
			class T5,
			class T6,
			class T7,
			class T8>
struct Tuple<T0, T1, T2, T3, T4, T5, T6, T7, T8, NullTypeList>
{
	typedef TypeList<T0, TypeList<T1, TypeList<T2, TypeList<T3, TypeList<T4, TypeList<T5, TypeList<T6, TypeList<T7, TypeList<T8, NullTypeList> > > > > > > > > Type;

	enum
	{
		length = Type::length
	};

	Tuple():_data()
	{
	}

	Tuple(typename TypeWrapper<T0>::CONSTTYPE& t0, 
		typename TypeWrapper<T1>::CONSTTYPE& t1 = POCO_TYPEWRAPPER_DEFAULTVALUE(T1),
		typename TypeWrapper<T2>::CONSTTYPE& t2 = POCO_TYPEWRAPPER_DEFAULTVALUE(T2),
		typename TypeWrapper<T3>::CONSTTYPE& t3 = POCO_TYPEWRAPPER_DEFAULTVALUE(T3),
		typename TypeWrapper<T4>::CONSTTYPE& t4 = POCO_TYPEWRAPPER_DEFAULTVALUE(T4),
		typename TypeWrapper<T5>::CONSTTYPE& t5 = POCO_TYPEWRAPPER_DEFAULTVALUE(T5),
		typename TypeWrapper<T6>::CONSTTYPE& t6 = POCO_TYPEWRAPPER_DEFAULTVALUE(T6),
		typename TypeWrapper<T7>::CONSTTYPE& t7 = POCO_TYPEWRAPPER_DEFAULTVALUE(T7),
		typename TypeWrapper<T8>::CONSTTYPE& t8 = POCO_TYPEWRAPPER_DEFAULTVALUE(T8)):
		_data(t0, 
			TypeList<T1, TypeList<T2, TypeList<T3, TypeList<T4, TypeList<T5, TypeList<T6, TypeList<T7, TypeList<T8, NullTypeList> > > > > > > > 
			(t1, TypeList<T2, TypeList<T3, TypeList<T4, TypeList<T5, TypeList<T6, TypeList<T7, TypeList<T8, NullTypeList> > > > > > >
			(t2, TypeList<T3, TypeList<T4, TypeList<T5, TypeList<T6, TypeList<T7, TypeList<T8, NullTypeList> > > > > >
			(t3, TypeList<T4, TypeList<T5, TypeList<T6, TypeList<T7, TypeList<T8, NullTypeList> > > > >
			(t4, TypeList<T5, TypeList<T6, TypeList<T7, TypeList<T8, NullTypeList> > > >
			(t5, TypeList<T6, TypeList<T7, TypeList<T8, NullTypeList> > >
			(t6, TypeList<T7, TypeList<T8, NullTypeList> >
			(t7, TypeList<T8, NullTypeList>
			(t8, NullTypeList())))))))))
	{
	}

	template<int N>
	typename TypeGetter<N, Type>::ConstHeadType& get() const
	{
		return Getter<N>::template get<typename TypeGetter<N, Type>::HeadType, typename Type::HeadType, typename Type::TailType>(_data);
	}

	template<int N>
	typename TypeGetter<N, Type>::HeadType& get()
	{
		return Getter<N>::template get<typename TypeGetter<N, Type>::HeadType, typename Type::HeadType, typename Type::TailType>(_data);
	}

	template<int N>
	void set(typename TypeGetter<N, Type>::ConstHeadType& val)
	{
		Getter<N>::template get<typename TypeGetter<N, Type>::HeadType, typename Type::HeadType, typename Type::TailType>(_data) = val;
	}

	bool operator == (const Tuple& other) const
	{
		return _data == other._data;
	}

	bool operator != (const Tuple& other) const
	{
		return !(_data == other._data);
	}

	bool operator < (const Tuple& other) const
	{
		return _data < other._data;
	}

private:
	Type _data;
};


template<	class T0,
			class T1,
			class T2,
			class T3,
			class T4,
			class T5,
			class T6,
			class T7>
struct Tuple<T0, T1, T2, T3, T4, T5, T6, T7, NullTypeList>
{
	typedef TypeList<T0, TypeList<T1, TypeList<T2, TypeList<T3, TypeList<T4, TypeList<T5, TypeList<T6, TypeList<T7, NullTypeList> > > > > > > > Type;

	enum
	{
		length = Type::length
	};

	Tuple():_data()
	{
	}

	Tuple(typename TypeWrapper<T0>::CONSTTYPE& t0, 
		typename TypeWrapper<T1>::CONSTTYPE& t1 = POCO_TYPEWRAPPER_DEFAULTVALUE(T1),
		typename TypeWrapper<T2>::CONSTTYPE& t2 = POCO_TYPEWRAPPER_DEFAULTVALUE(T2),
		typename TypeWrapper<T3>::CONSTTYPE& t3 = POCO_TYPEWRAPPER_DEFAULTVALUE(T3),
		typename TypeWrapper<T4>::CONSTTYPE& t4 = POCO_TYPEWRAPPER_DEFAULTVALUE(T4),
		typename TypeWrapper<T5>::CONSTTYPE& t5 = POCO_TYPEWRAPPER_DEFAULTVALUE(T5),
		typename TypeWrapper<T6>::CONSTTYPE& t6 = POCO_TYPEWRAPPER_DEFAULTVALUE(T6),
		typename TypeWrapper<T7>::CONSTTYPE& t7 = POCO_TYPEWRAPPER_DEFAULTVALUE(T7)):
		_data(t0, 
			TypeList<T1, TypeList<T2, TypeList<T3, TypeList<T4, TypeList<T5, TypeList<T6, TypeList<T7, NullTypeList> > > > > > >
			(t1, TypeList<T2, TypeList<T3, TypeList<T4, TypeList<T5, TypeList<T6, TypeList<T7, NullTypeList> > > > > >
			(t2, TypeList<T3, TypeList<T4, TypeList<T5, TypeList<T6, TypeList<T7, NullTypeList> > > > >
			(t3, TypeList<T4, TypeList<T5, TypeList<T6, TypeList<T7, NullTypeList> > > >
			(t4, TypeList<T5, TypeList<T6, TypeList<T7, NullTypeList> > >
			(t5, TypeList<T6, TypeList<T7, NullTypeList> >
			(t6, TypeList<T7, NullTypeList>
			(t7, NullTypeList()))))))))
	{
	}

	template<int N>
	typename TypeGetter<N, Type>::ConstHeadType& get() const
	{
		return Getter<N>::template get<typename TypeGetter<N, Type>::HeadType, typename Type::HeadType, typename Type::TailType>(_data);
	}

	template<int N>
	typename TypeGetter<N, Type>::HeadType& get()
	{
		return Getter<N>::template get<typename TypeGetter<N, Type>::HeadType, typename Type::HeadType, typename Type::TailType>(_data);
	}

	template<int N>
	void set(typename TypeGetter<N, Type>::ConstHeadType& val)
	{
		Getter<N>::template get<typename TypeGetter<N, Type>::HeadType, typename Type::HeadType, typename Type::TailType>(_data) = val;
	}

	bool operator == (const Tuple& other) const
	{
		return _data == other._data;
	}

	bool operator != (const Tuple& other) const
	{
		return !(_data == other._data);
	}

	bool operator < (const Tuple& other) const
	{
		return _data < other._data;
	}

private:
	Type _data;
};


template<	class T0,
			class T1,
			class T2,
			class T3,
			class T4,
			class T5,
			class T6>
struct Tuple<T0, T1, T2, T3, T4, T5, T6, NullTypeList>
{
	typedef TypeList<T0, TypeList<T1, TypeList<T2, TypeList<T3, TypeList<T4, TypeList<T5, TypeList<T6, NullTypeList> > > > > > > Type;

	enum
	{
		length = Type::length
	};

	Tuple():_data()
	{
	}

	Tuple(typename TypeWrapper<T0>::CONSTTYPE& t0, 
		typename TypeWrapper<T1>::CONSTTYPE& t1 = POCO_TYPEWRAPPER_DEFAULTVALUE(T1),
		typename TypeWrapper<T2>::CONSTTYPE& t2 = POCO_TYPEWRAPPER_DEFAULTVALUE(T2),
		typename TypeWrapper<T3>::CONSTTYPE& t3 = POCO_TYPEWRAPPER_DEFAULTVALUE(T3),
		typename TypeWrapper<T4>::CONSTTYPE& t4 = POCO_TYPEWRAPPER_DEFAULTVALUE(T4),
		typename TypeWrapper<T5>::CONSTTYPE& t5 = POCO_TYPEWRAPPER_DEFAULTVALUE(T5),
		typename TypeWrapper<T6>::CONSTTYPE& t6 = POCO_TYPEWRAPPER_DEFAULTVALUE(T6)):
		_data(t0, 
			TypeList<T1, TypeList<T2, TypeList<T3, TypeList<T4, TypeList<T5, TypeList<T6, NullTypeList> > > > > >
			(t1, TypeList<T2, TypeList<T3, TypeList<T4, TypeList<T5, TypeList<T6, NullTypeList> > > > >
			(t2, TypeList<T3, TypeList<T4, TypeList<T5, TypeList<T6, NullTypeList> > > >
			(t3, TypeList<T4, TypeList<T5, TypeList<T6, NullTypeList> > >
			(t4, TypeList<T5, TypeList<T6, NullTypeList> >
			(t5, TypeList<T6, NullTypeList>
			(t6, NullTypeList())))))))
	{
	}

	template<int N>
	typename TypeGetter<N, Type>::ConstHeadType& get() const
	{
		return Getter<N>::template get<typename TypeGetter<N, Type>::HeadType, typename Type::HeadType, typename Type::TailType>(_data);
	}

	template<int N>
	typename TypeGetter<N, Type>::HeadType& get()
	{
		return Getter<N>::template get<typename TypeGetter<N, Type>::HeadType, typename Type::HeadType, typename Type::TailType>(_data);
	}

	template<int N>
	void set(typename TypeGetter<N, Type>::ConstHeadType& val)
	{
		Getter<N>::template get<typename TypeGetter<N, Type>::HeadType, typename Type::HeadType, typename Type::TailType>(_data) = val;
	}

	bool operator == (const Tuple& other) const
	{
		return _data == other._data;
	}

	bool operator != (const Tuple& other) const
	{
		return !(_data == other._data);
	}

	bool operator < (const Tuple& other) const
	{
		return _data < other._data;
	}

private:
	Type _data;
};


template<	class T0,
			class T1,
			class T2,
			class T3,
			class T4,
			class T5>
struct Tuple<T0, T1, T2, T3, T4, T5, NullTypeList>
{
	typedef TypeList<T0, TypeList<T1, TypeList<T2, TypeList<T3, TypeList<T4, TypeList<T5, NullTypeList> > > > > > Type;

	enum
	{
		length = Type::length
	};

	Tuple():_data()
	{
	}

	Tuple(typename TypeWrapper<T0>::CONSTTYPE& t0, 
		typename TypeWrapper<T1>::CONSTTYPE& t1 = POCO_TYPEWRAPPER_DEFAULTVALUE(T1),
		typename TypeWrapper<T2>::CONSTTYPE& t2 = POCO_TYPEWRAPPER_DEFAULTVALUE(T2),
		typename TypeWrapper<T3>::CONSTTYPE& t3 = POCO_TYPEWRAPPER_DEFAULTVALUE(T3),
		typename TypeWrapper<T4>::CONSTTYPE& t4 = POCO_TYPEWRAPPER_DEFAULTVALUE(T4),
		typename TypeWrapper<T5>::CONSTTYPE& t5 = POCO_TYPEWRAPPER_DEFAULTVALUE(T5)):
		_data(t0, 
			TypeList<T1, TypeList<T2, TypeList<T3, TypeList<T4, TypeList<T5, NullTypeList> > > > >
			(t1, TypeList<T2, TypeList<T3, TypeList<T4, TypeList<T5, NullTypeList> > > >
			(t2, TypeList<T3, TypeList<T4, TypeList<T5, NullTypeList> > >
			(t3, TypeList<T4, TypeList<T5, NullTypeList> >
			(t4, TypeList<T5, NullTypeList>
			(t5, NullTypeList()))))))
	{
	}

	template<int N>
	typename TypeGetter<N, Type>::ConstHeadType& get() const
	{
		return Getter<N>::template get<typename TypeGetter<N, Type>::HeadType, typename Type::HeadType, typename Type::TailType>(_data);
	}

	template<int N>
	typename TypeGetter<N, Type>::HeadType& get()
	{
		return Getter<N>::template get<typename TypeGetter<N, Type>::HeadType, typename Type::HeadType, typename Type::TailType>(_data);
	}

	template<int N>
	void set(typename TypeGetter<N, Type>::ConstHeadType& val)
	{
		Getter<N>::template get<typename TypeGetter<N, Type>::HeadType, typename Type::HeadType, typename Type::TailType>(_data) = val;
	}

	bool operator == (const Tuple& other) const
	{
		return _data == other._data;
	}

	bool operator != (const Tuple& other) const
	{
		return !(_data == other._data);
	}

	bool operator < (const Tuple& other) const
	{
		return _data < other._data;
	}

private:
	Type _data;
};


template<	class T0,
			class T1,
			class T2,
			class T3,
			class T4>
struct Tuple<T0, T1, T2, T3, T4, NullTypeList>
{
	typedef TypeList<T0, TypeList<T1, TypeList<T2, TypeList<T3, TypeList<T4, NullTypeList> > > > > Type;

	enum
	{
		length = Type::length
	};

	Tuple():_data()
	{
	}

	Tuple(typename TypeWrapper<T0>::CONSTTYPE& t0, 
		typename TypeWrapper<T1>::CONSTTYPE& t1 = POCO_TYPEWRAPPER_DEFAULTVALUE(T1),
		typename TypeWrapper<T2>::CONSTTYPE& t2 = POCO_TYPEWRAPPER_DEFAULTVALUE(T2),
		typename TypeWrapper<T3>::CONSTTYPE& t3 = POCO_TYPEWRAPPER_DEFAULTVALUE(T3),
		typename TypeWrapper<T4>::CONSTTYPE& t4 = POCO_TYPEWRAPPER_DEFAULTVALUE(T4)):
		_data(t0, 
			TypeList<T1, TypeList<T2, TypeList<T3, TypeList<T4, NullTypeList> > > >
			(t1, TypeList<T2, TypeList<T3, TypeList<T4, NullTypeList> > >
			(t2, TypeList<T3, TypeList<T4, NullTypeList> >
			(t3, TypeList<T4, NullTypeList>
			(t4, NullTypeList())))))
	{
	}

	template<int N>
	typename TypeGetter<N, Type>::ConstHeadType& get() const
	{
		return Getter<N>::template get<typename TypeGetter<N, Type>::HeadType, typename Type::HeadType, typename Type::TailType>(_data);
	}

	template<int N>
	typename TypeGetter<N, Type>::HeadType& get()
	{
		return Getter<N>::template get<typename TypeGetter<N, Type>::HeadType, typename Type::HeadType, typename Type::TailType>(_data);
	}

	template<int N>
	void set(typename TypeGetter<N, Type>::ConstHeadType& val)
	{
		Getter<N>::template get<typename TypeGetter<N, Type>::HeadType, typename Type::HeadType, typename Type::TailType>(_data) = val;
	}

	bool operator == (const Tuple& other) const
	{
		return _data == other._data;
	}

	bool operator != (const Tuple& other) const
	{
		return !(_data == other._data);
	}

	bool operator < (const Tuple& other) const
	{
		return _data < other._data;
	}

private:
	Type _data;
};


template<	class T0,
			class T1,
			class T2,
			class T3>
struct Tuple<T0, T1, T2, T3, NullTypeList>
{
	typedef TypeList<T0, TypeList<T1, TypeList<T2, TypeList<T3, NullTypeList> > > > Type;

	enum
	{
		length = Type::length
	};

	Tuple():_data()
	{
	}

	Tuple(typename TypeWrapper<T0>::CONSTTYPE& t0, 
		typename TypeWrapper<T1>::CONSTTYPE& t1 = POCO_TYPEWRAPPER_DEFAULTVALUE(T1),
		typename TypeWrapper<T2>::CONSTTYPE& t2 = POCO_TYPEWRAPPER_DEFAULTVALUE(T2),
		typename TypeWrapper<T3>::CONSTTYPE& t3 = POCO_TYPEWRAPPER_DEFAULTVALUE(T3)):
		_data(t0, 
			TypeList<T1, TypeList<T2, TypeList<T3, NullTypeList> > >
			(t1, TypeList<T2, TypeList<T3, NullTypeList> >
			(t2, TypeList<T3, NullTypeList>
			(t3, NullTypeList()))))
	{
	}

	template<int N>
	typename TypeGetter<N, Type>::ConstHeadType& get() const
	{
		return Getter<N>::template get<typename TypeGetter<N, Type>::HeadType, typename Type::HeadType, typename Type::TailType>(_data);
	}

	template<int N>
	typename TypeGetter<N, Type>::HeadType& get()
	{
		return Getter<N>::template get<typename TypeGetter<N, Type>::HeadType, typename Type::HeadType, typename Type::TailType>(_data);
	}

	template<int N>
	void set(typename TypeGetter<N, Type>::ConstHeadType& val)
	{
		Getter<N>::template get<typename TypeGetter<N, Type>::HeadType, typename Type::HeadType, typename Type::TailType>(_data) = val;
	}

	bool operator == (const Tuple& other) const
	{
		return _data == other._data;
	}

	bool operator != (const Tuple& other) const
	{
		return !(_data == other._data);
	}

	bool operator < (const Tuple& other) const
	{
		return _data < other._data;
	}

private:
	Type _data;
};


template<	class T0,
			class T1,
			class T2>
struct Tuple<T0, T1, T2, NullTypeList>
{
	typedef TypeList<T0, TypeList<T1, TypeList<T2, NullTypeList> > > Type;

	enum
	{
		length = Type::length
	};

	Tuple():_data()
	{
	}

	Tuple(typename TypeWrapper<T0>::CONSTTYPE& t0, 
		typename TypeWrapper<T1>::CONSTTYPE& t1 = POCO_TYPEWRAPPER_DEFAULTVALUE(T1),
		typename TypeWrapper<T2>::CONSTTYPE& t2 = POCO_TYPEWRAPPER_DEFAULTVALUE(T2)):
		_data(t0, 
			TypeList<T1, TypeList<T2, NullTypeList> >
			(t1, TypeList<T2, NullTypeList>
			(t2, NullTypeList())))
	{
	}

	template<int N>
	typename TypeGetter<N, Type>::ConstHeadType& get() const
	{
		return Getter<N>::template get<typename TypeGetter<N, Type>::HeadType, typename Type::HeadType, typename Type::TailType>(_data);
	}

	template<int N>
	typename TypeGetter<N, Type>::HeadType& get()
	{
		return Getter<N>::template get<typename TypeGetter<N, Type>::HeadType, typename Type::HeadType, typename Type::TailType>(_data);
	}

	template<int N>
	void set(typename TypeGetter<N, Type>::ConstHeadType& val)
	{
		Getter<N>::template get<typename TypeGetter<N, Type>::HeadType, typename Type::HeadType, typename Type::TailType>(_data) = val;
	}

	bool operator == (const Tuple& other) const
	{
		return _data == other._data;
	}

	bool operator != (const Tuple& other) const
	{
		return !(_data == other._data);
	}

	bool operator < (const Tuple& other) const
	{
		return _data < other._data;
	}

private:
	Type _data;
};


template<	class T0,
			class T1>
struct Tuple<T0, T1, NullTypeList>
{
	typedef TypeList<T0, TypeList<T1, NullTypeList> > Type;

	enum
	{
		length = Type::length
	};

	Tuple():_data()
	{
	}

	Tuple(typename TypeWrapper<T0>::CONSTTYPE& t0, 
		typename TypeWrapper<T1>::CONSTTYPE& t1 = POCO_TYPEWRAPPER_DEFAULTVALUE(T1)):
		_data(t0, TypeList<T1, NullTypeList>(t1, NullTypeList()))
	{
	}

	template<int N>
	typename TypeGetter<N, Type>::ConstHeadType& get() const
	{
		return Getter<N>::template get<typename TypeGetter<N, Type>::HeadType, typename Type::HeadType, typename Type::TailType>(_data);
	}

	template<int N>
	typename TypeGetter<N, Type>::HeadType& get()
	{
		return Getter<N>::template get<typename TypeGetter<N, Type>::HeadType, typename Type::HeadType, typename Type::TailType>(_data);
	}

	template<int N>
	void set(typename TypeGetter<N, Type>::ConstHeadType& val)
	{
		Getter<N>::template get<typename TypeGetter<N, Type>::HeadType, typename Type::HeadType, typename Type::TailType>(_data) = val;
	}

	bool operator == (const Tuple& other) const
	{
		return _data == other._data;
	}

	bool operator != (const Tuple& other) const
	{
		return !(_data == other._data);
	}

	bool operator < (const Tuple& other) const
	{
		return _data < other._data;
	}

private:
	Type _data;
};


template<class T0>
struct Tuple<T0, NullTypeList>
{
	typedef TypeList<T0, NullTypeList> Type;
	
	enum
	{
		length = Type::length
	};

	Tuple():_data()
	{
	}

	Tuple(typename TypeWrapper<T0>::CONSTTYPE& t0):
		_data(t0, NullTypeList())
	{
	}

	template<int N>
	typename TypeGetter<N, Type>::ConstHeadType& get() const
	{
		return Getter<N>::template get<typename TypeGetter<N, Type>::HeadType, typename Type::HeadType, typename Type::TailType>(_data);
	}

	template<int N>
	typename TypeGetter<N, Type>::HeadType& get()
	{
		return Getter<N>::template get<typename TypeGetter<N, Type>::HeadType, typename Type::HeadType, typename Type::TailType>(_data);
	}

	template<int N>
	void set(typename TypeGetter<N, Type>::ConstHeadType& val)
	{
		Getter<N>::template get<typename TypeGetter<N, Type>::HeadType, typename Type::HeadType, typename Type::TailType>(_data) = val;
	}

	bool operator == (const Tuple& other) const
	{
		return _data == other._data;
	}

	bool operator != (const Tuple& other) const
	{
		return !(_data == other._data);
	}

	bool operator < (const Tuple& other) const
	{
		return _data < other._data;
	}

private:
	Type _data;
};


} // namespace Poco


#endif // Foundation_Tuple_INCLUDED
