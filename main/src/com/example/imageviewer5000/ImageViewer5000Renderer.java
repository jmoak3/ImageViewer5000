package com.example.imageviewer5000;

import javax.microedition.khronos.egl.EGLConfig;
import javax.microedition.khronos.opengles.GL10;

import android.content.Context;
import android.opengl.GLSurfaceView.Renderer;
import android.content.res.AssetManager;

public class ImageViewer5000Renderer implements Renderer {
	
	
	static {
		System.loadLibrary("imageviewer5000");
	}
	
	private final Context mContext;
	private ImageViewer5000Sensor mSensor;
	
	public ImageViewer5000Renderer(Context context, ImageViewer5000Sensor sensor) {
		mContext = context;
		mSensor = sensor;
	}
		
	@Override
	public void onSurfaceCreated(GL10 gl, EGLConfig config) {
		init_asset_manager(mContext.getAssets());
		on_surface_created();
	}
	
	@Override
	public void onSurfaceChanged(GL10 gl, int width, int height) {
		System.out.println("LOG SurfaceChange");
		on_surface_changed(width, height);		
	}
	
	@Override
	public void onDrawFrame(GL10 gl) {
		float[] or = mSensor.getOrientation();
		on_draw_frame(or[0], or[1], or[2]);
		//on_draw_frame(0.f, 0.f, 0.f);
	}
	
	private static native void init_asset_manager(AssetManager assetManager); 

	private static native void on_surface_created();

	private static native void on_surface_changed(int width, int height);

	private static native void on_draw_frame(float az, float pch, float rll);
}