//
// Base64Decoder.cpp
//
// $Id: //poco/1.3/Foundation/src/Base64Decoder.cpp#1 $
//
// Library: Foundation
// Package: Streams
// Module:  Base64
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


#include "Poco/Base64Decoder.h"
#include "Poco/Base64Encoder.h"
#include "Poco/Exception.h"
#include "Poco/Mutex.h"


namespace Poco {


unsigned char Base64DecoderBuf::IN_ENCODING[256];
bool Base64DecoderBuf::IN_ENCODING_INIT = false;


Base64DecoderBuf::Base64DecoderBuf(std::istream& istr): 
	_groupLength(0),
	_groupIndex(0),
	_istr(istr)
{
	static FastMutex mutex;
	FastMutex::ScopedLock lock(mutex);
	if (!IN_ENCODING_INIT)
	{
		for (unsigned i = 0; i < sizeof(IN_ENCODING); i++)
		{
			IN_ENCODING[i] = 0xFF;
		}
		for (unsigned i = 0; i < sizeof(Base64EncoderBuf::OUT_ENCODING); i++)
		{
			IN_ENCODING[Base64EncoderBuf::OUT_ENCODING[i]] = i;
		}
		IN_ENCODING['='] = 0;
		IN_ENCODING_INIT = true;
	}
}


Base64DecoderBuf::~Base64DecoderBuf()
{
}


int Base64DecoderBuf::readFromDevice()
{
	if (_groupIndex < _groupLength) 
	{
		return _group[_groupIndex++];
	}
	else
	{
		unsigned char buffer[4];
		int c;
		if ((c = readOne()) == -1) return -1;
		buffer[0] = (unsigned char) c;
		if (IN_ENCODING[buffer[0]] == 0xFF) throw DataFormatException();
		if ((c = readOne()) == -1) return -1;
		buffer[1] = (unsigned char) c;
		if (IN_ENCODING[buffer[1]] == 0xFF) throw DataFormatException();
		if ((c = readOne()) == -1) return -1;
		buffer[2] = c;
		if (IN_ENCODING[buffer[2]] == 0xFF) throw DataFormatException();
		if ((c = readOne()) == -1) return -1;
		buffer[3] = c;
		if (IN_ENCODING[buffer[3]] == 0xFF) throw DataFormatException();
		
		_group[0] = (IN_ENCODING[buffer[0]] << 2) | (IN_ENCODING[buffer[1]] >> 4);
		_group[1] = ((IN_ENCODING[buffer[1]] & 0x0F) << 4) | (IN_ENCODING[buffer[2]] >> 2);
		_group[2] = (IN_ENCODING[buffer[2]] << 6) | IN_ENCODING[buffer[3]];

		if (buffer[2] == '=')
			_groupLength = 1;
		else if (buffer[3] == '=') 
			_groupLength = 2;
		else
			_groupLength = 3;
		_groupIndex = 1;
		return _group[0];
	}
}


int Base64DecoderBuf::readOne()
{
	int ch = _istr.get();
	while (ch == ' ' || ch == '\r' || ch == '\t' || ch == '\n')
		ch = _istr.get();
	return ch;
}


Base64DecoderIOS::Base64DecoderIOS(std::istream& istr): _buf(istr)
{
	poco_ios_init(&_buf);
}


Base64DecoderIOS::~Base64DecoderIOS()
{
}


Base64DecoderBuf* Base64DecoderIOS::rdbuf()
{
	return &_buf;
}


Base64Decoder::Base64Decoder(std::istream& istr): Base64DecoderIOS(istr), std::istream(&_buf)
{
}


Base64Decoder::~Base64Decoder()
{
}


} // namespace Poco
