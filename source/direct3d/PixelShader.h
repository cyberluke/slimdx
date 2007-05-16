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
#pragma once

using namespace System;

namespace SlimDX
{
	namespace Direct3D
	{	
		ref class ConstantTable;
		
		public ref class PixelShader : public DirectXObject
		{
		private:
			IDirect3DPixelShader9* m_PixelShader;
			ConstantTable^ m_ConstantTable;

		internal:
			property IDirect3DPixelShader9* InternalPointer
			{
				IDirect3DPixelShader9* get() { return m_PixelShader; }
			}

			property IUnknown* ComPointer
			{
				virtual IUnknown* get() override { return m_PixelShader; }
				virtual void set( IUnknown* value ) override { m_PixelShader = (IDirect3DPixelShader9*) value; }
			}

		public:
			PixelShader( IDirect3DPixelShader9* pixelShader, ID3DXConstantTable* constantTable );
			
			property ConstantTable^ Constants
			{
				ConstantTable^ get() { return m_ConstantTable; }
			}
			
			static PixelShader^ FromString( Device^ device, String^ sourceCode, String^ entryPoint, String^ profile, ShaderFlags flags, [Out] String^ %compilationErrors );
		};
	}
}