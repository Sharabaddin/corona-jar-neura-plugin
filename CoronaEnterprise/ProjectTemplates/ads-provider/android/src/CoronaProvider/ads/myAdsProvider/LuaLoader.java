//
//  LuaLoader.java
//  AdsProvider Plugin
//
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

// TODO: Rename 'myAdsProvider' to the name of the actual provider
package CoronaProvider.ads.myAdsProvider;

import android.app.Activity;
import android.location.Location;
import android.view.ViewGroup;
import android.util.Log;
import com.naef.jnlua.LuaState;
import com.naef.jnlua.JavaFunction;
import com.naef.jnlua.NamedJavaFunction;
import com.ansca.corona.CoronaActivity;
import com.ansca.corona.CoronaEnvironment;
import com.ansca.corona.CoronaLua;
import com.ansca.corona.CoronaLuaEvent;
import com.ansca.corona.CoronaRuntime;
import com.ansca.corona.CoronaRuntimeListener;
import com.ansca.corona.CoronaRuntimeTaskDispatcher;
import java.util.Date;
import java.util.Timer;
import java.util.TimerTask;


/**
 * Implements the Lua interface for the ad plugin.
 * <p>
 * Only one instance of this class will be created by Corona for the lifetime of the application.
 * This instance will be re-used for every new Corona activity that gets created.
 */
public class LuaLoader implements JavaFunction, CoronaRuntimeListener {
	/** Used to access the Lua state on the Corona runtime's thread safely. */
	private CoronaRuntimeTaskDispatcher fDispatcher;

	/** String ID that you may need to access the ad network. */
	private String fApplicationId;

	/** Container used to hold the ad. */
	private android.widget.AbsoluteLayout fAbsoluteLayout;

	/** Lua registry ID to the Lua function to be called when the ad request finishes. */
	private int fListener;


	/**
	 * Creates a new object for displaying banner ads on the CoronaActivity.
	 * <p>
	 * Note that a new LuaLoader instance will not be created for every CoronaActivity instance.
	 * That is, only one instance of this class will be created for the lifetime of the application process.
	 * This gives a plugin the option to do operations in the background while the CoronaActivity is destroyed.
	 */
	public LuaLoader() {
		// Initialize member variables.
		fDispatcher = null;
		fApplicationId = "";
		fListener = CoronaLua.REFNIL;

		// Set up this plugin to listen for Corona runtime events to be received by methods
		// onLoaded(), onStarted(), onSuspended(), onResumed(), and onExiting().
		CoronaEnvironment.addRuntimeListener(this);
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
		// Create a new dispatcher for the new Corona runtime's Lua state.
		fDispatcher = new CoronaRuntimeTaskDispatcher( L );

		// Register this plugin into Lua with the following functions.
		NamedJavaFunction[] luaFunctions = new NamedJavaFunction[] {
			new InitWrapper(),
			new ShowWrapper(),
			new HideWrapper(),
		};
		String libName = L.toString( 1 );
		L.register(libName, luaFunctions);

		// Add fallback test app id.
		String testAppId = "4028cb962895efc50128fc99d4b7025b";
		L.pushString( testAppId );
		L.setField( -2, "testAppId" );

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
		// You may want to stop requesting ads here.
		// No point in fetching ads while the Corona activity is not shown.
	}

	/**
	 * Called just after the Corona runtime has been resumed after a suspend.
	 * <p>
	 * Warning! This method is not called on the main thread.
	 * @param runtime Reference to the CoronaRuntime object that has just been resumed.
	 */
	@Override
	public void onResumed(CoronaRuntime runtime) {
		// If you stopped requesting ads in the above onSuspended() method,
		// then you should restart the timer for fetching them here.
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
		// Remove the Lua listener reference.
		CoronaLua.deleteRef( runtime.getLuaState(), fListener );
		fListener = CoronaLua.REFNIL;

		// Let go of the reference to the ad view's container.
		// This allows it to be garbage collected after the CoronaActivity has been destroyed.
		fAbsoluteLayout = null;
	}

