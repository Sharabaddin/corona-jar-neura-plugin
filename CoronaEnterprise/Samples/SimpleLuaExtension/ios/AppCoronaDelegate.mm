//
//  AppCoronaDelegate.mm
//  TemplateApp
//
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#import "AppCoronaDelegate.h"

#import "CoronaRuntime.h"
#import "CoronaLua.h"

@implementation AppCoronaDelegate

// Returns random number between 0 and 1
static double
GetRandomNumber()
{
	return ((double)rand()) / RAND_MAX;
}

static int
getRandomBoolean( lua_State *L )
{
	// Push the boolean value to the Lua state's stack.
	// This is the value to be returned by the Lua function.
	lua_pushboolean( L, GetRandomNumber() < 0.5 );

	// Return 1 to indicate that this Lua function returns 1 value.
	return 1;
}

static int
getRandomNumber( lua_State *L )
{
	// Push the floating point value to the Lua state's stack.
	// This is the value to be returned by the Lua function.
	lua_pushnumber( L, GetRandomNumber() );

	// Return 1 to indicate that this Lua function returns 1 value.
	return 1;
}

static int
getRandomString( lua_State *L )
{
	// Create a random string
	int value = rand();
	char buffer[sizeof(value)*4];
	sprintf( buffer, "0x%x", value );

	// Push the string to the Lua state's stack.
	// This is the value to be returned by the Lua function.
	lua_pushstring( L, buffer );

	// Return 1 to indicate that this Lua function returns 1 value.
	return 1;
}

static int
getRandomArray( lua_State *L )
{
	int len = 3;

	// Create a new Lua array.
	// Creating a Lua array in this manner automatically pushes it on the Lua stack.
	// For best performance, you should pre-allocate the Lua array in one shot like below if the array size is known.
	// lua_createtable()'s first argument should be set to the array's length.
	// lua_createtable()'s second argument should be zero since we are not creating a key/value table in Lua.
	lua_createtable( L, len, 0 );
	for ( int i = 0; i < len; i++ )
	{
		// Push a random number on Lua stack
		lua_pushnumber( L, GetRandomNumber() );

		// Assign the above pushed value to the next Lua array element.
		// We do an "index + 1" because arrays in Lua are 1-based by default.
		lua_rawseti( L, -2, i + 1 );
	}

	// Return 1 to indicate that this Lua function returns 1 value.
	return 1;
}

static int
getRandomTable( lua_State *L )
{
	int numPairs = 3;

	// Create a new Lua table for key/value pairs
	// Creating a Lua table in this manner automatically pushes it on the Lua stack.
	// For best performance, you should pre-allocate the Lua table like below if the number of entries is known.
	// lua_createtable()'s first argument should be set to zero since we are not creating a Lua array.
	// lua_createtable()'s second argument should be set to the number of key/value pairs.
	lua_createtable( L, 0, numPairs );

	// Equivalent in Lua: t.x = randomNumber
	lua_pushnumber( L, GetRandomNumber() ); // push a random number on Lua stack
	lua_setfield( L, -2, "x" ); // sets the value in table and pops that value off Lua stack

	lua_pushnumber( L, GetRandomNumber() );
	lua_setfield( L, -2, "y" );

	lua_pushnumber( L, GetRandomNumber() );
	lua_setfield( L, -2, "z" );

	// Return 1 to indicate that this Lua function returns 1 value.
	return 1;
}

static int
printBoolean( lua_State *L )
{
	// Fetch the Lua function's first argument.
	int value = lua_toboolean( L, 1 );
	NSLog( @"printBoolean(): value = %s", ( value ? "true" : "false" ) );

	// Return 0 since this Lua function does not return any values.
	return 0;
}

static int
printNumber( lua_State *L )
{
	// Fetch the Lua function's first argument.
	// Will throw a Lua exception if it is not of type number.
	double value = luaL_checknumber( L, 1 );
	NSLog( @"printNumber(): value = %g", value );

	// Return 0 since this Lua function does not return any values.
	return 0;
}

static int
printString( lua_State *L )
{
	// Fetch the Lua function's first argument.
	// Will throw a Lua exception if it is not of type string.
	const char *value = luaL_checkstring( L, 1 );
	NSLog( @"printString(): value = %s", value );

	// Return 0 since this Lua function does not return any values.
	return 0;
}

static int
printArray( lua_State *L )
{
	// TODO
	NSLog( @"printArray() not implemented" );

	// Return 0 since this Lua function does not return any values.
	return 0;
}

static int
printTable( lua_State *L )
{
	// TODO
	NSLog( @"printTable() not implemented" );

	// Return 0 since this Lua function does not return any values.
	return 0;
}

