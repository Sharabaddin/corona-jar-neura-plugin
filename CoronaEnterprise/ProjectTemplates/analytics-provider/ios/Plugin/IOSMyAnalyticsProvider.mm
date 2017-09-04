//
//  IOSMyAnalyticsProvider.mm
//  AnalyticsProvider Plugin
//
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#include "IOSMyAnalyticsProvider.h"

#include "CoronaAssert.h"
#include "CoronaEvent.h"
#include "CoronaLibrary.h"

#import <Foundation/Foundation.h>
#import "CoronaRuntime.h"

// ----------------------------------------------------------------------------

CORONA_EXPORT
int luaopen_CoronaProvider_analytics_myAnalyticsProvider( lua_State *L )
{
	return Corona::IOSMyAnalyticsProvider::Open( L );
}

// ----------------------------------------------------------------------------

namespace Corona
{

// ----------------------------------------------------------------------------

// TODO: Rename.
const char IOSMyAnalyticsProvider::kName[] = "CoronaProvider.analytics.myAnalyticsProvider";

// TODO: Rename. Should correspond to kName above
static const char kProviderName[] = "myAnalyticsProvider";

// TODO: Rename.
static const char kPublisherId[] = "com.mycompany";

int
IOSMyAnalyticsProvider::Open( lua_State *L )
{
	void *platformContext = CoronaLuaGetContext( L ); // lua_touserdata( L, lua_upvalueindex( 1 ) );
	id<CoronaRuntime> runtime = (id<CoronaRuntime>)platformContext;

	const char *name = lua_tostring( L, 1 ); CORONA_ASSERT( 0 == strcmp( name, kName ) );
	int result = CoronaLibraryProviderNew( L, "analytics", name, kPublisherId );

	if ( result )
	{
		const luaL_Reg kFunctions[] =
		{
			{ "init", Self::Init },
			{ "logEvent", Self::LogEvent },

			{ NULL, NULL }
		};

		CoronaLuaInitializeGCMetatable( L, kName, Finalizer );

		// Use 'provider' in closure for kFunctions
		Self *provider = new Self( runtime );
		CoronaLuaPushUserdata( L, provider, kName );
		luaL_openlib( L, NULL, kFunctions, 1 );
	}

	return result;
}

int
IOSMyAnalyticsProvider::Finalizer( lua_State *L )
{
	Self *provider = (Self *)CoronaLuaToUserdata( L, 1 );
	delete provider;
	return 0;
}

IOSMyAnalyticsProvider *
IOSMyAnalyticsProvider::GetSelf( lua_State *L )
{
	return (Self *)CoronaLuaToUserdata( L, lua_upvalueindex( 1 ) );
}

// analytics.init( providerName, appId )
int
IOSMyAnalyticsProvider::Init( lua_State *L )
{
	Self *provider = GetSelf( L );

	const char *appId = lua_tostring( L, 2 );

	bool success = provider->Init( L, appId );
	lua_pushboolean( L, success );

	return 1;
}

// analytics.logEvent( eventId [, params] )
int
IOSMyAnalyticsProvider::LogEvent( lua_State *L )
{
	Self *provider = GetSelf( L );

	const char *eventId = luaL_checkstring( L, 1 );
	if ( eventId )
	{
		int paramsIndex = 2;

		provider->LogEvent( L, eventId, paramsIndex );
	}
	
	return 1;
}

// ----------------------------------------------------------------------------

IOSMyAnalyticsProvider::IOSMyAnalyticsProvider( id<CoronaRuntime> runtime )
:	fRuntime( runtime ),
	fAppId( nil )
{
}

IOSMyAnalyticsProvider::~IOSMyAnalyticsProvider()
{
	[fAppId release];
}

bool
IOSMyAnalyticsProvider::Init( lua_State *L, const char *appId )
{
	bool result = false;

	if ( appId )
	{
		fAppId = [[NSString alloc] initWithUTF8String:appId];

		// TODO: Add call to provider's API to initialize service
		NSLog( @"[WARNING] Unimplemented method analytics.init(%@)", fAppId );

		result = true;
	}

	return result;
}

// Convert to string, but avoid implicit Lua conversion which confuses lua_next
static NSString *
ToNSString( lua_State *L, int index )
{
	NSString *result = nil;

	int t = lua_type( L, -2 );
	switch ( t )
	{
		case LUA_TNUMBER:
			result = [NSString stringWithFormat:@"%g", lua_tonumber( L, index )];
			break;
		default:
			result = [NSString stringWithUTF8String:lua_tostring( L, index )];
			break;
	}

	return result;
}

void
IOSMyAnalyticsProvider::LogEvent( lua_State *L, const char *eventId, int paramsIndex )
{
	CORONA_ASSERT( eventId );

	if ( fAppId )
	{
		NSString *str = [NSString stringWithUTF8String:eventId];

		if ( lua_istable( L, paramsIndex ) )
		{
			const int kMaxParams = 10;
			NSMutableDictionary *params = [NSMutableDictionary dictionaryWithCapacity:kMaxParams];

			// Iterate through table
			paramsIndex = CoronaLuaNormalize( L, paramsIndex );
			lua_pushnil( L );
			for ( int i = 0; ( i < kMaxParams ) && lua_next( L, paramsIndex ); i++ )
			{
				NSString *key = ToNSString( L, -2 );
				NSString *value = ToNSString( L, -1 );

				if ( key && value )
				{
					[params setValue:value forKey:key];
				}

				lua_pop( L, 1 );
			}

			// TODO: Add call to provider's API to log event name (str) and payload (params)
			NSLog( @"[WARNING] Unimplemented method analytics.logEvent(%@, %@)", str, params );
		}
		else
		{
			// TODO: Add call to provider's API to log event name (str) only
			NSLog( @"[WARNING] Unimplemented method analytics.logEvent(%@)", str );
		}
	}
}

// ----------------------------------------------------------------------------

} // namespace Corona

// ----------------------------------------------------------------------------
