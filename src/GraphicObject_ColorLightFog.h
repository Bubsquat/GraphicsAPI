// graphics object for color light shader that includes fog functionality 

#ifndef _GraphicObject_ColorLightFog
#define _GraphicObject_ColorLightFog

#include "d3dUtil.h"
#include "GraphicObject_Base.h"

class ShaderColorLightFog;

class GraphicObject_ColorLightFog : public GraphicObject_Base
{
public:

	GraphicObject_ColorLightFog() = delete;
	GraphicObject_ColorLightFog(ShaderColorLightFog* shader, Model* model);
	GraphicObject_ColorLightFog(const GraphicObject_ColorLightFog&) = delete;
	GraphicObject_ColorLightFog& operator =(const GraphicObject_ColorLightFog&) = default;
	GraphicObject_ColorLightFog(GraphicObject_ColorLightFog&&) = default;
	GraphicObject_ColorLightFog& operator=(GraphicObject_ColorLightFog&&) = default;
	~GraphicObject_ColorLightFog();

	void Render();

	void SetWorld(const Matrix& m);
	void SetMaterialProperties(const Vect& amb, const Vect& dif, const Vect& sp);

private:

	Matrix world;
	ShaderColorLightFog* myShader;

	Vect amb;
	Vect dif;
	Vect sp;

};

#endif _GraphicObject_ColorLightFog