	/**
	 * The following Lua function has been called:  ads.init( providerName, appId [, listener] )
	 * <p>
	 * Warning! This method is not called on the main thread.
	 * @param L Reference to the Lua state that the Lua function was called from.
	 * @return Returns the number of values to be returned by the ads.init() function.
	 *         <p>
	 *         Expected to return 1 value, a boolean indicating if initialization succeeded or failed.
	 */
	public int init(LuaState L) {
		boolean success = false;

		String appId = L.toString( 2 );
		if ( "" == fApplicationId ) {
			if ( null != appId ) {
				fApplicationId = appId;

				int listenerIndex = 3;
				if ( CoronaLua.isListener( L, listenerIndex, "adsRequest" ) ) {
					fListener = CoronaLua.newRef( L, listenerIndex );
				}

				success = true;
			}
		} else {
			Log.v( "Corona", "WARNING: ads.init() should only be called once. The application id has already been set to :" + fApplicationId + "." );
		}

		L.pushBoolean( success );

		return 1;
	}

	/**
	 * The following Lua function has been called:  ads.show( adUnitType [, x, y] [, params] )
	 * <p>
	 * Warning! This method is not called on the main thread.
	 * @param L Reference to the Lua state that the Lua function was called from.
	 * @return Returns the number of values to be returned by the ads.show() function.
	 *         <p>
	 *         Expected to return 0, indicating nothing is returned by the Lua function.
	 */
	public int show(LuaState L) {
		// Fetch a reference to the Corona activity.
		// Note: Will be null if the end-user has just backed out of the activity.
		CoronaActivity activity = CoronaEnvironment.getCoronaActivity();
		if (activity == null) {
			return 0;
		}

		// Fetch the first Lua function argument.
		int nextArg = 1;
		String adUnitType = L.checkString( nextArg++ );
		
		// Fetch settings from Lua, if given.
		int x = 0;
		int y = 0;
		boolean testModeEnabled = true;
		int intervalInSeconds = 10;
		int index = nextArg;
		if ( L.isTable( index ) ) {
			L.getField( index, "x" );
			if ( L.isNumber( -1 ) )
			{
				x = (int)Math.round( L.toNumber( -1 ) );
			}
			L.pop( 1 );

			L.getField( index, "y" );
			if ( L.isNumber( -1 ) )
			{
				y = (int)Math.round( L.toNumber( -1 ) );
			}
			L.pop( 1 );

			L.getField( index, "testMode" );
			if ( L.isNumber( -1 ) )
			{
				testModeEnabled = L.toBoolean( -1 );
			}
			L.pop( 1 );

			L.getField( index, "interval" );
			if ( L.isNumber( -1 ) )
			{
				intervalInSeconds = (int)Math.round( L.toNumber( -1 ) );
			}
			L.pop( 1 );
		}
		android.graphics.Point p = activity.convertCoronaPointToAndroidPoint( x, y );
		if ( null != p ) {
			x = p.x;
			y = p.y;
		}

		// Display the ad.
		showAd( adUnitType, x, y, intervalInSeconds, testModeEnabled );
		return 0;
	}

	/**
	 * The following Lua function has been called:  ads.hide()
	 * <p>
	 * Warning! This method is not called on the main thread.
	 * @param L Reference to the Lua state that the Lua function was called from.
	 * @return Returns the number of values to be returned by the ads.hide() function.
	 *         <p>
	 *         Expected to return 0, indicating nothing is returned by the Lua function.
	 */
	public int hide(LuaState L) {
		hideAd();
		return 0;
	}


	/** Implements the ads.init() Lua function. */
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

	/** Implements the ads.show() Lua function. */
	private class ShowWrapper implements NamedJavaFunction {
		/**
		 * Gets the name of the Lua function as it would appear in the Lua script.
		 * @return Returns the name of the custom Lua function.
		 */
		@Override
		public String getName() {
			return "show";
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
			return show(L);
		}
	}

	/** Implements the ads.hide() Lua function. */
	private class HideWrapper implements NamedJavaFunction {
		/**
		 * Gets the name of the Lua function as it would appear in the Lua script.
		 * @return Returns the name of the custom Lua function.
		 */
		@Override
		public String getName() {
			return "hide";
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
			return hide(L);
		}
	}

