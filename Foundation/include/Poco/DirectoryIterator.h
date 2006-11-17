//
// DirectoryIterator.h
//
// $Id: //poco/1.3/Foundation/include/Poco/DirectoryIterator.h#1 $
//
// Library: Foundation
// Package: Filesystem
// Module:  DirectoryIterator
//
// Definition of the DirectoryIterator class.
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


#ifndef Foundation_DirectoryIterator_INCLUDED
#define Foundation_DirectoryIterator_INCLUDED


#include "Poco/Foundation.h"
#include "Poco/File.h"
#include "Poco/Path.h"


namespace Poco {


class DirectoryIteratorImpl;


class Foundation_API DirectoryIterator
	/// The DirectoryIterator class is used to enumerate
	/// all files in a directory.
	///
	/// DirectoryIterator has some limitations:
	///   * only forward iteration (++) is supported
	///   * an iterator copied from another one will always
	///   * point to the same file as the original iterator,
	///   * even is the original iterator has been advanced
	///     (all copies of an iterator share their state with
	///     the original iterator)
{
public:
	DirectoryIterator();
		/// Creates the end iterator.
		
	DirectoryIterator(const std::string& path);
		/// Creates a directory iterator for the given path.

	DirectoryIterator(const DirectoryIterator& iterator);
		/// Creates a directory iterator for the given path.
		
	DirectoryIterator(const File& file);
		/// Creates a directory iterator for the given file.

	DirectoryIterator(const Path& path);
		/// Creates a directory iterator for the given path.

	~DirectoryIterator();
		/// Destroys the DirectoryIterator.

	const std::string& name() const;
		/// Returns the current filename.
		
	const Path& path() const;
		/// Returns the current path.

	DirectoryIterator& operator = (const DirectoryIterator& it);
	DirectoryIterator& operator = (const File& file);
	DirectoryIterator& operator = (const Path& path);
	DirectoryIterator& operator = (const std::string& path);
	
	DirectoryIterator& operator ++ ();   // prefix
	DirectoryIterator operator ++ (int); // postfix
	const File& operator * () const;
	File& operator * ();
	const File* operator -> () const;
	File* operator -> ();
	bool operator == (const DirectoryIterator& iterator) const;
	bool operator != (const DirectoryIterator& iterator) const;

private:
	Path _path;
	File _file;
	DirectoryIteratorImpl* _pImpl;
};


//
// inlines
//
inline const std::string& DirectoryIterator::name() const
{
	return _path.getFileName();
}

	
inline const Path& DirectoryIterator::path() const
{
	return _path;
}


inline const File& DirectoryIterator::operator * () const
{
	return _file;
}


inline File& DirectoryIterator::operator * ()
{
	return _file;
}


inline const File* DirectoryIterator::operator -> () const
{
	return &_file;
}


inline File* DirectoryIterator::operator -> ()
{
	return &_file;
}


inline bool DirectoryIterator::operator == (const DirectoryIterator& iterator) const
{
	return name() == iterator.name();
}


inline bool DirectoryIterator::operator != (const DirectoryIterator& iterator) const
{
	return name() != iterator.name();
}


} // namespace Poco


#endif // Foundation_DirectoryIterator_INCLUDED
