//
//  IOSMyAnalyticsProvider.h
//  AnalyticsProvider Plugin
//
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#ifndef _IOSMyAnalyticsProvider_H__
#define _IOSMyAnalyticsProvider_H__

#include "CoronaLua.h"

// ----------------------------------------------------------------------------

CORONA_EXPORT int luaopen_CoronaProvider_analytics_myAnalyticsProvider( lua_State *L );

// ----------------------------------------------------------------------------

@class NSString;
@protocol CoronaRuntime;

namespace Corona
{

// ----------------------------------------------------------------------------

class IOSMyAnalyticsProvider
{
	public:
		typedef IOSMyAnalyticsProvider Self;

	public:
		static const char kName[];

	public:
		static int Open( lua_State *L );

	protected:
		static int Finalizer( lua_State *L );

	protected:
		static Self *GetSelf( lua_State *L );
		static int Init( lua_State *L );
		static int LogEvent( lua_State *L );

	public:
		IOSMyAnalyticsProvider( id<CoronaRuntime> runtime );
		virtual ~IOSMyAnalyticsProvider();

	public:
		bool Init( lua_State *L, const char *appId );
		void LogEvent( lua_State *L, const char *eventId, int paramsIndex );

	protected:
		id<CoronaRuntime> fRuntime;
		NSString *fAppId;
};

// ----------------------------------------------------------------------------

} // namespace Corona

// ----------------------------------------------------------------------------

#endif // _IOSMyAnalyticsProvider_H__