	/**
	 * Shows an ad view in the Corona activity.
	 * @param bannerTypeName String key used to identify the dimensions of the banner to show, such as "banner320x48".
	 * @param x The pixel position where the top-left corner of the banner will be shown. Must be at least zero.
	 * @param y The pixel position where the top-left corner of the banner will be shown. Must be at least zero.
	 * @param intervalInSeconds How often the ad should be changed for a new one, in seconds.
	 * @param testModeEnabled Set true to enable the banner's test mode, as defined by provider.
	 */
	public void showAd(
		final String bannerTypeName, final float x, final float y,
		final double intervalInSeconds, final boolean testModeEnabled)
	{
		// Fetch a reference to the Corona activity.
		// Note: Will be null if the end-user has just backed out of the activity.
		CoronaActivity activity = CoronaEnvironment.getCoronaActivity();
		if (activity == null) {
			return;
		}

		// Do not continue if an application ID was not assigned.
		if ((fApplicationId == null) || (fApplicationId.length() <= 0)) {
			return;
		}
		
		// Copy the reference of the current application ID to be used in the below threaded operation.
		// This is to avoid a race condition in case the ID changes on us from another thread.
		final String copyOfApplicationId = fApplicationId;
		
		// Run the "show" operation on the UI thread. Executes immediately if we're already on the UI thread.
		activity.runOnUiThread(new Runnable() {
			protected android.widget.AbsoluteLayout getParent() {
				if ( null == fAbsoluteLayout ) {
					fAbsoluteLayout = new android.widget.AbsoluteLayout(CoronaEnvironment.getCoronaActivity());
					CoronaEnvironment.getCoronaActivity().getOverlayView().addView(fAbsoluteLayout);
				}

				return fAbsoluteLayout;
			}

			@Override
			public void run() {
				// Hide the last banner.
				hideAd();
				
				// Get the banner type name's unique ID, width, and height.
				int bannerWidth = 0;
				int bannerHeight = 0;

				// TODO: Fetch dimensions based on bannerTypeName
				if ( 0 == bannerWidth && 0 == bannerHeight ) {
					Log.v( "Corona", "[WARNING] ads.show() missing implementation to determine ad dimensions." );
				}

				// Convert width and height to density independent coordinates.
				float displayDensity = CoronaEnvironment.getCoronaActivity().getResources().getDisplayMetrics().density;
				bannerWidth = (int)((bannerWidth * displayDensity) + 0.5f);
				bannerHeight = (int)((bannerHeight * displayDensity) + 0.5f);
				
				// TODO: Insert call to display new ad. You should add it as a child of 'getParent()'.
				// For example:
				// 		getParent().addView( adView );
				// Note you may need to convert between Corona coordinates and Android coordinates.
				// The following APIs will be useful:
				// int contentWidth = CoronaEnvironment.getCoronaActivity().getContentWidthInPixels();
				// int contentHeight = CoronaEnvironment.getCoronaActivity().getContentHeightInPixels();
				// int horizontalMargin = CoronaEnvironment.getCoronaActivity().getHorizontalMarginInPixels();
				// int verticalMargin = CoronaEnvironment.getCoronaActivity().getVerticalMarginInPixels();
				Log.v( "Corona", "[WARNING] ads.show() missing implementation to display View for ad." );

				// TODO: Make sure ad is refreshed according to 'intervalInSeconds'.
				// Some provider's already offer an API to do this for you,
				// If not, some pseudo-code below to help you.
				Log.v( "Corona", "[WARNING] ads.show() missing implementation to handle time interval for refreshing the ad." );
			}
		});
	}
	
	/**
	 * Hides the currently shown ad.
	 */
	public void hideAd() {
		// Fetch a reference to the Corona activity.
		// Note: Will be null if the end-user has just backed out of the activity.
		CoronaActivity activity = CoronaEnvironment.getCoronaActivity();
		if (activity == null) {
			return;
		}

		// TODO: If no banner is showing, then return early.
		Log.v( "Corona", "[WARNING] ads.hide() missing implementation to check if there is an ad shown." );
		
		// Remove the banner view from the activity.
		activity.runOnUiThread(new Runnable() {
			@Override
			public void run() {
				// TODO: Remove the ad view.
				Log.v( "Corona", "[WARNING] ads.hide() missing implementation to remove view for ad." );
			}
		});
	}
}