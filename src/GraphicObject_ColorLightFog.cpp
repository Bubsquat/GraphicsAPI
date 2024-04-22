// graphics object for color light shader that includes fog functionality 

#include "GraphicObject_ColorLightFog.h"
#include "Texture.h"
#include "ShaderColorLightFog.h"
#include "Model.h"
#include "d3dUtil.h"

GraphicObject_ColorLightFog::GraphicObject_ColorLightFog(ShaderColorLightFog* _shader, Model* _model)
{
	SetModel(_model);
	myShader = _shader;
	world = Matrix(IDENTITY);

}

GraphicObject_ColorLightFog::~GraphicObject_ColorLightFog()
{


}


void GraphicObject_ColorLightFog::SetWorld(const Matrix& _world)
{
	world = _world;
}

void GraphicObject_ColorLightFog::SetMaterialProperties(const Vect& _amb, const Vect& _dif, const Vect& _sp)
{
	amb = _amb;
	dif = _dif;
	sp = _sp;

}

void GraphicObject_ColorLightFog::Render()
{
	myShader->SendWorldAndMaterial(world, amb, dif, sp);

	pModel->SetToContext(myShader->GetContext());
	pModel->Render(myShader->GetContext());
}