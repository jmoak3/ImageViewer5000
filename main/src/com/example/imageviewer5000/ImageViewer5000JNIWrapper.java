package com.example.imageviewer5000;

public class ImageViewer5000JNIWrapper {
	static {
		System.loadLibrary("imageviewer5000");
	}

	public static native void on_surface_created();

	public static native void on_surface_changed(int width, int height);

	public static native void on_draw_frame();
}