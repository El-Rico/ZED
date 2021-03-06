#if defined ZED_PLATFORM_SUPPORTS_OPENGL

#include <Renderer/OGL/GLShader.hpp>
#include <cstdio>
#include <cstring>
#include <Renderer/OGL/GLExtender.hpp>

namespace ZED
{
	namespace Renderer
	{
		GLShader::GLShader( ) :
			m_VertexID( 0 ),
			m_FragmentID( 0 ),
			m_GeometryID( 0 ),
			m_ProgramID( 0 ),
			m_pLocationID( ZED_NULL ),
			m_AttributeCount( 0 ),
			m_pAttributes( 0 ),
			m_Flags( 0 ),
			m_pConstantMap( ZED_NULL )
		{
		}

		ZED_UINT32 GLShader::Compile( const ZED_CHAR8 **p_ppData,
			const ZED_SHADER_TYPE p_Type,
			const ZED_BOOL p_FromFile )
		{
			GLchar **ppSource = new GLchar*[ 1 ];
			ZED_MEMSIZE SourceLength = 0;
			FILE *pFile = ZED_NULL;

			if( p_FromFile == ZED_TRUE )
			{
				pFile = fopen( *p_ppData, "rb" );
				zedTrace( "[ZED::Renderer::GLShader::Compile] <INFO> "
					"File: %s\n", *p_ppData );

				// Read the source from the file
				fseek( pFile, 0, SEEK_END );
				SourceLength = ftell( pFile );
				rewind( pFile );

				ppSource[ 0 ] = new GLchar[ SourceLength ];

				fread( ppSource[ 0 ], sizeof( ZED_BYTE ), SourceLength,
					pFile );
			}
			else
			{
				SourceLength = strlen( *p_ppData );
				ppSource[ 0 ] = new GLchar[ SourceLength ];
				memcpy( ppSource[ 0 ], *p_ppData, SourceLength );
			}

			GLint CompileStatus = 0;
			char PrintSource[ SourceLength+1 ];
			strncpy( PrintSource, ppSource[ 0 ], SourceLength );
			PrintSource[ SourceLength ] = '\0';
			zedTrace( "[ZED::Renderer::GLShader::Compile] <INFO> "
				"Size: %d | Source:\n%s\n\n", SourceLength, PrintSource );

			// Depending on the type of shader, bind with vertex, fragment, or
			// geometry
			if( p_Type == ZED_VERTEX_SHADER )
			{
				if( !zglIsShader( m_VertexID ) )
				{
					this->AddType( p_Type );
				}

				zglShaderSource( m_VertexID, 1,
					const_cast< const GLchar ** >( ppSource ),
					reinterpret_cast< const GLint *>( &SourceLength ) );
				zglCompileShader( m_VertexID );

				// Get the compilation status
				zglGetShaderiv( m_VertexID, GL_COMPILE_STATUS,
					&CompileStatus );

				if( !CompileStatus )
				{
					// Something went wrong
					GLint LogLength = 0;
					GLchar *pLog = ZED_NULL;
					zglGetShaderiv( m_VertexID, GL_INFO_LOG_LENGTH,
						&LogLength );
					pLog = new GLchar[ LogLength ];

					zglGetShaderInfoLog( m_VertexID, LogLength, &LogLength,
						pLog );
					zedTrace( "[ZED::Renderer::GLShader::Compile] <ERROR> "
						"Vertex Shader Log:\n\t%s\n", pLog );

					delete [ ] pLog;

					fclose( pFile );
					pFile = ZED_NULL;

					if( ppSource[ 0 ] != ZED_NULL )
					{
						delete [ ] ppSource[ 0 ];
						delete [ ] ppSource;
					}

					return ZED_GRAPHICS_ERROR;
				}
			}

			if( p_Type == ZED_FRAGMENT_SHADER )
			{
				if( !zglIsShader( m_FragmentID ) )
				{
					this->AddType( p_Type );
				}

				zglShaderSource( m_FragmentID, 1,
					const_cast< const GLchar ** >( ppSource ),
					reinterpret_cast< const GLint *>( &SourceLength ) );
				zglCompileShader( m_FragmentID );

				// Get the compilation status
				zglGetShaderiv( m_FragmentID, GL_COMPILE_STATUS,
					&CompileStatus );

				if( !CompileStatus )
				{
					// Something went wrong
					GLint LogLength = 0;
					GLchar *pLog = ZED_NULL;
					zglGetShaderiv( m_FragmentID, GL_INFO_LOG_LENGTH,
						&LogLength );
					pLog = new GLchar[ LogLength ];

					zglGetShaderInfoLog( m_FragmentID, LogLength, &LogLength,
						pLog );
					zedTrace( "[ZED::Renderer::GLShader::Compile] <ERROR> "
						"Fragment Shader Log:\n\t%s\n", pLog );

					delete [ ] pLog;

					fclose( pFile );
					pFile = ZED_NULL;

					if( ppSource[ 0 ] != ZED_NULL )
					{
						delete [ ] ppSource[ 0 ];
						delete [ ] ppSource;
					}

					return ZED_GRAPHICS_ERROR;
				}
			}

			if( ppSource[ 0 ] != ZED_NULL )
			{
				ExtractUniformNames( ppSource[ 0 ] );

				delete [ ] ppSource[ 0 ];
				delete [ ] ppSource;
			}

			if( pFile != ZED_NULL )
			{
				fclose( pFile );
			}

			return ZED_OK;
		}

