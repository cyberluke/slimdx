/*
* Copyright (c) 2007 SlimDX Group
* 
* Permission is hereby granted, free of charge, to any person obtaining a copy
* of this software and associated documentation files (the "Software"), to deal
* in the Software without restriction, including without limitation the rights
* to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
* copies of the Software, and to permit persons to whom the Software is
* furnished to do so, subject to the following conditions:
* 
* The above copyright notice and this permission notice shall be included in
* all copies or substantial portions of the Software.
* 
* THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
* IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
* FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
* AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
* LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
* OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
* THE SOFTWARE.
*/
#include <d3d9.h>
#include <d3dx9.h>

#include "../Utils.h"
#include "Device.h"
#include "GraphicsStream.h"

using namespace System::Runtime::InteropServices;

namespace SlimDX
{
	GraphicsStream::GraphicsStream( void* buffer, bool canRead, bool canWrite )
	{
		m_Buffer = (char*) buffer;
		m_CanRead = canRead;
		m_CanWrite = canWrite;
		m_Position = 0;
	}

	void GraphicsStream::Close()
	{
		Stream::Close();
	}

	Int64 GraphicsStream::Seek( Int64 offset, SeekOrigin origin )
	{
		Int64 targetPosition;

		switch( origin )
		{
		case SeekOrigin::Begin:
			targetPosition = offset;
			break;

		case SeekOrigin::Current:
			targetPosition = m_Position + offset;
			break;

		case SeekOrigin::End:
			throw gcnew NotSupportedException();
		}

		if( targetPosition < 0 )
			throw gcnew InvalidOperationException();

		m_Position = targetPosition;
		return m_Position;
	}

	void GraphicsStream::Write( array<Byte>^ buffer, int offset, int count )
	{
		if( !m_CanWrite )
			throw gcnew NotSupportedException();
		if( buffer == nullptr )
			throw gcnew ArgumentNullException( "buffer" );
		if( offset < 0 || offset >= buffer->Length )
			throw gcnew ArgumentOutOfRangeException( "offset" );
		if( count < 0 || offset + count > buffer->Length )
			throw gcnew ArgumentOutOfRangeException( "count" );

		pin_ptr<Byte> pinnedBuffer = &buffer[offset];
		memcpy( m_Buffer + m_Position, pinnedBuffer, count );

		m_Position += count;
	}

	generic<typename T> where T : value class
	void GraphicsStream::Write( T value )
	{
		if( !m_CanWrite )
			throw gcnew NotSupportedException();

		int size = Marshal::SizeOf( T::typeid );
		memcpy( m_Buffer + m_Position, &value, size );
		m_Position += size;
	}

	generic<typename T> where T : value class
	void GraphicsStream::Write( array<T>^ data, int startIndex, int count )
	{
		if( startIndex < 0 || startIndex > data->Length - 1 )
			throw gcnew ArgumentOutOfRangeException( "startIndex" );
		if( count < 0 )
			throw gcnew ArgumentOutOfRangeException( "count" );
		if( count == 0 )
			count = data->Length;
		if( startIndex + count > data->Length )
			throw gcnew InvalidOperationException();

		int size = count * Marshal::SizeOf( T::typeid );
		pin_ptr<T> pinnedData = &data[startIndex];
		memcpy( m_Buffer + Position, pinnedData, size );
	}
}