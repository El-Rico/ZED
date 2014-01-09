#ifndef __ZED_RENDERER_GLSHADERMATERIAL_HPP__
#define __ZED_RENDERER_GLSHADERMATERIAL_HPP__

#include <Renderer/ShaderMaterial.hpp>
#include <vector>
#include <map>
#include <string>

namespace ZED
{
	namespace Renderer
	{
		// Forward declarations
		class GLShader;
		class GLTexture;
		class Texture;

		class GLShaderMaterial : public ShaderMaterial
		{
		public:
			GLShaderMaterial( );
			virtual ~GLShaderMaterial( );

			virtual ZED_UINT32 AttachTexture(
				const ZED::Renderer::Texture *p_pTexture,
				const ZED_UINT32 p_Unit );

			virtual ZED_UINT32 AttachShader(
				const ZED::Renderer::Shader *p_pShader );
			virtual ZED_UINT32 SetNamedConstant( const ZED_CHAR8 *p_pName,
				const void *p_pData );
			virtual ZED_UINT32 SetRegisterConstant(
				const ZED_UINT32 p_Register, const void *p_pData );

			virtual ZED_UINT32 RegisterCount( );

		private:
			typedef std::map< std::string, GLuint > NameIndexMap;

			GLShader					*m_pShader;
			std::vector< GLTexture * >	m_Textures;
			NameIndexMap				m_NameMap;
		};
	}
}

#endif // __ZED_RENDERER_GLSHADERMATERIAL_HPP__
