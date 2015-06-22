package com.example.imageviewer5000;

import javax.microedition.khronos.egl.EGLConfig;
import javax.microedition.khronos.opengles.GL10;

import android.content.Context;
import android.opengl.GLSurfaceView;
import android.opengl.GLSurfaceView.Renderer;
import android.content.res.AssetManager;

public class ImageViewer5000Renderer implements GLSurfaceView.Renderer {
	static {
		System.loadLibrary("imageviewer5000");
	}
	
	private final Context context;
	
	public ImageViewer5000Renderer(Context context) {
		this.context = context;
	}
	
	@Override
	public void onSurfaceCreated(GL10 gl, EGLConfig config) {
		init_asset_manager(context.getAssets());
		on_surface_created();
	}
	
	@Override
	public void onSurfaceChanged(GL10 gl, int width, int height) {
		on_surface_changed(width, height);
	}
	
	@Override
	public void onDrawFrame(GL10 gl) {
		on_draw_frame();
	}
	
	private static native void init_asset_manager(AssetManager assetManager); 

	private static native void on_surface_created();

	private static native void on_surface_changed(int width, int height);

	private static native void on_draw_frame();
}