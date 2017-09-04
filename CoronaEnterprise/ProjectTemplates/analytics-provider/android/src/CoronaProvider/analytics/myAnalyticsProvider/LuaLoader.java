//
//  LuaLoader.java
//  AnalyticsProvider Plugin
//
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

// TODO: Rename 'myAnalyticsProvider' to the name of the actual provider
package CoronaProvider.analytics.myAnalyticsProvider;

import android.app.Activity;
import android.util.Log;
import com.naef.jnlua.LuaState;
import com.naef.jnlua.LuaType;
import com.naef.jnlua.JavaFunction;
import com.naef.jnlua.NamedJavaFunction;
import com.ansca.corona.CoronaActivity;
import com.ansca.corona.CoronaEnvironment;
import com.ansca.corona.CoronaRuntime;
import com.ansca.corona.CoronaRuntimeListener;
import java.util.HashMap;


/**
 * Implements the Lua interface for the analytics plugin.
 * <p>
 * Only one instance of this class will be created by Corona for the lifetime of the application.
 * This instance will be re-used for every new Corona activity that gets created.
 */
public class LuaLoader implements JavaFunction, CoronaRuntimeListener {
	/** String ID that you may need to access the analytics system. */
	private String fApplicationId = null;

	/** Set true if an analytics session has been started. */
	private boolean fSessionStarted = false;


	/**
	 * Creates a new object for managing analytics.
	 * <p>
	 * Note that a new LuaLoader instance will not be created for every CoronaActivity instance.
	 * That is, only one instance of this class will be created for the lifetime of the application process.
	 * This gives a plugin the option to do operations in the background while the CoronaActivity is destroyed.
	 */
	public LuaLoader() {
		// Initialize member variables.
		initialize();

		// Set up this plugin to listen for Corona runtime events to be received by methods
		// onLoaded(), onStarted(), onSuspended(), onResumed(), and onExiting().
		CoronaEnvironment.addRuntimeListener(this);
	}

	/** Initializes member variables. */
	protected void initialize() {
		fApplicationId = null;
		fSessionStarted = false;
	}

	/**
	 * Called when this plugin is being loaded via the Lua require() function.
	 * <p>
	 * Note that this method will be called everytime a new CoronaActivity has been launched.
	 * This means that you'll need to re-initialize this plugin here.
	 * <p>
	 * Warning! This method is not called on the main UI thread.
	 * @param L Reference to the Lua state that the require() function was called from.
	 * @return Returns the number of values that the require() function will return.
	 *         <p>
	 *         Expected to return 1, the library that the require() function is loading.
	 */
	@Override
	public int invoke(LuaState L) {
		// Initialize member variables.
		initialize();

		// Register this plugin into Lua with the following functions.
		NamedJavaFunction[] luaFunctions = new NamedJavaFunction[] {
			new InitWrapper(),
			new LogEventWrapper(),
		};
		String libName = L.toString( 1 );
		L.register(libName, luaFunctions);

		// Returning 1 indicates that the Lua require() function will return the above Lua library.
		return 1;
	}

	/**
	 * Called after the Corona runtime has been created and just before executing the "main.lua" file.
	 * <p>
	 * Warning! This method is not called on the main thread.
	 * @param runtime Reference to the CoronaRuntime object that has just been loaded/initialized.
	 *                Provides a LuaState object that allows the application to extend the Lua API.
	 */
	@Override
	public void onLoaded(CoronaRuntime runtime) {
		// Note that this method will not be called the first time a Corona activity has been launched.
		// This is because this listener cannot be added to the CoronaEnvironment until after
		// this plugin has been required-in by Lua, which occurs after the onLoaded() event.
		// However, this method will be called when a 2nd Corona activity has been created.
	}

	/**
	 * Called just after the Corona runtime has executed the "main.lua" file.
	 * <p>
	 * Warning! This method is not called on the main thread.
	 * @param runtime Reference to the CoronaRuntime object that has just been started.
	 */
	@Override
	public void onStarted(CoronaRuntime runtime) {
	}

	/**
	 * Called just after the Corona runtime has been suspended which pauses all rendering, audio, timers,
	 * and other Corona related operations. This can happen when another Android activity (ie: window) has
	 * been displayed, when the screen has been powered off, or when the screen lock is shown.
	 * <p>
	 * Warning! This method is not called on the main thread.
	 * @param runtime Reference to the CoronaRuntime object that has just been suspended.
	 */
	@Override
	public void onSuspended(CoronaRuntime runtime) {
		if ( null != fApplicationId ) {
			fSessionStarted = false;

			// TODO: Call provider API to notify it that the app is about to suspend
			Log.v( "Corona", "[WARNING] Missing call to tell provider that the app is about to suspend." );
		}
	}

	/**
	 * Called just after the Corona runtime has been resumed after a suspend.
	 * <p>
	 * Warning! This method is not called on the main thread.
	 * @param runtime Reference to the CoronaRuntime object that has just been resumed.
	 */
	@Override
	public void onResumed(CoronaRuntime runtime) {
		if ( null != fApplicationId ) {
			fSessionStarted = true;

			// TODO: Call provider API to notify it that the app is about to resume
			Log.v( "Corona", "[WARNING] Missing call to tell provider that the app is about to resume." );
		}
	}

