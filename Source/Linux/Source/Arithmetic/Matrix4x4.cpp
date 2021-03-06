#include <Arithmetic/Matrix3x3.hpp>
#include <Arithmetic/Matrix4x4.hpp>
#include <Arithmetic/Vector3.hpp>
#include <Arithmetic/Vector4.hpp>
#include <Arithmetic/Arithmetic.hpp>
#include <Arithmetic/Quaternion.hpp>

namespace ZED
{
	namespace Arithmetic
	{
		Matrix4x4::Matrix4x4( const Matrix4x4 &p_Other )
		{
			m_M[ 0 ] = p_Other[ 0 ];
			m_M[ 1 ] = p_Other[ 1 ];
			m_M[ 2 ] = p_Other[ 2 ];
			m_M[ 3 ] = p_Other[ 3 ];
			m_M[ 4 ] = p_Other[ 4 ];
			m_M[ 5 ] = p_Other[ 5 ];
			m_M[ 6 ] = p_Other[ 6 ];
			m_M[ 7 ] = p_Other[ 7 ];
			m_M[ 8 ] = p_Other[ 8 ];
			m_M[ 9 ] = p_Other[ 9 ];
			m_M[ 10 ] = p_Other[ 10 ];
			m_M[ 11 ] = p_Other[ 11 ];
			m_M[ 12 ] = p_Other[ 12 ];
			m_M[ 13 ] = p_Other[ 13 ];
			m_M[ 14 ] = p_Other[ 14 ];
			m_M[ 15 ] = p_Other[ 15 ];
		}

		Matrix4x4 &Matrix4x4::operator=( const Matrix4x4 &p_Other )
		{
			m_M[ 0 ] = p_Other[ 0 ];
			m_M[ 1 ] = p_Other[ 1 ];
			m_M[ 2 ] = p_Other[ 2 ];
			m_M[ 3 ] = p_Other[ 3 ];
			m_M[ 4 ] = p_Other[ 4 ];
			m_M[ 5 ] = p_Other[ 5 ];
			m_M[ 6 ] = p_Other[ 6 ];
			m_M[ 7 ] = p_Other[ 7 ];
			m_M[ 8 ] = p_Other[ 8 ];
			m_M[ 9 ] = p_Other[ 9 ];
			m_M[ 10 ] = p_Other[ 10 ];
			m_M[ 11 ] = p_Other[ 11 ];
			m_M[ 12 ] = p_Other[ 12 ];
			m_M[ 13 ] = p_Other[ 13 ];
			m_M[ 14 ] = p_Other[ 14 ];
			m_M[ 15 ] = p_Other[ 15 ];

			return *this;
		}

		void Matrix4x4::Identity( )
		{
			m_M[ 0 ] = m_M[ 5 ] = m_M[ 10 ] = m_M[ 15 ] = 1.0f;

			m_M[ 1 ] = m_M[ 2 ] = m_M[ 3 ] = m_M[ 4 ] = m_M[ 6 ] = m_M[ 7 ] =
				m_M[ 8 ] = m_M[ 9 ] = m_M[ 11 ] = m_M[ 12 ] = m_M[ 13 ] =
				m_M[ 14 ] = 0.0f;
		}

		Matrix4x4::Matrix4x4( const Quaternion &p_Quaternion )
		{
			ZED_FLOAT32 XX, YY, ZZ, XY, WZ, XZ, WY, YZ, WX;
			ZED_FLOAT32 Scale, XScale, YScale, ZScale;
			Scale = 2.0f / ( p_Quaternion[ 0 ] * p_Quaternion[ 0 ] +
				p_Quaternion[ 1 ] * p_Quaternion[ 1 ] +
				p_Quaternion[ 2 ] * p_Quaternion[ 2 ] +
				p_Quaternion[ 3 ] * p_Quaternion[ 3 ] );

			XScale = Scale*p_Quaternion[ 0 ];
			YScale = Scale*p_Quaternion[ 1 ];
			ZScale = Scale * p_Quaternion[ 2 ];

			WX = p_Quaternion[ 3 ] * XScale;
			WY = p_Quaternion[ 3 ] * YScale;
			WZ = p_Quaternion[ 3 ] * ZScale;

			XX = p_Quaternion[ 0 ] * XScale;
			XY = p_Quaternion[ 0 ] * YScale;
			XZ = p_Quaternion[ 0 ] * ZScale;

			YY = p_Quaternion[ 1 ] * YScale;
			YZ = p_Quaternion[ 1 ] * ZScale;
			ZZ = p_Quaternion[ 2 ] * ZScale;

			m_M[ 0 ] = 1.0f - ( YY + ZZ );
			m_M[ 1 ] = XY + WZ;
			m_M[ 2 ] = XZ - WY;
			
			m_M[ 4 ] = XY - WZ;
			m_M[ 5 ] = 1.0f - ( XX + ZZ );
			m_M[ 6 ] = YZ + WX;

			m_M[ 8 ] = XZ + WY;
			m_M[ 9 ] = YZ - WX;
			m_M[ 10 ] = 1.0f - ( XX + YY );

			m_M[ 3 ] = m_M[ 4 ] = m_M[ 7 ] = m_M[ 11 ] = m_M[ 12 ] =
				m_M[ 13 ] = m_M[ 14 ] = 0.0f;
			m_M[ 15 ] = 1.0f;
		}

		Matrix4x4 &Matrix4x4::Rotate( const ZED_FLOAT32 p_Angle,
			const Vector3 &p_Axis )
		{
			ZED_FLOAT32 Cos = 0.0f, Tan = 0.0f, Sin = 0.0f;
			
			Arithmetic::SinCos( p_Angle, Sin, Cos );

			Tan = 1.0f - Cos;

			m_M[ 0 ] = ( Tan*( p_Axis[ 0 ]*p_Axis[ 0 ] ) ) + Cos;
			m_M[ 1 ] = ( Tan*p_Axis[ 0 ]*p_Axis[ 1 ] ) + ( Sin*p_Axis[ 2 ] );
			m_M[ 2 ] = ( Tan*p_Axis[ 0 ]*p_Axis[ 2 ] ) - ( Sin*p_Axis[ 1 ] );

			m_M[ 4 ] = ( Tan*p_Axis[ 0 ]*p_Axis[ 1 ] ) - ( Sin*p_Axis[ 2 ] );
			m_M[ 5 ] = ( Tan*( p_Axis[ 1 ]*p_Axis[ 1 ] ) ) + Cos;
			m_M[ 6 ] = ( Tan*p_Axis[ 1 ]*p_Axis[ 2 ] ) + ( Sin*p_Axis[ 0 ] );

			m_M[ 8 ] = ( Tan*p_Axis[ 0 ]*p_Axis[ 2 ] ) + ( Sin*p_Axis[ 1 ] );
			m_M[ 9 ] = ( Tan*p_Axis[ 1 ]*p_Axis[ 2 ] ) - ( Sin*p_Axis[ 0 ] );
			m_M[ 10 ] = ( Tan*( p_Axis[ 2 ]*p_Axis[ 2 ] ) ) + Cos;
			
			m_M[ 3 ] = m_M[ 7 ] = m_M[ 11 ] = m_M[ 12 ] = m_M[ 13 ] =
				m_M[ 14 ] = 0.0f;
			m_M[ 15 ] = 1.0f;

			return *this;
		}

