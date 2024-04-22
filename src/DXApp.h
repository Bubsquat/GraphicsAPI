// DXApp
// Andre Berthiaume, June 2016
// Note: DX 11 SDK https://www.microsoft.com/en-us/download/details.aspx?id=6812
// Note on weird stuff with swap chain (1s and 2s) https://msdn.microsoft.com/en-us/library/windows/desktop/jj863687(v=vs.85).aspx

#ifndef _DXApp
#define _DXApp

#include <d3d11.h>
#include "d3dUtil.h"
#include "Align16.h"
#include "GameTimer.h"
#include <string>

// New includes for demo
#include "Vect.h"
#include "Matrix.h"
#include "Camera.h"
#include "ShaderColor.h"
#include "ShaderColorLight.h"
#include "ShaderColorLightFog.h"
#include "ShaderTextureLightFog.h"


class SkyBox;
class GraphicObject_Skybox;
class GraphicObject_Terrain;
class GraphicObject_TextureLightFog;
class GraphicObject_Color;
class ShaderTexture;
class TerrainModel;
class Model;

class DXApp : public Align16
{
private:	
	// Main window handle
	HWND      mhMainWnd;

	Vect BackgroundColor;
	int SyncInterval = 1;  // 1 for sync to refresh rate, 0 for no sync

	// DX application elements
	ID3D11Device* md3dDevice;					// Connects to the graphics card
	ID3D11DeviceContext* md3dImmediateContext;	// Settings for the GPU to use
	IDXGISwapChain* mSwapChain;					// image buffers used for rendering
	ID3D11RenderTargetView* mRenderTargetView;	// Where to send rendring operations (typically: points to one of the swap buffers)
	ID3D11DepthStencilView* mpDepthStencilView; // Needed to force depth-buffer operations

	GameTimer mTimer;
	std::string mMainWndCaption;
	int mClientWidth;
	int mClientHeight;

	void InitDirect3D();
	void InitDemo();
	void UpdateScene();
	void DrawScene();
	void CalculateFrameStats();

	// Shader loading utility. SHould be moved elsewhere later...
	HRESULT CompileShaderFromFile(WCHAR* szFileName, LPCSTR szEntryPoint, LPCSTR szShaderModel, ID3DBlob** ppBlobOut);

	// Debug utility
	void ReportLiveDXObjects();

	// Demo specific additions

	//const Vect fogColor{ 0.0f, 0.07f, 0.15f };
	const Vect fogColor{ 0.0f, 0.0f, 0.03f }; // <-------- use this one 


	Matrix World;

	Camera mCam;
	SkyBox* skybox;
	TerrainModel* terrain;
	Model* tombStone1;
	Model* tombStone2;
	Model* tombStone3;
	Model* tombStone4;
	Model* mausoleum;
	Model* deadTree;
	Model* lantern;

	Texture* pyTex;
	Texture* cubeTex;
	Matrix pyWorld;
	Matrix cubeWorld;
	Model* pyramid;
	Model* sixFace;
	GraphicObject_TextureLightFog* testGO;

	GraphicObject_Skybox* pGO_Skybox;
	GraphicObject_Terrain* pGO_Terrain;
	GraphicObject_TextureLightFog* pGO_Tombstone1;
	GraphicObject_TextureLightFog* pGO_Tombstone2;
	GraphicObject_TextureLightFog* pGO_Tombstone3;
	GraphicObject_TextureLightFog* pGO_Tombstone4;
	GraphicObject_TextureLightFog* pGO_Mausoleum;
	GraphicObject_TextureLightFog* pGO_Tree;
	GraphicObject_Color* pGO_Lantern;

	Texture* skyboxTex;
	Texture* dirtTex;
	Texture* graveStoneTex;
	Texture* mausoleumTex;
	Texture* barkTex;

	ShaderTexture* pTextureShader;
	ShaderColor* pShaderColor;
	ShaderTextureLightFog* pShaderTexLightFog;

	// Positioning 

	const Matrix mausoleumWorld = Matrix(SCALE, .4, .4, .4) * Matrix(ROT_Y, MATH_PI + (MATH_PI/6)) * Matrix(TRANS, 165, 0, 250);

	const Matrix GraveStoneScale = Matrix(SCALE, .35, .35, .35);

	const Matrix TreePos = Matrix(SCALE, 40, 40, 40) * Matrix(ROT_X, -MATH_PI/2) * Matrix(ROT_Y, MATH_PI /3) * Matrix(TRANS, -18, 10, 200);
	const Matrix TreePos2 = Matrix(SCALE, 40, 40, 40) * Matrix(ROT_X, -MATH_PI / 2) * Matrix(ROT_Y, MATH_PI / -2) * Matrix(TRANS, 98, -27, -120);
	const Matrix TreePos3 = Matrix(SCALE, 40, 40, 40) * Matrix(ROT_X, -MATH_PI / 2) * Matrix(ROT_Y, MATH_PI / 6) * Matrix(TRANS, -253, -21, -203);

	const Matrix LanternScale = Matrix(SCALE, .025, .025, .025);

	const Matrix initialLanternRT = Matrix(ROT_Y, .04) * Matrix(TRANS, 15, 77, 192);
	const Matrix initialLanternRT2 = Matrix(ROT_Y, .04) * Matrix(TRANS, -283, 60, -44);
	Vect lantAncorToPos;
	Vect lantPosOffset;
	float rotAmount;
	Matrix Rot;

