// graphics object for color light shader 

#include "GraphicObject_ColorLight.h"
#include "Texture.h"
#include "ShaderColorLight.h"
#include "Model.h"
#include "d3dUtil.h"

GraphicObject_ColorLight::GraphicObject_ColorLight(ShaderColorLight* _shader, Model* _model)
{
	SetModel(_model);
	myShader = _shader;
	world = Matrix(IDENTITY);
	matPropsSet = false;
}

GraphicObject_ColorLight::~GraphicObject_ColorLight()
{}


void GraphicObject_ColorLight::Render()
{

	myShader->SendWorldAndMaterial(world, amb, dif, sp);

	pModel->SetToContext(myShader->GetContext());
	pModel->Render(myShader->GetContext());

}

void GraphicObject_ColorLight::SetWorld(const Matrix& _world)
{
	world = _world;
}


void GraphicObject_ColorLight::SetMaterialProperties(const Vect& _amb, const Vect& _dif, const Vect& _sp)
{
	amb = _amb;
	dif = _dif;
	sp = _sp;
	matPropsSet = true;
}