#include "DXApp.h"
#include <windows.h>
#include <sstream>
#include <assert.h>
#include "d3dUtil.h"

// needed to load shaders from file
#include <d3dcompiler.h>

#include "Model.h"
#include "ShaderColor.h"
#include "ShaderTexture.h"
#include "ShaderTextureLightFog.h"
#include "DirectXTex.h"
#include "Texture.h"
#include "FlatPlane.h"
#include "TerrainModel.h"
#include "GraphicObject_ColorLightFog.h"
#include "GraphicObject_TextureLightFog.h"
#include "GraphicObject_Skybox.h"
#include "GraphicObject_Terrain.h"
#include "GraphicObject_Color.h"
#include "SkyBox.h"

void DXApp::InitDemo()
{
	//HRESULT hr = S_OK;

	// demo scene <-------------------------------------------------------

	World = Matrix(SCALE, 1, 1, 1);

	// set up skybox and texture shader 
	//skyboxTex = new Texture(md3dDevice, L"../Assets/Textures/skyboxTexture.tga", D3D11_FILTER_MIN_MAG_MIP_POINT);
	skyboxTex = new Texture(md3dDevice, L"../Assets/Textures/nightSkySkybox.tga", D3D11_FILTER_MIN_MAG_MIP_POINT);
	skyboxTex->SetToContext(md3dImmediateContext);

	pTextureShader = new ShaderTexture(md3dDevice);
	pTextureShader->SetToContext(md3dImmediateContext);
	pTextureShader->SetTextureResourceAndSampler(skyboxTex);
	pTextureShader->SendWorld(World);

	skybox = new SkyBox(md3dDevice, 5000.0f);

	pGO_Skybox = new GraphicObject_Skybox(pTextureShader, skybox);
	pGO_Skybox->SetWorld(World);
	pGO_Skybox->SetTexture(skyboxTex);

	// set up terrain 

	dirtTex = new Texture(md3dDevice, L"../Assets/Textures/seamlessDirt2.tga", D3D11_FILTER_MIN_MAG_MIP_POINT);
	dirtTex->SetToContext(md3dImmediateContext);

	pShaderTexLightFog = new ShaderTextureLightFog(md3dDevice);
	pShaderTexLightFog->SetToContext(md3dImmediateContext);
	pShaderTexLightFog->SetTextureResourceAndSampler(dirtTex);
	pShaderTexLightFog->SendWorldAndMaterial(World, .9 * Colors::White, .03 * Colors::White, Vect(1, 1, 1, 100));
	pShaderTexLightFog->SetFogParameters(300, 1200, fogColor);
	pShaderTexLightFog->SendFogParameters();

	// set up some lights 
	pShaderTexLightFog->SetDirectionalLightParameters(Vect(-2,-2,-1).getNorm(), .1 *Vect(1,1,1), .5 *Vect(1,1,1), Vect(1,1,1)); // matches the moon pos 
	
	terrain = new TerrainModel(md3dDevice, L"../Assets/Textures/graveyardHM.tga", 1000, 40, -25.0f, 1, 1);
	
	pGO_Terrain = new GraphicObject_Terrain(pShaderTexLightFog, terrain);
	pGO_Terrain->SetWorld(World);
	pGO_Terrain->SetTexture(dirtTex);
	pGO_Terrain->SetMaterialProperties(.5 * Colors::Gray, 2 * Colors::Gray, .1 * Vect(1, 1, 1, 100));

	// scene objects 

	// Mausoleum

	mausoleumTex = new Texture(md3dDevice, L"../Assets/Textures/Mausoleum_AlbedoTransparency.tga");

	mausoleum = new Model(md3dDevice, "../Assets/Models/Mausoleum.azul");

	pGO_Mausoleum = new GraphicObject_TextureLightFog(pShaderTexLightFog, mausoleum);
	pGO_Mausoleum->SetMaterialProperties(.9 * Colors::Gray, Colors::Gray, .1 * Vect(1, 1, 1, 100));
	pGO_Mausoleum->SetTexture(mausoleumTex);
	pGO_Mausoleum->SetWorld(mausoleumWorld);

	// tree

	barkTex = new Texture(md3dDevice, L"../Assets/Textures/Main_Bark_Color.tga");
	deadTree = new Model(md3dDevice, "../Assets/Models/dead_tree.azul");

	pGO_Tree = new GraphicObject_TextureLightFog(pShaderTexLightFog, deadTree);
	pGO_Tree->SetMaterialProperties( .02 * Colors::LightGray, .03 * Colors::LightGray, .08 * Vect(1, 1, 1, 50));
	pGO_Tree->SetTexture(barkTex); // hope this works 
	pGO_Tree->SetWorld(TreePos);

	// Tombstones

	graveStoneTex = new Texture(md3dDevice, L"../Assets/Textures/GraveStones_Albedo.tga");

	tombStone1 = new Model(md3dDevice, "../Assets/Models/GraveStone1.azul");

	pGO_Tombstone1 = new GraphicObject_TextureLightFog(pShaderTexLightFog, tombStone1);
	pGO_Tombstone1->SetMaterialProperties(.9 * Colors::Gray,  Colors::Gray, .1 * Vect(1, 1, 1, 100));
	pGO_Tombstone1->SetTexture(graveStoneTex);
	pGO_Tombstone1->SetWorld(GS1Pos);

	tombStone2 = new Model(md3dDevice, "../Assets/Models/GraveStone2.azul");

	pGO_Tombstone2 = new GraphicObject_TextureLightFog(pShaderTexLightFog, tombStone2);
	pGO_Tombstone2->SetMaterialProperties(.9 * Colors::Gray, Colors::Gray, .1 * Vect(1, 1, 1, 100));
	pGO_Tombstone2->SetTexture(graveStoneTex);
	pGO_Tombstone2->SetWorld(GS2Pos);

	tombStone3 = new Model(md3dDevice, "../Assets/Models/GraveStone3.azul");

	pGO_Tombstone3 = new GraphicObject_TextureLightFog(pShaderTexLightFog, tombStone3);
	pGO_Tombstone3->SetMaterialProperties(.9 * Colors::Gray,  Colors::Gray, .1 * Vect(1, 1, 1, 100));
	pGO_Tombstone3->SetTexture(graveStoneTex);
	pGO_Tombstone3->SetWorld(GS3Pos);

	tombStone4 = new Model(md3dDevice, "../Assets/Models/GraveStone4.azul");

	pGO_Tombstone4 = new GraphicObject_TextureLightFog(pShaderTexLightFog, tombStone4);
	pGO_Tombstone4->SetMaterialProperties(.9 * Colors::Gray,  Colors::Gray, .1 * Vect(1, 1, 1, 100));
	pGO_Tombstone4->SetTexture(graveStoneTex);
	pGO_Tombstone4->SetWorld(GS4Pos);

	// generated models for demo 

	pyWorld = Matrix(SCALE, 5, 5, 5) * Matrix(TRANS, 150, 50, 400);
	cubeWorld = Matrix(SCALE, 5, 5, 5) * Matrix(TRANS, 170, 50, 400);

	pyTex = new Texture(md3dDevice, L"../Assets/Textures/AlignmentTest.tga");
	cubeTex = new Texture(md3dDevice, L"../Assets/Textures/CubeFaces.tga");
	pyramid = new Model(md3dDevice, Model::PreMadeModels::UnitPyramid);
	sixFace = new Model(md3dDevice, Model::PreMadeModels::UnitBoxSixFacesTexture);

	testGO = new GraphicObject_TextureLightFog(pShaderTexLightFog, pyramid);
	testGO->SetMaterialProperties( .2 * Colors::Gray, Colors::Gray, .1 * Vect(1, 1, 1, 100));
	testGO->SetTexture(pyTex);
	testGO->SetWorld(pyWorld);

	// lantern + color shader

	pShaderColor = new ShaderColor(md3dDevice);

	lantern = new Model(md3dDevice, "../Assets/Models/newerLantern.azul");
	
	pGO_Lantern = new GraphicObject_Color(pShaderColor, lantern);
	pGO_Lantern->SetWorld(LanternScale* initialLanternRT);
	pGO_Lantern->SetColor(Colors::LightGreen);
	pGO_Lantern->SetColor(Colors::LightYellow, 1);

	// lantern motion stuff

	lantPosOffset = Vect(0, 35, 0);
	Rot = Matrix(ROT_X, 0.0f);

	// Initialize the projection matrix
	mCam.setPerspective( 3.14159/3, mClientWidth / (float)mClientHeight, 1.0f, 8000.0f);
	mCam.setOrientAndPosition(Vect(0, 1, 0), Vect(-0.5818,-0.2764,-0.76871), Vect(-273.7, 24.958, -191.548) );

	mTimer.Reset();
}