		Matrix4x4 &Matrix4x4::Rotate( const ZED_FLOAT32 p_Roll,
			const ZED_FLOAT32 p_Pitch, const ZED_FLOAT32 p_Yaw )
		{
			ZED_FLOAT32 CX = 0.0f, CY = 0.0f, CZ = 0.0f;
			ZED_FLOAT32 SX = 0.0f, SY = 0.0f, SZ = 0.0f;
			
			Arithmetic::SinCos( p_Pitch, SX, CX );
			Arithmetic::SinCos( p_Yaw, SY, CY );
			Arithmetic::SinCos( p_Roll, SZ, CZ );

			m_M[ 0 ] = CY*CZ;
			m_M[ 1 ] = ( SX*SY*CZ) + ( CX*SZ );
			m_M[ 2 ] = -( CX*SY*CZ ) + ( SX*SZ );
			m_M[ 3 ] = 0.0f;

			m_M[ 4 ] = -( CY*SZ );
			m_M[ 5 ] = -( SX*SY*SZ ) + ( CX*CZ );
			m_M[ 6 ] = -( CX*SY*SZ ) + ( SX*CZ );
			m_M[ 7 ] = 0.0f;

			m_M[ 8 ] = SY;
			m_M[ 9 ] = -( SX*CY );
			m_M[ 10 ] = ( CX*CY );
			m_M[ 11 ] = 0.0f;

			m_M[ 12 ] = 0.0f;
			m_M[ 13 ] = 0.0f;
			m_M[ 14 ] = 0.0f;
			m_M[ 15 ] = 1.0f;

			return *this;
		}

		Matrix4x4 &Matrix4x4::Rotate( const Matrix3x3 &p_Matrix )
		{
			// Just copy into the upper-left 3x3 part of the matrix
			m_M[ 0 ] = p_Matrix[ 0 ];
			m_M[ 1 ] = p_Matrix[ 1 ];
			m_M[ 2 ] = p_Matrix[ 2 ];
			m_M[ 3 ] = 0.0f;

			m_M[ 4 ] = p_Matrix[ 3 ];
			m_M[ 5 ] = p_Matrix[ 4 ];
			m_M[ 6 ] = p_Matrix[ 5 ];
			m_M[ 7 ] = 0.0f;

			m_M[ 8 ] = p_Matrix[ 6 ];
			m_M[ 9 ] = p_Matrix[ 7 ];
			m_M[ 10 ] = p_Matrix[ 8 ];
			m_M[ 11 ] = 0.0f;

			m_M[ 12 ] = 0.0f;
			m_M[ 13 ] = 0.0f;
			m_M[ 14 ] = 0.0f;
			m_M[ 15 ] = 1.0f;

			return *this;
		}

		Matrix4x4 &Matrix4x4::RotateX( const ZED_FLOAT32 p_X )
		{
			ZED_FLOAT32 Sin = 0.0f, Cos = 0.0f;
			Arithmetic::SinCos( p_X, Sin, Cos );

			m_M[ 0 ] = 1.0f;
			m_M[ 1 ] = 0.0f;
			m_M[ 2 ] = 0.0f;
			m_M[ 3 ] = 0.0f;

			m_M[ 4 ] = 0.0f;
			m_M[ 5 ] = Cos;
			m_M[ 6 ] = -Sin;
			m_M[ 7 ] = 0.0f;

			m_M[ 8 ] = 0.0f;
			m_M[ 9 ] = Sin;
			m_M[ 10 ] = Cos;
			m_M[ 11 ] = 0.0f;
			
			m_M[ 12 ] = 0.0f;
			m_M[ 13 ] = 0.0f;
			m_M[ 14 ] = 0.0f;
			m_M[ 15 ] = 1.0f;

			return *this;
		}

		Matrix4x4 &Matrix4x4::RotateY( const ZED_FLOAT32 p_Y )
		{
			ZED_FLOAT32 Sin = 0.0f, Cos = 0.0f;
			Arithmetic::SinCos( p_Y, Sin, Cos );

			m_M[ 0 ] = Cos;
			m_M[ 1 ] = 0.0f;
			m_M[ 2 ] = Sin;
			m_M[ 3 ] = 0.0f;

			m_M[ 4 ] = 0.0f;
			m_M[ 5 ] = 1.0f;
			m_M[ 6 ] = 0.0f;
			m_M[ 7 ] = 0.0f;

			m_M[ 8 ] = -Sin;
			m_M[ 9 ] = 0.0f;
			m_M[ 10 ] = Cos;
			m_M[ 11 ] = 0.0f;

			m_M[ 12 ] = 0.0f;
			m_M[ 13 ] = 0.0f;
			m_M[ 14 ] = 0.0f;
			m_M[ 15 ] = 1.0f;

			return *this;
		}

		Matrix4x4 &Matrix4x4::RotateZ( const ZED_FLOAT32 p_Z )
		{
			ZED_FLOAT32 Sin = 0.0f, Cos = 0.0f;
			Arithmetic::SinCos( p_Z, Sin, Cos );

			m_M[ 0 ] = Cos;
			m_M[ 1 ] = -Sin;
			m_M[ 2 ] = 0.0f;
			m_M[ 3 ] = 0.0f;

			m_M[ 4 ] = Sin;
			m_M[ 5 ] = Cos;
			m_M[ 6 ] = 0.0f;
			m_M[ 7 ] = 0.0f;

			m_M[ 8 ] = 0.0f;
			m_M[ 9 ] = 0.0f;
			m_M[ 10 ] = 1.0f;
			m_M[ 11 ] = 0.0f;

			m_M[ 12 ] = 0.0f;
			m_M[ 13 ] = 0.0f;
			m_M[ 14 ] = 0.0f;
			m_M[ 15 ] = 1.0f;

			return *this;
		}

		Matrix4x4 &Matrix4x4::Scale( const ZED_FLOAT32 p_Scalar )
		{
			m_M[ 0 ] = p_Scalar;
			m_M[ 1 ] = 0.0f;
			m_M[ 2 ] = 0.0f;
			m_M[ 3 ] = 0.0f;

			m_M[ 4 ] = 0.0f;
			m_M[ 5 ] = p_Scalar;
			m_M[ 6 ] = 0.0f;
			m_M[ 7 ] = 0.0f;
			
			m_M[ 8 ] = 0.0f;
			m_M[ 9 ] = 0.0f;
			m_M[ 10 ] = p_Scalar;
			m_M[ 11 ] = 0.0f;

			m_M[ 12 ] = 0.0f;
			m_M[ 13 ] = 0.0f;
			m_M[ 14 ] = 0.0f;
			m_M[ 15 ] = 1.0f;

			return *this;
		}

