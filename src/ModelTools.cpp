#include "ModelTools.h"
//#include "Enum.h"
//#include <math.h>
#include "Matrix.h"
#include <assert.h>
#include "Model.h"
#include "d3dUtil.h"


/// Creates the unit box centered at the origin
void ModelTools::CreateUnitBox(StandardVertex *&pVerts, int& nverts, TriangleByIndex *&pTriList, int& ntri)
{
	nverts = 8;
	pVerts = new StandardVertex[nverts];
	ntri = 12;
	pTriList = new TriangleByIndex[ntri];

	pVerts[0].set(-0.5f, -0.5f, -0.5f, Colors::Black);
	pVerts[1].set(-0.5f, +0.5f, -0.5f, Colors::Lime);
	pVerts[2].set(+0.5f, +0.5f, -0.5f, Colors::Yellow);
	pVerts[3].set(+0.5f, -0.5f, -0.5f, Colors::Red );
	pVerts[4].set(-0.5f, -0.5f, +0.5f, Colors::Blue);
	pVerts[5].set(-0.5f, +0.5f, +0.5f, Colors::Cyan);
	pVerts[6].set(+0.5f, +0.5f, +0.5f, Colors::White);
	pVerts[7].set(+0.5f, -0.5f, +0.5f, Colors::Magenta);

	// back face
	pTriList[0].set(0, 1, 2);
	pTriList[1].set(0, 2, 3);

	// front face
	pTriList[2].set(4, 6, 5);
	pTriList[3].set(4, 7, 6);

	// left face
	pTriList[4].set(4, 5, 1);
	pTriList[5].set(4, 1, 0);

	// right face
	pTriList[6].set(3, 2, 6);
	pTriList[7].set(3, 6, 7);

	// top face
	pTriList[8].set(1, 5, 6);
	pTriList[9].set(1, 6, 2);

	// bottom face
	pTriList[10].set(4, 0, 3);
	pTriList[11].set(4, 3, 7);
}

void ModelTools::CreateUnitBoxRepTexture(StandardVertex *&pVerts, int& nverts, TriangleByIndex *&pTriList, int& ntri)
{
	nverts = 24;
	pVerts = new StandardVertex[nverts];
	ntri = 12;
	pTriList = new TriangleByIndex[ntri];



	// Setting up faces
	// Forward
	int vind = 0;
	int tind = 0;
	pVerts[vind].set(0.5f, 0.5f, 0.5f, 1, 0, 0, 0, 1 );
	pVerts[vind + 1].set(-0.5f, 0.5f, 0.5f, 0, 0, 0, 0, 1);
	pVerts[vind + 2].set(-0.5f, -0.5f, 0.5f, 0, 1, 0, 0, 1);
	pVerts[vind + 3].set(0.5f, -0.5f, 0.5f, 1, 1, 0, 0, 1);
	pTriList[tind].set(vind, vind + 1, vind + 2);
	pTriList[tind + 1].set(vind, vind + 2, vind + 3);

	// Back
	vind += 4;
	tind += 2;
	pVerts[vind].set(0.5f, 0.5f, -0.5f, 0, 0, 0, 0, -1);
	pVerts[vind + 1].set(-0.5f, 0.5f, -0.5f, 1, 0, 0, 0, -1);
	pVerts[vind + 2].set(-0.5f, -0.5f, -0.5f, 1, 1, 0, 0, -1);
	pVerts[vind + 3].set(0.5f, -0.5f, -0.5f, 0, 1, 0, 0, -1);
	pTriList[tind].set(vind + 2, vind + 1, vind);
	pTriList[tind + 1].set(vind + 3, vind + 2, vind);

	// Left
	vind += 4;
	tind += 2;
	pVerts[vind].set(0.5f, 0.5f, -0.5f, 1, 0, 1, 0, 0);
	pVerts[vind + 1].set(0.5f, 0.5f, 0.5f, 0, 0, 1, 0, 0);
	pVerts[vind + 2].set(0.5f, -0.5f, 0.5f, 0, 1, 1, 0, 0);
	pVerts[vind + 3].set(0.5f, -0.5f, -0.5f, 1, 1, 1, 0, 0);
	pTriList[tind].set(vind, vind + 1, vind + 2);
	pTriList[tind + 1].set(vind, vind + 2, vind + 3);

	// Right
	vind += 4;
	tind += 2;
	pVerts[vind].set(-0.5f, 0.5f, 0.5f, 1, 0, -1, 0, 0);
	pVerts[vind + 1].set(-0.5f, 0.5f, -0.5f, 0, 0, -1, 0, 0);
	pVerts[vind + 2].set(-0.5f, -0.5f, -0.5f, 0, 1, -1, 0, 0);
	pVerts[vind + 3].set(-0.5f, -0.5f, 0.5f, 1, 1, -1, 0, 0);
	pTriList[tind].set(vind, vind + 1, vind + 2);
	pTriList[tind + 1].set(vind, vind + 2, vind + 3);

	// Top
	vind += 4;
	tind += 2;
	pVerts[vind].set(0.5f, 0.5f, -0.5f, 1, 0, 0, 1, 0);
	pVerts[vind + 1].set(-0.5f, 0.5f, -0.5f, 0, 0, 0, 1, 0);
	pVerts[vind + 2].set(-0.5f, 0.5f, 0.5f, 0, 1, 0, 1, 0);
	pVerts[vind + 3].set(0.5f, 0.5f, 0.5f, 1, 1, 0, 1, 0);
	pTriList[tind].set(vind, vind + 1, vind + 2);
	pTriList[tind + 1].set(vind, vind + 2, vind + 3);

	// Bottom
	vind += 4;
	tind += 2;
	pVerts[vind].set(0.5f, -0.5f, 0.5f, 1, 0, 0, -1, 0);
	pVerts[vind + 1].set(-0.5f, -0.5f, 0.5f, 0, 0, 0, -1, 0);
	pVerts[vind + 2].set(-0.5f, -0.5f, -0.5f, 0, 1, 0, -1, 0);
	pVerts[vind + 3].set(0.5f, -0.5f, -0.5f, 1, 1, 0, -1, 0);
	pTriList[tind].set(vind, vind + 1, vind + 2);
	pTriList[tind + 1].set(vind, vind + 2, vind + 3);
}