void DXApp::UpdateScene()
{
	// lantern 1
	Rot = Matrix(ROT_X, rotAmount);
	rotAmount = 0.01f* cosf(mTimer.TotalTime());
	lantPosOffset = lantPosOffset * Rot;

	// lantern 2

	transAmt = cosf(mTimer.TotalTime() * 0.5f);
	curve = cosf(mTimer.TotalTime() * 1.2f);

	lant2Pos = Matrix(TRANS, (lantMul * transAmt) + (10 * curve), 11, (lantMul * transAmt) + (-10 * curve))* lant2Offset;

	float camSpeed = 1.0f;
	if (GetKeyState('W') & 0x08000)
	{
		mCam.TranslateFwdBack(camSpeed);
	}
	else if (GetKeyState('S') & 0x08000)
	{
		mCam.TranslateFwdBack(-camSpeed);
	}

	if (GetKeyState('A') & 0x08000)
	{
		mCam.TranslateLeftRight(-camSpeed);
	}
	else if (GetKeyState('D') & 0x08000)
	{
		mCam.TranslateLeftRight(camSpeed);
	}

	float rotSpeed = 0.05f;
	if (GetKeyState(VK_LEFT) & 0x08000)
	{
		mCam.TurnLeftRight(rotSpeed);
	}
	else if (GetKeyState(VK_RIGHT) & 0x08000)
	{
		mCam.TurnLeftRight(-rotSpeed);
	}

	if (GetKeyState(VK_UP) & 0x08000)
	{
		mCam.TiltUpDown(rotSpeed);
	}
	else if (GetKeyState(VK_DOWN) & 0x08000)
	{
		mCam.TiltUpDown(-rotSpeed);
	}

	mCam.updateCamera();
}

