#ifndef __ZED_SYSTEM_INPUT_KEYBOARD_HPP__
#define __ZED_SYSTEM_INPUT_KEYBOARD_HPP__

#include <InputDevice.hpp>

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

			virtual ZED_INLINE ZED_INPUT_DEVICE_TYPE Type( ) const
			{
				return ZED_INPUT_DEVICE_KEYBOARD;
			}

			ZED_INLINE ZED_BOOL KeyUp( const ZED_UINT32 p_Key ) const
				{ return ( m_Keys[ p_Key ] != 0 ); }
			ZED_INLINE ZED_BOOL KeyDown( const ZED_UINT32 p_Key ) const
				{ return ( m_Keys[ p_Key ] != 1 ); }

			ZED_INLINE void KeyUp( const ZED_UINT32 p_Key )
				{ m_Keys[ p_Key ] = 1; }
			ZED_INLINE void KeyDown( const ZED_UINT32 p_Key )
				{ m_Keys[ p_Key ] = 0; }

		private:
			char m_Keys[ 128 ];
		};
	}
}

#endif

