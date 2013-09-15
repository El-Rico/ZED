#include <System/WindowsWindow.hpp>
#include <System/Debugger.hpp>

namespace ZED
{
	namespace System
	{
		ZED_UINT32 GetNativeScreenSize( const ZED_UINT32 p_DisplayNumber,
			const ZED_UINT32 p_ScreenNumber, ZED_SCREENSIZE &p_ScreenSize )
		{
			DISPLAY_DEVICE Display;
			DEVMODE DevMode;

			memset( &DevMode, 0, sizeof( DevMode ) );
			memset( &Display, 0, sizeof( Display ) );

			Display.cb = sizeof( Display );
			DevMode.dmSize = sizeof( DevMode );

			if( !EnumDisplayDevices( NULL, p_DisplayNumber, &Display, 0 ) )
			{
				zedTrace( "[ZED::System::GetNativeScreenSiz] <ERROR> "
					"Failed to enumerate display device\n" );

				return ZED_FAIL;
			}

			if( !EnumDisplayDevices( Display.DeviceName, p_ScreenNumber,
				&Display, 0 ) )
			{
				zedTrace( "[ZED::System::GetNativeScreenSize] <ERROR> "
					"Failed to enumerate screen\n" );
				return ZED_FAIL;
			}

			if( !EnumDisplaySettingsEx( Display.DeviceName,
				ENUM_CURRENT_SETTINGS, &DevMode, 0 ) )
			{
				zedTrace( "[ZED::System::GetNativeScreenSize] <ERROR> "
					"Failed to enumerate display settings\n" );

				return ZED_FAIL;
			}

			p_ScreenSize.Width = DevMode.dmPelsWidth;
			p_ScreenSize.Height = DevMode.dmPelsHeight;

			return ZED_OK;
		}

		ZED_UINT32 GetDisplayCount( ZED_UINT32 *p_pDisplayCount )
		{
			DISPLAY_DEVICE Display;
			memset( &Display, 0, sizeof( Display ) );
			Display.cb = sizeof( Display );
			ZED_UINT32 DeviceNum = 0;
			while( EnumDisplayDevices( NULL, DeviceNum, &Display, 0 ) )
			{
				++DeviceNum;
			}

			( *p_pDisplayCount ) = DeviceNum;

			return ZED_OK;
		}

		ZED_UINT32 GetScreenCount( const ZED_UINT32 p_DisplayNumber,
			ZED_UINT32 *p_pScreenCount )
		{
			ZED_UINT32 ScreenCount = 0;
			TCHAR DisplayName[ 32 ];
			DISPLAY_DEVICE Display;
			memset( &Display, 0, sizeof( Display ) );
			Display.cb = sizeof( Display );
			memset( DisplayName, '\0', sizeof( DisplayName ) );

			// Get the display name to use for enumerating the screen count
			if( !EnumDisplayDevices( NULL, p_DisplayNumber, &Display, 0 ) )
			{
				zedTrace( "[ZED::System::GetScreenCount] <ERROR> "
					"Failed to enumerate the display\n" );
				return ZED_FAIL;
			}

			memcpy( DisplayName, Display.DeviceName,
				sizeof( Display.DeviceName ) );

			// Now get the amount of screens
			while( EnumDisplayDevices( DisplayName, ScreenCount, &Display,
				0 ) )
			{
				++ScreenCount;
			}

			( *p_pScreenCount ) = ScreenCount;

			return ZED_OK;
		}

		ZED_UINT32 GetScreenOrientation( const ZED_UINT32 p_DisplayNumber,
			const ZED_UINT32 p_ScreenNumber,
			ZED_SCREEN_ORIENTATION *p_pOrientation )
		{
			DISPLAY_DEVICE Display;
			DEVMODE DevMode;

			memset( &DevMode, 0, sizeof( DevMode ) );
			memset( &Display, 0, sizeof( Display ) );

			Display.cb = sizeof( Display );
			DevMode.dmSize = sizeof( DevMode );

			if( !EnumDisplayDevices( NULL, p_DisplayNumber, &Display, 0 ) )
			{
				zedTrace( "[ZED::System::GetScreenOrientation] <ERROR> "
					"Failed to get display device\n" );
				
				return ZED_FAIL;
			}

			if( !EnumDisplayDevices( Display.DeviceName, p_ScreenNumber,
				&Display, 0 ) )
			{
				zedTrace( "[ZED::System::GetScreenOrientation] <ERROR> "
					"Failed to enumerate screen device\n" );

				return ZED_FAIL;
			}

			if( !EnumDisplaySettingsEx( Display.DeviceName,
				ENUM_CURRENT_SETTINGS, &DevMode, 0 ) )
			{
				zedTrace( "[ZED::System::GetScreenOrientation] <ERROR> "
					"Failed to enumerate display settings\n" );

				return ZED_FAIL;
			}

			switch( DevMode.dmDisplayOrientation )
			{
				case DMDO_DEFAULT:
				{
					( *p_pOrientation ) = ZED_SCREEN_ORIENTATION_0;
					break;
				}
				case DMDO_90:
				{
					( *p_pOrientation ) = ZED_SCREEN_ORIENTATION_90;
					break;
				}
				case DMDO_180:
				{
					( *p_pOrientation ) = ZED_SCREEN_ORIENTATION_180;
					break;
				}
				case DMDO_270:
				{
					( *p_pOrientation ) = ZED_SCREEN_ORIENTATION_270;
					break;
				}
				default:
				{
					zedTrace( "[ZED::System::GetScreenOrientation] <ERROR> "
						"Failed to get valid screen orientation\n" );
					return ZED_FAIL;
				}
			}

			return ZED_OK;
		}
	}
}