void DXApp::DrawScene()
{
	// Clear the back buffer
	md3dImmediateContext->ClearRenderTargetView(mRenderTargetView, VasA(BackgroundColor));
	// Clear the depth stencil;
	md3dImmediateContext->ClearDepthStencilView(mpDepthStencilView, D3D11_CLEAR_DEPTH, 1.0f, 0);

	// demo scene <-------------------------------------------------------------------------------------

	Vect eyepos;
	mCam.getPos(eyepos);

	pTextureShader->SetTextureResourceAndSampler(skyboxTex);
	pTextureShader->SetToContext(md3dImmediateContext);
	pTextureShader->SendCamMatrices(mCam.getViewMatrix(), mCam.getProjMatrix());
	pGO_Skybox->Render();

	Matrix pos = Matrix(TRANS, lantPosOffset) * Matrix(TRANS, initialLanternRT.get(MatrixRowType::ROW_3));
	Matrix pos2 = Matrix(TRANS, lantPosOffset) * Matrix(TRANS, initialLanternRT2.get(MatrixRowType::ROW_3));
	
	pShaderTexLightFog->SetPointLightParameters(1, pos.get(MatrixRowType::ROW_3), 150.0f, .2 * Vect(0, 1, 0), .2 * Vect(1, 1, 1), 2 * Vect(1, 1, 1), 1 * Vect(1, 1, 1));
	pShaderTexLightFog->SetPointLightParameters(2, pos2.get(MatrixRowType::ROW_3), 150.0f, .2 * Vect(0, 1, 0), .2 * Vect(1, 1, 1), 2 * Vect(1, 1, 1), 1 * Vect(1, 1, 1));
	pShaderTexLightFog->SetPointLightParameters(3, lant2Pos.get(MatrixRowType::ROW_3), 150.0f, .2 * Vect(0, 1, 0), .2 * Vect(1, 1, 1), 2 * Vect(1, 1, 1), 1 * Vect(1, 1, 1));

	pShaderTexLightFog->SetToContext(md3dImmediateContext);
	pShaderTexLightFog->SendCamMatrices(mCam.getViewMatrix(), mCam.getProjMatrix());
	pShaderTexLightFog->SendFogParameters();
	pShaderTexLightFog->SendLightParameters(eyepos);
	pShaderTexLightFog->SendWorldAndMaterial(World);


	//pTextureShader->SetTextureResourceAndSampler(dirtTex);
	pShaderTexLightFog->SetTextureResourceAndSampler(dirtTex);
	
	pGO_Terrain->Render();


	// tombstones
	pShaderTexLightFog->SetTextureResourceAndSampler(graveStoneTex);

	for (int i = 0; i < numGS1Pos; i++)
	{
		pGO_Tombstone1->SetWorld(GS1Positions[i]);
		pGO_Tombstone1->Render();
	}
	for (int i = 0; i < numGS2Pos; i++)
	{
		pGO_Tombstone2->SetWorld(GS2Positions[i]);
		pGO_Tombstone2->Render();
	}
	for (int i = 0; i < numGS3Pos; i++)
	{
		pGO_Tombstone3->SetWorld(GS3Positions[i]);
		pGO_Tombstone3->Render();
	}
	for (int i = 0; i < numGS4Pos; i++)
	{
		pGO_Tombstone4->SetWorld(GS4Positions[i]);
		pGO_Tombstone4->Render();
	}


	pShaderTexLightFog->SetTextureResourceAndSampler(mausoleumTex);

	pGO_Mausoleum->Render();

	pShaderTexLightFog->SetTextureResourceAndSampler(barkTex);

	pGO_Tree->SetWorld(TreePos);
	pGO_Tree->Render();
	pGO_Tree->SetWorld(TreePos2);
	pGO_Tree->Render();
	pGO_Tree->SetWorld(TreePos3);
	pGO_Tree->Render();
	
	// premade demo models
	testGO->SetTexture(pyTex);
	testGO->SetModel(pyramid);
	testGO->SetWorld(pyWorld);
	testGO->Render();
	testGO->SetModel(sixFace);
	testGO->SetTexture(cubeTex);
	testGO->SetWorld(cubeWorld);
	testGO->Render();

	// switch to color shader 

	pShaderColor->SetToContext(md3dImmediateContext);
	pShaderColor->SendCamMatrices(mCam.getViewMatrix(), mCam.getProjMatrix());

	float rotAmt = 0.3f * sinf(mTimer.TotalTime());

	pGO_Lantern->SetWorld(LanternScale * Matrix(ROT_X, rotAmt) * pos);
	pGO_Lantern->Render();

	pGO_Lantern->SetWorld(LanternScale * Matrix(ROT_X, rotAmount * 60) * lant2Pos);
	pGO_Lantern->Render();

	pGO_Lantern->SetWorld(LanternScale * Matrix(ROT_X, -rotAmt) * pos2);
	pGO_Lantern->Render();

	mSwapChain->Present(SyncInterval, 0);
}


