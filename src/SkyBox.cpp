// Skybox model

#include "SkyBox.h"
#include "Model.h"
#include "d3dUtil.h"

SkyBox::SkyBox(ID3D11Device* dev, float len)
{
	int nverts = 24;
	StandardVertex* pVerts = new StandardVertex[nverts];
	int ntri = 12;
	TriangleByIndex* pTriList = new TriangleByIndex[ntri];

	// old skybox texture, UVs are wrong 

	//// back face 
	////verts
	//pVerts[0].set(0.5f * len, 0.5f * len, -0.5f * len, 1.0f , 0.333f); // top left
	//pVerts[1].set(-0.5f * len, 0.5f * len, -0.5f * len, 0.75f, 0.333f); // top right
	//pVerts[2].set(0.5f * len, -0.5f * len, -0.5f * len, 1.0f, 0.666f); // bottom left
	//pVerts[3].set(-0.5f * len, -0.5f * len, -0.5f * len, 0.75f, 0.666f); // bottom right
	////tris
	//pTriList[0].set(1, 2, 0); 
	//pTriList[1].set(1, 3, 2);

	//// left
	////verts
	//pVerts[4].set(0.5f * len, 0.5f * len, 0.5f * len, 0.25f, 0.333f); // top left
	//pVerts[5].set(0.5f * len, 0.5f * len, -0.5f * len, 0.0f, 0.333f); // top right
	//pVerts[6].set(0.5f * len, -0.5f * len, 0.5f * len, 0.25f, 0.666f); // bottom left
	//pVerts[7].set(0.5f * len, -0.5f * len, -0.5f * len, 0.0f, 0.666f); // bottom right
	////tris
	//pTriList[2].set(5, 6, 4);
	//pTriList[3].set(5, 7, 6);

	//// right 
	////verts
	//pVerts[8].set(-0.5f * len, 0.5f * len, -0.5f * len, 0.75f, 0.333f); // top left
	//pVerts[9].set(-0.5f * len, 0.5f * len, 0.5f * len, 0.5f, 0.333f); // top right 
	//pVerts[10].set(-0.5f * len, -0.5f * len, -0.5f * len, 0.75f, 0.666f); // bottom left
	//pVerts[11].set(-0.5f * len, -0.5f * len, 0.5f * len, 0.5f, 0.666f); // bottom right
	////tris
	//pTriList[4].set(9, 10, 8);
	//pTriList[5].set(9, 11, 10);

	//// front
	////verts
	//pVerts[12].set(0.5f * len, 0.5f * len, 0.5f * len, 0.25f, 0.333f); // top left
	//pVerts[13].set(-0.5f * len, 0.5f * len, 0.5f * len, 0.5f, 0.333f); // top right
	//pVerts[14].set(0.5f * len, -0.5f * len, 0.5f * len, 0.25f, 0.666f); // bottom left
	//pVerts[15].set(-0.5f * len, -0.5f * len, 0.5f * len, 0.5f, 0.666f); // bottom right
	////tris
	//pTriList[6].set(13, 12, 14);
	//pTriList[7].set(13, 14, 15);

	//// top
	////verts
	//pVerts[16].set(0.5f * len, 0.5f * len, 0.5f * len, 0.25f, 0.333f); // top left
	//pVerts[17].set(-0.5f * len, 0.5f * len, 0.5f * len, 0.5f, 0.333f); // top right
	//pVerts[18].set(0.5f * len, 0.5f * len, -0.5f * len, 0.25f, 0.0f); // bottom left
	//pVerts[19].set(-0.5f * len, 0.5f * len, -0.5f * len, 0.5f, 0.0f); // bottom right
	////tris
	//pTriList[8].set(17, 18, 16);
	//pTriList[9].set(17, 19, 18);

	//// bottom
	//	//verts
	//pVerts[20].set(0.5f * len, -0.5f * len, -0.5f * len, 0.25f, 0.666f); // top left
	//pVerts[21].set(-0.5f * len, -0.5f * len, -0.5f * len, 0.5f, 0.666f); // top right
	//pVerts[22].set(0.5f * len, -0.5f * len, 0.5f * len, 0.25f, 1.0f); // bottom left
	//pVerts[23].set(-0.5f * len, -0.5f * len, 0.5f * len, 0.5f, 1.0f); // bottom right
	////tris
	//pTriList[10].set(21, 22, 20);
	//pTriList[11].set(21, 23, 22);

	// new skybox texure with different UVs

		// back face 
	//verts
	pVerts[0].set(0.5f * len, 0.5f * len, -0.5f * len, 0.25f, 0.666f);	// top left       
	pVerts[1].set(-0.5f * len, 0.5f * len, -0.5f * len, 0.5f, 0.666f);	// top right	 
	pVerts[2].set(0.5f * len, -0.5f * len, -0.5f * len, 0.25f, 1.0f);	// bottom left	 
	pVerts[3].set(-0.5f * len, -0.5f * len, -0.5f * len, 0.5f, 1.0f);	// bottom right 
	//tris
	pTriList[0].set(1, 2, 0); 
	pTriList[1].set(1, 3, 2);

	// left
	//verts
	pVerts[4].set(0.5f * len, 0.5f * len, 0.5f * len, 0.25f, 0.333f); // top left
	pVerts[5].set(0.5f * len, 0.5f * len, -0.5f * len, 0.25f, 0.666f); // top right
	pVerts[6].set(0.5f * len, -0.5f * len, 0.5f * len, 0.0f, 0.333f); // bottom left
	pVerts[7].set(0.5f * len, -0.5f * len, -0.5f * len, 0.0f, 0.666f); // bottom right
	//tris
	pTriList[2].set(5, 6, 4);
	pTriList[3].set(5, 7, 6);

	// right 
	//verts
	pVerts[8].set(-0.5f * len, 0.5f * len, -0.5f * len, 0.50f, 0.666f); // top left
	pVerts[9].set(-0.5f * len, 0.5f * len, 0.5f * len, 0.5f, 0.333f); // top right 
	pVerts[10].set(-0.5f * len, -0.5f * len, -0.5f * len, 0.75f, 0.666f); // bottom left
	pVerts[11].set(-0.5f * len, -0.5f * len, 0.5f * len, 0.75f, 0.333f); // bottom right
	//tris
	pTriList[4].set(9, 10, 8);
	pTriList[5].set(9, 11, 10);

	// front
	//verts
	pVerts[12].set(0.5f * len, 0.5f * len, 0.5f * len, 0.25f, 0.333f);		// top left
	pVerts[13].set(-0.5f * len, 0.5f * len, 0.5f * len, 0.50f, 0.333f);		// top right
	pVerts[14].set(0.5f * len, -0.5f * len, 0.5f * len, 0.25f, 0.0f);		// bottom left
	pVerts[15].set(-0.5f * len, -0.5f * len, 0.5f * len, 0.50f, 0.0f);		// bottom right
	//tris
	pTriList[6].set(13, 12, 14);
	pTriList[7].set(13, 14, 15);

	// top
	//verts
	pVerts[16].set(0.5f * len, 0.5f * len, 0.5f * len, 0.25f, 0.333f); // top left
	pVerts[17].set(-0.5f * len, 0.5f * len, 0.5f * len, 0.5f, 0.333f); // top right
	pVerts[18].set(0.5f * len, 0.5f * len, -0.5f * len, 0.25f, 0.666f); // bottom left
	pVerts[19].set(-0.5f * len, 0.5f * len, -0.5f * len, 0.5f, 0.666f); // bottom right
	//tris
	pTriList[8].set(17, 18, 16);
	pTriList[9].set(17, 19, 18);

	// bottom
		//verts
	pVerts[20].set(0.5f * len, -0.5f * len, -0.5f * len, 0.75f, 0.333f);	// top left
	pVerts[21].set(-0.5f * len, -0.5f * len, -0.5f * len, 1.0f, 0.333f);	// top right
	pVerts[22].set(0.5f * len, -0.5f * len, 0.5f * len, 0.75f, 0.666f);		// bottom left
	pVerts[23].set(-0.5f * len, -0.5f * len, 0.5f * len, 1.0f, 0.666f);		// bottom right
	//tris
	pTriList[10].set(21, 22, 20);
	pTriList[11].set(21, 23, 22);



	pSkybox = new Model(dev, pVerts, nverts, pTriList, ntri);

	delete[] pVerts;
	delete[] pTriList;
}

SkyBox::~SkyBox()
{
	delete pSkybox;
}

void SkyBox::Render(ID3D11DeviceContext* context)
{
	pSkybox->SetToContext(context);
	pSkybox->Render(context);
}

