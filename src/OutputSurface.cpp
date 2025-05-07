#include "OutputSurface.hpp"

OutputSurface::OutputSurface()
{
}

OutputSurface::~OutputSurface()
{
}

void OutputSurface::draw (Graphics<WIDTH, HEIGHT, THIS_COLOR_FORMAT, THIS_RENDER_API, ENABLE_3D, SHADER_PASS_DATA_SIZE>* graphics)
{
	static bool flip = false;

	if ( flip )
	{
		graphics->setColor( 0.0f, 0.0f, 1.0f );
	}
	else
	{
		graphics->setColor( 1.0f, 0.0f, 0.0f );
	}

	flip = !flip;

	graphics->fill();
}