		Matrix4x4 &Matrix4x4::Scale( const Vector3 &p_Scale )
		{
			m_M[ 0 ] = p_Scale[ 0 ];
			m_M[ 1 ] = m_M[ 2 ] = m_M[ 3 ] = m_M[ 4 ] = 0.0f;
			m_M[ 5 ] = p_Scale[ 1 ];
			m_M[ 6 ] = m_M[ 7 ] = m_M[ 8 ] = m_M[ 9 ] = 0.0f;
			m_M[ 10 ] = p_Scale[ 2 ];
			m_M[ 11 ] = m_M[ 12 ] = m_M[ 13 ] = m_M[ 14 ] = 0.0f;
			m_M[ 15 ] = 1.0f;
			
			return *this;
		}

		Matrix4x4 &Matrix4x4::ScaleX( const ZED_FLOAT32 p_X )
		{
			m_M[ 0 ] = p_X;
			m_M[ 1 ] = m_M[ 2 ] = m_M[ 3 ] = m_M[ 4 ] = 0.0f;
			m_M[ 5 ] = 1.0f;
			m_M[ 6 ] = m_M[ 7 ] = m_M[ 8 ] = m_M[ 9 ] = 0.0f;
			m_M[ 10 ] = 1.0f;
			m_M[ 11 ] = m_M[ 12 ] = m_M[ 13 ] = m_M[ 14 ] = 0.0f;
			m_M[ 15 ] = 1.0f;

			return *this;
		}

		Matrix4x4 &Matrix4x4::ScaleY( const ZED_FLOAT32 p_Y )
		{
			m_M[ 0 ] = 1.0f;
			m_M[ 1 ] = m_M[ 2 ] = m_M[ 3 ] = m_M[ 4 ] = 0.0f;
			m_M[ 5 ] = p_Y;
			m_M[ 6 ] = m_M[ 7 ] = m_M[ 8 ] = m_M[ 9 ] = 0.0f;
			m_M[ 10 ] = 1.0f;
			m_M[ 11 ] = m_M[ 12 ] = m_M[ 13 ] = m_M[ 14 ] = 0.0f;
			m_M[ 15 ] = 1.0f;

			return *this;
		}

		Matrix4x4 &Matrix4x4::ScaleZ( const ZED_FLOAT32 p_Z )
		{
			m_M[ 0 ] = 1.0f;
			m_M[ 1 ] = m_M[ 2 ] = m_M[ 3 ] = m_M[ 4 ] = 0.0f;
			m_M[ 5 ] = 1.0f;
			m_M[ 6 ] = m_M[ 7 ] = m_M[ 8 ] = m_M[ 9 ] = 0.0f;
			m_M[ 10 ] = p_Z;
			m_M[ 11 ] = m_M[ 12 ] = m_M[ 13 ] = m_M[ 14 ] = 0.0f;
			m_M[ 15 ] = 1.0f;

			return *this;
		}

		ZED_BOOL Matrix4x4::IsZero( ) const
		{
			for( ZED_MEMSIZE i = 0; i < 16; i++ )
			{
				if( !Arithmetic::IsZero( m_M[ i ] ) )
				{
					return ZED_FALSE;
				}
			}

			return ZED_TRUE;
		}

		ZED_BOOL Matrix4x4::IsIdentity( ) const
		{
			if( Arithmetic::Equal( m_M[ 0 ], 1.0f ) &&
				Arithmetic::IsZero( m_M[ 1 ] ) &&
				Arithmetic::IsZero( m_M[ 2 ] ) &&
				Arithmetic::IsZero( m_M[ 3 ] ) &&
				Arithmetic::IsZero( m_M[ 4 ] ) &&
				Arithmetic::Equal( m_M[ 5 ], 1.0f ) &&
				Arithmetic::IsZero( m_M[ 6 ] ) &&
				Arithmetic::IsZero( m_M[ 7 ] ) &&
				Arithmetic::IsZero( m_M[ 8 ] ) &&
				Arithmetic::IsZero( m_M[ 9 ] ) &&
				Arithmetic::Equal( m_M[ 10 ], 1.0f ) &&
				Arithmetic::IsZero( m_M[ 11 ] ) &&
				Arithmetic::IsZero( m_M[ 12 ] ) &&
				Arithmetic::IsZero( m_M[ 13 ] ) &&
				Arithmetic::IsZero( m_M[ 14 ] ) &&
				Arithmetic::Equal( m_M[ 15 ], 1.0f ) )
			{
				return ZED_TRUE;
			}
			return ZED_FALSE;
		}

		void Matrix4x4::SetRows( const Vector4 &p_Row1, const Vector4 &p_Row2,
			const Vector4 &p_Row3, const Vector4 &p_Row4 )
		{
			m_M[ 0 ] = p_Row1[ 0 ];
			m_M[ 4 ] = p_Row1[ 1 ];
			m_M[ 8 ] = p_Row1[ 2 ];
			m_M[ 12 ] = p_Row1[ 3 ];

			m_M[ 1 ] = p_Row2[ 0 ];
			m_M[ 5 ] = p_Row2[ 1 ];
			m_M[ 9 ] = p_Row2[ 2 ];
			m_M[ 13 ] = p_Row2[ 3 ];
			
			m_M[ 2 ] = p_Row3[ 0 ];
			m_M[ 6 ] = p_Row3[ 1 ];
			m_M[ 10 ] = p_Row3[ 2 ];
			m_M[ 14 ] = p_Row3[ 3 ];
			
			m_M[ 3 ] = p_Row4[ 0 ];
			m_M[ 7 ] = p_Row4[ 1 ];
			m_M[ 11 ] = p_Row4[ 2 ];
			m_M[ 15 ] = p_Row4[ 3 ];
		}

		void Matrix4x4::GetRows( Vector4 &p_Row1, Vector4 &p_Row2,
			Vector4 &p_Row3, Vector4 &p_Row4 ) const
		{
			p_Row1[ 0 ] = m_M[ 0 ];
			p_Row1[ 1 ] = m_M[ 4 ];
			p_Row1[ 2 ] = m_M[ 8 ];
			p_Row1[ 3 ] = m_M[ 12 ];

			p_Row2[ 0 ] = m_M[ 1 ];
			p_Row2[ 1 ] = m_M[ 5 ];
			p_Row2[ 2 ] = m_M[ 9 ];
			p_Row2[ 3 ] = m_M[ 13 ];

			p_Row3[ 0 ] = m_M[ 2 ];
			p_Row3[ 1 ] = m_M[ 6 ];
			p_Row3[ 2 ] = m_M[ 10 ];
			p_Row3[ 3 ] = m_M[ 14 ];

			p_Row4[ 0 ] = m_M[ 3 ];
			p_Row4[ 1 ] = m_M[ 7 ];
			p_Row4[ 2 ] = m_M[ 11 ];
			p_Row4[ 3 ] = m_M[ 15 ];
		}

