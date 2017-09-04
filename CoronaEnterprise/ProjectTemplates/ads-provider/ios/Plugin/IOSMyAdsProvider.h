//
//  IOSMyAdsProvider.h
//  AdsProvider Plugin
//
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#ifndef _IOSMyAdsProvider_H__
#define _IOSMyAdsProvider_H__

#include "CoronaLua.h"

// ----------------------------------------------------------------------------

CORONA_EXPORT int luaopen_CoronaProvider_ads_myAdsProvider( lua_State *L );

// ----------------------------------------------------------------------------

@class NSString;
@protocol CoronaRuntime;

namespace Corona
{

// ----------------------------------------------------------------------------

class IOSMyAdsProvider
{
	public:
		typedef IOSMyAdsProvider Self;

	public:
		static const char kName[];

	public:
		static int Open( lua_State *L );

	protected:
		static int Finalizer( lua_State *L );

	protected:
		static Self *GetSelf( lua_State *L );
		static int Init( lua_State *L );
		static int Show( lua_State *L );
		static int Hide( lua_State *L );

	public:
		IOSMyAdsProvider( id<CoronaRuntime> runtime );
		virtual ~IOSMyAdsProvider();

	public:
		bool Init( lua_State *L, const char *appId, int listenerIndex );
		bool Show( lua_State *L, const char *adUnitType, int index );
		void Hide();

	public:
		void DispatchEvent( bool isError ) const;

	protected:
		id<CoronaRuntime> fRuntime;
		NSString *fAppId;
		CoronaLuaRef fListener;
};

// ----------------------------------------------------------------------------

} // namespace Corona

// ----------------------------------------------------------------------------

#endif // _IOSMyAdsProvider_H__
