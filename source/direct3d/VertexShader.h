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
		
		public ref class VertexShader : public DirectXObject
		{
		private:
			IDirect3DVertexShader9* m_VertexShader;
			ConstantTable^ m_ConstantTable;

		internal:
			property IDirect3DVertexShader9* InternalPointer
			{
				IDirect3DVertexShader9* get() { return m_VertexShader; }
			}

			property IUnknown* ComPointer
			{
				virtual IUnknown* get() override { return m_VertexShader; }
				virtual void set( IUnknown* value ) override { m_VertexShader = (IDirect3DVertexShader9*) value; }
			}

		public:
			VertexShader( IDirect3DVertexShader9* VertexShader, ID3DXConstantTable* constantTable );
			
			property ConstantTable^ Constants
			{
				ConstantTable^ get() { return m_ConstantTable; }
			}
			
			static VertexShader^ FromString( Device^ device, String^ sourceCode, String^ entryPoint, String^ profile, ShaderFlags flags, [Out] String^ %compilationErrors );
		};
	}
}