		void Matrix4x4::GetRow( const ZED_MEMSIZE p_Index,
			Vector4 &p_Row ) const
		{
			p_Row.Set(	m_M[ p_Index ],
						m_M[ p_Index+4 ],
						m_M[ p_Index+8 ],
						m_M[ p_Index+12 ] );
		}

		void Matrix4x4::SetColumns( const Vector4 &p_Column1,
			const Vector4 &p_Column2, const Vector4 &p_Column3,
			const Vector4 &p_Column4 )
		{
			m_M[ 0 ] = p_Column1[ 0 ];
			m_M[ 1 ] = p_Column1[ 1 ];
			m_M[ 2 ] = p_Column1[ 2 ];
			m_M[ 3 ] = p_Column1[ 3 ];

			m_M[ 4 ] = p_Column2[ 0 ];
			m_M[ 5 ] = p_Column2[ 1 ];
			m_M[ 6 ] = p_Column2[ 2 ];
			m_M[ 7 ] = p_Column2[ 3 ];

			m_M[ 8 ] = p_Column3[ 0 ];
			m_M[ 9 ] = p_Column3[ 1 ];
			m_M[ 10 ] = p_Column3[ 2 ];
			m_M[ 11 ] = p_Column3[ 3 ];

			m_M[ 12 ] = p_Column4[ 0 ];
			m_M[ 13 ] = p_Column4[ 1 ];
			m_M[ 14 ] = p_Column4[ 2 ];
			m_M[ 15 ] = p_Column4[ 3 ];
		}

		void Matrix4x4::GetColumns( Vector4 &p_Column1, Vector4 &p_Column2,
			Vector4 &p_Column3, Vector4 &p_Column4 ) const
		{
			p_Column1[ 0 ] = m_M[ 0 ];
			p_Column1[ 1 ] = m_M[ 1 ];
			p_Column1[ 2 ] = m_M[ 2 ];
			p_Column1[ 3 ] = m_M[ 3 ];

			p_Column2[ 0 ] = m_M[ 4 ];
			p_Column2[ 1 ] = m_M[ 5 ];
			p_Column2[ 2 ] = m_M[ 6 ];
			p_Column2[ 3 ] = m_M[ 7 ];

			p_Column3[ 0 ] = m_M[ 8 ];
			p_Column3[ 1 ] = m_M[ 9 ];
			p_Column3[ 2 ] = m_M[ 10 ];
			p_Column3[ 3 ] = m_M[ 11 ];

			p_Column4[ 0 ] = m_M[ 12 ];
			p_Column4[ 1 ] = m_M[ 13 ];
			p_Column4[ 2 ] = m_M[ 14 ];
			p_Column4[ 3 ] = m_M[ 15 ];
		}

		void Matrix4x4::GetColumn( const ZED_MEMSIZE p_Index,
			Vector4 &p_Column ) const
		{
			ZED_MEMSIZE Offset = p_Index*4;

			p_Column.Set(	m_M[ Offset ],
							m_M[ Offset+1 ],
							m_M[ Offset+2 ],
							m_M[ Offset+3 ] );
		}

		void Matrix4x4::Clean( )
		{
			for( ZED_MEMSIZE i = 0; i < 16; i++ )
			{
				if( Arithmetic::IsZero( m_M[ i ] ) )
				{
					m_M[ i ] = 0.0f;
				}
			}
		}

		Matrix4x4 &Matrix4x4::Transpose( )
		{
			ZED_FLOAT32 Temp = m_M[ 1 ];
			m_M[ 1 ] = m_M[ 4 ];
			m_M[ 4 ] = Temp;

			Temp = m_M[ 2 ];
			m_M[ 2 ] = m_M[ 8 ];
			m_M[ 8 ] = Temp;

			Temp = m_M[ 3 ];
			m_M[ 3 ] = m_M[ 12 ];
			m_M[ 12 ] = Temp;

			Temp = m_M[ 6 ];
			m_M[ 6 ] = m_M[ 9 ];
			m_M[ 9 ] = Temp;

			Temp = m_M[ 7 ];
			m_M[ 7 ] = m_M[ 10 ];
			m_M[ 10 ] = Temp;

			Temp = m_M[ 11 ];
			m_M[ 11 ] = m_M[ 14 ];
			m_M[ 14 ] = Temp;

			return *this;
		}

		void Matrix4x4::Transpose( Matrix4x4 &p_Matrix ) const
		{
			p_Matrix[ 0 ] = m_M[ 0 ];
			p_Matrix[ 1 ] = m_M[ 4 ];
			p_Matrix[ 2 ] = m_M[ 8 ];
			p_Matrix[ 3 ] = m_M[ 12 ];

			p_Matrix[ 4 ] = m_M[ 1 ];
			p_Matrix[ 5 ] = m_M[ 5 ];
			p_Matrix[ 6 ] = m_M[ 9 ];
			p_Matrix[ 7 ] = m_M[ 13 ];

			p_Matrix[ 8 ] = m_M[ 2 ];
			p_Matrix[ 9 ] = m_M[ 6 ];
			p_Matrix[ 10 ] = m_M[ 10 ];
			p_Matrix[ 11 ] = m_M[ 14 ];

			p_Matrix[ 12 ] = m_M[ 3 ];
			p_Matrix[ 13 ] = m_M[ 7 ];
			p_Matrix[ 14 ] = m_M[ 11 ];
			p_Matrix[ 15 ] = m_M[ 15 ];
		}

		Matrix4x4 &Matrix4x4::TransposeOf( const Matrix4x4 &p_Transpose )
		{
			p_Transpose.Transpose( *this );

			return *this;
		}

