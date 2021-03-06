#ifndef __ZED_SYSTEM_INPUT_KEYBOARD_HPP__
#define __ZED_SYSTEM_INPUT_KEYBOARD_HPP__

#include <System/InputDevice.hpp>
#include <System/Debugger.hpp>
#include <cstring>

namespace ZED
{
	namespace System
	{
		class Keyboard : public InputDevice
		{
		public:
			Keyboard( );
			virtual ~Keyboard( ) { }

			virtual ZED_UINT32 State( void *p_pState ) const;

			virtual ZED_INLINE ZED_UINT32 Type( ) const
			{
				return ZED_INPUT_DEVICE_KEYBOARD;
			}

			ZED_INLINE ZED_BOOL IsKeyUp( const ZED_UINT32 p_Key ) const
				{ return ( m_Keys[ p_Key ] != 1 ); }
			ZED_INLINE ZED_BOOL IsKeyDown( const ZED_UINT32 p_Key ) const
				{ return ( m_Keys[ p_Key ] != 0 ); }
			
			ZED_INLINE void KeyUp( const ZED_UINT32 p_Key )
				{ m_Keys[ p_Key ] = 0; }
			ZED_INLINE void KeyDown( const ZED_UINT32 p_Key )
				{ m_Keys[ p_Key ] = 1; }

			ZED_INLINE void AllKeysUp( )
				{ memset( m_Keys, 0, sizeof( m_Keys ) ); }
			ZED_INLINE void AllKeysDown( )
				{ memset( m_Keys, 1, sizeof( m_Keys ) ); }

		private:
			char m_Keys[ 256 ];
			ZED_UINT32 m_KeyModifiers;
		};
	}
}

#endif // __ZED_SYSTEM_KEYBOARD_HPP__