		ZED_UINT32 GLShader::Create( const ZED_UCHAR8 *p_pData,
			const ZED_SHADER_TYPE p_Type,
			const ZED_BOOL p_FromFile )
		{
			return ZED_OK;
		}

		ZED_UINT32 GLShader::Activate( )
		{
			// Check if the program has not already been linked
			if( !( m_Flags && ZED_SHADER_LINKED ) )
			{
				if( this->Link( ) != ZED_OK )
				{
					return ZED_FAIL;
				}
			}

			if( zglIsProgram( m_ProgramID ) )
			{
				zglUseProgram( m_ProgramID );
			}

			return ZED_OK;
		}

		void GLShader::Deactivate( )
		{
		}

		void GLShader::AddType( const ZED_SHADER_TYPE p_Type )
		{
			if( p_Type == ZED_VERTEX_SHADER )
			{
				m_VertexID = zglCreateShader( GL_VERTEX_SHADER );
			}
			else if( p_Type == ZED_FRAGMENT_SHADER )
			{
				m_FragmentID = zglCreateShader( GL_FRAGMENT_SHADER );
			}
		}

		void GLShader::Delete( )
		{
			if( m_pConstantMap != ZED_NULL )
			{
				delete [ ] m_pConstantMap;
			}

			if( m_VertexID != 0 )
			{
				zglDeleteShader( m_VertexID );
			}
			if( m_FragmentID != 0 )
			{
				zglDeleteShader( m_FragmentID );
			}
			if( m_GeometryID != 0 )
			{
				zglDeleteShader( m_GeometryID );
			}
			if( m_ProgramID != 0 )
			{
				zglDeleteProgram( m_ProgramID );
			}
		}

#ifdef ZED_BUILD_DEBUG
		ZED_UINT32 GLShader::Save( const ZED_UCHAR8 *p_pFile,
			const ZED_BOOL p_HLSL )
		{
			return ZED_OK;
		}
#endif

		ZED_UINT32 GLShader::SetVertexAttributeTypes(
			const ZED_SHADER_VERTEXATTRIBUTE *p_pVAMap,
			const ZED_MEMSIZE p_Count )
		{
			return ZED_OK;
		}

		ZED_UINT32 GLShader::SetConstantTypes(
			const ZED_SHADER_CONSTANT_MAP *p_pConstants,
			const ZED_MEMSIZE p_Count )
		{
			// The program has to already be linked before calling!
			if( !( m_Flags && ZED_SHADER_LINKED ) )
			{
				if( this->Link( ) != ZED_OK )
				{
					return ZED_FAIL;
				}
			}

			m_pConstantMap = new ZED_SHADER_CONSTANT_MAP[ p_Count ];

			for( ZED_MEMSIZE i = 0; i < p_Count; i++ )
			{
				m_pConstantMap[ i ].Location = zglGetUniformLocation(
					m_ProgramID, p_pConstants[ i ].pName );
				m_pConstantMap[ i ].Index = p_pConstants[ i ].Index;
				m_pConstantMap[ i ].Type = p_pConstants[ i ].Type;
#ifdef ZED_BUILD_DEBUG
				m_pConstantMap[ i ].pName = p_pConstants[ i ].pName;
#endif
			}	

			return ZED_OK;
		}