		Matrix4x4 &Matrix4x4::AffineInverse( )
		{
			// 0 4 8  12
			// 1 5 9  13
			// 2 6 10 14
			// 3 7 11 15
			ZED_FLOAT32 CoFactor0 = m_M[ 5 ]*m_M[ 10 ] - m_M[ 6 ]*m_M[ 9 ];
			ZED_FLOAT32 CoFactor4 = m_M[ 2 ]*m_M[ 9 ] - m_M[ 1 ]*m_M[ 10 ];
			ZED_FLOAT32 CoFactor8 = m_M[ 1 ]*m_M[ 6 ] - m_M[ 2 ]*m_M[ 5 ];
			
			ZED_FLOAT32 Determinate = m_M[ 0 ]*CoFactor0 + m_M[ 4 ]*CoFactor4 +
				m_M[ 8 ]*CoFactor8;

			if( ZED::Arithmetic::IsZero( Determinate ) )
			{
				zedTrace( "[ZED::Arithmetic::Matrix4x4::AffineInverse][self] "
					"<WARN> Matrix is singular\n" );
				zedAssert( ZED_FALSE );

				return *this;
			}

			ZED_FLOAT32 InvDet = 1.0f / Determinate;

			Matrix4x4 Temp;

			Temp.m_M[ 0 ] = InvDet * CoFactor0;
			Temp.m_M[ 1 ] = InvDet * CoFactor4;
			Temp.m_M[ 2 ] = InvDet * CoFactor8;

			Temp.m_M[ 4 ] = InvDet*( m_M[ 6 ]*m_M[ 8 ] - m_M[ 4 ]*m_M[ 10 ] );
			Temp.m_M[ 5 ] = InvDet*( m_M[ 0 ]*m_M[ 10 ] - m_M[ 2 ]*m_M[ 8 ] );
			Temp.m_M[ 6 ] = InvDet*( m_M[ 2 ]*m_M[ 4 ] - m_M[ 0 ]*m_M[ 6 ] );

			Temp.m_M[ 8 ] = InvDet*( m_M[ 4 ]*m_M[ 9 ] - m_M[ 5 ]*m_M[ 8 ] );
			Temp.m_M[ 9 ] = InvDet*( m_M[ 1 ]*m_M[ 8 ] - m_M[ 0 ]*m_M[ 9 ] );
			Temp.m_M[ 10 ] = InvDet*( m_M[ 0 ]*m_M[ 5 ] - m_M[ 1 ]*m_M[ 4 ] );

			Temp.m_M[ 12 ] = -Temp.m_M[ 0 ]*m_M[ 12 ] -
							 Temp.m_M[ 4 ]*m_M[ 13 ] -
							 Temp.m_M[ 8 ]*m_M[ 14 ];
			Temp.m_M[ 13 ] = -Temp.m_M[ 1 ]*m_M[ 12 ] -
							 Temp.m_M[ 5 ]*m_M[ 13 ] -
							 Temp.m_M[ 9 ]*m_M[ 14 ];
			Temp.m_M[ 14 ] = -Temp.m_M[ 2 ]*m_M[ 12 ] -
							 Temp.m_M[ 6 ]*m_M[ 13 ] -
							 Temp.m_M[ 10 ]*m_M[ 14 ];

			*this = Temp;

			return *this;
		}

		void Matrix4x4::AffineInverse( Matrix4x4 &p_Matrix ) const
		{
			ZED_FLOAT32 CoFactor0 = m_M[ 5 ]*m_M[ 10 ] - m_M[ 6 ]*m_M[ 9 ];
			ZED_FLOAT32 CoFactor4 = m_M[ 2 ]*m_M[ 9 ] - m_M[ 1 ]*m_M[ 10 ];
			ZED_FLOAT32 CoFactor8 = m_M[ 1 ]*m_M[ 6 ] - m_M[ 2 ]*m_M[ 5 ];

			ZED_FLOAT32 Determinate = m_M[ 0 ]*CoFactor0 + m_M[ 4 ]*CoFactor4 +
				m_M[ 8 ]*CoFactor8;

			if( ZED::Arithmetic::IsZero( Determinate ) )
			{
				zedTrace( "[ZED::Arithmetic::Matrix4x4::AffineInverse] "
					"<WARN> Matrix is singular\n" );
				zedAssert( ZED_FALSE );

				return;
			}

			ZED_FLOAT32 InvDet = 1.0f / Determinate;

			p_Matrix.m_M[ 0 ] = InvDet * CoFactor0;
			p_Matrix.m_M[ 1 ] = InvDet * CoFactor4;
			p_Matrix.m_M[ 2 ] = InvDet * CoFactor8;
			p_Matrix.m_M[ 3 ] = 0.0f;


			p_Matrix.m_M[ 4 ] = InvDet * ( m_M[ 6 ] * m_M[ 8 ] -
									m_M[ 4 ] * m_M[ 10 ] );
			p_Matrix.m_M[ 5 ] = InvDet * ( m_M[ 0 ] * m_M[ 10 ] -
									m_M[ 2 ] * m_M[ 8 ] );
			p_Matrix.m_M[ 6 ] = InvDet * ( m_M[ 2 ] * m_M[ 4 ] -
									m_M[ 0 ] * m_M[ 6 ] );
			p_Matrix.m_M[ 7 ] = 0.0f;


			p_Matrix.m_M[ 8 ] = InvDet * ( m_M[ 4 ] * m_M[ 9 ] -
									m_M[ 5 ] * m_M[ 8 ] );
			p_Matrix.m_M[ 9 ] = InvDet * ( m_M[ 1 ] * m_M[ 8 ] -
									m_M[ 0 ] * m_M[ 9 ] );
			p_Matrix.m_M[ 10 ] = InvDet * ( m_M[ 0 ] * m_M[ 5 ] -
									m_M[ 1 ] * m_M[ 4 ] );
			p_Matrix.m_M[ 11 ] = 0.0f;


			p_Matrix.m_M[ 12 ] = -p_Matrix.m_M[ 0 ] * m_M[ 12 ] -
								 p_Matrix.m_M[ 4 ] * m_M[ 13 ] -
								 p_Matrix.m_M[ 8 ] * m_M[ 14 ];
			p_Matrix.m_M[ 13 ] = -p_Matrix.m_M[ 1 ] * m_M[ 12 ] -
								 p_Matrix.m_M[ 5 ] * m_M[ 13 ] -
								 p_Matrix.m_M[ 9 ] * m_M[ 14 ];
			p_Matrix.m_M[ 14 ] = -p_Matrix[ 2 ] * m_M[ 12 ] -
								 p_Matrix.m_M[ 6 ] * m_M[ 13 ] -
								 p_Matrix.m_M[ 10 ] * m_M[ 14 ];
			p_Matrix.m_M[ 15 ] = 1.0f;
		}

		Matrix4x4 &Matrix4x4::Translate( const Vector3 &p_Translate )
		{
			m_M[ 0 ] = 1.0f;
			m_M[ 1 ] = m_M[ 2 ] = m_M[ 3 ] = m_M[ 4 ] = 0.0f;
			m_M[ 5 ] = 1.0f;
			m_M[ 6 ] = m_M[ 7 ] = m_M[ 8 ] = m_M[ 9 ] = 0.0f;
			m_M[ 10 ] = 1.0f;
			m_M[ 11 ] =  0.0f;
			m_M[ 12 ] = p_Translate[ 0 ];
			m_M[ 13 ] = p_Translate[ 1 ];
			m_M[ 14 ] = p_Translate[ 2 ];
			m_M[ 15 ] = 1.0f;

			return *this;
		}

		Matrix4x4 &Matrix4x4::AffineInverseOf(
			const Matrix4x4 &p_AffineInverse )
		{
			p_AffineInverse.AffineInverse( *this );

			return *this;
		}

		Vector3 Matrix4x4::Transform( const Vector3 &p_Point ) const
		{
			Vector3 Transform;

			Transform[ 0 ] =	m_M[ 0 ]*p_Point[ 0 ] +
								m_M[ 4 ]*p_Point[ 1 ] +
								m_M[ 8 ]*p_Point[ 2 ] +
								m_M[ 12 ];

			Transform[ 1 ] =	m_M[ 1 ]*p_Point[ 0 ] +
								m_M[ 5 ]*p_Point[ 1 ] +
								m_M[ 9 ]*p_Point[ 2 ] +
								m_M[ 13 ];

			Transform[ 2 ] =	m_M[ 2 ]*p_Point[ 0 ] +
								m_M[ 6 ]*p_Point[ 1 ] +
								m_M[ 10 ]*p_Point[ 2 ] +
								m_M[ 14 ];

			return Transform;			
		}

