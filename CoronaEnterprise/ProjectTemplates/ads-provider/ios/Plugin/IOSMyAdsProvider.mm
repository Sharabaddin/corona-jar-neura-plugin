//
//  IOSMyAdsProvider.mm
//  AdsProvider Plugin
//
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#include "IOSMyAdsProvider.h"

#include "CoronaAssert.h"
#include "CoronaEvent.h"
#include "CoronaLibrary.h"

#import <Foundation/Foundation.h>
#import "CoronaRuntime.h"

// ----------------------------------------------------------------------------

CORONA_EXPORT
int luaopen_CoronaProvider_ads_myAdsProvider( lua_State *L )
{
	return Corona::IOSMyAdsProvider::Open( L );
}

// ----------------------------------------------------------------------------

namespace Corona
{

// ----------------------------------------------------------------------------

// TODO: Rename.
const char IOSMyAdsProvider::kName[] = "CoronaProvider.ads.myAdsProvider";

// TODO: Rename. Should correspond to kName above
static const char kProviderName[] = "myAdsProvider";

// TODO: Rename.
static const char kPublisherId[] = "com.mycompany";

int
IOSMyAdsProvider::Open( lua_State *L )
{
	void *platformContext = CoronaLuaGetContext( L ); // lua_touserdata( L, lua_upvalueindex( 1 ) );
	id<CoronaRuntime> runtime = (id<CoronaRuntime>)platformContext;

	const char *name = lua_tostring( L, 1 ); CORONA_ASSERT( 0 == strcmp( name, kName ) );
	int result = CoronaLibraryProviderNew( L, "ads", name, kPublisherId );

	if ( result )
	{
		const luaL_Reg kFunctions[] =
		{
			{ "init", Self::Init },
			{ "show", Self::Show },
			{ "hide", Self::Hide },

			{ NULL, NULL }
		};

		CoronaLuaInitializeGCMetatable( L, kName, Finalizer );

		// Use 'provider' in closure for kFunctions
		Self *provider = new Self( runtime );
		CoronaLuaPushUserdata( L, provider, kName );
		luaL_openlib( L, NULL, kFunctions, 1 );

		const char kTestAppId[] = "someDefaultAppId";
		lua_pushstring( L, kTestAppId );
		lua_setfield( L, -2, "testAppId" );
	}

	return result;
}

int
IOSMyAdsProvider::Finalizer( lua_State *L )
{
	Self *provider = (Self *)CoronaLuaToUserdata( L, 1 );
	delete provider;
	return 0;
}

IOSMyAdsProvider *
IOSMyAdsProvider::GetSelf( lua_State *L )
{
	return (Self *)CoronaLuaToUserdata( L, lua_upvalueindex( 1 ) );
}

// ads.init( providerName, appId [, listener] )
int
IOSMyAdsProvider::Init( lua_State *L )
{
	Self *provider = GetSelf( L );

	const char *appId = lua_tostring( L, 2 );

	bool success = provider->Init( L, appId, 3 );
	lua_pushboolean( L, success );

	return 1;
}

// ads.show( adUnitType [, params] )
int
IOSMyAdsProvider::Show( lua_State *L )
{
	Self *provider = GetSelf( L );

	const char *adUnitType = lua_tostring( L, 1 );
	int paramsIndex = 2;

	bool success = provider->Show( L, adUnitType, paramsIndex );
	lua_pushboolean( L, success );
	
	return 1;
}

// ads.hide()
int
IOSMyAdsProvider::Hide( lua_State *L )
{
	Self *provider = GetSelf( L );

	provider->Hide();

	return 0;
}

// ----------------------------------------------------------------------------

IOSMyAdsProvider::IOSMyAdsProvider( id<CoronaRuntime> runtime )
:	fRuntime( runtime ),
	fAppId( nil ),
	fListener( NULL )
{
}

IOSMyAdsProvider::~IOSMyAdsProvider()
{
	CoronaLuaDeleteRef( fRuntime.L, fListener );
	Hide();
	[fAppId release];
}

bool
IOSMyAdsProvider::Init( lua_State *L, const char *appId, int listenerIndex )
{
	bool result = false;

	if ( appId )
	{
		CORONA_ASSERT( NULL == fListener );

		fListener = 
			( CoronaLuaIsListener( L, listenerIndex, "adsRequest" ) ? CoronaLuaNewRef( L, 3 ) : NULL );

		fAppId = [[NSString alloc] initWithUTF8String:appId];

		if ( ! appId )
		{
			NSLog( @"WARNING: No app id was supplied. A test app id will be used for ads served by %s.", kName );
		}

		result = true;
	}

	return result;
}


static bool
FloatEqual( float a, float b )
{
	return fabsf( a - b ) < FLT_EPSILON;
}

bool
IOSMyAdsProvider::Show( lua_State *L, const char *adUnitType, int index )
{
	// TODO: If banner is already showing, hide the current ad
	NSLog( @"[WARNING] ads.show() missing implementation to hide previous ad when a new ad is being shown." );
	/*
	if ( fAd )
	{
		Hide();
	}
	*/

	CGFloat w=0, h=0;

	// Defaults
	CGFloat x = 0;
	CGFloat y = 0;
	bool isTestMode = true;
	int interval = 60; // default interval

	if ( lua_istable( L, index ) )
	{
		lua_getfield( L, index, "x" );
		x = lua_tonumber( L, -1 );
		lua_pop( L, 1 );
		
		lua_getfield( L, index, "y" );
		y = lua_tonumber( L, -1 );
		lua_pop( L, 1 );

		lua_getfield( L, index, "testMode" );
		if ( lua_isboolean( L, -1 ) )
		{
			isTestMode = lua_toboolean( L, -1 );
		}
		lua_pop( L, 1 );

		lua_getfield( L, index, "interval" );
		if ( lua_isnumber( L, -1 ) )
		{
			interval = (int)lua_tointeger( L, -1 );
			if ( ! lua_isnil( L, -1 ) )
			{
				if ( interval <= 0 )
				{
					interval = 20;
				}
				else
				{
					// 20 is minimum interval
					interval = ( 20 > interval ? 20 : interval );
				}
			}
		}
		lua_pop( L, 1 );
	}

	CORONA_ASSERT( ! fAd );

	// Convert (x,y) from Corona 'content' units to UIKit 'points'
	CGPoint originContent = { x, y };
	CGPoint originPoints = [fRuntime coronaPointToUIKitPoint:originContent];
	x = originPoints.x;
	y = originPoints.y;

	// TODO: w=, h= are defined by sizes from provider. If these are _not_ in UIKit 'points'
	// then you need to convert them
	NSLog( @"[WARNING] ads.show() missing implementation to convert w,h of ad to UIKit 'points'." );

	// TODO: Add call to provider's API to create UIView for ad based on dimensions (r).
	CGRect r = CGRectMake( x, y, w, h );
	NSLog( @"[WARNING] ads.show() missing implementation to create ad's UIView." );
	// UIView *view = ...

	// TODO: Add ad UIView as subview of viewController
	UIViewController *viewController = fRuntime.appViewController;
	NSLog( @"[WARNING] ads.show() missing implementation to add ad's UIView to parent viewController (%@) for rect %@.", viewController, CGRectCreateDictionaryRepresentation(r) );
	// [viewController.view addSubview:view];

	return true;
}

void
IOSMyAdsProvider::Hide()
{
	// TODO: Remove view from super view. Also free any other resources associated with this ad.
	NSLog( @"[WARNING] ads.show() missing implementation to remove current ad so it no longer displays." );
}

void
IOSMyAdsProvider::DispatchEvent( bool isError ) const
{
	lua_State *L = fRuntime.L;

	CoronaLuaNewEvent( L, CoronaEventAdsRequestName() );

	lua_pushstring( L, kProviderName );
	lua_setfield( L, -2, CoronaEventProviderKey() );

	lua_pushboolean( L, isError );
	lua_setfield( L, -2, CoronaEventIsErrorKey() );

	CoronaLuaDispatchEvent( L, fListener, 0 );
}

// ----------------------------------------------------------------------------

} // namespace Corona

// ----------------------------------------------------------------------------