		ZED_UINT32 GLShader::SetConstantData( const ZED_UINT32 p_Index,
			const void *p_pValue )
		{
			switch( m_pConstantMap[ p_Index ].Type )
			{
				case ZED_FLOAT1:
				{
					zglUniform1f( m_pConstantMap[ p_Index ].Location,
						*( reinterpret_cast< const GLfloat * >(
							&p_pValue ) ) );
					break;
				
				}
				case ZED_FLOAT2:
				{
					zglUniform2fv( m_pConstantMap[ p_Index ].Location, 1,
						static_cast< const GLfloat * >( p_pValue ) );
					break;
				}
				case ZED_FLOAT3:
				{
					zglUniform3fv( m_pConstantMap[ p_Index ].Location, 1,
						static_cast< const GLfloat * >( p_pValue ) );
					break;
				}
				case ZED_FLOAT4:
				{
					zglUniform4fv( m_pConstantMap[ p_Index ].Location, 1,
						static_cast< const GLfloat * >( p_pValue ) );
					break;
				}
				case ZED_INT1:
				{
					zglUniform1i( m_pConstantMap[ p_Index ].Location,
						*( reinterpret_cast< const GLint * >( &p_pValue ) ) );
					break;
				}
				case ZED_INT2:
				{
					zglUniform2iv( m_pConstantMap[ p_Index ].Location, 1,
						static_cast< const GLint * >( p_pValue ) );
					break;
				}
				case ZED_INT3:
				{
					zglUniform3iv( m_pConstantMap[ p_Index ].Location, 1,
						static_cast< const GLint * >( p_pValue ) );
					break;
				}
				case ZED_INT4:
				{
					zglUniform4iv( m_pConstantMap [ p_Index ].Location, 1,
						static_cast< const GLint * >( p_pValue ) );
					break;
				}
				case ZED_MAT2X2:
				{
					zglUniformMatrix2fv( m_pConstantMap[ p_Index ].Location, 1,
						GL_FALSE,
						static_cast< const GLfloat * > ( p_pValue ) );
					break;
				}
				case ZED_MAT3X3:
				{
					zglUniformMatrix3fv( m_pConstantMap[ p_Index ].Location,
						1, GL_FALSE,
						static_cast< const GLfloat * >( p_pValue ) );
					break;
				}
				case ZED_MAT4X4:
				{
					zglUniformMatrix4fv( m_pConstantMap[ p_Index ].Location, 1,
						GL_FALSE, static_cast< const GLfloat * >( p_pValue ) );
					break;
				}
				case ZED_SHADER_CONSTANT_TYPE_UNKNOWN:
				default:
				{
					zedTrace( "[ZED::Renderer::GLShader::SetConstatantData] "
						"<ERROR> Unknown type stored for constant\n" );
					return ZED_FAIL;
				}
			}
			return ZED_OK;
		}

		ZED_UINT32 GLShader::GetConstantIndex( ZED_UINT32 &p_Location,
			const ZED_CHAR8 *p_pConstantName )
		{
			UniformNameLocationMap::const_iterator Itr =
				m_NameLocationMap.find( p_pConstantName );

			if( Itr == m_NameLocationMap.end( ) )
			{
				return ZED_FAIL;
			}

			p_Location = Itr->second;

			return ZED_OK;
		}

		ZED_UINT32 GLShader::GetConstantName( const ZED_UINT32 p_Location,
			ZED_CHAR8 **p_ppConstantName,
			const ZED_MEMSIZE p_ConstantNameLength )
		{
			UniformNameLocationMap::const_iterator Itr =
				m_NameLocationMap.begin( );

			for( ; Itr != m_NameLocationMap.end( ); ++Itr )
			{
				// It is assumed that there is a one-to-one mapping between the
				// name and location
				if( p_Location == Itr->second )
				{
					if( Itr->first.size( ) < ( p_ConstantNameLength + 1 ) )
					{
						strncpy( ( *p_ppConstantName ), Itr->first.c_str( ),
							Itr->first.size( ) );
						( *p_ppConstantName )[ Itr->first.size( ) ] = '\0';
					}
					break;
				}
			}

			if( Itr == m_NameLocationMap.end( ) )
			{
				return ZED_FAIL;
			}

			return ZED_OK;
		}

