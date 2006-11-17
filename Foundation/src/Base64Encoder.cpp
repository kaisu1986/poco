//
// Base64Encoder.cpp
//
// $Id: //poco/1.3/Foundation/src/Base64Encoder.cpp#1 $
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


#include "Poco/Base64Encoder.h"


namespace Poco {


const unsigned char Base64EncoderBuf::OUT_ENCODING[64] =
{
	'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H',
	'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P',
	'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X',
	'Y', 'Z', 'a', 'b', 'c', 'd', 'e', 'f',
	'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n',
	'o', 'p', 'q', 'r', 's', 't', 'u', 'v',
	'w', 'x', 'y', 'z', '0', '1', '2', '3', 
	'4', '5', '6', '7', '8', '9', '+', '/'
};


Base64EncoderBuf::Base64EncoderBuf(std::ostream& ostr): 
	_groupLength(0),
	_pos(0),
	_lineLength(72),
	_ostr(ostr)
{
}


Base64EncoderBuf::~Base64EncoderBuf()
{
	try
	{
		close();
	}
	catch (...)
	{
	}
}


void Base64EncoderBuf::setLineLength(int lineLength)
{
	poco_assert (lineLength > 0);
	
	_lineLength = lineLength;
}


int Base64EncoderBuf::getLineLength() const
{
	return _lineLength;
}


int Base64EncoderBuf::writeToDevice(char c)
{
	_group[_groupLength++] = (unsigned char) c;
	if (_groupLength == 3)
	{
		unsigned char idx;
		idx = _group[0] >> 2;
		_ostr.put(OUT_ENCODING[idx]);
		idx = ((_group[0] & 0x03) << 4) | (_group[1] >> 4);
		_ostr.put(OUT_ENCODING[idx]);
		idx = ((_group[1] & 0x0F) << 2) | (_group[2] >> 6);
		_ostr.put(OUT_ENCODING[idx]);
		idx = _group[2] & 0x3F;
		_ostr.put(OUT_ENCODING[idx]);
		_pos += 4;
		if (_pos >= _lineLength) 
		{
			_ostr << "\r\n";
			_pos = 0;
		}
		_groupLength = 0;
	}
	return _ostr ? charToInt(c) : -1;
}


int Base64EncoderBuf::close()
{
	sync();
	if (_groupLength == 1)
	{
		_group[1] = 0;
		unsigned char idx;
		idx = _group[0] >> 2;
		_ostr.put(OUT_ENCODING[idx]);
		idx = ((_group[0] & 0x03) << 4) | (_group[1] >> 4);
		_ostr.put(OUT_ENCODING[idx]);
		_ostr << "==";
	}
	else if (_groupLength == 2)
	{
		_group[2] = 0;
		unsigned char idx;
		idx = _group[0] >> 2;
		_ostr.put(OUT_ENCODING[idx]);
		idx = ((_group[0] & 0x03) << 4) | (_group[1] >> 4);
		_ostr.put(OUT_ENCODING[idx]);
		idx = ((_group[1] & 0x0F) << 2) | (_group[2] >> 6);
		_ostr.put(OUT_ENCODING[idx]);
		_ostr.put('=');
	}
	_ostr.flush();
	_groupLength = 0;
	return _ostr ? 0 : -1;
}


Base64EncoderIOS::Base64EncoderIOS(std::ostream& ostr): _buf(ostr)
{
	poco_ios_init(&_buf);
}


Base64EncoderIOS::~Base64EncoderIOS()
{
}


int Base64EncoderIOS::close()
{
	return _buf.close();
}


Base64EncoderBuf* Base64EncoderIOS::rdbuf()
{
	return &_buf;
}


Base64Encoder::Base64Encoder(std::ostream& ostr): Base64EncoderIOS(ostr), std::ostream(&_buf)
{
}


Base64Encoder::~Base64Encoder()
{
}


} // namespace Poco
