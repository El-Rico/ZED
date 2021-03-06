#ifndef __ZED_GAME_GAMESTATEMANAGER_HPP__
#define __ZED_GAME_GAMESTATEMANAGER_HPP__

#include <System/DataTypes.hpp>
#include <set>
#include <stack>

namespace ZED
{
	namespace Utility
	{
		class InputBinder;
	}
	namespace Renderer
	{
		class Renderer;
	}
	namespace Game
	{
		class GameState;
		class GameStateInputListener;

		const ZED_FLOAT64 OneOverMillion = 1.0d / 1000000.0d;

		class GameStateManager
		{
		public:
			GameStateManager( );
			virtual ~GameStateManager( );

			virtual ZED_UINT32 Initialise( );

			ZED_UINT32 Execute( );

			ZED_UINT32 RegisterState( GameState * const &p_pGameState );
			ZED_UINT32 GetNumberOfStates( ) const;
			ZED_CHAR8 * GetStateName( const ZED_UINT32 p_Index ) const;

			ZED_UINT32 ChangeState( const ZED_CHAR8 *p_pGameStateName,
				const ZED_UINT32 p_Level = 0 );

			ZED_UINT32 PushState( const ZED_CHAR8 *p_pGameStateName );
			void PopState( );

			ZED_UINT32 SetInputBinder(
				ZED::Utility::InputBinder * const &p_pInputBinder );

			void Quit( );
			ZED_BOOL IsRunning( ) const;

			ZED::Renderer::Renderer * const GetRenderer( );
			ZED_UINT32 SetRenderer(
				ZED::Renderer::Renderer * const &p_pRenderer );

			ZED_FLOAT64 GetTotalElapsedTimeAsFloat64( ) const;
			ZED_UINT64 GetTotalElapsedTimeAsUInt64( ) const;

			static GameStateManager &GetInstance( );

		protected:
			typedef std::stack< GameState * > GameStateStack;
			typedef std::set< GameState * > GameStateRegistry;

			ZED_BOOL IsGameStateNameValid(
				const ZED_CHAR8 *p_pGameStateName ) const;
			
			GameStateStack		m_GameStateStack;
			GameStateRegistry	m_GameStateRegistry;

			ZED::Renderer::Renderer	*m_pRenderer;
			GameStateInputListener	*m_pInputListener;

			ZED_UINT64	m_TotalElapsedTime;
			ZED_UINT64	m_StartTime;

			ZED_BOOL	m_Running;

			virtual ZED_UINT32 Update( const ZED_UINT64 p_TimeDelta );
			virtual ZED_UINT32 Render( );
		};
	}
}

#endif // __ZED_GAME_GAMESTATEMANAGER_HPP__
