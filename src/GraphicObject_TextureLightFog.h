// graphics object for texture shader with lighting and fog

#ifndef _GraphicObject_TextureLightFog
#define _GraphicObject_TextureLightFog

#include "GraphicObject_Base.h"


class Texture;
class ShaderTextureLightFog;

class GraphicObject_TextureLightFog : public GraphicObject_Base
{
public:

	GraphicObject_TextureLightFog() = delete;
	GraphicObject_TextureLightFog(ShaderTextureLightFog* shader, Model* model);
	GraphicObject_TextureLightFog(const GraphicObject_TextureLightFog&) = delete;
	GraphicObject_TextureLightFog& operator =(const GraphicObject_TextureLightFog&) = default;
	GraphicObject_TextureLightFog(GraphicObject_TextureLightFog&&) = default;
	GraphicObject_TextureLightFog& operator=(GraphicObject_TextureLightFog&&) = default;
	~GraphicObject_TextureLightFog();

	void SetWorld(const Matrix& m);
	void SetTexture(Texture* tex);
	void SetMaterialProperties(const Vect& amb, const Vect& dif, const Vect& sp);

	void Render();

private:

	Texture* myTexture;
	ShaderTextureLightFog* myShader;
	Matrix world;

	Vect amb;
	Vect dif;
	Vect sp;

};




#endif _GraphicObject_TextureLightFog


