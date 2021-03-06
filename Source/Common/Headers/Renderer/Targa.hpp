#ifndef __ZED_RENDERER_TARGA_HPP__
#define __ZED_RENDERER_TARGA_HPP__

#include <System/DataTypes.hpp>
#include <Renderer/RenderTypes.hpp>
#include <System/File.hpp>

namespace ZED
{
	namespace Renderer
	{
#pragma pack( 1 )
		typedef struct __ZED_TARGA_HEADER
		{
			ZED_BYTE	IDLength;
			ZED_BYTE	ColourmapType;
			ZED_BYTE	ImageType;
			ZED_BYTE	ColourmapSpecification[ 5 ];
			ZED_UINT16	X;
			ZED_UINT16	Y;
			ZED_UINT16	Width;
			ZED_UINT16	Height;
			ZED_BYTE	BitsPerPixel;
			ZED_BYTE	ImageDescription;
		}TARGA_HEADER,*LPTARGA_HEADER;
#pragma pack( )

		class Targa
		{
		public:
			Targa( );
			~Targa( );

			ZED_UINT32 Load( const ZED_CHAR8 *p_pFileName );
			ZED_UINT32 Load( ZED::System::File *p_pFile );

			ZED_BYTE * const GetImageData( ) const;
			ZED_UINT32 GetWidth( ) const;
			ZED_UINT32 GetHeight( ) const;
			ZED_FORMAT GetFormat( ) const;

		private:
			ZED_BYTE	*m_pData;
			ZED_UINT32	m_Width;
			ZED_UINT32	m_Height;
			ZED_FORMAT	m_Format;
		};
	}
}

#endif // __ZED_RENDERER_TARGA_HPP__

