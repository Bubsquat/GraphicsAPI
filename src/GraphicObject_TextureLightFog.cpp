// graphics object for texture shader with lighting and fog

#include "GraphicObject_TextureLightFog.h"
#include "ShaderTextureLightFog.h"
#include "Model.h"
#include "d3dUtil.h"
#include "Texture.h"

GraphicObject_TextureLightFog::GraphicObject_TextureLightFog(ShaderTextureLightFog* _shader, Model* _model)
{
	SetModel(_model);
	myTexture = nullptr;
	myShader = _shader;
	world = Matrix(IDENTITY);
}

GraphicObject_TextureLightFog::~GraphicObject_TextureLightFog()
{

}

void GraphicObject_TextureLightFog::SetTexture(Texture* tex)
{
	myTexture = tex;
}

void GraphicObject_TextureLightFog::SetWorld(const Matrix& _world)
{
	world = _world;
}

void GraphicObject_TextureLightFog::SetMaterialProperties(const Vect& _amb, const Vect& _dif, const Vect& _sp)
{
	amb = _amb;
	dif = _dif;
	sp = _sp;

}

void GraphicObject_TextureLightFog::Render()
{
	assert(myTexture != nullptr);

	myShader->SetTextureResourceAndSampler(myTexture);
	myShader->SendWorldAndMaterial(world, amb, dif, sp);
	pModel->SetToContext(myShader->GetContext());
	pModel->Render(myShader->GetContext());
}