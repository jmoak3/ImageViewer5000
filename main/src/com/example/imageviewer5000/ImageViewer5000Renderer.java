package com.example.imageviewer5000;

import java.nio.ByteBuffer;
import java.nio.ByteOrder;
import java.nio.FloatBuffer;

import javax.microedition.khronos.egl.EGLConfig;
import javax.microedition.khronos.opengles.GL10;

import android.opengl.GLES20;
import android.opengl.GLSurfaceView;
import android.opengl.GLSurfaceView.Renderer;
import android.opengl.Matrix;
import android.os.SystemClock;

public class ImageViewer5000Renderer implements GLSurfaceView.Renderer {

	@Override
	public void onSurfaceCreated(GL10 gl, EGLConfig config) {
		ImageViewer5000JNIWrapper.on_surface_created();
	}

	@Override
	public void onSurfaceChanged(GL10 gl, int width, int height) {
		ImageViewer5000JNIWrapper.on_surface_changed(width, height);
	}

	@Override
	public void onDrawFrame(GL10 gl) {
		ImageViewer5000JNIWrapper.on_draw_frame();
	}

}
