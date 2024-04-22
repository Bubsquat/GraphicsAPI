#include "TerrainModel.h"
#include "Model.h"
#include "d3dUtil.h"
#include "DirectXTex.h"
#include <assert.h>


TerrainModel::TerrainModel(ID3D11Device* dev, LPCWSTR heightmapFile, float len, float maxheight, float ytrans, int RepeatU, int RepeatV)
{
	DirectX::ScratchImage scrtTex;
	HRESULT hr = LoadFromTGAFile(heightmapFile, nullptr, scrtTex);
	assert(SUCCEEDED(hr));

	hgtmap = scrtTex.GetImage(0, 0, 0);
	assert(hgtmap->height == hgtmap->width);

	int pixWidth = hgtmap->width;
	int pixHeight = hgtmap->height;

	int nverts = pixHeight * pixWidth; // one vert for each pizel in the image (functionally n^2 because images are square)
	StandardVertex* pVerts = new StandardVertex[nverts];

	int ntri = 2 * (pixWidth - 1) * (pixHeight - 1); // 2* (n - 1)^2 
	TriangleByIndex* pTriList = new TriangleByIndex[ntri];

	int curVert = 0;
	float offset = len / pixWidth;

	float slope = maxheight / 255.0f;
	float step = (1.0f / pixWidth); // this only works with squares 

	// set all the verteces 
	for (int z = 0; z < pixHeight; z++)
	{

		for (int x = 0; x < pixWidth; x++)
		{

			float height = slope * texelIndex(x, z);

			float u = x * step + (step / 2.0f);
			float v = z * step + (step / 2.0f);

			pVerts[curVert].set((float)(x * -offset) + len/2.0f, height + ytrans, (float)(z * -offset) + len/2.0f, u,v); // doing nothing with y for now 
			curVert++;

		}

	}

	// set the indicies 

	int triNum = 0;

	for (int z = 0; z < pixHeight - 1; z++)
	{
		for (int x = 0; x < pixWidth - 1; x++)
		{

			pTriList[triNum].set(x + (pixWidth * z), x + (pixWidth * (z + 1)), x + (pixWidth * z) + 1);
			triNum++;
			pTriList[triNum].set(x + (pixWidth * (z + 1)), x + (pixWidth * (z + 1)) + 1, x + (pixWidth * z) + 1);
			triNum++;
		}

	}



	// -------

	pModTerrain = new Model(dev, pVerts, nverts, pTriList, ntri);

	delete[] pVerts;
	delete[] pTriList;
}

TerrainModel::~TerrainModel()
{
	delete pModTerrain;
}

uint8_t TerrainModel::texelIndex(int _x, int _y)
{
	return hgtmap->pixels[pixel_width * (_y * hgtmap->height + _x)];
}

void TerrainModel::Render(ID3D11DeviceContext* context)
{
	pModTerrain->SetToContext(context);
	pModTerrain->Render(context);
}