#ifndef __ZED_RENDERER_MODEL_HPP__
#define __ZED_RENDERER_MODEL_HPP__

#include <Renderer/ModelStructs.hpp>
#include <Arithmetic/Vector2.hpp>
#include <Arithmetic/Vector3.hpp>
#include <Renderer/Shader.hpp>
#include <Arithmetic/Matrix3x3.hpp>
#include <Arithmetic/Matrix4x4.hpp>
#include <cstring>
#include <Arithmetic/AABB.hpp>

namespace ZED
{
	namespace Renderer
	{
		class Mesh
		{
		public:
			ZED_EXPLICIT Mesh( )
			{
				m_StripCount = 0;
				m_ListCount = 0;
				m_FanCount = 0;
				m_ppStrips = ZED_NULL;
				m_ppLists = ZED_NULL;
				m_ppFans = ZED_NULL;
				m_pStripIndexCount = ZED_NULL;
				m_pListIndexCount = ZED_NULL;
				m_pFanIndexCount = ZED_NULL;
				m_pVertices = ZED_NULL;
			}

			ZED_EXPLICIT Mesh( const ZED_UINT32 p_StripCount,
				const ZED_UINT32 p_ListCount,
				const ZED_UINT32 p_FanCount )
			{
				if( p_StripCount > 0 )
				{
					m_ppStrips = new ZED_UINT16*[ p_StripCount ];
					m_pStripIndexCount = new ZED_UINT32[ p_StripCount ];
				}
				if( p_ListCount > 0 )
				{
					m_ppLists = new ZED_UINT16*[ p_ListCount ];
					m_pListIndexCount = new ZED_UINT32[ p_ListCount ];
				}
				if( p_FanCount > 0 )
				{
					m_ppFans = new ZED_UINT16*[ p_FanCount ];
					m_pFanIndexCount = new ZED_UINT32[ p_FanCount ];
				}

				m_StripCount = p_StripCount;
				m_ListCount = p_ListCount;
				m_FanCount = p_FanCount;
				m_pVertices = ZED_NULL;
			}

			~Mesh( )
			{
				if( m_pVertices )
				{
					delete [ ] m_pVertices;
					m_pVertices = ZED_NULL;
				}

				if( m_pStripIndexCount )
				{
					delete [ ] m_pStripIndexCount;
					m_pStripIndexCount = ZED_NULL;
				}

				if( m_pListIndexCount )
				{
					delete [ ] m_pListIndexCount;
					m_pListIndexCount = ZED_NULL;
				}

				if( m_pFanIndexCount )
				{
					delete [ ] m_pFanIndexCount;
					m_pFanIndexCount = ZED_NULL;
				}

				if( m_ppStrips )
				{
					for( ZED_MEMSIZE i = 0; i < m_StripCount; ++i )
					{
						if( m_ppStrips[ i ] )
						{
							delete [ ] m_ppStrips[ i ];
							m_ppStrips[ i ] = ZED_NULL;
						}
					}

					delete [ ] m_ppStrips;
					m_ppStrips = ZED_NULL;
				}

				if( m_ppLists )
				{
					for( ZED_MEMSIZE i = 0; i < m_ListCount; ++i )
					{
						if( m_ppLists[ i ] )
						{
							delete [ ] m_ppLists[ i ];
							m_ppLists[ i ] = ZED_NULL;
						}
					}

					delete [ ] m_ppLists;
					m_ppLists = ZED_NULL;
				}

				if( m_ppFans )
				{
					for( ZED_MEMSIZE i = 0; i < m_FanCount; ++i )
					{
						if( m_ppFans[ i ] )
						{
							delete [ ] m_ppFans[ i ];
							m_ppFans[ i ] = ZED_NULL;
						}
					}

					delete [ ] m_ppFans;
					m_ppFans = ZED_NULL;
				}
			}

			void Vertices( const ZED_BYTE *p_pVertices,
				const ZED_UINT32 p_VertexCount )
			{
				if( p_pVertices )
				{
					if( m_pVertices )
					{
						delete [ ] m_pVertices;
						m_pVertices = ZED_NULL;
					}
				}

				m_pVertices =
					new ZED_BYTE[ sizeof( VERTEX_V2 )*p_VertexCount ];
				memcpy( m_pVertices, p_pVertices,
					p_VertexCount*sizeof( VERTEX_V2 ) );
				m_VertexCount = p_VertexCount;
			}

			ZED_BYTE *Vertices( ) const { return m_pVertices; }

			void Strip( const ZED_UINT16 *p_pStrip, const ZED_MEMSIZE p_Index,
				const ZED_MEMSIZE p_Count )
			{
			}

			void List( const ZED_UINT16 *p_pList, const ZED_MEMSIZE p_Index,
				const ZED_UINT32 p_Count )
			{
				if( p_Index > ( m_ListCount+1 ) )
				{
					return;
				}

				if( m_ppLists )
				{
					m_ppLists[ p_Index ] = new ZED_UINT16[ p_Count ];
					//memcpy( m_ppLists[ p_Index ], p_pList, p_Count );
					for( ZED_UINT32 i = 0; i < p_Count; ++i )
					{
						m_ppLists[ p_Index ][ i ] = p_pList[ i ];
					}
					m_pListIndexCount[ p_Index ] = p_Count;
				}
			}

