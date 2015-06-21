package com.example.imageviewer5000;

import java.nio.ByteBuffer;

import java.nio.ByteOrder;
import java.nio.FloatBuffer;

import javax.microedition.khronos.egl.EGLConfig;
import javax.microedition.khronos.opengles.GL10;

import android.content.Context;
import android.opengl.GLES20;
import android.opengl.GLSurfaceView;
import android.opengl.GLSurfaceView.Renderer;
import android.opengl.Matrix;
import android.os.SystemClock;
import android.content.res.AssetManager;

public class ImageViewer5000Renderer implements GLSurfaceView.Renderer {
	
	private final Context context;

	public ImageViewer5000Renderer(Context context) {
		this.context = context;}
	
	public static native void initializeAssetManager(AssetManager assetManager); 
	
	@Override
	public void onSurfaceCreated(GL10 gl, EGLConfig config) {
		initializeAssetManager(context.getAssets());
		ImageViewer5000JNIWrapper.on_surface_created();
	}
	
	@Override
	public void onSurfaceChanged(GL10 gl, int width, int height) {
		ImageViewer5000JNIWrapper.on_surface_changed(width, height);
	}

	@Override
	public void onDrawFrame(GL10 gl) {
		System.out.println("HI");
		ImageViewer5000JNIWrapper.on_draw_frame();
		System.out.println("BIE");
	}
}