DXApp::DXApp(HWND hwnd)
{
	assert(hwnd);
	mhMainWnd = hwnd;

	BackgroundColor = Colors::MidnightBlue;
	//BackgroundColor = Colors::Beige;

	md3dDevice = nullptr;
	md3dImmediateContext = nullptr;
	mSwapChain = nullptr;
	mRenderTargetView = nullptr;

	// Get window data through the window handle
	RECT rc;
	BOOL err = GetClientRect(mhMainWnd, &rc);  // Seriously MS: Redifining BOOL as int? Confusing much?
	assert(err);

	// get width/hight
	mClientWidth = rc.right - rc.left;
	mClientHeight = rc.bottom - rc.top;

	// Get window caption
	const int MAX_LABEL_LENGTH = 100; // probably overkill...
	CHAR str[MAX_LABEL_LENGTH];
	GetWindowText(mhMainWnd, str, MAX_LABEL_LENGTH);
	mMainWndCaption = str;

	// Initialize DX11
	this->InitDirect3D();

	// Demo initialization
	this->InitDemo();
}

DXApp::~DXApp()
{

	delete skyboxTex;
	delete pGO_Skybox;
	delete pGO_Terrain;
	delete skybox;
	delete terrain;
	delete dirtTex;
	delete mausoleum;
	delete mausoleumTex;
	delete tombStone1;
	delete tombStone2;
	delete tombStone3;
	delete tombStone4;
	delete graveStoneTex;
	delete pTextureShader;
	delete pGO_Mausoleum;
	delete pGO_Tombstone1;
	delete pGO_Tombstone2;
	delete pGO_Tombstone3;
	delete pGO_Tombstone4;
	delete pGO_Lantern;
	delete pGO_Tree;
	delete barkTex;
	delete deadTree;
	delete lantern;

	delete pShaderColor;
	delete pShaderTexLightFog;

	delete pyTex;
	delete cubeTex;
	delete pyramid;
	delete sixFace;
	delete testGO;

	ReleaseAndDeleteCOMobject(mRenderTargetView);
	ReleaseAndDeleteCOMobject(mpDepthStencilView);
	ReleaseAndDeleteCOMobject(mSwapChain);
	ReleaseAndDeleteCOMobject(md3dImmediateContext);

	// Must be done BEFORE the device is released
	ReportLiveDXObjects();		// See http://masterkenth.com/directx-leak-debugging/

	ReleaseAndDeleteCOMobject(md3dDevice);
}

