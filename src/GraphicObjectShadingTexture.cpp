// graphics object for handling objects with textures 

#include "GraphicObjectShadingTexture.h"
#include "Texture.h"
#include "ShaderTexture.h"
#include "Model.h"
#include <assert.h>

GraphicObjectShadingTexture::GraphicObjectShadingTexture(ShaderTexture* shader, Model* model)
{

	myTexture = nullptr;
	myShader = shader;
	SetModel(model);

	world = Matrix(IDENTITY);

}

GraphicObjectShadingTexture::~GraphicObjectShadingTexture()
{}


void GraphicObjectShadingTexture::Render()
{
	assert(myTexture != nullptr);
	
	myShader->SetTextureResourceAndSampler(myTexture);
	myShader->SendWorld(world);
	pModel->SetToContext(myShader->GetContext());
	pModel->Render(myShader->GetContext());

}

void GraphicObjectShadingTexture::SetWorld(const Matrix& _world)
{
	world = _world;
}

void GraphicObjectShadingTexture::SetTexture(Texture* tex)
{
	myTexture = tex;
}