		void GLShader::ExtractUniformNames( const ZED_CHAR8 *p_pSource )
		{
			// Look for the key word "uniform", followed by whitespace until
			// a built-in keyword for a vector or scalar type is found.  The
			// next part of the string should be whitespace followed by the
			// uniform name, any additional whitespace, then a semi-colon,
			// indicating the end of the line
			std::string SourceCopy( p_pSource );

			size_t UniformPosition = SourceCopy.find_first_of( "uniform" );
			while( UniformPosition == std::string::npos )
			{
				// Get the first set of non-whitespace characters before the
				// semi-colon
				size_t SemiColonPosition = SourceCopy.find_first_of( ";",
					UniformPosition );

				if( SemiColonPosition == std::string::npos )
				{
					break;
				}

				// Find any arrays and stop progression making it easier to 
				// separate the uniform name instead of working backward from
				// the semi-colon and handling spaces, numbers inside square
				// brackets and square brackets
				size_t UniformNameEnd = SourceCopy.find_first_of( '[',
					UniformPosition );
				--UniformNameEnd;

				if( UniformNameEnd > SemiColonPosition )
				{
					UniformNameEnd = SourceCopy.find_last_not_of( " \t",
						UniformNameEnd );
				}

				size_t UniformNameStart = SourceCopy.find_last_of( " \t",
					UniformNameEnd );

				m_UniformNames.push_back( SourceCopy.substr( UniformNameStart,
					( UniformNameEnd - UniformNameStart ) + 1 ) );

				UniformPosition = SourceCopy.find_first_of( "uniform",
					SemiColonPosition );
			}
		}

		ZED_UINT32 GLShader::Link( )
		{
			m_ProgramID = zglCreateProgram( );

			if( m_ProgramID == 0 )
			{
				zedTrace( "[ZED::Renderer::GLShader::Activate] <ERROR> "
					"Failed to create program for shader.\n" );
				return ZED_GRAPHICS_ERROR;
			}

			// Attach shaders
			if( zglIsShader( m_VertexID ) )
			{
				zglAttachShader( m_ProgramID, m_VertexID );
			}
			if( zglIsShader( m_FragmentID ) )
			{
				zglAttachShader( m_ProgramID, m_FragmentID );
			}

			zglLinkProgram( m_ProgramID );

			// Get the link status
			GLint Error;
			zglGetProgramiv( m_ProgramID, GL_LINK_STATUS, &Error );

			if( Error == GL_FALSE )
			{
				zedTrace( "[ZED::Renderer::GLShader::Activate] <ERROR> "
					"Failed to link program\n" );
				GLsizei Length = 0;
				GLchar *pLog;

				zglGetProgramiv( m_ProgramID, GL_INFO_LOG_LENGTH,
					&Length );
				pLog = new GLchar[ Length ];

				zglGetProgramInfoLog( m_ProgramID, Length, &Length, pLog );
				zedTrace( "%s\n", pLog );
				zedAssert( ZED_FALSE );

				delete pLog;

				return ZED_FAIL;
			}

			if( this->BindUniformNamesToLocations( ) != ZED_OK )
			{
				return ZED_FAIL;
			}

			m_Flags |= ZED_SHADER_LINKED;

			return ZED_OK;
		}

		ZED_UINT32 GLShader::BindUniformNamesToLocations( )
		{
			std::list< std::string>::const_iterator Itr =
				m_UniformNames.begin( );

			for( ; Itr != m_UniformNames.end( ); ++Itr )
			{
				GLuint Location = zglGetUniformLocation( m_ProgramID,
					( *Itr ).c_str( ) );

				switch( Location )
				{
					case GL_INVALID_VALUE:
					{
						zedTrace( "[ZED::Renderer::GLShader::"
							"BindUniformNamesToLocations] <ERROR> Program was "
							"not generated by OpenGL" );
						return ZED_FAIL;
					}
					case GL_INVALID_OPERATION:
					{
						zedTrace( "[ZED::Renderer::GLShader::"
							"BindUniformNamesToLocations] <ERROR> Program "
							"object not valid\n" );
					}
					default:
					{
						m_NameLocationMap.insert(
							std::pair< std::string, GLuint >(
								( *Itr ), Location ) );
						break;
					}
				}
			}

			return ZED_OK;
		}
	}
}

#endif // ZED_PLATFORM_SUPPORTS_OPENGL