void ModelTools::CreateUnitPyramid(StandardVertex*& pVerts, int& nverts, TriangleByIndex*& pTriList, int& ntri)
{

	nverts = 16;
	pVerts = new StandardVertex[nverts];
	ntri = 6;
	pTriList = new TriangleByIndex[ntri];

	// front face 
	//verts 
	pVerts[0].set(0.0f, 0.5f, 0.0f, 0.5f, 0.0f);
	pVerts[1].set(0.5f, -0.5f, -0.5f, 0.0f, 1.0f);
	pVerts[2].set(-0.5f, -0.5f, -0.5f, 1.0f, 1.0f);

	//face
	pTriList[0].set(0, 1, 2);

	// left face
	//verts
	pVerts[3].set(0.0f, 0.5f, 0.0f, 0.5f, 0.0f);
	pVerts[4].set(0.5f, -0.5f, 0.5f, 0.0f, 1.0f);
	pVerts[5].set(0.5f, -0.5f, -0.5f, 1.0f, 1.0f);

	//face
	pTriList[1].set(3, 4, 5);

	// right face
	//verts
	pVerts[6].set(0.0f, 0.5f, 0.0f, 0.5f, 0.0f);
	pVerts[7].set(-0.5f, -0.5f, -0.5f, 0.0f, 1.0f);
	pVerts[8].set(-0.5f, -0.5f, 0.5f, 1.0f, 1.0f);

	//face 
	pTriList[2].set(6, 7, 8);

	// back face
	//verts
	pVerts[9].set(0.0f, 0.5f, 0.0f, 0.5f, 0.0f);
	pVerts[10].set(-0.5f, -0.5f, 0.5f, 0.0f, 1.0f);
	pVerts[11].set(0.5f, -0.5f, 0.5f, 1.0f, 1.0f);

	//face
	pTriList[3].set(9, 10, 11);

	// bottom face 
	//verts
	pVerts[12].set(0.5f, -0.5f, -0.5f, 0.0f, 0.0f); // top left 
	pVerts[13].set(-0.5f, -0.5f, -0.5f, 1.0f, 0.0f); // top right
	pVerts[14].set(0.5f, -0.5f, 0.5f, 0.0f, 1.0f); // bottom left 
	pVerts[15].set(-0.5f, -0.5f, 0.5f, 1.0f, 1.0f); // bottom right 

	//face
	pTriList[4].set(12, 14, 13);
	pTriList[5].set(13, 14, 15);

}

