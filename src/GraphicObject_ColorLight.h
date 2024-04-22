// graphics object for color light shader 

#ifndef _GraphicObject_ColorLight
#define _GraphicObject_ColorLight

#include "GraphicObject_Base.h"

class ShaderColorLight;
class Model;

class GraphicObject_ColorLight : public GraphicObject_Base
{
public:
	GraphicObject_ColorLight() = delete; 
	GraphicObject_ColorLight(ShaderColorLight* shader, Model* model);
	GraphicObject_ColorLight(const GraphicObject_ColorLight&) = delete;
	GraphicObject_ColorLight& operator =(const GraphicObject_ColorLight&) = default;
	GraphicObject_ColorLight(GraphicObject_ColorLight&&) = default;
	GraphicObject_ColorLight& operator=(GraphicObject_ColorLight&&) = default;
	~GraphicObject_ColorLight();

	void Render();

	void SetWorld(const Matrix& m);
	void SetMaterialProperties(const Vect& amb, const Vect& dif, const Vect& sp);

private:

	Matrix world;
	ShaderColorLight* myShader;

	Vect amb;
	Vect dif;
	Vect sp;

	bool matPropsSet;
};

#endif _GraphicObject_ColorLight
