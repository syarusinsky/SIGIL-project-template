#include "OutputSurface.hpp"

#include <string>

OutputSurface::OutputSurface() :
	m_CurrentFPS( 0 ),
	m_VShader( vShader ),
	m_FShader( fShader )
{
	m_BoxMesh = createCubeMesh();
	for ( Face& face : m_BoxMesh.faces )
	{
		Vector<4> faceNormals = face.calcFaceNormals();
		for ( Vertex& vertex : face.vertices )
		{
			vertex.normal.at(0) = faceNormals.at(0);
			vertex.normal.at(1) = faceNormals.at(1);
			vertex.normal.at(2) = faceNormals.at(2);
			vertex.normal.at(3) = faceNormals.at(3);
		}
	}
}

OutputSurface::~OutputSurface()
{
}

void OutputSurface::draw (Graphics<WIDTH, HEIGHT, THIS_COLOR_FORMAT, THIS_RENDER_API, ENABLE_3D, SHADER_PASS_DATA_SIZE>* graphics)
{
	graphics->setColor( 0.0f, 0.0f, 0.0f );
	graphics->fill();

	std::array<Texture<CP_FORMAT::RGBA_32BIT, THIS_RENDER_API>*, 5> texArray1 = { m_BoxTex };
	const float aspectRatio = static_cast<float>( this->getWidth() ) / static_cast<float>( this->getHeight() );
	Camera3D camera( 0.01f, 1000.0f, 60.0f, aspectRatio );
	Mesh boxMesh = m_BoxMesh;
	boxMesh.transformMat = generateIdentityMatrix();
	static float xTranslate = 0.0f;
	static float xTranslateIncr = 0.1f;
	static float xRotation = 0.0f;
	static float xRotationIncr = 1.0f;
	TriShaderData<CP_FORMAT::RGBA_32BIT, THIS_RENDER_API, SHADER_PASS_DATA_SIZE> shaderData
	{
		texArray1, camera, Color(), nullptr, m_VShader, m_FShader
	};
	boxMesh.scale( 25.0f );
	boxMesh.rotate( 180.0f, xRotation, 0.0f );
	boxMesh.translate( 0.0f, 0.0f, 75.0f );
	boxMesh.translate( 0.0f, xTranslate * 0.5f, 0.0f );
	for ( Face face : boxMesh.faces )
	{
		face.vertices[0].vec = face.vertices[0].vec * boxMesh.transformMat;
		face.vertices[1].vec = face.vertices[1].vec * boxMesh.transformMat;
		face.vertices[2].vec = face.vertices[2].vec * boxMesh.transformMat;
		face.vertices[0].normal = face.vertices[0].normal * boxMesh.transformMat;
		face.vertices[1].normal = face.vertices[1].normal * boxMesh.transformMat;
		face.vertices[2].normal = face.vertices[2].normal * boxMesh.transformMat;

		graphics->drawTriangleShaded( face, shaderData );
	}

	xTranslate += xTranslateIncr;
	if ( xTranslate >= 50.0f )
	{
		xTranslateIncr *= -1.0f;
	}
	else if ( xTranslate <= -50.0f )
	{
		xTranslateIncr *= -1.0f;
	}
	xRotation += xRotationIncr;
	if ( xRotation >= 360.0f || xRotation <= 0.0f )
	{
		xRotationIncr = -xRotationIncr;
	}

	std::string counterString = "FPS: " + std::to_string( m_CurrentFPS );
	graphics->setColor( 1.0f, 1.0f, 1.0f );
	graphics->drawText( 0.0f, 0.0f, counterString.c_str(), 2.0f );
}

void OutputSurface::setBoxTex (Texture<CP_FORMAT::RGBA_32BIT, THIS_RENDER_API>* boxTex)
{
	m_BoxTex = boxTex;
}

void OutputSurface::vShader (TriShaderData<CP_FORMAT::RGBA_32BIT, THIS_RENDER_API, SHADER_PASS_DATA_SIZE>& vShaderData)
{
}

void OutputSurface::fShader (Color& colorOut, TriShaderData<CP_FORMAT::RGBA_32BIT, THIS_RENDER_API, SHADER_PASS_DATA_SIZE>& fShaderData,
		float v1Cur, float v2Cur, float v3Cur, float texCoordX, float texCoordY, float lightAmnt)
{
	colorOut = fShaderData.textures[0]->getColor( texCoordX, texCoordY ) * lightAmnt;
}

