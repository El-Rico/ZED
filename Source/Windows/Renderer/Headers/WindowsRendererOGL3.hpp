#ifndef __ZEDWINDOWSRENDERER_HPP__
#define __ZEDWINDOWSRENDERER_HPP__

#include <DataTypes.hpp>
#include <GLExtender.hpp>
#include <CanvasDescription.hpp>
#include <Renderer.hpp>
#include <Vector3.hpp>

namespace ZED
{
	namespace Renderer
	{
		class WindowsRendererOGL3 : public Renderer
		{
		public:
			WindowsRendererOGL3( );
			virtual ~WindowsRendererOGL3( );

			virtual ZED_UINT32 Create( GraphicsAdapter *p_pAdapter,
				const CanvasDescription &p_Canvas );

			// Provide an alternative to allow the HDC to be set in Create
			ZED_UINT32 Create( GraphicsAdapter *p_pAdapter,
				const CanvasDescription &p_Canvas, const HDC &p_HDC );

			virtual void ForceClear( const ZED_BOOL p_Colour,
				const ZED_BOOL p_Depth, const ZED_BOOL p_Stencil );
			virtual ZED_UINT32 BeginScene( const ZED_BOOL p_Colour,
				const ZED_BOOL p_Depth, const ZED_BOOL p_Stencil );
			virtual void EndScene( );

			virtual void ClearColour( const ZED_FLOAT32 p_Red,
				const ZED_FLOAT32 p_Green, const ZED_FLOAT32 p_Blue );

			virtual ZED_BOOL ToggleFullscreen( );
			virtual ZED_BOOL ResizeCanvas( const ZED_UINT32 p_Width,
				const ZED_UINT32 p_Height );

			virtual void Release( );

			// Windows-specific functions
			ZED_UINT32 SetHDC( const HDC &p_HDC );

			/*virtual ZED_UINT32 SetView3D( const Arithmetic::Vector3 &p_Right,
				const Arithmetic::Vector3 &p_Up,
				const Arithmetic::Vector3 &p_Direction,
				const Arithmetic::Vector3 &p_Position );*/

		private:
			PIXELFORMATDESCRIPTOR	m_PixelFormat;
			HGLRC					m_HGLRC;
			HDC						m_HDC;
			GLExtender				m_Ext;
			CanvasDescription		m_Canvas;
			ZED_FLOAT32				m_AspectRatio;

			// Near and far viewing planes
			ZED_FLOAT32 m_Near;
			ZED_FLOAT32 m_Far;

			// The view mode to apply
			ZED_VIEWMODE m_ViewMode;

			// Up to four viewports can be rendered
			ZED_VIEWPORT m_Viewport[ 4 ];

			// Which viewport should be rendered
			ZED_UINT32 m_Stage;
		};
	}
}

#endif