	/**
	 * Called just before the Corona runtime terminates.
	 * <p>
	 * This happens when the Corona activity is being destroyed which happens when the user presses the Back button
	 * on the activity, when the native.requestExit() method is called in Lua, or when the activity's finish()
	 * method is called. This does not mean that the application is exiting.
	 * <p>
	 * Warning! This method is not called on the main thread.
	 * @param runtime Reference to the CoronaRuntime object that is being terminated.
	 */
	@Override
	public void onExiting(CoronaRuntime runtime) {
	}

	/**
	 * The following Lua function has been called:  analytics.init( providerName, appId )
	 * <p>
	 * Warning! This method is not called on the main thread.
	 * @param L Reference to the Lua state that the Lua function was called from.
	 * @return Returns the number of values to be returned by the analytics.init() function.
	 *         <p>
	 *         Expected to return 1 value, a boolean indicating if initialization succeeded or failed.
	 */
	public int init(LuaState L) {
		boolean success = false;

		if ( ! fSessionStarted && null == fApplicationId ) {
			String appId = L.toString( 2 );
			if ( null != appId ) {
				fApplicationId = new String( appId );
				fSessionStarted = true;
				success = true;

				// TODO: Add call to provider's API to initialize service
				Log.v( "Corona", "[WARNING] Unimplemented method analytics.init(" + appId + ")" );
			}
		}

		L.pushBoolean( success );

		return 1;
	}

	/**
	 * Safely fetches a string from Lua without converting the type.
	 * @param L Reference to the Lua state to fetch the string from.
	 * @param index Index to the value in the Lua stack to fetch the string from.
	 * @return Returns the indexed string from Lua.
	 *         <p>
	 *         Returns null if the indexed Lua value cannot interpretted as a string.
	 */
	static String getStringFrom( LuaState L, int index ) {
		String result = null;

		LuaType t = L.type( -2 );
		switch ( t ) {
			case NUMBER:
				result = String.valueOf( L.toNumber( index ) );
				break;
			default:
				result = L.toString( index );
				break;
		}
		return result;
	}


	/**
	 * The following Lua function has been called:  analytics.logEvent( eventId [, params] )
	 * <p>
	 * Warning! This method is not called on the main thread.
	 * @param L Reference to the Lua state that the Lua function was called from.
	 * @return Returns the number of values to be returned by the analytics.logEvent() function.
	 *         <p>
	 *         Expected to return 0, meaning nothing is returned by this Lua function.
	 */
	public int logEvent(LuaState L) {
		if ( fSessionStarted ) {
			final String eventId = L.checkString( 1 );

			if ( null != eventId )
			{
				int paramsIndex = 2;

				final int kMaxParams = 10;
				final HashMap< String, String > params =
					( L.isTable( paramsIndex ) ? new HashMap< String, String >( kMaxParams ) : null );

				if ( null != params ) {

					// Convert Lua table to Map
					L.pushNil();
					for ( int i = 0; ( i < kMaxParams ) && L.next( paramsIndex ); i++ ) {
						String key = getStringFrom( L, -2 );
						String value = getStringFrom( L, -1 );

						if ( null != key && null != value )
						{
							params.put( key, value );
						}

						L.pop( 1 );
					}

					// TODO: Add call to provider's API to log event name (eventId) and payload (params)
					Log.v( "Corona", "[WARNING] Unimplemented method analytics.logEvent(" + eventId + "," + params.toString() + ")" );
				} else {
					// TODO: Add call to provider's API to log event name (eventId) only
					Log.v( "Corona", "[WARNING] Unimplemented method analytics.logEvent(" + eventId + ")" );
				}
			}

		}

		return 0;
	}


	/** Implements the analytics.init() Lua function. */
	private class InitWrapper implements NamedJavaFunction {
		/**
		 * Gets the name of the Lua function as it would appear in the Lua script.
		 * @return Returns the name of the custom Lua function.
		 */
		@Override
		public String getName() {
			return "init";
		}
		
		/**
		 * This method is called when the Lua function is called.
		 * <p>
		 * Warning! This method is not called on the main UI thread.
		 * @param luaState Reference to the Lua state.
		 *                 Needed to retrieve the Lua function's parameters and to return values back to Lua.
		 * @return Returns the number of values to be returned by the Lua function.
		 */
		@Override
		public int invoke(LuaState L) {
			return init(L);
		}
	}

	/** Implements the analytics.logEvent() Lua function. */
	private class LogEventWrapper implements NamedJavaFunction {
		/**
		 * Gets the name of the Lua function as it would appear in the Lua script.
		 * @return Returns the name of the custom Lua function.
		 */
		@Override
		public String getName() {
			return "logEvent";
		}
		
		/**
		 * This method is called when the Lua function is called.
		 * <p>
		 * Warning! This method is not called on the main UI thread.
		 * @param luaState Reference to the Lua state.
		 *                 Needed to retrieve the Lua function's parameters and to return values back to Lua.
		 * @return Returns the number of values to be returned by the Lua function.
		 */
		@Override
		public int invoke(LuaState L) {
			return logEvent(L);
		}
	}
}