			void Fan( const ZED_UINT16 *p_pFan, const ZED_MEMSIZE p_Index,
				const ZED_UINT32 p_Count )
			{
			}

			ZED_UINT16 *Strip( const ZED_MEMSIZE p_Index )
			{
				return ZED_NULL;
			}

			ZED_UINT16 *List( const ZED_MEMSIZE p_Index )
			{
				if( p_Index > ( m_ListCount+1 ) )
				{
					return ZED_NULL;
				}

				return m_ppLists[ p_Index ];
			}

			ZED_UINT16 *Fan( const ZED_MEMSIZE p_Index )
			{
				return ZED_NULL;
			}

			void StripCount( const ZED_UINT32 p_StripCount )
			{
				if( m_ppStrips )
				{
					for( ZED_MEMSIZE i = 0; i < m_StripCount; ++i )
					{
						delete [ ] m_ppStrips[ i ];
						m_ppStrips[ i ] = ZED_NULL;
					}
					delete [ ] m_ppStrips;
					m_ppStrips = ZED_NULL;
				}

				if( m_pStripIndexCount )
				{
					delete [ ] m_pStripIndexCount;
					m_pStripIndexCount = ZED_NULL;
				}

				m_ppStrips = new ZED_UINT16*[ p_StripCount ];
				m_pStripIndexCount = new ZED_UINT32[ p_StripCount ];
				m_StripCount = p_StripCount;
			}

			void ListCount( const ZED_UINT32 p_ListCount )
			{
				if( m_ppLists )
				{
					for( ZED_MEMSIZE i = 0; i < m_ListCount; ++i )
					{
						delete [ ] m_ppLists[ i ];
						m_ppLists[ i ] = ZED_NULL;
					}
					delete [ ] m_ppLists;
					m_ppLists = ZED_NULL;
				}

				if( m_pListIndexCount )
				{
					delete [ ] m_pListIndexCount;
					m_pListIndexCount = ZED_NULL;
				}

				m_ppLists = new ZED_UINT16*[ p_ListCount ];
				m_pListIndexCount = new ZED_UINT32[ p_ListCount ];
				m_ListCount = p_ListCount;
			}

			void FanCount( const ZED_UINT32 p_FanCount )
			{
				if( m_ppFans )
				{
					for( ZED_MEMSIZE i = 0; i < m_FanCount; ++i )
					{
						delete [ ] m_ppFans[ i ];
						m_ppFans[ i ] = ZED_NULL;
					}
					delete [ ] m_ppFans;
					m_ppFans = ZED_NULL;
				}

				if( m_pFanIndexCount )
				{
					delete [ ] m_pFanIndexCount;
					m_pFanIndexCount = ZED_NULL;
				}

				m_ppFans = new ZED_UINT16*[ p_FanCount ];
				m_pFanIndexCount = new ZED_UINT32[ p_FanCount ];
				m_FanCount = p_FanCount;
			}

			void CalculateBoundingBox( )
			{
				if( m_VertexCount < 4 )
				{
					return;
				}

				VERTEX_V2 Vertices[ m_VertexCount ];

				memcpy( Vertices, m_pVertices,
					sizeof( VERTEX_V2 )*m_VertexCount );

				ZED::Arithmetic::Vector3 Min(
					Vertices[ 0 ].Position[ 0 ],
					Vertices[ 0 ].Position[ 1 ],
					Vertices[ 0 ].Position[ 2 ] );

				ZED::Arithmetic::Vector3 Max(
					Vertices[ 0 ].Position[ 0 ],
					Vertices[ 0 ].Position[ 1 ],
					Vertices[ 0 ].Position[ 2 ] );

				for( ZED_UINT32 i = 1; i < m_VertexCount; ++i )
				{
					if( Vertices[ i ].Position[ 0 ] > Max[ 0 ] )
					{
						Max[ 0 ] = Vertices[ i ].Position[ 0 ];
					}
					if( Vertices[ i ].Position[ 0 ] < Min[ 0 ] )
					{
						Min[ 0 ] = Vertices[ i ].Position[ 0 ];
					}
					if( Vertices[ i ].Position[ 1 ] > Max[ 1 ] )
					{
						Max[ 1 ] = Vertices[ i ].Position[ 1 ];
					}
					if( Vertices[ i ].Position[ 1 ] < Min[ 1 ] )
					{
						Min[ 1 ] = Vertices[ i ].Position[ 1 ];
					}
					if( Vertices[ i ].Position[ 2 ] > Max[ 2 ] )
					{
						Max[ 2 ] = Vertices[ i ].Position[ 2 ];
					}
					if( Vertices[ i ].Position[ 2 ] < Min[ 2 ] )
					{
						Min[ 2 ] = Vertices[ i ].Position[ 2 ];
					}
				}

				m_BoundingBox.Min( Min );
				m_BoundingBox.Max( Max );
			}

