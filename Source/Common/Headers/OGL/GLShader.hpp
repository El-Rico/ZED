#ifndef __ZED_RENDERER_GLSHADER_HPP__
#define __ZED_RENDERER_GLSHADER_HPP__

#include <Shader.hpp>

namespace ZED
{
	namespace Renderer
	{
		class GLShader : public Shader
		{
		public:
			GLShader( );
			GLShader( const ZED_BOOL p_Vertex, const ZED_BOOL p_Fragment,
				const ZED_BOOL p_Geometry );
			virtual ZED_INLINE ~GLShader( ){ this->Delete( ); }

			virtual ZED_UINT32 Compile( const ZED_CHAR8 **p_ppData,
				const ZED_SHADER_TYPE p_Type,
				const ZED_BOOL p_FromFile );
			
			virtual ZED_UINT32 Create( const ZED_UCHAR8 *p_pData,
				const ZED_SHADER_TYPE p_Type,
				const ZED_BOOL p_FromFile );

			virtual ZED_UINT32 Activate( );
			virtual void Deactivate( );

			virtual void AddType( const ZED_SHADER_TYPE p_Type );

			virtual void Delete( );

			virtual ZED_UINT32 SetVertexAttributeTypes(
				const ZED_SHADER_VERTEXATTRIBUTE *p_pAttributes,
				const ZED_MEMSIZE p_Count );

			virtual ZED_UINT32 SetConstantTypes(
				const ZED_SHADER_CONSTANT_MAP *p_pTypes,
				const ZED_MEMSIZE p_Count );
			
			virtual ZED_UINT32 SetConstantData( const ZED_UINT32 p_Index,
				const void *p_pValue );

#ifdef ZED_BUILD_DEBUG
			virtual ZED_UINT32 Save( const ZED_UCHAR8 *p_pFile,
				const ZED_BOOL p_HLSL );
#endif

		private:
			//GLuint GetLocation( );

			ZED_UINT32 Link( );

			ZED_UINT32 AttachShaders( );

			GLint	m_VertexID;
			GLint	m_FragmentID;
			GLint	m_GeometryID;

			GLint	m_ProgramID;
			GLint	*m_pLocationID;

			ZED_MEMSIZE						m_AttributeCount;
			ZED_SHADER_VERTEXATTRIBUTE_GL	*m_pAttributes;

			// Flags to indicate if the shaders are attached and if the program
			// has been linked
			ZED_UINT32	m_Flags;

			ZED_SHADER_CONSTANT_MAP	*m_pConstantMap;

			// Store the source for debugging
#ifdef ZED_BUILD_DEBUG
			ZED_CHAR8 **m_ppVertexSrc;
			ZED_CHAR8 **m_ppFragmentSrc;
			ZED_CHAR8 **m_ppGeometrySrc;
#endif
		};
	}
}

#endif