void ModelTools::CreateUnitBoxSixFaceTexture(StandardVertex*& pVerts, int& nverts, TriangleByIndex*& pTriList, int& ntri)
{

	nverts = 24;
	pVerts = new StandardVertex[nverts];
	ntri = 12;
	pTriList = new TriangleByIndex[ntri];

	// front face
	//verts
	pVerts[0].set(0.5f, 0.5f, -0.5f, 0.25f, 0.375f); // top left
	pVerts[1].set(-0.5f, 0.5f, -0.5f, 0.25f, 0.625f); // top right 
	pVerts[2].set(0.5f, -0.5f, -0.5f, 0.0f, 0.375f); // bottom left
	pVerts[3].set(-0.5f, -0.5f, -0.5f, 0.0f, 0.625f); // bottom right
	//tris
	pTriList[0].set(1, 0, 2);
	pTriList[1].set(1, 2, 3);

	// left face 
	//verts 
	pVerts[4].set(0.5f, 0.5f, 0.5f, 0.25f, 0.625f); // top left
	pVerts[5].set(0.5f, 0.5f, -0.5f, 0.5f, 0.625f); // top right
	pVerts[6].set(0.5f, -0.5f, 0.5f, 0.25f, 0.875f); // bottom left
	pVerts[7].set(0.5f, -0.5f, -0.5f, 0.5f, 0.875f); // bottom right
	//tris
	pTriList[2].set(5, 4, 6);
	pTriList[3].set(5, 6, 7);

	// right face
	//verts
	pVerts[8].set(-0.5f, 0.5f, -0.5f, 0.5f, 0.375f); // top left
	pVerts[9].set(-0.5f, 0.5f, 0.5f, 0.25f, 0.375f); // top right 
	pVerts[10].set(-0.5f, -0.5f, -0.5f, 0.5f, 0.125f); // bottom left
	pVerts[11].set(-0.5f, -0.5f, 0.5f, 0.25f, 0.125f); // bottom right
	//tris
	pTriList[4].set(9, 8, 10);
	pTriList[5].set(9, 10, 11);

	// back face
	//verts
	pVerts[12].set(0.5f, 0.5f, 0.5f, 0.5f, 0.375f); // top left
	pVerts[13].set(-0.5f, 0.5f, 0.5f, 0.5f, 0.625f); // top right
	pVerts[14].set(0.5f, -0.5f, 0.5f, 0.75f, 0.375f); // bottom left
	pVerts[15].set(-0.5f, -0.5f, 0.5f, 0.75f, 0.625f); // bottom right
	//tris
	pTriList[6].set(13, 14, 12);
	pTriList[7].set(13, 15, 14);

	// top face
	//verts
	pVerts[16].set(0.5f, 0.5f, 0.5f, 0.5f, 0.375f); // top left
	pVerts[17].set(-0.5f, 0.5f, 0.5f, 0.5f, 0.625f); // top right
	pVerts[18].set(0.5f, 0.5f, -0.5f, 0.25f, 0.375f); // bottom left
	pVerts[19].set(-0.5f, 0.5f, -0.5f, 0.25f, 0.625f); // bottom right
	//tris
	pTriList[8].set(17, 16, 18);
	pTriList[9].set(17, 18, 19);

	// bottom face
	//verts
	pVerts[20].set(0.5f, -0.5f, -0.5f, 1.0f, 0.375f); // top left
	pVerts[21].set(-0.5f, -0.5f, -0.5f, 1.0f, 0.625f); // top right
	pVerts[22].set(0.5f, -0.5f, 0.5f, 0.75f, 0.375f); // bottom left
	pVerts[23].set(-0.5f, -0.5f, 0.5f, 0.75f, 0.625f); // bottom right
	//tris
	pTriList[10].set(21, 20, 22);
	pTriList[11].set(21, 22, 23);

}