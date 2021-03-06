#ifndef __ZED_UTILITY_EVENTROUTER_HPP__
#define __ZED_UTILITY_EVENTROUTER_HPP__

#include <System/DataTypes.hpp>
#include <System/Debugger.hpp>
#include <Utility/Event.hpp>
#include <set>
#include <queue>
#include <map>
#include <list>

namespace ZED
{
	namespace Utility
	{
		class Event;
		class EventRouter;

		// Helper typedefs
		typedef std::set< EventType > EventTypeSet;
		typedef std::pair< EventTypeSet::iterator, ZED_BOOL >
			EventTypeSetInsRes;
		typedef std::priority_queue< Event * > EventQueue;
		typedef std::list< EventListener * > EventListenerList;
		typedef std::map< ZED_UINT32, EventListenerList > EventListenerTypeMap;
		typedef std::pair< ZED_UINT32, EventListenerList >
			EventListenerTypeMapEntry;
		typedef std::pair< EventListenerTypeMap::iterator, ZED_BOOL >
			EventListenerTypeMapInsRes;

		extern EventRouter *g_pEventRouter;

		class EventRouter
		{
		public:
			ZED_EXPLICIT EventRouter( const ZED_CHAR8 * const p_pName,
				const ZED_BOOL p_Global, const ZED_UINT32 p_BufferCount );

			~EventRouter( );

			// Associate an event type with an event listener
			ZED_BOOL Add( EventListener * const &p_pListener,
				const EventType &p_Type );

			// Disassociate an event type from an event listener
			ZED_BOOL Remove( EventListener * const &p_pListener );

			// Broadcast an event
			ZED_BOOL Send( const Event &p_Event ); 

			// Add a delay to an event to be dispatched at a later date
			ZED_BOOL Queue( const Event &p_Event,
				const ZED_UINT64 p_DeliveryTime = 0UL );

			// Remove the last event of the event type, optionally removing all
			// of them
			ZED_BOOL Abort( const EventType &p_Type,
				const ZED_BOOL p_All = ZED_FALSE );

			// Process events given an amount of time to process them
			ZED_BOOL Process(
				const ZED_UINT64 p_MaxMicroSeconds =
					ZED::System::ZED_INFINITE_TIME );

			// Check if an event type has not lost its integrity
			ZED_BOOL ValidateType( const EventType &p_Type,
				ZED_UINT32 *p_pError ) const;

		private:
			static EventRouter *Get( ) { return g_pEventRouter; }

			friend ZED_INLINE ZED_BOOL AddEventListener(
				EventListener * const &p_pListener,
				const EventType &p_Type );
			friend ZED_INLINE ZED_BOOL RemoveEventListener(
				EventListener * const &p_pListener );
			friend ZED_INLINE ZED_BOOL SendEvent( const Event &p_Event );
			friend ZED_INLINE ZED_BOOL QueueEvent( const Event &p_Event,
				const ZED_UINT64 p_DeliveryTime = 0UL );
			friend ZED_INLINE ZED_BOOL AbortEvent( const EventType &p_Event,
				const ZED_BOOL p_All = ZED_FALSE );
			friend ZED_INLINE ZED_BOOL ProcessEvents(
				const ZED_UINT64 p_MaxMicroSeconds =
					ZED::System::ZED_INFINITE_TIME );
			friend ZED_INLINE ZED_BOOL ValidateEventType(
				const EventType &p_Type, ZED_UINT32 *p_pError );

			EventTypeSet			m_Types;
			EventQueue				*m_pQueue;
			EventListenerTypeMap	m_Registry;

			ZED_UINT32	m_BufferCount;
			ZED_UINT32	m_ActiveBuffer;

			ZED_CHAR8	*m_pName;
		};

		ZED_INLINE ZED_UINT32 SetGlobalEventRouter(
			EventRouter * const &p_pEventRouter )
		{
			if( p_pEventRouter )
			{
				g_pEventRouter = p_pEventRouter;
				return ZED_OK;
			}
			return ZED_FAIL;
		}

		ZED_INLINE ZED_BOOL AddEventListener(
			EventListener * const &p_pListener, const EventType &p_Type )
		{
#ifdef ZED_BUILD_DEBUG
			zedAssert( EventRouter::Get( ) );
#endif
			return EventRouter::Get( )->Add( p_pListener, p_Type );
		}

		ZED_INLINE ZED_BOOL RemoveEventListener(
			EventListener * const &p_pListener )
		{
#ifdef ZED_BUILD_DEBUG
			zedAssert( EventRouter::Get( ) );
#endif
			return EventRouter::Get( )->Remove( p_pListener );
		}

		ZED_INLINE ZED_BOOL SendEvent( const Event &p_Event )
		{
#ifdef ZED_BUILD_DEBUG
			zedAssert( EventRouter::Get( ) );
#endif
			return EventRouter::Get( )->Send( p_Event );
		}

		ZED_INLINE ZED_BOOL QueueEvent( const Event &p_Event,
			const ZED_UINT64 p_DeliveryTime )
		{
#ifdef ZED_BUILD_DEBUG
			zedAssert( EventRouter::Get( ) );
#endif
			return EventRouter::Get( )->Queue( p_Event, p_DeliveryTime );
		}

		ZED_INLINE ZED_BOOL AbortEvent( const EventType &p_Event,
			const ZED_BOOL p_All )
		{
#ifdef ZED_BUILD_DEBUG
			zedAssert( EventRouter::Get( ) );
#endif
			return EventRouter::Get( )->Abort( p_Event, p_All );
		}

		ZED_INLINE ZED_BOOL ProcessEvents( const ZED_UINT64 p_MaxMicroSeconds )
		{
#ifdef ZED_BUILD_DEBUG
			zedAssert( EventRouter::Get( ) );
#endif
			return EventRouter::Get( )->Process( p_MaxMicroSeconds );
		}

		ZED_INLINE ZED_BOOL ValidateEventType( const EventType &p_Type,
			ZED_UINT32 *p_pError )
		{
#ifdef ZED_BUILD_DEBUG
			zedAssert( EventRouter::Get( ) );
#endif
			return EventRouter::Get( )->ValidateType( p_Type, p_pError );
		}
	}
}

#endif

