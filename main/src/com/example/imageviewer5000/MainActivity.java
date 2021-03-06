package com.example.imageviewer5000;

import android.os.Bundle;
import android.app.Activity;
import android.app.ActivityManager;
import android.content.Context;
import android.content.pm.ConfigurationInfo;
import android.content.Context;
import android.hardware.SensorManager;
import android.opengl.GLSurfaceView;

public class MainActivity extends Activity {

	private GLSurfaceView mGLSurfaceView;
	private ImageViewer5000Sensor mSensor;
	
	@Override
	protected void onCreate(Bundle savedInstanceState) {
		super.onCreate(savedInstanceState);
		
		mSensor = new ImageViewer5000Sensor((SensorManager)getSystemService(Context.SENSOR_SERVICE));
		
		mGLSurfaceView = new GLSurfaceView(this);

		// Check if the system supports OpenGL ES 2.0.
		final ActivityManager activityManager = (ActivityManager) getSystemService(Context.ACTIVITY_SERVICE);
		final ConfigurationInfo configurationInfo = activityManager.getDeviceConfigurationInfo();
		final boolean supportsES2 = configurationInfo.reqGlEsVersion >= 0x20000;
		

		if (supportsES2) {
			mGLSurfaceView.setEGLContextClientVersion(2);
			mGLSurfaceView.setRenderer(new ImageViewer5000Renderer(this, mSensor));
		}
		
		setContentView(mGLSurfaceView);
	}
	
	@Override
	protected void onResume() 
	{
		// The activity must call the GL surface view's onResume() on activity onResume().
		super.onResume();
		System.out.println("LOG onResume");
		mGLSurfaceView.onResume();
		mSensor.onResume();
	}

	@Override
	protected void onPause() 
	{
		// The activity must call the GL surface view's onPause() on activity onPause().
		super.onPause();
		System.out.println("LOG onPaused");
		mGLSurfaceView.onPause();
		mSensor.onPause();
	}
}