		ZED_FLOAT32 Matrix4x4::Trace( ) const
		{
			return ( m_M[ 0 ] + m_M[ 5 ] + m_M[ 10 ] + m_M[ 15 ] );
		}

		System::Writer &operator<<( System::Writer &p_Out,
			const Matrix4x4 &p_Source )
		{
			for( ZED_MEMSIZE i = 0; i < 4; i++ )
			{
				p_Out << "| " << p_Source[ i ] << " " << 
					p_Source[ i+4 ] << " " << p_Source[ i+8 ] <<
					" " << p_Source[ i+12 ] << " |" << std::endl;
			}

			return p_Out;
		}

		ZED_BOOL Matrix4x4::operator==( const Matrix4x4 &p_Other ) const
		{
			for( ZED_MEMSIZE i = 0; i < 16; i++ )
			{
				if( !Arithmetic::Equal( m_M[ i ], p_Other[ i ] ) )
				{
					return ZED_FALSE;
				}
			}
			return ZED_TRUE;
		}

		ZED_BOOL Matrix4x4::operator!=( const Matrix4x4 &p_Other ) const
		{
			for( ZED_MEMSIZE i = 0; i < 16; i++ )
			{
				if( Arithmetic::Equal( m_M[ i ], p_Other[ i ] ) )
				{
					return ZED_TRUE;
				}
			}
			return ZED_FALSE;
		}

		Matrix4x4 Matrix4x4::operator+( const Matrix4x4 &p_Other ) const
		{
			Matrix4x4 Matrix;

			Matrix[ 0 ] = m_M[ 0 ]+p_Other[ 0 ];
			Matrix[ 1 ] = m_M[ 1 ]+p_Other[ 1 ];
			Matrix[ 2 ] = m_M[ 2 ]+p_Other[ 2 ];
			Matrix[ 3 ] = m_M[ 3 ]+p_Other[ 3 ];
			Matrix[ 4 ] = m_M[ 4 ]+p_Other[ 4 ];
			Matrix[ 5 ] = m_M[ 5 ]+p_Other[ 5 ];
			Matrix[ 6 ] = m_M[ 6 ]+p_Other[ 6 ];
			Matrix[ 7 ] = m_M[ 7 ]+p_Other[ 7 ];
			Matrix[ 8 ] = m_M[ 8 ]+p_Other[ 8 ];
			Matrix[ 9 ] = m_M[ 9 ]+p_Other[ 9 ];
			Matrix[ 10 ] = m_M[ 10 ]+p_Other[ 10 ];
			Matrix[ 11 ] = m_M[ 11 ]+p_Other[ 11 ];
			Matrix[ 12 ] = m_M[ 12 ]+p_Other[ 12 ];
			Matrix[ 13 ] = m_M[ 13 ]+p_Other[ 13 ];
			Matrix[ 14 ] = m_M[ 14 ]+p_Other[ 14 ];
			Matrix[ 15 ] = m_M[ 15 ]+p_Other[ 15 ];

			return Matrix;
		}

		Matrix4x4 Matrix4x4::operator-( const Matrix4x4 &p_Other ) const
		{
			Matrix4x4 Matrix;

			Matrix[ 0 ] = m_M[ 0 ]-p_Other[ 0 ];
			Matrix[ 1 ] = m_M[ 1 ]-p_Other[ 1 ];
			Matrix[ 2 ] = m_M[ 2 ]-p_Other[ 2 ];
			Matrix[ 3 ] = m_M[ 3 ]-p_Other[ 3 ];
			Matrix[ 4 ] = m_M[ 4 ]-p_Other[ 4 ];
			Matrix[ 5 ] = m_M[ 5 ]-p_Other[ 5 ];
			Matrix[ 6 ] = m_M[ 6 ]-p_Other[ 6 ];
			Matrix[ 7 ] = m_M[ 7 ]-p_Other[ 7 ];
			Matrix[ 8 ] = m_M[ 8 ]-p_Other[ 8 ];
			Matrix[ 9 ] = m_M[ 9 ]-p_Other[ 9 ];
			Matrix[ 10 ] = m_M[ 10 ]-p_Other[ 10 ];
			Matrix[ 11 ] = m_M[ 11 ]-p_Other[ 11 ];
			Matrix[ 12 ] = m_M[ 12 ]-p_Other[ 12 ];
			Matrix[ 13 ] = m_M[ 13 ]-p_Other[ 13 ];
			Matrix[ 14 ] = m_M[ 14 ]-p_Other[ 14 ];
			Matrix[ 15 ] = m_M[ 15 ]-p_Other[ 15 ];

			return Matrix;
		}

		Matrix4x4 Matrix4x4::operator-( ) const
		{
			Matrix4x4 Matrix;
			
			Matrix[ 0 ] = -m_M[ 0 ];
			Matrix[ 1 ] = -m_M[ 1 ];
			Matrix[ 2 ] = -m_M[ 2 ];
			Matrix[ 3 ] = -m_M[ 3 ];
			Matrix[ 4 ] = -m_M[ 4 ];
			Matrix[ 5 ] = -m_M[ 5 ];
			Matrix[ 6 ] = -m_M[ 6 ];
			Matrix[ 7 ] = -m_M[ 7 ];
			Matrix[ 8 ] = -m_M[ 8 ];
			Matrix[ 9 ] = -m_M[ 9 ];
			Matrix[ 10 ] = -m_M[ 10 ];
			Matrix[ 11 ] = -m_M[ 11 ];
			Matrix[ 12 ] = -m_M[ 12 ];
			Matrix[ 13 ] = -m_M[ 13 ];
			Matrix[ 14 ] = -m_M[ 14 ];
			Matrix[ 15 ] = -m_M[ 15 ];

			return Matrix;
		}