// See http://masterkenth.com/directx-leak-debugging/
void DXApp::ReportLiveDXObjects()
{
#ifdef _DEBUG
	HRESULT hr = S_OK;

	// Now we set up the Debug interface, to be queried on shutdown
	ID3D11Debug* debugDev;
	hr = md3dDevice->QueryInterface(__uuidof(ID3D11Debug), reinterpret_cast<void**>(&debugDev));

	debugDev->ReportLiveDeviceObjects(D3D11_RLDO_DETAIL);
	ReleaseAndDeleteCOMobject(debugDev);
#endif
}

void DXApp::InitDirect3D()
{
	HRESULT hr = S_OK;

	UINT createDeviceFlags = 0;
#ifdef _DEBUG
	createDeviceFlags |= D3D11_CREATE_DEVICE_DEBUG;
#endif

	// This is a *greatly* simplified process to create a DX device and context:
	// We force the use of DX11 feature level since that's what CDM labs are limited to.
	// For real-life applications would need to test what's the best feature level and act accordingly
	hr = D3D11CreateDevice(nullptr, D3D_DRIVER_TYPE_HARDWARE, nullptr, createDeviceFlags, nullptr, 0, D3D11_SDK_VERSION, &md3dDevice, nullptr, &md3dImmediateContext);
	assert(SUCCEEDED(hr));

	// Now we obtain the associated DXGIfactory1 with our device 
	// Many steps...
	IDXGIDevice* dxgiDevice = nullptr;
	hr = md3dDevice->QueryInterface(__uuidof(IDXGIDevice), reinterpret_cast<void**>(&dxgiDevice));
	assert(SUCCEEDED(hr));

	IDXGIAdapter* adapter = nullptr;
	hr = dxgiDevice->GetAdapter(&adapter);
	assert(SUCCEEDED(hr));

	IDXGIFactory1* dxgiFactory1 = nullptr;
	hr = adapter->GetParent(__uuidof(IDXGIFactory1), reinterpret_cast<void**>(&dxgiFactory1));
	assert(SUCCEEDED(hr));
	// See also note on weird stuff with factories and swap chains (1s and 2s)
	// https://msdn.microsoft.com/en-us/library/windows/desktop/jj863687(v=vs.85).aspx

	// We are done with these now...
	ReleaseAndDeleteCOMobject(adapter);
	ReleaseAndDeleteCOMobject(dxgiDevice);

	// Controls MSAA option:
	// - 4x count level garanteed for all DX11 
	// - MUST be the same for depth buffer!
	// - We _need_ to work with the depth buffer because reasons... (see below)
	DXGI_SAMPLE_DESC sampDesc;
	sampDesc.Count = 1;
	sampDesc.Quality = static_cast<UINT>(D3D11_CENTER_MULTISAMPLE_PATTERN);  // MS: what's with the type mismtach?

	DXGI_MODE_DESC buffdesc;				// https://msdn.microsoft.com/en-us/library/windows/desktop/bb173064(v=vs.85).aspx
	ZeroMemory(&buffdesc, sizeof(buffdesc));
	buffdesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;

	// Next we create a swap chain. 
	// Useful thread: http://stackoverflow.com/questions/27270504/directx-creating-the-swapchain
	// Note that this is for a DirectX 11.0: in a real app, we should test the feature levels and act accordingly

	DXGI_SWAP_CHAIN_DESC sd;				// See MSDN: https://msdn.microsoft.com/en-us/library/windows/desktop/bb173075(v=vs.85).aspx
	ZeroMemory(&sd, sizeof(sd));
	sd.BufferCount = 2;						// Much confusion about this number... see http://www.gamedev.net/topic/633807-swap-chain-buffer-count/
	sd.BufferDesc = buffdesc;
	sd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
	sd.OutputWindow = mhMainWnd;
	sd.SampleDesc = sampDesc;
	sd.Windowed = TRUE;

	hr = dxgiFactory1->CreateSwapChain(md3dDevice, &sd, &mSwapChain);
	assert(SUCCEEDED(hr));
	ReleaseAndDeleteCOMobject(dxgiFactory1);

	// Create a render target view		https://msdn.microsoft.com/en-us/library/windows/desktop/ff476582(v=vs.85).aspx
	ID3D11Texture2D* pBackBuffer = nullptr;
	hr = mSwapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), reinterpret_cast<void**>(&pBackBuffer));
	assert(SUCCEEDED(hr));;

	hr = md3dDevice->CreateRenderTargetView(pBackBuffer, nullptr, &mRenderTargetView);
	ReleaseAndDeleteCOMobject(pBackBuffer);
	assert(SUCCEEDED(hr));

	/**********************************************************/

	// First we fix what it means for triangles to be front facing.
	// Requires setting a whole new rasterizer state
	//*
	D3D11_RASTERIZER_DESC rd;
	rd.FillMode = D3D11_FILL_SOLID;  // Also: D3D11_FILL_WIREFRAME
	rd.CullMode = D3D11_CULL_BACK;
	rd.FrontCounterClockwise = true; // true for RH forward facing
	rd.DepthBias = 0;
	rd.SlopeScaledDepthBias = 0.0f;
	rd.DepthBiasClamp = 0.0f;
	rd.DepthClipEnable = true;
	rd.ScissorEnable = false;
	rd.MultisampleEnable = true;  // Does not in fact turn on/off multisample: https://msdn.microsoft.com/en-us/library/windows/desktop/ff476198(v=vs.85).aspx
	rd.AntialiasedLineEnable = false;

	ID3D11RasterizerState* rs;
	md3dDevice->CreateRasterizerState(&rd, &rs);

	md3dImmediateContext->RSSetState(rs);
	ReleaseAndDeleteCOMobject(rs); // we can release this resource since we won't be changing it any further
	//*/

	// We must turn on the abilty to process depth during rendering.
	// Done through depth stencils (see https://msdn.microsoft.com/en-us/library/windows/desktop/bb205074(v=vs.85).aspx)
	// Below is a simplified version
	//*
	D3D11_TEXTURE2D_DESC descDepth;
	descDepth.Width = mClientWidth;
	descDepth.Height = mClientHeight;
	descDepth.MipLevels = 1;
	descDepth.ArraySize = 1;
	descDepth.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;
	descDepth.SampleDesc = sampDesc;
	descDepth.Usage = D3D11_USAGE_DEFAULT;
	descDepth.BindFlags = D3D11_BIND_DEPTH_STENCIL;
	descDepth.CPUAccessFlags = 0;
	descDepth.MiscFlags = 0;

	ID3D11Texture2D* pDepthStencil;
	hr = md3dDevice->CreateTexture2D(&descDepth, NULL, &pDepthStencil);
	assert(SUCCEEDED(hr));

	// Create the depth stencil view
	D3D11_DEPTH_STENCIL_VIEW_DESC descDSV;
	ZeroMemory(&descDSV, sizeof(descDSV));
	descDSV.Format = descDepth.Format;
	descDSV.ViewDimension = D3D11_DSV_DIMENSION_TEXTURE2DMS;
	descDSV.Texture2D.MipSlice = 0;;

	hr = md3dDevice->CreateDepthStencilView(pDepthStencil, &descDSV, &mpDepthStencilView);
	assert(SUCCEEDED(hr));
	ReleaseAndDeleteCOMobject(pDepthStencil);
	//*/

	/**********************************************************/

	//md3dImmediateContext->OMSetRenderTargets(1, &mRenderTargetView, nullptr);  // to use without depth stencil
	md3dImmediateContext->OMSetRenderTargets(1, &mRenderTargetView, mpDepthStencilView);

	// Setup the viewport
	D3D11_VIEWPORT vp;
	vp.Width = (FLOAT)mClientWidth;
	vp.Height = (FLOAT)mClientHeight;
	vp.MinDepth = 0.0f;
	vp.MaxDepth = 1.0f;
	vp.TopLeftX = 0;
	vp.TopLeftY = 0;
	md3dImmediateContext->RSSetViewports(1, &vp);
}

