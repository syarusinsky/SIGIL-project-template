#ifndef OUTPUTSURFACE_HPP
#define OUTPUTSURFACE_HPP

#include "Surface.hpp"

// adjust for your own screen resolution
#define WIDTH 			800
#define HEIGHT 			480
#define THIS_COLOR_FORMAT 	CP_FORMAT::RGB_24BIT
#define THIS_RENDER_API 	RENDER_API::SOFTWARE
#define NUM_THREADS 		1
#define ENABLE_3D 		true
#define SHADER_PASS_DATA_SIZE 	256

class Font;

class OutputSurface : public Surface<THIS_RENDER_API, WIDTH, HEIGHT, THIS_COLOR_FORMAT, NUM_THREADS, ENABLE_3D, SHADER_PASS_DATA_SIZE>
{
	public:
		OutputSurface();
		~OutputSurface();

		void draw (Graphics<WIDTH, HEIGHT, THIS_COLOR_FORMAT, THIS_RENDER_API, ENABLE_3D, SHADER_PASS_DATA_SIZE>* graphics) override;

		void setBoxTex (Texture<CP_FORMAT::RGBA_32BIT, THIS_RENDER_API>* boxTex);

		static void vShader (TriShaderData<CP_FORMAT::RGBA_32BIT, THIS_RENDER_API, SHADER_PASS_DATA_SIZE>& vShaderData);
		static void fShader (Color& colorOut, TriShaderData<CP_FORMAT::RGBA_32BIT, THIS_RENDER_API, SHADER_PASS_DATA_SIZE>& fShaderData,
				float v1Cur, float v2Cur, float v3Cur, float texCoordX, float texCoordY, float lightAmnt);

	private:
		Mesh 							m_BoxMesh;
		Texture<CP_FORMAT::RGBA_32BIT, THIS_RENDER_API>* 	m_BoxTex;

		void (*m_VShader) (TriShaderData<CP_FORMAT::RGBA_32BIT, THIS_RENDER_API, SHADER_PASS_DATA_SIZE>& vShaderData);
		void (*m_FShader) (Color& colorOut, TriShaderData<CP_FORMAT::RGBA_32BIT, THIS_RENDER_API, SHADER_PASS_DATA_SIZE>& fShaderData,
				float v1Cur, float v2Cur, float v3Cur, float texCoordX, float texCoordY, float lightAmnt);

		Mesh createCubeMesh();
};

#endif // OUTPUTSURFACE_HPP
