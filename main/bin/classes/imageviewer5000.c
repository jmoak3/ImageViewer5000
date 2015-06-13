#include "imageviewer5000.h"
#include "glwrapper.h"

void on_surface_created()
{
	glClearColor(0.f, 0.f, 1.0f, 0.0f);
}

void on_surface_changed()
{
	//nothing
}

void on_draw_frame()
{
	glClear(GL_COLOR_BUFFER_BIT);
}
