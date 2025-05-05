#ifndef OUTPUTSURFACE_HPP
#define OUTPUTSURFACE_HPP

#include "Surface.hpp"

// adjust for your own screen resolution
#define WIDTH 			800
#define HEIGHT 			480
#define THIS_COLOR_FORMAT 	CP_FORMAT::RGB_24BIT
#define THIS_RENDER_API 	RENDER_API::SOFTWARE
#define NUM_THREADS 		1
#define ENABLE_3D 		false
#define SHADER_PASS_DATA_SIZE 	256

class OutputSurface : public Surface<THIS_RENDER_API, WIDTH, HEIGHT, THIS_COLOR_FORMAT, NUM_THREADS, ENABLE_3D, SHADER_PASS_DATA_SIZE>
{
	public:
		OutputSurface();
		~OutputSurface();

		void draw (Graphics<WIDTH, HEIGHT, THIS_COLOR_FORMAT, THIS_RENDER_API, ENABLE_3D, SHADER_PASS_DATA_SIZE>* graphics) override;
};

#endif // OUTPUTSURFACE_HPP