			void BoundingBox( ZED::Arithmetic::AABB *p_pBoundingBox )
			{
				( *p_pBoundingBox ) = m_BoundingBox;
				ZED::Arithmetic::Vector3 Min, Max;
				m_BoundingBox.Min( &Min );
				m_BoundingBox.Max( &Max );
				zedTrace( "\tMinimum: %f | %f | %f\n", Min[ 0 ], Min[ 1 ],
					Min[ 2 ] );
				zedTrace( "\tMaximum: %f | %f | %f\n", Max[ 0 ], Max[ 1 ],
					Max[ 2 ] );
			}

			ZED_INLINE ZED_UINT32 StripCount( ) const { return m_StripCount; }
			ZED_INLINE ZED_UINT32 StripIndexCount(
				const ZED_MEMSIZE p_Index ) const
					{ return m_pStripIndexCount[ p_Index ]; }
			ZED_INLINE ZED_UINT32 ListCount( ) const { return m_ListCount; }
			ZED_INLINE ZED_UINT32 ListIndexCount(
				const ZED_MEMSIZE p_Index ) const 
					{ return m_pListIndexCount[ p_Index ]; }
			ZED_INLINE ZED_UINT32 FanCount( ) const { return m_FanCount; }
			ZED_INLINE ZED_UINT32 FanIndexCount(
				const ZED_MEMSIZE p_Index ) const
					{ return m_pFanIndexCount[ p_Index ]; }
			ZED_INLINE ZED_UINT32 VertexCount( ) const
				{ return m_VertexCount; }
			ZED_INLINE void Attributes( const ZED_UINT64 p_Attributes )
				{ m_Attributes = p_Attributes; }
			ZED_INLINE ZED_UINT64 Attributes( ) const { return m_Attributes; }
			ZED_INLINE void MaterialID( const ZED_UINT32 p_MaterialID )
				{ m_MaterialID = p_MaterialID; }
			ZED_INLINE ZED_UINT32 MaterialID( ) const { return m_MaterialID; }

		private:
			ZED_UINT16				**m_ppStrips;
			ZED_UINT16				**m_ppLists;
			ZED_UINT16				**m_ppFans;
			ZED_UINT32				m_StripCount;
			ZED_UINT32				*m_pStripIndexCount;
			ZED_UINT32				m_ListCount;
			ZED_UINT32				*m_pListIndexCount;
			ZED_UINT32				m_FanCount;
			ZED_UINT32				*m_pFanIndexCount;
			ZED_BYTE				*m_pVertices;
			ZED_UINT32				m_VertexCount;
			ZED_UINT64				m_Attributes;
			ZED_UINT32				m_MaterialID;
			ZED::Arithmetic::AABB	m_BoundingBox;
		};

		class Model
		{
		public:
			virtual ~Model( ){ }

			virtual ZED_UINT32 Load( const ZED_CHAR8 *p_pFilename ) = 0;
			virtual void Render( ) = 0;
			virtual void Update( const ZED_FLOAT32 p_Delta,
				const Arithmetic::Matrix4x4 &p_ViewProjection ) = 0;

			virtual void SetPosition(
				const Arithmetic::Vector3 &p_Position ) = 0;
			virtual void SetScale( const Arithmetic::Vector3 &p_Scale ) = 0;
			virtual void SetOrientation(
				const Arithmetic::Quaternion &p_Orientation ) = 0;
			virtual void CalculateBoundingBox( ) = 0;
			virtual void BoundingBox( Arithmetic::AABB *p_pBoundingBox ) = 0;
			virtual void BoundingBox( Arithmetic::AABB *p_pBoundingBox,
				const ZED_UINT32 p_MeshIndex ) = 0;

#ifdef ZED_BUILD_DEBUG
			virtual void SetWireframeColour( const ZED_COLOUR &p_Colour ) = 0;

			virtual void ToggleWireframe( ) = 0;
			virtual void ToggleBones( ) = 0;
			virtual void ToggleFaceNormals( ) = 0;
			virtual void ToggleVertexNormals( ) = 0;
			virtual void ToggleBoundingBox( ) = 0;
#endif

		protected:
			// Make sure this is a ZED Model file
			virtual ZED_UINT32 LoadHeader( ) = 0;

			// Loads in the meshes.  Each mesh has its own vertices and
			// indices.
			virtual ZED_UINT32 LoadMeshes( const ZED_UINT64 p_Size ) = 0;

			// Animations are documented in the Renderer SDK.  Basically,
			// they're comprised of the bind pose + sampled animations.
			virtual ZED_UINT32 LoadAnimation( const ZED_UINT64 p_Size ) = 0;

			// Little helper!
			virtual void ReadChunk( ZED_UINT16 &p_Type,	
				ZED_UINT64 &p_Size ) = 0;
		};
	}
}

#endif

