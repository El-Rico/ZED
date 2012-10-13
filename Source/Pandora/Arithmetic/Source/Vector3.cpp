#include <Vector3.hpp>

namespace ZED
{
	namespace Arithmetic
	{
		void Vector3::Normalise( )
		{
			ZED_FLOAT32 Mag = ( m_X*m_X )+( m_Y*m_Y )+( m_Z*m_Z );

			// Don't continue if the squared magnitude is zero
			if( ZED::Arithmetic::IsZero( Mag ) )
			{
				zedTrace( "[ZED::Arithmetic::Vector3::Normalise] <WARN> "
					"Magnitude is zero!\n" );
				Zero( );
			}
			else
			{
				ZED_FLOAT32 Factor = ZED::Arithmetic::InvSquareRoot( Mag );

				m_X *= Factor;
				m_Y *= Factor;
				m_Z *= Factor;
			}
		}

		ZED_FLOAT32 Vector3::Magnitude( ) const
		{
			return Arithmetic::SquareRoot( m_X*m_X + m_Y*m_Y + m_Z*m_Z );
		}

		ZED_FLOAT32 Vector3::MagnitudeSq( ) const
		{
			return ( m_X*m_X + m_Y*m_Y + m_Z*m_Z );
		}

		ZED_FLOAT32 Vector3::Distance( const Vector3 &p_Other ) const
		{
			ZED_FLOAT32 X, Y, Z;

			X = m_X - p_Other[ 0 ];
			Y = m_Y - p_Other[ 1 ];
			Z = m_Z - p_Other[ 2 ];

			return Arithmetic::InvSquareRoot( X*X + Y*Y + Z*Z );
		}

		ZED_FLOAT32 Vector3::DistanceSq( const Vector3 &p_Other ) const
		{
			ZED_FLOAT32 X, Y, Z;

			X = m_X - p_Other[ 0 ];
			Y = m_Y - p_Other[ 1 ];
			Z = m_Z - p_Other[ 2 ];

			return ( X*X + Y*Y + Z*Z );
		}

		void Vector3::Clean( )
		{
			if( Arithmetic::IsZero( m_X ) )
			{
				m_X = 0.0f;
			}

			if( Arithmetic::IsZero( m_Y ) )
			{
				m_Y = 0.0f;
			}

			if( Arithmetic::IsZero( m_Z ) )
			{
				m_Z = 0.0f;
			}
		}

		ZED_FLOAT32 Vector3::Dot( const Vector3 &p_Other ) const
		{	
			return ( m_X*p_Other[ 0 ] + m_Y*p_Other[ 1 ] + m_Z*p_Other[ 2 ] );
		}

		Vector3 Vector3::Cross( const Vector3 &p_Other ) const
		{
			return Vector3( ( m_Y*p_Other[ 2 ] - m_Z*p_Other[ 1 ] ),
							( m_Z*p_Other[ 0 ] - m_X*p_Other[ 2 ] ),
							( m_X*p_Other[ 1 ] - m_Y*p_Other[ 0 ] ) );
		}

		ZED::System::Writer &operator<<( ZED::System::Writer &p_Out,
			const Vector3 &p_Source )
		{
			p_Out << "< " <<p_Source[ 0 ] << " " << p_Source[ 1 ] << " "
				<< p_Source[ 2 ] << " >";

			return p_Out;
		}

		ZED_BOOL Vector3::operator==( const Vector3 &p_Other ) const
		{
			if( Arithmetic::Equal( m_X, p_Other[ 0 ] ) &&
				Arithmetic::Equal( m_Y, p_Other[ 1 ] ) &&
				Arithmetic::Equal( m_Z, p_Other[ 2 ] ) )
			{
				return ZED_TRUE;
			}

			return ZED_FALSE;
		}

		ZED_BOOL Vector3::operator!=( const Vector3 &p_Other ) const
		{
			if( !Arithmetic::Equal( m_X, p_Other[ 0 ] ) ||
				!Arithmetic::Equal( m_Y, p_Other[ 1 ] ) ||
				!Arithmetic::Equal( m_Z, p_Other[ 2 ] ) )
			{
				return ZED_TRUE;
			}

			return ZED_FALSE;
		}

		Vector3 Vector3::operator+( const Vector3 &p_Other ) const
		{
			return Vector3( m_X+p_Other[ 0 ], m_Y+p_Other[ 1 ],
				m_Z+p_Other[ 2 ] );
		}

		Vector3 Vector3::operator-( const Vector3 &p_Other ) const
		{
			return Vector3( m_X-p_Other[ 0 ], m_Y+p_Other[ 1 ],
				m_Z+p_Other[ 2 ] );
		}

		Vector3 Vector3::operator*( const Vector3 &p_Other ) const
		{
			return Vector3( m_X*p_Other[ 0 ], m_Y*p_Other[ 1 ],
				m_Z*p_Other[ 2 ] );
		}

		Vector3 Vector3::operator*( const ZED_FLOAT32 p_Scalar ) const
		{
			return Vector3( m_X*p_Scalar, m_Y*p_Scalar, m_Z*p_Scalar );
		}

		Vector3 operator*( const ZED_FLOAT32 p_Scalar, const Vector3 &p_Self )
		{
			return Vector3( p_Self[ 0 ]*p_Scalar, p_Self[ 1 ]*p_Scalar,
				p_Self[ 2 ]*p_Scalar );
		}

		Vector3 Vector3::operator/( const ZED_FLOAT32 p_Scalar ) const
		{
			// No divide-by-zero check!
			return Vector3( m_X/p_Scalar, m_Y/p_Scalar, m_Z/p_Scalar );
		}

		Vector3 &Vector3::operator+=( const Vector3 &p_Other )
		{
			m_X += p_Other[ 0 ];
			m_Y += p_Other[ 1 ];
			m_Z += p_Other[ 2 ];

			return *this;
		}

		Vector3 &Vector3::operator-=( const Vector3 &p_Other )
		{
			m_X -= p_Other[ 0 ];
			m_Y -= p_Other[ 1 ];
			m_Z -= p_Other[ 2 ];

			return *this;
		}

		Vector3 &Vector3::operator*=( const Vector3 &p_Other )
		{
			m_X *= p_Other[ 0 ];
			m_Y *= p_Other[ 1 ];
			m_Z *= p_Other[ 2 ];

			return *this;
		}

		Vector3 &Vector3::operator*=( const ZED_FLOAT32 p_Scalar )
		{
			m_X *= p_Scalar;
			m_Y *= p_Scalar;
			m_Z *= p_Scalar;

			return *this;
		}

		Vector3 &Vector3::operator/=( const ZED_FLOAT32 p_Scalar )
		{
			m_X /= p_Scalar;
			m_Y /= p_Scalar;
			m_Z /= p_Scalar;
			
			return *this;
		}
	}
}

