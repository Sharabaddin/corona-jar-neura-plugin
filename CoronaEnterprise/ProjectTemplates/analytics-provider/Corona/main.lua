--------------------------------------------------------------------------------
-- Sample code is MIT licensed, see http://www.coronalabs.com/links/code/license
-- Copyright (C) 2012 Corona Labs Inc. All Rights Reserved.
--------------------------------------------------------------------------------

-- Hide the status bar
display.setStatusBar( display.HiddenStatusBar )

-- The name of the ad provider.
-- Corona uses this value to construct the name of the plugin. Corona then asks
-- Lua to load a module with this name: "CoronaProvider.analytics." .. provider
local provider = "myAnalyticsProvider"

local appID = "myProviderSpecificApplicationID"

-- Load Corona 'analytics' library
local analytics = require "analytics"

analytics.init( provider, appID )

analytics.logEvent( "eventOnly")

analytics.logEvent( "eventWithParams", { foo = "bar" } )