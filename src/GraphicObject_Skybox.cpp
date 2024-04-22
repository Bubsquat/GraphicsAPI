// graphics object for handling skybox, uses texture shaded without light or fog

#include "GraphicObject_Skybox.h"
#include "SkyBox.h"
#include "ShaderTexture.h"

GraphicObject_Skybox::GraphicObject_Skybox(ShaderTexture* shader, SkyBox* _skybox)
{

	skybox = _skybox;
	myShader = shader;
	myTexture = nullptr;
	world = Matrix(IDENTITY);

}


GraphicObject_Skybox::~GraphicObject_Skybox()
{
	
}

void GraphicObject_Skybox::Render()
{
	myShader->SetTextureResourceAndSampler(myTexture);
	myShader->SendWorld(world);

	skybox->Render(myShader->GetContext());

}

void GraphicObject_Skybox::SetWorld(const Matrix& m)
{
	world = m;
}

void GraphicObject_Skybox::SetTexture(Texture* tex)
{
	myTexture = tex;
}

void GraphicObject_Skybox::SetSkybox(SkyBox* _sb)
{
	skybox = _sb;
}