Mesh OutputSurface::createCubeMesh()
{
	Mesh cube;
	cube.faces =
	{
		// front face
		Face{ {Vertex{Vector<4>({0.0f, 0.0f, 0.0f, 1.0f}), {}, Vector<2>({0.0f, 0.0f})}, Vertex{Vector<4>({0.0f, 1.0f, 0.0f, 1.0f}), {}, Vector<2>({0.0f, 1.0f})}, Vertex{Vector<4>({1.0f, 1.0f, 0.0f, 1.0f}), {}, Vector<2>({1.0f, 1.0f})}} },
		Face{ {Vertex{Vector<4>({0.0f, 0.0f, 0.0f, 1.0f}), {}, Vector<2>({0.0f, 0.0f})}, Vertex{Vector<4>({1.0f, 1.0f, 0.0f, 1.0f}), {}, Vector<2>({1.0f, 1.0f})}, Vertex{Vector<4>({1.0f, 0.0f, 0.0f, 1.0f}), {}, Vector<2>({1.0f, 0.0f})}} },
		// right face
		Face{ {Vertex{Vector<4>({1.0f, 0.0f, 0.0f, 1.0f}), {}, Vector<2>({0.0f, 0.0f})}, Vertex{Vector<4>({1.0f, 1.0f, 0.0f, 1.0f}), {}, Vector<2>({0.0f, 1.0f})}, Vertex{Vector<4>({1.0f, 1.0f, 1.0f, 1.0f}), {}, Vector<2>({1.0f, 1.0f})}} },
		Face{ {Vertex{Vector<4>({1.0f, 0.0f, 0.0f, 1.0f}), {}, Vector<2>({0.0f, 0.0f})}, Vertex{Vector<4>({1.0f, 1.0f, 1.0f, 1.0f}), {}, Vector<2>({1.0f, 1.0f})}, Vertex{Vector<4>({1.0f, 0.0f, 1.0f, 1.0f}), {}, Vector<2>({1.0f, 0.0f})}} },
		// back face
		Face{ {Vertex{Vector<4>({1.0f, 0.0f, 1.0f, 1.0f}), {}, Vector<2>({0.0f, 0.0f})}, Vertex{Vector<4>({1.0f, 1.0f, 1.0f, 1.0f}), {}, Vector<2>({0.0f, 1.0f})}, Vertex{Vector<4>({0.0f, 1.0f, 1.0f, 1.0f}), {}, Vector<2>({1.0f, 1.0f})}} },
		Face{ {Vertex{Vector<4>({1.0f, 0.0f, 1.0f, 1.0f}), {}, Vector<2>({0.0f, 0.0f})}, Vertex{Vector<4>({0.0f, 1.0f, 1.0f, 1.0f}), {}, Vector<2>({1.0f, 1.0f})}, Vertex{Vector<4>({0.0f, 0.0f, 1.0f, 1.0f}), {}, Vector<2>({1.0f, 0.0f})}} },
		// left face
		Face{ {Vertex{Vector<4>({0.0f, 0.0f, 1.0f, 1.0f}), {}, Vector<2>({0.0f, 0.0f})}, Vertex{Vector<4>({0.0f, 1.0f, 1.0f, 1.0f}), {}, Vector<2>({0.0f, 1.0f})}, Vertex{Vector<4>({0.0f, 1.0f, 0.0f, 1.0f}), {}, Vector<2>({1.0f, 1.0f})}} },
		Face{ {Vertex{Vector<4>({0.0f, 0.0f, 1.0f, 1.0f}), {}, Vector<2>({0.0f, 0.0f})}, Vertex{Vector<4>({0.0f, 1.0f, 0.0f, 1.0f}), {}, Vector<2>({1.0f, 1.0f})}, Vertex{Vector<4>({0.0f, 0.0f, 0.0f, 1.0f}), {}, Vector<2>({1.0f, 0.0f})}} },
		// top face
		Face{ {Vertex{Vector<4>({0.0f, 1.0f, 0.0f, 1.0f}), {}, Vector<2>({0.0f, 0.0f})}, Vertex{Vector<4>({0.0f, 1.0f, 1.0f, 1.0f}), {}, Vector<2>({0.0f, 1.0f})}, Vertex{Vector<4>({1.0f, 1.0f, 1.0f, 1.0f}), {}, Vector<2>({1.0f, 1.0f})}} },
		Face{ {Vertex{Vector<4>({0.0f, 1.0f, 0.0f, 1.0f}), {}, Vector<2>({0.0f, 0.0f})}, Vertex{Vector<4>({1.0f, 1.0f, 1.0f, 1.0f}), {}, Vector<2>({1.0f, 1.0f})}, Vertex{Vector<4>({1.0f, 1.0f, 0.0f, 1.0f}), {}, Vector<2>({1.0f, 0.0f})}} },
		// bottom face
		Face{ {Vertex{Vector<4>({0.0f, 0.0f, 1.0f, 1.0f}), {}, Vector<2>({0.0f, 0.0f})}, Vertex{Vector<4>({0.0f, 0.0f, 0.0f, 1.0f}), {}, Vector<2>({0.0f, 1.0f})}, Vertex{Vector<4>({1.0f, 0.0f, 0.0f, 1.0f}), {}, Vector<2>({1.0f, 1.0f})}} },
		Face{ {Vertex{Vector<4>({0.0f, 0.0f, 1.0f, 1.0f}), {}, Vector<2>({0.0f, 0.0f})}, Vertex{Vector<4>({1.0f, 0.0f, 0.0f, 1.0f}), {}, Vector<2>({1.0f, 1.0f})}, Vertex{Vector<4>({1.0f, 0.0f, 1.0f, 1.0f}), {}, Vector<2>({1.0f, 0.0f})}} }
	};
	return cube;
}