		Matrix4x4 Matrix4x4::operator*( const Matrix4x4 &p_Other ) const
		{
			Matrix4x4 Matrix;

			Matrix[ 0 ] =	( m_M[ 0 ]*p_Other[ 0 ] ) +
							( m_M[ 4 ]*p_Other[ 1 ] ) +
							( m_M[ 8 ]*p_Other[ 2 ] ) +
							( m_M[ 12 ]*p_Other[ 3 ] );
			Matrix[ 1 ] =	( m_M[ 1 ]*p_Other[ 0 ] ) +
							( m_M[ 5 ]*p_Other[ 1 ] ) +
							( m_M[ 9 ]*p_Other[ 2 ] ) +
							( m_M[ 13 ]*p_Other[ 3 ] );
			Matrix[ 2 ] =	( m_M[ 2 ]*p_Other[ 0 ] ) +
							( m_M[ 6 ]*p_Other[ 1 ] ) +
							( m_M[ 10 ]*p_Other[ 2 ] ) +
							( m_M[ 14 ]*p_Other[ 3 ] );
			Matrix[ 3 ] =	( m_M[ 3 ]*p_Other[ 0 ] ) +
							( m_M[ 6 ]*p_Other[ 1 ] ) +
							( m_M[ 11 ]*p_Other[ 2 ] ) +
							( m_M[ 15 ]*p_Other[ 3 ] );
			
			Matrix[ 4 ] =	( m_M[ 0 ]*p_Other[ 4 ] ) +
							( m_M[ 4 ]*p_Other[ 5 ] ) +
							( m_M[ 8 ]*p_Other[ 6 ] ) +
							( m_M[ 12 ]*p_Other[ 7 ] );
			Matrix[ 5 ] =	( m_M[ 1 ]*p_Other[ 4 ] ) +
							( m_M[ 5 ]*p_Other[ 5 ] ) +
							( m_M[ 9 ]*p_Other[ 6 ] ) +
							( m_M[ 13 ]*p_Other[ 7 ] );
			Matrix[ 6 ] =	( m_M[ 2 ]*p_Other[ 4 ] ) +
							( m_M[ 6 ]*p_Other[ 5 ] ) +
							( m_M[ 10 ]*p_Other[ 6 ] ) +
							( m_M[ 14 ]*p_Other[ 7 ] );
			Matrix[ 7 ] =	( m_M[ 3 ]*p_Other[ 4 ] ) +
							( m_M[ 7 ]*p_Other[ 5 ] ) +
							( m_M[ 11 ]*p_Other[ 6 ] ) +
							( m_M[ 15 ]*p_Other[ 7 ] );

			Matrix[ 8 ] =	( m_M[ 0 ]*p_Other[ 8 ] ) +
							( m_M[ 4 ]*p_Other[ 9 ] ) +
							( m_M[ 8 ]*p_Other[ 10 ] ) +
							( m_M[ 12 ]*p_Other[ 11 ] );
			Matrix[ 9 ] =	( m_M[ 1 ]*p_Other[ 8 ] ) +
							( m_M[ 5 ]*p_Other[ 9 ] ) +
							( m_M[ 9 ]*p_Other[ 10 ] ) +
							( m_M[ 13 ]*p_Other[ 11 ] );
			Matrix[ 10 ] =	( m_M[ 2 ]*p_Other[ 8 ] ) +
							( m_M[ 6 ]*p_Other[ 9 ] ) +
							( m_M[ 10 ]*p_Other[ 10 ] ) +
							( m_M[ 14 ]*p_Other[ 11 ] );
			Matrix[ 11 ] =	( m_M[ 3 ]*p_Other[ 8 ] ) +
							( m_M[ 7 ]*p_Other[ 9 ] ) +
							( m_M[ 11 ]*p_Other[ 10 ] ) +
							( m_M[ 15 ]*p_Other[ 11 ] );
			
			Matrix[ 12 ] =	( m_M[ 0 ]*p_Other[ 12 ] ) +
							( m_M[ 4 ]*p_Other[ 13 ] ) +
							( m_M[ 8 ]*p_Other[ 14 ] ) +
							( m_M[ 12 ]*p_Other[ 15 ] );
			Matrix[ 13 ] =	( m_M[ 1 ]*p_Other[ 12 ] ) +
							( m_M[ 5 ]*p_Other[ 13 ] ) +
							( m_M[ 9 ]*p_Other[ 14 ] ) +
							( m_M[ 13 ]*p_Other[ 15 ] );
			Matrix[ 14 ] =	( m_M[ 2 ]*p_Other[ 12 ] ) +
							( m_M[ 6 ]*p_Other[ 13 ] ) +
							( m_M[ 10 ]*p_Other[ 14 ] ) +
							( m_M[ 14 ]*p_Other[ 15 ] );
			Matrix[ 15 ] =	( m_M[ 3 ]*p_Other[ 12 ] ) +
							( m_M[ 7 ]*p_Other[ 13 ] ) +
							( m_M[ 11 ]*p_Other[ 14 ] ) +
							( m_M[ 15 ]*p_Other[ 15 ] );

			return Matrix;
		}

		Matrix4x4 Matrix4x4::operator*( const ZED_FLOAT32 p_Scalar ) const
		{
			Matrix4x4 Matrix;

			Matrix[ 0 ] = m_M[ 0 ]*p_Scalar;
			Matrix[ 1 ] = m_M[ 1 ]*p_Scalar;
			Matrix[ 2 ] = m_M[ 2 ]*p_Scalar;
			Matrix[ 3 ] = m_M[ 3 ]*p_Scalar;
			Matrix[ 4 ] = m_M[ 4 ]*p_Scalar;
			Matrix[ 5 ] = m_M[ 5 ]*p_Scalar;
			Matrix[ 6 ] = m_M[ 6 ]*p_Scalar;
			Matrix[ 7 ] = m_M[ 7 ]*p_Scalar;
			Matrix[ 8 ] = m_M[ 8 ]*p_Scalar;
			Matrix[ 9 ] = m_M[ 9 ]*p_Scalar;
			Matrix[ 10 ] = m_M[ 10 ]*p_Scalar;
			Matrix[ 11 ] = m_M[ 11 ]*p_Scalar;
			Matrix[ 12 ] = m_M[ 12 ]*p_Scalar;
			Matrix[ 13 ] = m_M[ 13 ]*p_Scalar;
			Matrix[ 14 ] = m_M[ 14 ]*p_Scalar;
			Matrix[ 15 ] = m_M[ 15 ]*p_Scalar;

			return Matrix;
		}

		Matrix4x4 operator*( const ZED_FLOAT32 p_Scalar,
			const Matrix4x4 &p_Matrix )
		{
			Matrix4x4 Matrix;

			Matrix[ 0 ] = p_Matrix[ 0 ]*p_Scalar;
			Matrix[ 1 ] = p_Matrix[ 1 ]*p_Scalar;
			Matrix[ 2 ] = p_Matrix[ 2 ]*p_Scalar;
			Matrix[ 3 ] = p_Matrix[ 3 ]*p_Scalar;
			Matrix[ 4 ] = p_Matrix[ 4 ]*p_Scalar;
			Matrix[ 5 ] = p_Matrix[ 5 ]*p_Scalar;
			Matrix[ 6 ] = p_Matrix[ 6 ]*p_Scalar;
			Matrix[ 7 ] = p_Matrix[ 7 ]*p_Scalar;
			Matrix[ 8 ] = p_Matrix[ 8 ]*p_Scalar;
			Matrix[ 9 ] = p_Matrix[ 9 ]*p_Scalar;
			Matrix[ 10 ] = p_Matrix[ 10 ]*p_Scalar;
			Matrix[ 11 ] = p_Matrix[ 11 ]*p_Scalar;
			Matrix[ 12 ] = p_Matrix[ 12 ]*p_Scalar;
			Matrix[ 13 ] = p_Matrix[ 13 ]*p_Scalar;
			Matrix[ 14 ] = p_Matrix[ 14 ]*p_Scalar;
			Matrix[ 15 ] = p_Matrix[ 15 ]*p_Scalar;

			return Matrix;
		}