void DXApp::CalculateFrameStats()
{
	// Code computes the average frames per second, and also the 
	// average time it takes to render one frame.  These stats 
	// are appended to the window caption bar.

	static int frameCnt = 0;
	static float timeElapsed = 0.0f;

	frameCnt++;

	// Compute averages over one second period.
	if ((mTimer.TotalTime() - timeElapsed) >= 1.0f)
	{
		float fps = (float)frameCnt; // fps = frameCnt / 1
		float mspf = 1000.0f / fps;

		std::ostringstream outs;
		outs.precision(6);
		outs << mMainWndCaption << "    "
			<< "FPS: " << fps << "    "
			<< "Frame Time: " << mspf << " (ms)";
		SetWindowText(mhMainWnd, outs.str().c_str());

		// Reset for next average.
		frameCnt = 0;
		timeElapsed += 1.0f;
	}
}

void DXApp::FrameTick()
{
	mTimer.Tick();
	CalculateFrameStats();

	this->UpdateScene();
	this->DrawScene();
}

void DXApp::OnMouseDown(WPARAM btnState, int xval, int yval)
{
	UNREFERENCED_PARAMETER(btnState);
	UNREFERENCED_PARAMETER(xval);
	UNREFERENCED_PARAMETER(yval);
}

void DXApp::OnMouseUp(WPARAM btnState, int xval, int yval)
{
	UNREFERENCED_PARAMETER(btnState);
	UNREFERENCED_PARAMETER(xval);
	UNREFERENCED_PARAMETER(yval);
}

