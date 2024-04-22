// graphics object for handling skybox, uses texture shaded without light or fog

#ifndef _GraphicObject_Skybox
#define _GraphicObject_Skybox

#include "GraphicObject_Base.h"


class Texture;
class ShaderTexture;
class SkyBox;

class GraphicObject_Skybox : public GraphicObject_Base
{
public:

	GraphicObject_Skybox() = delete;
	GraphicObject_Skybox(ShaderTexture* shader, SkyBox* Skybox);
	GraphicObject_Skybox(const GraphicObject_Skybox&) = delete;
	GraphicObject_Skybox& operator =(const GraphicObject_Skybox&) = default;
	GraphicObject_Skybox(GraphicObject_Skybox&&) = default;
	GraphicObject_Skybox& operator=(GraphicObject_Skybox&&) = default;
	~GraphicObject_Skybox();

	void SetWorld(const Matrix& m);
	void SetTexture(Texture* tex);
	void SetSkybox(SkyBox* s);

	void SetModel(Model* m) = delete;

	void Render();

private:

	Texture* myTexture;
	ShaderTexture* myShader;
	Matrix world;
	SkyBox* skybox;

};




#endif _GraphicObject_Skybox