		Vector4 Matrix4x4::operator*( const Vector4 &p_Vec ) const
		{
			Vector4 Vec;
			
			Vec[ 0 ] = m_M[ 0 ]*p_Vec[ 0 ] + m_M[ 4 ]*p_Vec[ 1 ] +
				m_M[ 8 ]*p_Vec[ 2 ] + m_M[ 12 ]*p_Vec[ 3 ];
			Vec[ 1 ] = m_M[ 1 ]*p_Vec[ 0 ] + m_M[ 5 ]*p_Vec[ 1 ] +
				m_M[ 9 ]*p_Vec[ 2 ] + m_M[ 13 ]*p_Vec[ 3 ];
			Vec[ 2 ] = m_M[ 2 ]*p_Vec[ 0 ] + m_M[ 6 ]*p_Vec[ 1 ] +
				m_M[ 10 ]*p_Vec[ 2 ] + m_M[ 14 ]*p_Vec[ 3 ];
			Vec[ 3 ] = m_M[ 3 ]*p_Vec[ 0 ] + m_M[ 7 ]*p_Vec[ 1 ] +
				m_M[ 11 ]*p_Vec[ 2 ] + m_M[ 15 ]*p_Vec[ 3 ];

			return Vec;
		}

		Vector4 operator*( const Vector4 &p_Vec, const Matrix4x4 &p_Matrix )
		{
			Vector4 Vec;

			Vec[ 0 ] = p_Vec[ 0 ]*p_Matrix[ 0 ] + p_Vec[ 1 ]*p_Matrix[ 1 ] +
				p_Vec[ 2 ]*p_Matrix[ 2 ] + p_Vec[ 3 ]*p_Matrix[ 3 ];
			Vec[ 1 ] = p_Vec[ 0 ]*p_Matrix[ 4 ] + p_Vec[ 1 ]*p_Matrix[ 5 ] +
				p_Vec[ 2 ]*p_Matrix[ 6 ] + p_Vec[ 3 ]*p_Matrix[ 7 ];
			Vec[ 2 ] = p_Vec[ 0 ]*p_Matrix[ 8 ] + p_Vec[ 1 ]*p_Matrix[ 9 ] +
				p_Vec[ 2 ]*p_Matrix[ 10 ] + p_Vec[ 3 ]*p_Matrix[ 11 ];
			Vec[ 3 ] = p_Vec[ 0 ]*p_Matrix[ 12 ] + p_Vec[ 1 ]*p_Matrix[ 13 ] +
				p_Vec[ 2 ]*p_Matrix[ 14 ] + p_Vec[ 3 ]*p_Matrix[ 15 ];

			return Vec;
		}

		Matrix4x4 &Matrix4x4::operator+=( const Matrix4x4 &p_Other )
		{
			m_M[ 0 ] += p_Other[ 0 ];
			m_M[ 1 ] += p_Other[ 1 ];
			m_M[ 2 ] += p_Other[ 2 ];
			m_M[ 3 ] += p_Other[ 3 ];
			m_M[ 4 ] += p_Other[ 4 ];
			m_M[ 5 ] += p_Other[ 5 ];
			m_M[ 6 ] += p_Other[ 6 ];
			m_M[ 7 ] += p_Other[ 7 ];
			m_M[ 8 ] += p_Other[ 8 ];
			m_M[ 9 ] += p_Other[ 9 ];
			m_M[ 10 ] += p_Other[ 10 ];
			m_M[ 11 ] += p_Other[ 11 ];
			m_M[ 12 ] += p_Other[ 12 ];
			m_M[ 13 ] += p_Other[ 13 ];
			m_M[ 14 ] += p_Other[ 14 ];
			m_M[ 15 ] += p_Other[ 15 ];

			return *this;
		}

		Matrix4x4 &Matrix4x4::operator-=( const Matrix4x4 &p_Other )
		{
			m_M[ 0 ] -= p_Other[ 0 ];
			m_M[ 1 ] -= p_Other[ 1 ];
			m_M[ 2 ] -= p_Other[ 2 ];
			m_M[ 3 ] -= p_Other[ 3 ];
			m_M[ 4 ] -= p_Other[ 4 ];
			m_M[ 5 ] -= p_Other[ 5 ];
			m_M[ 6 ] -= p_Other[ 6 ];
			m_M[ 7 ] -= p_Other[ 7 ];
			m_M[ 8 ] -= p_Other[ 8 ];
			m_M[ 9 ] -= p_Other[ 9 ];
			m_M[ 10 ] -= p_Other[ 10 ];
			m_M[ 11 ] -= p_Other[ 11 ];
			m_M[ 12 ] -= p_Other[ 12 ];
			m_M[ 13 ] -= p_Other[ 13 ];
			m_M[ 14 ] -= p_Other[ 14 ];
			m_M[ 15 ] -= p_Other[ 15 ];

			return *this;
		}

		Matrix4x4 &Matrix4x4::operator*=( const Matrix4x4 &p_Other )
		{
			m_M[ 0 ] = 1.0f;

			return *this;
		}

		Matrix4x4 &Matrix4x4::operator*=( const ZED_FLOAT32 p_Scalar )
		{
			m_M[ 0 ] *= p_Scalar;
			m_M[ 1 ] *= p_Scalar;
			m_M[ 2 ] *= p_Scalar;
			m_M[ 3 ] *= p_Scalar;
			m_M[ 4 ] *= p_Scalar;
			m_M[ 5 ] *= p_Scalar;
			m_M[ 6 ] *= p_Scalar;
			m_M[ 7 ] *= p_Scalar;
			m_M[ 8 ] *= p_Scalar;
			m_M[ 9 ] *= p_Scalar;
			m_M[ 10 ] *= p_Scalar;
			m_M[ 11 ] *= p_Scalar;
			m_M[ 12 ] *= p_Scalar;
			m_M[ 13 ] *= p_Scalar;
			m_M[ 14 ] *= p_Scalar;
			m_M[ 15 ] *= p_Scalar;

			return *this;
		}

		ZED_FLOAT32 &Matrix4x4::operator( )( const ZED_MEMSIZE p_Row,
			const ZED_MEMSIZE p_Column )
		{
			return ( m_M[ p_Row+( p_Column*4 ) ] );
		//	return ( m_M[ p_Column+( p_Row*4 ) ] );
		}

		ZED_FLOAT32 Matrix4x4::operator( )( const ZED_MEMSIZE p_Row,
			const ZED_MEMSIZE p_Column ) const
		{
			return ( m_M[ p_Row+( p_Column*4 ) ] );
		//	return ( m_M[ p_Column+( p_Row*4 ) ] );
		}
	}
}