static int
printTableValuesXY( lua_State *L )
{
	// TODO
	NSLog( @"printTableValuesXY() not implemented" );

	// Return 0 since this Lua function does not return any values.
	return 0;
}

static int
callLuaFunction( lua_State *L )
{
	// Check if the first argument is a function.
	if ( lua_isfunction( L, 1 ) )
	{
		// Push Lua function b/c lua_call() will pop that value off the top of stack
		// and we want the stack to be balanced.
		lua_pushvalue( L, 1 );

		// Call the given Lua function.
		// The first argument indicates the number of arguments that we are passing to the Lua function.
		// The second argument indicates the number of return values to accept from the Lua function.
		// In this case, we are calling this Lua function with no arguments and are accepting no return values.
		// Note: If you want to call the Lua function with arguments, then you need to push each argument
		//       value to the luaState object's stack.

		lua_call( L, 0, 0 );
	}
	else
	{
		luaL_typerror( L, 1, lua_typename( L, LUA_TFUNCTION ) );
	}
	
	return 0;
}

static int
asyncCallLuaFunction( lua_State *L )
{
	if ( lua_isfunction( L, 1 ) )
	{
		// Store a native reference to the Lua function parameter in the registry.
		// This allows us to use the Lua function in the block below.
		//
		// We must store a native reference, since the Lua function will not
		// be available beyond the scope of this native function.
		int functionRef = luaL_ref( L, LUA_REGISTRYINDEX );

		// Use standard method for async invocation.
		// On iOS, Corona executes Lua code on the main thread, so we use the main queue.
		dispatch_async( dispatch_get_main_queue(), ^(void) {
			// Fetch Lua function from registry, and push to the top of the stack
			lua_rawgeti( L, LUA_REGISTRYINDEX, functionRef );
			
			// Call the Lua function.
			// 0 arguments passed to this Lua function. 0 expected results.
			lua_call( L, 0, 0);

			// Remove the native reference to the Lua function from the registry,
			// so we don't leak.
			luaL_unref( L, LUA_REGISTRYINDEX, functionRef );
		});
	}

	return 0;
}

- (void)willLoadMain:(id<CoronaRuntime>)runtime
{
	lua_State *L = runtime.L;

	const luaL_Reg kFunctions[] =
	{
		"getRandomBoolean", getRandomBoolean,
		"getRandomNumber", getRandomNumber,
		"getRandomString", getRandomString,
		"getRandomArray", getRandomArray,
		"getRandomTable", getRandomTable,
		"printBoolean", printBoolean,
		"printNumber", printNumber,
		"printString", printString,
		"printArray", printArray,
		"printTable", printTable,
		"printTableValuesXY", printTableValuesXY,
		"callLuaFunction", callLuaFunction,
		"asyncCallLuaFunction", asyncCallLuaFunction,

		NULL, NULL
	};

	luaL_register( L, "myTests", kFunctions );
	lua_pop( L, 1 );
}

- (void)didLoadMain:(id<CoronaRuntime>)runtime
{
}

#pragma mark UIApplicationDelegate methods

// The following are stubs for common delegate methods. Uncomment and implement
// the ones you wish to be called. Or add additional delegate methods that
// you wish to be called.

/*
- (void)applicationWillResignActive:(UIApplication *)application
{
	// Sent when the application is about to move from active to inactive state. This can occur for certain types of temporary interruptions (such as an incoming phone call or SMS message) or when the user quits the application and it begins the transition to the background state.
	// Use this method to pause ongoing tasks, disable timers, and throttle down OpenGL ES frame rates. Games should use this method to pause the game.
}
*/

/*
- (void)applicationDidEnterBackground:(UIApplication *)application
{
	// Use this method to release shared resources, save user data, invalidate timers, and store enough application state information to restore your application to its current state in case it is terminated later. 
	// If your application supports background execution, this method is called instead of applicationWillTerminate: when the user quits.
}
*/

/*
- (void)applicationWillEnterForeground:(UIApplication *)application
{
	// Called as part of the transition from the background to the inactive state; here you can undo many of the changes made on entering the background.
}
*/

/*
- (void)applicationDidBecomeActive:(UIApplication *)application
{
	// Restart any tasks that were paused (or not yet started) while the application was inactive. If the application was previously in the background, optionally refresh the user interface.
}
*/

/*
- (void)applicationWillTerminate:(UIApplication *)application
{
	// Called when the application is about to terminate. Save data if appropriate. See also applicationDidEnterBackground:.
}
*/

@end