void DXApp::OnMouseMove(WPARAM btnState, int xval, int yval)
{
	UNREFERENCED_PARAMETER(btnState);
	UNREFERENCED_PARAMETER(xval);
	UNREFERENCED_PARAMETER(yval);
}

void  DXApp::OnMouseWheel(short delta)
{
	UNREFERENCED_PARAMETER(delta);
}


// Shader loading utility. Will be moved elsewhere later...
// Needs to be moved. Requires
HRESULT DXApp::CompileShaderFromFile(WCHAR* szFileName, LPCSTR szEntryPoint, LPCSTR szShaderModel, ID3DBlob** ppBlobOut)
{
	HRESULT hr = S_OK;

	DWORD dwShaderFlags = D3DCOMPILE_ENABLE_STRICTNESS;
#ifdef _DEBUG
	// Set the D3DCOMPILE_DEBUG flag to embed debug information in the shaders.
	// Setting this flag improves the shader debugging experience, but still allows 
	// the shaders to be optimized and to run exactly the way they will run in 
	// the release configuration of this program.
	dwShaderFlags |= D3DCOMPILE_DEBUG;

	// Disable optimizations to further improve shader debugging
	dwShaderFlags |= D3DCOMPILE_SKIP_OPTIMIZATION;
#endif

	ID3DBlob* pErrorBlob = nullptr;
	hr = D3DCompileFromFile(szFileName, nullptr, nullptr, szEntryPoint, szShaderModel, dwShaderFlags, 0, ppBlobOut, &pErrorBlob);
	if (FAILED(hr))
	{
		if (pErrorBlob)
		{
			OutputDebugStringA(reinterpret_cast<const char*>(pErrorBlob->GetBufferPointer()));
			pErrorBlob->Release();
		}
		return hr;
	}
	if (pErrorBlob) pErrorBlob->Release();

	return S_OK;
}