	Matrix lant2Pos;
	const Matrix lant2Offset = Matrix(TRANS, 59, 0, -100);
	const float lantMul = 100;
	float transAmt;
	float curve;
	
	// gs 1
	const Matrix GS1Pos = GraveStoneScale * Matrix(ROT_Y, MATH_PI - .3) * Matrix(ROT_Z, .2) * Matrix(TRANS, -3, -3, 150);
	const Matrix GS1Pos2 = GraveStoneScale * Matrix(ROT_Y, MATH_PI + .9) * Matrix(TRANS, 160, -7, 20);
	const Matrix GS1Pos3 = GraveStoneScale * Matrix(ROT_Y, MATH_PI ) * Matrix(ROT_Z, .3) * Matrix(TRANS, -290, -20, 290);
	const Matrix GS1Pos4 = GraveStoneScale * Matrix(ROT_Y, MATH_PI) * Matrix(TRANS, -290, -20, 65);
	const Matrix GS1Pos5 = GraveStoneScale * Matrix(ROT_Y, MATH_PI + 1.15) * Matrix(TRANS, 93, -24, -243);
	const Matrix GS1Pos6 = GraveStoneScale * Matrix(ROT_Y, MATH_PI -.4) * Matrix(TRANS, -245, -18, -147);
	const Matrix Gs1Pos7 = GraveStoneScale * Matrix(ROT_Y, MATH_PI) * Matrix(TRANS, -210, -18, -120);

	// gs 2
	const Matrix GS2Pos = GraveStoneScale * Matrix(ROT_Y, MATH_PI - .2) * Matrix(TRANS, -225, -15 , 210);
	const Matrix GS2Pos2 = GraveStoneScale * Matrix(ROT_Y, MATH_PI - .2) * Matrix(ROT_Z, -.02) * Matrix(TRANS, -390, -29, 190);
	const Matrix GS2Pos3 = GraveStoneScale * Matrix(ROT_Y, MATH_PI + .1) * Matrix(TRANS, 240, -7, 0);
	const Matrix GS2Pos4 = GraveStoneScale * Matrix(ROT_Y, MATH_PI) * Matrix(TRANS, 255, -20, -147);
	const Matrix GS2Pos5 = GraveStoneScale * Matrix(ROT_Y, MATH_PI + .3) * Matrix(TRANS, 325, -1, 200);
	const Matrix GS2Pos6 = GraveStoneScale * Matrix(ROT_Y, MATH_PI) * Matrix(TRANS, -300, -18, -133);
	// gs3 
	const Matrix GS3Pos = GraveStoneScale * Matrix(ROT_Y, MATH_PI + .55) * Matrix(ROT_Z, -.04) * Matrix(TRANS, -140, -16, 160);
	const Matrix GS3Pos2 = GraveStoneScale * Matrix(ROT_Y, MATH_PI) * Matrix(ROT_Z, -.04) * Matrix(TRANS, 210, -12, -97);
	const Matrix GS3Pos3 = GraveStoneScale * Matrix(ROT_Y, MATH_PI + .7) * Matrix(ROT_Z, -.04) * Matrix(TRANS, 10, -24, -180);
	const Matrix GS3Pos4 = GraveStoneScale * Matrix(ROT_Y, MATH_PI ) * Matrix(ROT_Z, .3)* Matrix(TRANS, -390, -24, -10);
	const Matrix GS3Pos5 = GraveStoneScale * Matrix(ROT_Y, MATH_PI + .43) * Matrix(TRANS, 373, -4, 74);

	// gs4
	const Matrix GS4Pos = GraveStoneScale * Matrix(ROT_Y, MATH_PI + .4) * Matrix(TRANS, -180, -12, 25);
	const Matrix GS4Pos2 = GraveStoneScale * Matrix(ROT_Y, MATH_PI + -.05) * Matrix(TRANS, 340, -12, -47);
	const Matrix GS4Pos3 = GraveStoneScale * Matrix(ROT_Y, MATH_PI + .09) * Matrix(TRANS, -100, -12, 60);
	const Matrix GS4Pos4 = GraveStoneScale * Matrix(ROT_Y, MATH_PI + .02) * Matrix(TRANS, 321, -12, -217);


	const int numGS1Pos = 7;
	Matrix GS1Positions[7] = {
		GS1Pos,
		GS1Pos2,
		GS1Pos3,
		GS1Pos4,
		GS1Pos5,
		GS1Pos6,
		Gs1Pos7
	};

	const int numGS2Pos = 6;
	Matrix GS2Positions[6] = {
		GS2Pos,
		GS2Pos2,
		GS2Pos3,
		GS2Pos4,
		GS2Pos5,
		GS2Pos6
	};

	const int numGS3Pos = 5;
	Matrix GS3Positions[5] = {
		GS3Pos,
		GS3Pos2,
		GS3Pos3,
		GS3Pos4,
		GS3Pos5
	};

	const int numGS4Pos = 4;
	Matrix GS4Positions[4] = {
		GS4Pos,
		GS4Pos2,
		GS4Pos3,
		GS4Pos4
	};


public:
	DXApp(HWND hwnd);
	virtual ~DXApp();
	
	void FrameTick();

	// overrides for handling mouse input.
	void OnMouseDown(WPARAM btnState, int xval, int yval);
	void OnMouseUp(WPARAM btnState, int xval, int yval);
	void OnMouseMove(WPARAM btnState, int xval, int yval);
	void OnMouseWheel(short delta);


};

#endif _DXApp