package com.example.imageviewer5000;

import java.util.List;

import android.content.Context;
import android.hardware.Sensor;
import android.hardware.SensorEvent;
import android.hardware.SensorEventListener;
import android.hardware.SensorManager;


public class ImageViewer5000Sensor implements SensorEventListener {
	private SensorManager mSensorManager;
	private Sensor mAccel;
	private Sensor mMagnet;
	private float[] mOrientation;
	private float[] mPrevOr;
	private boolean Writing;
	
	public ImageViewer5000Sensor(SensorManager manager) {
		mSensorManager = manager;
		mAccel = mSensorManager.getDefaultSensor(Sensor.TYPE_ACCELEROMETER);
		mMagnet = mSensorManager.getDefaultSensor(Sensor.TYPE_MAGNETIC_FIELD);
		Writing = false;
	}
	
	public void onPause() {
		mSensorManager.unregisterListener(this);
	}
	
	public void onResume() {
		mSensorManager.registerListener(this, mAccel, SensorManager.SENSOR_DELAY_GAME);
		mSensorManager.registerListener(this, mMagnet, SensorManager.SENSOR_DELAY_GAME);
	}
	
	public float[] getOrientation() {
		//if (Writing)
		//	return mPrevOr;
		return mOrientation;
	}
	
	
	private float[] acc;
	private float[] mag;
	@Override
	public void onSensorChanged(SensorEvent event) {
		Writing = true;
		
		if (event.sensor.getType() == Sensor.TYPE_ACCELEROMETER) {
			acc = new float[3];
			for (int i=0;i<3;++i) {
				acc[i] = event.values[i];
			}
		}
		if (event.sensor.getType() == Sensor.TYPE_MAGNETIC_FIELD) {
			mag = new float[3];
			for (int i=0;i<3;++i) {
				mag[i] = event.values[i];
			}
		}
		if (acc != null && mag != null) {
			float R[] = new float[9];
			float I[] = new float[9];
			boolean success = SensorManager.getRotationMatrix(R, I, acc, mag);
			if (success) {
				float or[] = new float[3];
				SensorManager.getOrientation(R, or);
				mPrevOr = mOrientation;
				mOrientation = or;
			}
		}
		
		Writing = false;
	}

	@Override
	public void onAccuracyChanged(Sensor sensor, int accuracy) {
		
	}
}
