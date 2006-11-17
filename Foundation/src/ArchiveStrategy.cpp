//
// ArchiveStrategy.cpp
//
// $Id: //poco/1.3/Foundation/src/ArchiveStrategy.cpp#1 $
//
// Library: Foundation
// Package: Logging
// Module:  FileChannel
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


#include "Poco/ArchiveStrategy.h"
#include "Poco/NumberFormatter.h"
#include "Poco/File.h"
#include "Poco/Path.h"
#include "Poco/DeflatingStream.h"
#include "Poco/StreamCopier.h"
#include "Poco/Exception.h"
#include "Poco/ActiveDispatcher.h"
#include "Poco/ActiveMethod.h"
#include "Poco/Void.h"
#include <fstream>


namespace Poco {


//
// ArchiveCompressor
//


class ArchiveCompressor: public ActiveDispatcher
{
public:
	ArchiveCompressor():
		compress(this, &ArchiveCompressor::compressImpl)
	{
	}
	
	~ArchiveCompressor()
	{
	}
	
	ActiveMethod<Void, std::string, ArchiveCompressor, ActiveStarter<ActiveDispatcher> > compress;

protected:
	Void compressImpl(const std::string& path)
	{
		std::string gzPath(path);
		gzPath.append(".gz");
		std::ifstream istr(path.c_str(), std::ios::binary | std::ios::in);
		if (!istr.good()) throw OpenFileException(path);
		std::ofstream ostr(gzPath.c_str(), std::ios::binary | std::ios::out);
		if (ostr.good())
		{
			DeflatingOutputStream deflater(ostr, DeflatingStreamBuf::STREAM_GZIP);
			StreamCopier::copyStream(istr, deflater);
			deflater.close();
			ostr.close();
			istr.close();
			File f(path);
			f.remove();
		}
		else throw CreateFileException(gzPath);
		return Void();
	}
};


//
// ArchiveStrategy
//


ArchiveStrategy::ArchiveStrategy(): 
	_compress(false),
	_pCompressor(0)
{
}


ArchiveStrategy::~ArchiveStrategy()
{
	delete _pCompressor;
}


void ArchiveStrategy::compress(bool flag)
{
	_compress = flag;
}


void ArchiveStrategy::moveFile(const std::string& oldPath, const std::string& newPath)
{
	bool compressed = false;
	Path p(oldPath);
	File f(oldPath);
	if (!f.exists())
	{
		f = oldPath + ".gz";
		compressed = true;
	}
	std::string mvPath(newPath);
	if (_compress || compressed)
		mvPath.append(".gz");
	if (!_compress || compressed)
	{
		f.renameTo(mvPath);
	}
	else
	{
		f.renameTo(newPath);
		if (!_pCompressor) _pCompressor = new ArchiveCompressor;
		_pCompressor->compress(newPath);
	}
}


bool ArchiveStrategy::exists(const std::string& name)
{
	File f(name);
	if (f.exists())
	{
		return true;
	}
	else if (_compress)
	{
		std::string gzName(name);
		gzName.append(".gz");
		File gzf(gzName);
		return gzf.exists();
	}
	else return false;
}


//
// ArchiveByNumberStrategy
//


ArchiveByNumberStrategy::ArchiveByNumberStrategy()
{
}


ArchiveByNumberStrategy::~ArchiveByNumberStrategy()
{
}


LogFile* ArchiveByNumberStrategy::archive(LogFile* pFile)
{
	std::string basePath = pFile->path();
	delete pFile;
	int n = -1;
	std::string path;
	do
	{
		path = basePath;
		path.append(".");
		path.append(NumberFormatter::format(++n));
	}
	while (exists(path));
	
	while (n >= 0)
	{
		std::string oldPath = basePath;
		if (n > 0)
		{
			oldPath.append(".");
			oldPath.append(NumberFormatter::format(n - 1));
		}
		std::string newPath = basePath;
		newPath.append(".");
		newPath.append(NumberFormatter::format(n));
		moveFile(oldPath, newPath);
		--n;
	}
	return new LogFile(basePath);
}


} // namespace Poco
