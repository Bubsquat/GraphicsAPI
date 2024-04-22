#include "GraphicObject_Color.h"
#include "Model.h"
#include "ShaderColor.h"
#include <assert.h>
#include "d3dUtil.h"

GraphicObject_Color::GraphicObject_Color(ShaderColor* shader,  Model* mod)
{
	SetModel(mod );
	pShader = shader;


	for (int i = 0; i < pModel->GetMeshCount(); i++)
	{
		MeshColors[i] = Colors::HotPink;
	}
	World = Matrix(IDENTITY);
}

GraphicObject_Color::~GraphicObject_Color()
{

}

void GraphicObject_Color::SetColor(const Vect& col) 
{
	MeshColors[0] = col;
}

void GraphicObject_Color::SetColor(const Vect& col, int meshNum)
{
	MeshColors[meshNum] = col;
}

void GraphicObject_Color::SetWorld(const Matrix& m) 
{ 
	World = m;
}

void GraphicObject_Color::Render()
{
	//pShader->SendWorldColor(World, Color);
	pModel->SetToContext(pShader->GetContext());
	//pModel->Render(pShader->GetContext());

	for (int i = 0; i < pModel->GetMeshCount(); i++)
	{
		pShader->SendWorldColor(World, MeshColors[i]);
		pModel->RenderMesh(pShader->GetContext(), i);
	}
	
}