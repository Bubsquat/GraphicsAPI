// graphics object for handling objects with textures 

#ifndef _GraphicObjectShadingTexture
#define _GraphicObjectShadingTexture

#include "GraphicObject_Base.h"


class Texture;
class ShaderTexture;

class GraphicObjectShadingTexture : public GraphicObject_Base
{
public:

	GraphicObjectShadingTexture() = delete;
	GraphicObjectShadingTexture(ShaderTexture* shader, Model* model);
	GraphicObjectShadingTexture(const GraphicObjectShadingTexture&) = delete;
	GraphicObjectShadingTexture& operator =(const GraphicObjectShadingTexture&) = default;
	GraphicObjectShadingTexture(GraphicObjectShadingTexture&&) = default;
	GraphicObjectShadingTexture& operator=(GraphicObjectShadingTexture&&) = default;
	~GraphicObjectShadingTexture();

	void SetWorld(const Matrix& m);
	void SetTexture(Texture* tex);


	void Render();

private:
	
	Texture* myTexture;
	ShaderTexture* myShader;
	Matrix world;

};




#endif _GraphicObjectShadingTexture


